#if 0
#include "config.h"
#include "auth_log.h"

#include <SPI.h>
#include <SD.h>

namespace
{
  void printTimestamp(Print* _logOutput)
  {
    // Division constants
    const unsigned long MSECS_PER_SEC       = 1000;
    const unsigned long SECS_PER_MIN        = 60;
    const unsigned long SECS_PER_HOUR       = 3600;
    const unsigned long SECS_PER_DAY        = 86400;

    // Total time
    const unsigned long msecs               =  millis();
    const unsigned long secs                =  msecs / MSECS_PER_SEC;

    // Time in components
    const unsigned long MilliSeconds        =  msecs % MSECS_PER_SEC;
    const unsigned long Seconds             =  secs  % SECS_PER_MIN ;
    const unsigned long Minutes             = (secs  / SECS_PER_MIN) % SECS_PER_MIN;
    const unsigned long Hours               = (secs  % SECS_PER_DAY) / SECS_PER_HOUR;

    // Time as string
    char timestamp[20];
    sprintf(timestamp, "%02d:%02d:%02d.%03d ", Hours, Minutes, Seconds, MilliSeconds);
    _logOutput->print(timestamp);
  }

  void printPrefix(Print* _logOutput, int logLevel) {
    printTimestamp(_logOutput);
  }
}

TAuthLog& TAuthLog::Instance()
{
  static TAuthLog instance;
  return instance;
}

bool TAuthLog::Begin()
{
  Log.infoln("setup authlog");

  log = Logging();
  log.setPrefix(printPrefix);

#if USE_SD_LOGSTORE
  if (!SD.begin(SD_SS_PIN, SPI, 4000000U, "/sd", 2, true)) {
    Log.errorln("unable to detect SDCard");
    return false;
  }

  if (SD.cardType() == CARD_NONE || SD.cardType() == CARD_UNKNOWN) {
    Log.errorln("unsupported SD Card type");
    return false;
  }

  Log.infoln(
    "authlog uses SD card (size: %dMB)",
    SD.cardSize() / (1024 * 1024)
  );

  File file = SD.open("/auth.log", FILE_WRITE, true);
  if (!file) {
    Log.errorln("error opening auth.log");
    return false;
  }

  log.begin(LOG_LEVEL_INFO, &file, false);
#else
  if (!Serial || !Serial.available()) {
    Log.errorln("unable to create source: serial is not available");
    return false;
  }

  Log.begin(LOG_LEVEL_INFO, &Serial, false);
#endif

  Log.infoln("authlog setup complete");
  return true;
}

void TAuthLog::Tick()
{
}

Logging TAuthLog::Logger()
{
  return log;
}
#endif
