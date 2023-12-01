#include "board_config.h"
#include "board_manager.h"
#include "pref_store.h"
#include "secrets.h"
#include "net_manager.h"

#include <Esp.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoLog.h>

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES
#include <LilyGo_AMOLED.h>
#endif

namespace
{
  static TNetManager& netManager = TNetManager::Instance();

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES
  static LilyGo_Class amoled;
#endif

  void shutdown()
  {
    for (int d = ESP_PD_DOMAIN_RTC_PERIPH; d < ESP_PD_DOMAIN_MAX; ++d) {
      esp_sleep_pd_config(static_cast<esp_sleep_pd_domain_t>(d), ESP_PD_OPTION_OFF);
    }

    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_deep_sleep_start();
  }

}

TBoardManager& TBoardManager::Instance()
{
  static TBoardManager instance;
  return instance;
}

bool TBoardManager::Begin()
{
  Log.infoln("board manager starts");
  startTime = millis();

#ifdef HAVE_IDR
  Log.infoln("setup IDR (PIN: %d)", IDR_CASE_OPENED_PIN);
  pinMode(IDR_CASE_OPENED_PIN, IDR_CASE_OPENED_MODE);
  tickIntruder();
#else
  Log.infoln("IDR not available");
#endif

  Log.infoln("setup preferences");
  if (!TPrefStore::Instance().Begin()) {
    Log.errorln("unable to open preferences");
    return false;
  }

  Log.infoln("setup secrets manager");
  if (!TSecrets::Instance().Begin()) {
    Log.errorln("unable to initialize secrets manager");
    return false;
  }

  Log.infoln("setup runtime config");
  if (!TConfig::Begin()) {
    Log.errorln("begin runtime config fail");
    return false;
  }

  auto cfgRes = TConfig::LoadOrStore(CONFIG_KEY);
  if (cfgRes.has_error()) {
    Log.errorln("load runtime config fail: %d", cfgRes.error());
    return false;
  }
  runtimeConfig = cfgRes.value();

  Log.infoln("setup SPI (SCK: %d, MISO: %d, MOSI: %d)", SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN);
  SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN);

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES
  Log.infoln("setup lilygo AMOLED display");
  if (!amoled.beginAMOLED_191(true)) {
    Log.errorln("display start failed");
    return false;
  }
#endif

  Log.infoln("setup network");
  if (!netManager.Begin(runtimeConfig.Hostname, runtimeConfig.Net)) {
    Log.errorln("unable to setup network");
    return false;
  }

  Log.infoln("board manager complete");
  return true;
}

void TBoardManager::Tick()
{
  netManager.Tick();
#ifdef HAVE_IDR
  tickIntruder();
#endif
}

long TBoardManager::Uptime()
{
  unsigned long elapsedTime = millis() - startTime;
  return elapsedTime / 1000;
}

TNetManager& TBoardManager::Net()
{
  return netManager;
}

TConfig& TBoardManager::RuntimeConfig()
{
  return runtimeConfig;
}

void TBoardManager::tickIntruder()
{
  if (digitalRead(IDR_CASE_OPENED_PIN)) {
    Log.warningln("case opened: will shutdown");
    shutdown();
  }
}
