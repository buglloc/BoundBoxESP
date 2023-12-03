#include "ssh_handler.h"
#include "config.h"
#include "board_manager.h"

#include <ArduinoLog.h>

namespace
{
  using TCommandHandler = std::function<bool(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)>;
  static TBoardManager& boardManager = TBoardManager::Instance();

  bool HandleGetConfig(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObject runtimeCfg = rsp.createNestedObject("config");
    auto err = boardManager.RuntimeConfig().ToJson(runtimeCfg);
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
  return true;
}

void TCommandDispatcher::Handle(const TSshAuthInfoHolder& sess, const String& cmd, const JsonObjectConst& req, JsonObject& rsp)
{
  // TODO(buglloc): registrator? unordered_map?!
  typedef struct {
    String cmd;
    String help;
    TCommandHandler handler;
  } THandler;
  static const THandler handlers[] {
    {"/get/status", "Returns BoundBoxESP status", HandleGetStatus},
    {"/get/config", "Returns runtime config in rsp[\"config\"]", HandleGetConfig},
    {"/set/config", "Store runtime config from req[\"config\"]", HandleSetConfig},
    {"/restart", "Restart BoundBoxESP in req[\"sec\"]", HandleRestart},
    {"/help", "Returns commands info", nullptr},
  };

  if (cmd == "/help") {
    JsonArray commands = rsp.createNestedArray("commands");
    for (uint8_t i = 0; i < sizeof(handlers)/sizeof(THandler); ++i) {
      JsonObject command = commands.createNestedObject();
      command["command"] = handlers[i].cmd;
      command["description"] = handlers[i].help;
    }

    rsp["ok"] = true;
    return;
  }

  for (uint8_t i = 0; i < sizeof(handlers)/sizeof(THandler); ++i) {
    if (handlers[i].cmd != cmd) {
      continue;
    }

    rsp["ok"] = handlers[i].handler(sess, req, rsp);
    return;
  }

  rsp["ok"] = false;
  rsp["error"] = "command not found: " + cmd;
}
