#include "ssh_handler.h"
#include "defaults.h"
#include "config.h"
#include "board_manager.h"
#include "secrets.h"

#include <ArduinoLog.h>

#define LOG_PREFIX "ssh_handler: "

namespace
{
  static TBoardManager& boardManager = TBoardManager::Instance();
  static TSecrets& secrets = TSecrets::Instance();

  using TCommandHandler = std::function<bool(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)>;

  bool HandleGetConfig(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObject runtimeObj = rsp.createNestedObject("config");
    auto err = boardManager.RuntimeConfig().ToJson(runtimeObj);
    if (err.has_error()) {
      return false;
    }

    return true;
  }

  bool HandleSetConfig(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    auto cfg = TConfig::FromJson(req["config"].as<JsonObjectConst>());
    if (cfg.has_error()) {
      rsp["error_code"] = static_cast<uint8_t>(cfg.error());
      return false;
    }

    return boardManager.StoreConfig(std::move(cfg.value()));
  }

  bool HandleResetConfig(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    return boardManager.ResetConfig();
  }

  bool HandleGetSecrets(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObject secretsObj = rsp.createNestedObject("secrets");
    auto err = secrets.ToJson(secretsObj);
    if (err.has_error()) {
      return false;
    }

    return true;
  }

  bool HandleSetSecrets(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    auto err = secrets.SetFromJson(req["secrets"].as<JsonObjectConst>());
    if (err.has_error()) {
      rsp["error_code"] = static_cast<uint8_t>(err.error());
      return false;
    }

    err = secrets.Store();
    if (err.has_error()) {
      rsp["error_code"] = static_cast<uint8_t>(err.error());
      return false;
    }

    return true;
  }

  bool HandleResetSecrets(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    auto err = secrets.Reset();
    if (err.has_error()) {
      rsp["error_code"] = static_cast<uint8_t>(err.error());
      return false;
    }

    return true;
  }

  bool HandleRestart(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    return boardManager.ScheduleRestart(req["sec"] | 5);
  }

  bool HandleGetStatus(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    rsp["uptime"] = boardManager.Uptime();
    rsp["free_heap"] = boardManager.FreeHeap();
    return true;
  }
}

TCommandDispatcher& TCommandDispatcher::Instance()
{
  static TCommandDispatcher instance;
  return instance;
}

bool TCommandDispatcher::Begin()
{
  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

bool TCommandDispatcher::Handle(const TSshAuthInfoHolder& sess, const String& cmd, const JsonObjectConst& req, JsonObject& rsp)
{
  // TODO(buglloc): registrator? unordered_map?!
  typedef struct {
    String Cmd;
    bool Restricted;
    String Help;
    TCommandHandler Handler;
  } THandler;
  static const THandler handlers[] {
    {"/get/status", true, "Returns BoundBoxESP status", HandleGetStatus},
    {"/get/config", true, "Returns runtime config in rsp[\"config\"]", HandleGetConfig},
    {"/set/config", true, "Store runtime config from req[\"config\"]", HandleSetConfig},
    {"/reset/config", true, "Reset config to default values", HandleResetConfig},
    {"/set/secrets", true, "Store runtime secrets from req[\"secrets\"]", HandleSetSecrets},
    {"/reset/secrets", true, "Reset secrets to it's default values", HandleResetSecrets},
#if DANGEROUS_SECRETS
    {"/get/secrets", true, "Returns runtime secrets in rsp[\"secrets\"]", HandleGetSecrets},
#endif
    {"/restart", true, "Restart BoundBoxESP in req[\"sec\"]", HandleRestart},
    {"/help", false, "Returns commands info", nullptr},
  };

  if (cmd == "/help") {
    JsonArray commands = rsp.createNestedArray("commands");
    for (uint8_t i = 0; i < sizeof(handlers)/sizeof(THandler); ++i) {
      JsonObject command = commands.createNestedObject();
      command["command"] = handlers[i].Cmd;
      command["restricted"] = handlers[i].Restricted;
      command["description"] = handlers[i].Help;
    }

    rsp["ok"] = true;
    return true;
  }

  for (uint8_t i = 0; i < sizeof(handlers)/sizeof(THandler); ++i) {
    if (handlers[i].Cmd != cmd) {
      continue;
    }

    if (handlers[i].Restricted && !sess->IsSysop) {
      rsp["ok"] = false;
      rsp["error"] = "The command '" + cmd + "' can only be used by sysops, but you are just a random user";
      return false;
    }

    rsp["ok"] = handlers[i].Handler(sess, req, rsp);
    return true;
  }

  rsp["ok"] = false;
  rsp["error"] = "command not found: " + cmd;
  return false;
}
