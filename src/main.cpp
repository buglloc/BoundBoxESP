#include "board_config.h"
#include "board_manager.h"
#include "ssh_service.h"

#include <Arduino.h>
#include <ArduinoLog.h>

#define LOG_FOREVER(msg) {while(true){Log.errorln(msg);delay(60000);}}

TBoardManager& gBoardManager = TBoardManager::Instance();
TSshService& gSshService = TSshService::Instance();

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

  Log.infoln("started");
}

void loop()
{
  Log.infoln("it's alive!!");
  gBoardManager.Tick();
  gSshService.Tick([](const TSshAuthInfo& sess, const String& cmd, const Stream& r, Print& w) -> bool {
    Log.infoln("Got action: %s", cmd.c_str());
    return true;
  });

  delay(1000);
}
