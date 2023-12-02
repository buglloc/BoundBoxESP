#include "ssh_handler.h"
#include "board_manager.h"
#include <ArduinoLog.h>
#include <Esp.h>
#include <String>

namespace
{
  using TCommandHandler = std::function<bool(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)>;
  static TBoardManager& boardManager = TBoardManager::Instance();

  bool HandleGetStatus(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    rsp["uptime"] = boardManager.Uptime();
    rsp["free_heap"] = ESP.getFreeHeap();
    return true;
  }

  bool HandleGetConfig(const TSshAuthInfoHolder& sess, const JsonObjectConst& req, JsonObject& rsp)
  {
    JsonObject runtimeCfg = rsp.createNestedObject("config");
    auto err = boardManager.RuntimeConfig().ToJson(runtimeCfg);
    if (err.has_error()) {
      return false;
    }

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
    {"/get/status", "returns box status", HandleGetStatus},
    {"/get/config", "returns runtime config", HandleGetConfig},
  };

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
