#include "board_config.h"
#include "board_manager.h"
#include "ssh_service.h"

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define LOG_FOREVER(msg) {while(true){Log.errorln(msg);delay(60000);}}

TBoardManager& gBoardManager = TBoardManager::Instance();
TSshService& gSshService = TSshService::Instance();
TaskHandle_t gBgTask;
TaskHandle_t gMainTask;

void doBgTask(void* params);
void doMainTask(void* params);

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.infoln("starting up");

  if (!gBoardManager.Begin()) {
    LOG_FOREVER("Unable to setup board manager, check log for details");
  }

  TConfig& cfg = gBoardManager.RuntimeConfig();
  if (!gSshService.Begin(cfg.Ssh)) {
    LOG_FOREVER("Unable to setup SSH service, check log for details");
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
    sleep(50);
  } while (1);
}

void doMainTask(void* params)
{
  do {
    gSshService.Tick([](const TSshAuthInfoHolder& sess, const String& cmd, TSshReader& r, TSshWriter& w) -> bool {
      StaticJsonDocument<1024> doc;
      DeserializationError jsonErr = deserializeJson(doc, r);
      if (jsonErr && jsonErr != DeserializationError::Code::EmptyInput) {
        Log.errorln("unable to read request: %s", jsonErr.c_str());
        return false;
      }

      const char* data = doc["in"] | "Empty";
      Log.infoln("data for command '%s' by %p: %s", cmd.c_str(), sess.get(), data);
      doc["uptime"] = gBoardManager.Uptime();

      if (serializeJson(doc, w) == 0) {
        Log.errorln("unable to write reponse");
        return false;
      }

      w.write('\n');
      return true;
    });
  } while (1);
}

void loop()
{}
