#include <sdkconfig.h>
#include "commands.h"

#include <vector>
#include <functional>

#include <esp_log.h>

#include <defer.h>
#include <ArduinoJson.h>

#include <hardware/manager.h>
#include <ui/manager.h>


namespace
{
  static const char *TAG = "main::cmd";
  Hardware::Manager& hw = Hardware::Manager::Instance();
  UI::Manager& ui = UI::Manager::Instance();

  using HandleFn = std::function<bool(const SSH::UserInfo& userInfo, const JsonObjectConst& req, JsonObject& rsp)>;

  struct Command
  {
    std::string Name;
    bool Restricted;
    std::string Help;
    HandleFn Handle;
  };

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

Error Commands::Initialize(Authenticator* auth)
{
  this->auth = auth;
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
//     {"/make/assertation", true, "Generate assertion for req[\"salt\"] into rsp[\"assertion\"]", HandleMakeAssertion},
//     {"/get/status", true, "Returns BoundBoxESP status", HandleGetStatus},
//     {"/set/secrets", true, "Store runtime secrets from req[\"secrets\"]", HandleSetSecrets},
//     {"/reset/secrets", true, "Reset secrets to it's default values", HandleResetSecrets},
// #if DANGEROUS_SECRETS
//     {"/get/secrets", true, "Returns runtime secrets in rsp[\"secrets\"]", HandleGetSecrets},
// #endif
    {
      .Name = "/restart",
      .Restricted = true,
      .Help = R"(Restart BoundBoxESP in req["delay_ms"])",
      .Handle = HandleRestart
    },
    {
      .Name = "/help",
      .Restricted = false,
      .Help = "Returns commands info",
      .Handle = nullptr
    },
  };

  if (cmdName == "/help") {
    JsonArray jsonCommands = rsp.createNestedArray("commands");
    for (const auto& cmd : commands) {
      JsonObject jsonCmd = jsonCommands.createNestedObject();
      jsonCmd["command"] = cmd.Name;
      jsonCmd["restricted"] = cmd.Restricted;
      jsonCmd["description"] = cmd.Help;
    }

    return true;
  }

  for (const auto& cmd : commands) {
    if (cmd.Name != cmdName) {
      continue;
    }

    if (cmd.Restricted && userInfo.Role != SSH::UserRole::SysOp) {
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
