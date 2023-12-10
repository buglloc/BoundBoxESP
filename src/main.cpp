#include "board_config.h"
#include "board_manager.h"
#include "ssh_service.h"
#include "ssh_handler.h"
#include "authenticator.h"

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define LOG_FOREVER(msg) {while(true){Log.errorln(msg);delay(120000);}}
#define LOG_PREFIX "main: "

namespace {
  TBoardManager& boardManager = TBoardManager::Instance();
  TSshService& sshService = TSshService::Instance();
  TCommandDispatcher& commandDispatcher = TCommandDispatcher::Instance();
  TAuthenticator& authenticator = TAuthenticator::Instance();
  TaskHandle_t bgTask;
  TaskHandle_t mainTask;
}

void doBgTask(void* params);
void doMainTask(void* params);

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
#if BOOT_DELAY
  Log.infoln(LOG_PREFIX "wait boot delay: %d");
  delay(BOOT_DELAY);
#endif
  Log.infoln(LOG_PREFIX "starting up");

  if (!boardManager.Begin()) {
    LOG_FOREVER(LOG_PREFIX "Unable to setup board manager, check log for details");
  }

  const TConfig& cfg = boardManager.RuntimeConfig();
  if (!sshService.Begin(*cfg.Ssh)) {
    LOG_FOREVER(LOG_PREFIX "Unable to setup SSH service, check log for details");
  }

  if (!commandDispatcher.Begin()) {
    LOG_FOREVER(LOG_PREFIX "Unable to setup command dispatcher, check log for details");
  }

  boardManager.ToState(TBoardManager::BoardState::Idle);
  Log.infoln(LOG_PREFIX "setup tasks");
  xTaskCreatePinnedToCore(
    doBgTask,
    "BgTask",   /* name of task. */
    12288,      /* Stack size of task */
    nullptr,    /* parameter of the task */
    1,          /* priority of the task */
    &bgTask,   /* Task handle to keep track of created task */
    0           /* pin task to core 0 */
  );

  xTaskCreatePinnedToCore(
    doMainTask,
    "MainTask", /* name of task. */
    65536,      /* Stack size of task */
    nullptr,    /* parameter of the task */
    1,          /* priority of the task */
    &mainTask,   /* Task handle to keep track of created task */
    1           /* pin task to core 0 */
  );

  Log.infoln(LOG_PREFIX "started");
}

void doBgTask(void* params)
{
  do {
    boardManager.Tick();
    delay(10);
  } while (1);
}

void doMainTask(void* params)
{
  boardManager.ToState(TBoardManager::BoardState::WaitNet);
  Log.infoln(LOG_PREFIX "prepare network");
  const TConfig& cfg = boardManager.RuntimeConfig();
  if (!boardManager.Net().Connect(cfg.Hostname, *cfg.Net)) {
    LOG_FOREVER(LOG_PREFIX "Unable to start connect network, check log for details");
  }

  Log.infoln(LOG_PREFIX "prepare authenticator");
  boardManager.ToState(TBoardManager::BoardState::WaitCredential);
  authenticator.BuildCredential();
  do {
    Log.infoln(LOG_PREFIX "wait credential...");
    delay(1000);
  } while (!authenticator.HasCredential());

  do {
    Log.infoln(LOG_PREFIX "wait connection...");
    boardManager.ToState(TBoardManager::BoardState::Idle);
    sshService.AcceptConnection([](const TSshAuthInfoHolder& sess, const String& cmd, TSshReader& r, TSshWriter& w) -> bool {
      boardManager.ToState(TBoardManager::BoardState::Process);
      Log.infoln(LOG_PREFIX "%p called: %s", sess.get(), cmd.c_str());

      DynamicJsonDocument req(REQ_RSP_CAPACITY);
      DeserializationError jsonErr = deserializeJson(req, r);
      if (jsonErr && jsonErr != DeserializationError::Code::EmptyInput) {
        Log.errorln(LOG_PREFIX "unable to read request: %s", jsonErr.c_str());
        return false;
      }

      DynamicJsonDocument rspDoc(REQ_RSP_CAPACITY);
      JsonObject rsp = rspDoc.to<JsonObject>();
      bool ok = commandDispatcher.Handle(sess, cmd, req.as<JsonObjectConst>(), rsp);

      if (serializeJson(rspDoc, w) == 0) {
        Log.errorln(LOG_PREFIX "unable to write reponse");
        return false;
      }

      w.write('\n');
      return ok;
    });
  } while (1);
}

void loop()
{}
