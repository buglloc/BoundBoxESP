#include <sdkconfig.h>
#include "commands.h"

#include <vector>
#include <functional>

#include <esp_log.h>

#include <defer.h>
#include <ArduinoJson.h>

#include <hardware/manager.h>
#include <ui/manager.h>
#include <blob/bytes.h>
#include <blob/base64.h>
#include <blob/hash.h>


#define CMD_ERR_CODE_HMAC_SECRET_INVALID_SALT 1001
#define CMD_ERR_CODE_GET_SECRETS_FAILED 1002
#define CMD_ERR_CODE_SET_SECRETS_INVALID_HOST_KEY 1003
#define CMD_ERR_CODE_SET_SECRETS_INVALID_SECRET_KEY 1004

#define STR(X) #X
#define ASSTR(X) STR(X)


namespace
{
  static const char *TAG = "main::cmd";
  Hardware::Manager& hw = Hardware::Manager::Instance();
  UI::Manager& ui = UI::Manager::Instance();

  using HandleFn = std::function<bool(const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)>;

  struct Command
  {
    std::string Name;
    bool UsedAllowed;
    std::string Help;
    HandleFn Handle;
  };

  bool HandleHmacSecret(Authenticator* auth, const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    std::string_view encodedSalt = req["salt"].as<std::string_view>();
    if (encodedSalt.empty()) {
      rsp["error_code"] = CMD_ERR_CODE_HMAC_SECRET_INVALID_SALT;
      rsp["error_msg"] = "no salt provided";
      return false;
    }

    Blob::Bytes salt = Blob::Base64Decode(encodedSalt);
    if (salt.empty()) {
      rsp["error_code"] = CMD_ERR_CODE_HMAC_SECRET_INVALID_SALT;
      rsp["error_msg"] = "empty salt";
      return false;
    }

    if (salt.size() < CONFIG_HMAC_MIN_SALT_LEN) {
      rsp["error_code"] = CMD_ERR_CODE_HMAC_SECRET_INVALID_SALT;
      rsp["error_msg"] = "salt is too short: required at least " ASSTR(CONFIG_HMAC_MIN_SALT_LEN) " bytes";
      return false;
    }

    Blob::Bytes key = Blob::Bytes(userInfo.KeyFingerprint.begin(), userInfo.KeyFingerprint.end());
    std::expected<Blob::Bytes, Blob::Error> bindedSalt = Blob::HMAC::Sum(
      key, salt, Blob::HashType::SHA256
    );
    if (!bindedSalt) {
      rsp["error_code"] = static_cast<uint8_t>(bindedSalt.error());
      rsp["error_msg"] = "bind salst to user key failed";
      return false;
    }

    std::expected<Blob::Bytes, Error> assert = auth->MakeAssertion(
      bindedSalt.value(), userInfo.ClientIP
    );
    if (!assert) {
      rsp["error_code"] = static_cast<uint8_t>(assert.error());
      rsp["error_msg"] = "assertation failed";
      return false;
    }

    rsp["secret"] = Blob::Base64Encode(assert.value());
    return true;
  }

  bool HandleGetStatus(const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    // TODO(buglloc): show something usefull
    return true;
  }

#if CONFIG_DUMPABLE_SECRETS
  bool HandleGetSecrets(Secrets* secrets, const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObject secretsObj = rsp.createNestedObject("secrets");
    Error err = secrets->ToJson(secretsObj);
    if (err != Error::None) {
      rsp["error_code"] = CMD_ERR_CODE_GET_SECRETS_FAILED;
      return false;
    }

    return true;
  }
#endif

  bool HandleSetSecrets(Secrets* secrets, const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObjectConst secretsJson = req["secrets"].as<JsonObjectConst>();
    if (!secretsJson.containsKey("host_key")) {
      rsp["error_code"] = CMD_ERR_CODE_SET_SECRETS_INVALID_HOST_KEY;
      rsp["error_msg"] = "empty host key";
      return false;
    }

    if (!secretsJson.containsKey("secret_key")) {
      rsp["error_code"] = CMD_ERR_CODE_SET_SECRETS_INVALID_SECRET_KEY;
      rsp["error_msg"] = "empty host key";
      return false;
    }

    Error err = secrets->FromJson(secretsJson);
    if (err != Error::None) {
      rsp["error_code"] = static_cast<uint8_t>(err);
      rsp["error_msg"] = "unable to load secrets from json";
      return false;
    }

    err = secrets->Store();
    if (err != Error::None) {
      rsp["error_code"] = static_cast<uint8_t>(err);
      rsp["error_msg"] = "unable to store secrets";
      return false;
    }

    return true;
  }

  bool HandleResetSecrets(Secrets* secrets, const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    Error err = secrets->Erase();
    if (err != Error::None) {
      rsp["error_code"] = static_cast<uint8_t>(err);
      rsp["error_msg"] = "erase failed";
      return false;
    }

    return true;
  }

