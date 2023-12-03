#include "board_config.h"
#include "board_manager.h"
#include "ssh_service.h"
#include "ssh_handler.h"
#include "authenticator.h"

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define LOG_FOREVER(msg) {while(true){Log.errorln(msg);delay(120000);}}

TBoardManager& gBoardManager = TBoardManager::Instance();
TSshService& gSshService = TSshService::Instance();
TCommandDispatcher& gCommandDispatcher = TCommandDispatcher::Instance();
TAuthenticator& gAuthenticator = TAuthenticator::Instance();
TaskHandle_t gBgTask;
TaskHandle_t gMainTask;

void doBgTask(void* params);
void doMainTask(void* params);

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
#if BOOT_DELAY
  Log.infoln("wait boot delay: %d");
  delay(BOOT_DELAY);
#endif
  Log.infoln("starting up");

  if (!gBoardManager.Begin()) {
    LOG_FOREVER("Unable to setup board manager, check log for details");
  }

  if (!gAuthenticator.Begin()) {
    LOG_FOREVER("Unable to setup authenticator, check log for details");
  }

  const TConfig& cfg = gBoardManager.RuntimeConfig();
  if (!gSshService.Begin(*cfg.Ssh)) {
    LOG_FOREVER("Unable to setup SSH service, check log for details");
  }

  if (!gCommandDispatcher.Begin()) {
    LOG_FOREVER("Unable to setup command dispatcher, check log for details");
  }

  Log.infoln("setup tasks");
  xTaskCreatePinnedToCore(
    doBgTask,
    "BgTask",   /* name of task. */
    10000,      /* Stack size of task */
    nullptr,    /* parameter of the task */
    1,          /* priority of the task */
    &gBgTask,   /* Task handle to keep track of created task */
    0           /* pin task to core 0 */
  );

  xTaskCreatePinnedToCore(
    doMainTask,
    "MainTask", /* name of task. */
    50000,      /* Stack size of task */
    nullptr,    /* parameter of the task */
    1,          /* priority of the task */
    &gMainTask,   /* Task handle to keep track of created task */
    1           /* pin task to core 0 */
  );

  Log.infoln("started");
}

void doBgTask(void* params)
{
  do {
    gBoardManager.Tick();
    delay(25);
  } while (1);
}

void doMainTask(void* params)
{
  do {
    gSshService.Tick([](const TSshAuthInfoHolder& sess, const String& cmd, TSshReader& r, TSshWriter& w) -> bool {
      Log.infoln("%p called: %s", sess.get(), cmd.c_str());

      DynamicJsonDocument req(REQ_RSP_CAPACITY);
      DeserializationError jsonErr = deserializeJson(req, r);
      if (jsonErr && jsonErr != DeserializationError::Code::EmptyInput) {
        Log.errorln("unable to read request: %s", jsonErr.c_str());
        return false;
      }

      DynamicJsonDocument rspDoc(REQ_RSP_CAPACITY);
      JsonObject rsp = rspDoc.to<JsonObject>();
      bool ok = gCommandDispatcher.Handle(sess, cmd, req.as<JsonObjectConst>(), rsp);

      if (serializeJson(rspDoc, w) == 0) {
        Log.errorln("unable to write reponse");
        return false;
      }

      w.write('\n');
      return ok;
    });
  } while (1);
}

void loop()
{}
