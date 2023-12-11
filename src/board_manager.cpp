#include "board_config.h"
#include "board_manager.h"
#include "pref_store.h"
#include "secrets.h"
#include "net_manager.h"
#include "ui_manager.h"
#include "authenticator.h"

#include <Esp.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoLog.h>

#define LOG_PREFIX "board_manager: "

namespace
{
  static TNetManager& netManager = TNetManager::Instance();
  static TUIManager& uiManager = TUIManager::Instance();
  static TAuthenticator& authenticator = TAuthenticator::Instance();

  void restart()
  {
    esp_restart();
  }

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
  Log.infoln(LOG_PREFIX "starts");
  startTime = millis();
  ToState(TBoardManager::BoardState::Boot);

#ifdef HAVE_IDR
  Log.infoln(LOG_PREFIX "setup IDR (PIN: %d)", IDR_CASE_OPENED_PIN);
  pinMode(IDR_CASE_OPENED_PIN, IDR_CASE_OPENED_MODE);
  tickIntruder();
#else
  Log.infoln(LOG_PREFIX "IDR not available");
#endif

  Log.infoln(LOG_PREFIX "setup preferences");
  if (!TPrefStore::Instance().Begin()) {
    Log.errorln(LOG_PREFIX "unable to open preferences");
    return false;
  }

  Log.infoln(LOG_PREFIX "setup secrets manager");
  if (!TSecrets::Instance().Begin()) {
    Log.errorln(LOG_PREFIX "unable to initialize secrets manager");
    return false;
  }

  Log.infoln(LOG_PREFIX "setup runtime config");
  if (!TConfig::Begin()) {
    Log.errorln(LOG_PREFIX "begin runtime config fail");
    return false;
  }

  auto cfgRes = TConfig::LoadOrStore(CONFIG_KEY);
  if (cfgRes.has_error()) {
    Log.errorln(LOG_PREFIX "load runtime config fail: %d", cfgRes.error());
    return false;
  }
  runtimeConfig = std::move(cfgRes.value());

  Log.infoln(LOG_PREFIX "setup SPI (SCK: %d, MISO: %d, MOSI: %d)", SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN);
  SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN);

  Log.infoln(LOG_PREFIX "setup authenticator");
  if (!authenticator.Begin()) {
    Log.errorln(LOG_PREFIX "authenticator start failed");
    return false;
  }

  Log.infoln(LOG_PREFIX "setup UI");
  TUIManager::EventHandlers uiHandlers{
    .OnPinEnter = std::bind(&TAuthenticator::OnPinChar, &authenticator, std::placeholders::_1),
    .OnPinEntered = std::bind(&TAuthenticator::OnPinEntered, &authenticator, std::placeholders::_1),
    .OnPinVerified = std::bind(&TAuthenticator::OnPinVerified, &authenticator, std::placeholders::_1),
  };
  if (!uiManager.Begin(std::move(uiHandlers))) {
    Log.errorln(LOG_PREFIX "display start failed");
    return false;
  }

  Log.infoln(LOG_PREFIX "setup network");
  if (!netManager.Begin(runtimeConfig->Net->Kind)) {
    Log.errorln(LOG_PREFIX "unable to setup network");
    return false;
  }

  Log.infoln(LOG_PREFIX "startup complete");
  return true;
}

void TBoardManager::Tick()
{
#ifdef HAVE_IDR
  tickIntruder();
#endif

  uptime = (millis() - startTime) / 1000;
  tickRestart();
  tickBoardInfo();
  uiManager.Tick(boardInfo);
}

bool TBoardManager::ResetConfig()
{
  auto defaultConfig = TConfig::Remove(CONFIG_KEY);
  if (defaultConfig.has_error()) {
    Log.errorln(LOG_PREFIX "remove runtime config fail: %d", defaultConfig.error());
    return false;
  }

  defaultConfig = std::move(defaultConfig.value());
  return true;
}

bool TBoardManager::StoreConfig(std::unique_ptr<TConfig> cfg)
{
  auto cfgRes = cfg->Store(CONFIG_KEY);
  if (cfgRes.has_error()) {
    Log.errorln(LOG_PREFIX "store runtime config fail: %d", cfgRes.error());
    return false;
  }

  runtimeConfig = std::move(cfg);
  return true;
}

TNetManager& TBoardManager::Net() const
{
  return netManager;
}

void TBoardManager::ToState(BoardState targetState)
{
  // racy
  boardInfo.State = targetState;
}

bool TBoardManager::ScheduleRestart(int sec)
{
  if (restartAt > 0) {
    Log.infoln(LOG_PREFIX "restart already scheduled");
    return false;
  }

  restartAt = Uptime() + sec;
  Log.infoln(LOG_PREFIX "restart scheduled in %ds", sec);
  return true;
}

const TConfig& TBoardManager::RuntimeConfig() const
{
  return *runtimeConfig;
}

uint32_t TBoardManager::Uptime() const
{
  return uptime;
}

uint32_t TBoardManager::FreeHeap() const
{
  return esp_get_free_heap_size();
}

void TBoardManager::tickRestart()
{
  if (restartAt > 0 && Uptime() >= restartAt) {
    Log.warningln(LOG_PREFIX "reboot");
    restart();
  }
}

void TBoardManager::tickIntruder()
{
  if (digitalRead(IDR_CASE_OPENED_PIN)) {
    Log.warningln(LOG_PREFIX "case opened: will shutdown");
    shutdown();
  }
}

void TBoardManager::tickBoardInfo()
{
  if (Uptime() - infoUpdatedAt < 2) {
    return;
  }

  infoUpdatedAt = Uptime();
  boardInfo.LocalIP = netManager.LocalIP();
}