  bool HandleRestart(const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)
  {
    ui.SetBoardState(UI::BoardState::Restart);
    esp_err_t err = hw.ScheduleRestart(req["delay_ms"] | CONFIG_DEFAULT_RESTART_DELAY_MS);
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "schecule restart failed: %s", esp_err_to_name(err));
      return false;
    }

    return true;
  }
}

Error Commands::Initialize(Authenticator* auth, Secrets* secrets)
{
  this->auth = auth;
  this->secrets = secrets;
  return Error::None;
}

Error Commands::Dispatch(const SSH::UserInfo& userInfo, std::string_view cmdName, SSH::Stream& stream)
{
  ESP_LOGI(TAG, "client %s called command: %s", userInfo.ClientIP.c_str(), cmdName.cbegin());
  DynamicJsonDocument req(CONFIG_COMMAND_BUFFER_SIZE);
  DeserializationError jsonErr = deserializeJson(req, stream);
  if (jsonErr && jsonErr != DeserializationError::Code::EmptyInput) {
    ESP_LOGE(TAG, "unable to read request from client %s: %s", userInfo.ClientIP.c_str(), jsonErr.c_str());
    return Error::CommandFailed;
  }

  DynamicJsonDocument rspDoc(CONFIG_COMMAND_BUFFER_SIZE);
  JsonObject rsp = rspDoc.to<JsonObject>();

  bool ok = Handle(userInfo, cmdName, req.as<JsonObjectConst>(), rsp);
  rspDoc["ok"] = ok;

  if (serializeJson(rspDoc, stream) == 0) {
    ESP_LOGE(TAG, "unable to write response for client %s: %s", userInfo.ClientIP.c_str(), jsonErr.c_str());
    return Error::CommandFailed;
  }

  stream.write('\n');
  stream.flush();

  return ok ? Error::None : Error::ShitHappens;
}

bool Commands::Handle(const SSH::UserInfo& userInfo, std::string_view cmdName, const JsonObjectConst& req, JsonObject& rsp)
{
  static const std::vector<Command> commands = {
    {
      .Name = "/hmac/secret",
      .UsedAllowed = true,
      .Help = "Generate HMAC secret for req[\"salt\"] into rsp[\"secret\"]",
      .Handle = std::bind(HandleHmacSecret, auth, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    },
    {
      .Name = "/help",
      .UsedAllowed = true,
      .Help = "Returns commands info",
      .Handle = nullptr
    },
    {
      .Name = "/get/status",
      .UsedAllowed = false,
      .Help = "Returns BoundBoxESP status",
      .Handle = HandleGetStatus,
    },
    {
      .Name = "/set/secrets",
      .UsedAllowed = false,
      .Help = "Store runtime secrets from req[\"secrets\"]",
      .Handle = std::bind(HandleSetSecrets, secrets, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    },
    {
      .Name = "/reset/secrets",
      .UsedAllowed = false,
      .Help = "Reset secrets to it's default values",
      .Handle = std::bind(HandleResetSecrets, secrets, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    },
#if CONFIG_DUMPABLE_SECRETS
    {
      .Name = "/get/secrets",
      .UsedAllowed = false,
      .Help = "Returns runtime secrets in rsp[\"secrets\"]",
      .Handle = std::bind(HandleGetSecrets, secrets, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    },
#endif
    {
      .Name = "/restart",
      .UsedAllowed = false,
      .Help = R"(Restart BoundBoxESP in req["delay_ms"])",
      .Handle = HandleRestart
    }
  };

  if (cmdName == "/help") {
    JsonArray jsonCommands = rsp.createNestedArray("commands");
    for (const auto& cmd : commands) {
      if (!cmd.UsedAllowed && userInfo.Role != SSH::UserRole::SysOp) {
        continue;
      }

      JsonObject jsonCmd = jsonCommands.createNestedObject();
      jsonCmd["command"] = cmd.Name;
      jsonCmd["description"] = cmd.Help;
    }

    return true;
  }

  for (const auto& cmd : commands) {
    if (cmd.Name != cmdName) {
      continue;
    }

    if (!cmd.UsedAllowed && userInfo.Role != SSH::UserRole::SysOp) {
      rsp["error"] = "403: command can only be used by sysops, but you are just a random user";

      ESP_LOGW(TAG, "try to call privileged command '%s' from '%s' w/o permissions", cmdName.cbegin(), userInfo.ClientIP.c_str());
      return false;
    }

    return cmd.Handle(userInfo, req, rsp);
  }

  rsp["error"] = "404: command not found";
  ESP_LOGW(TAG, "called unknown command '%s' from '%s'", cmdName.cbegin(), userInfo.ClientIP.c_str());
  return false;
}
