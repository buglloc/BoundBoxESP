#include "net_wifi.h"
#include "net_common.h"

#include <assert.h>

#include <esp_system.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <esp_log.h>
#include <esp_check.h>
#include <esp_event.h>


using namespace Hardware;

namespace
{
  static const char* TAG = "hardware::net::wifi";

  struct EventsCtx
  {
    const NetConfig& NetCfg;
    esp_netif_t *Netif;
  };

  void wifiEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
  {
    ESP_LOGI(TAG, "got event %s:%ld", eventBase, eventId);

    EventsCtx* ctx = reinterpret_cast<EventsCtx *>(arg);
    esp_err_t ret = ESP_OK;
    switch (eventId) {
    case WIFI_EVENT_STA_START:
      ESP_LOGI(TAG, "wifi starts");
      ESP_GOTO_ON_ERROR(esp_wifi_connect(), err, TAG, "wifi connect");
      return;

    case WIFI_EVENT_STA_CONNECTED:
      ESP_LOGI(TAG, "wifi connected");
      ESP_GOTO_ON_ERROR(SetIPInfo(ctx->Netif, ctx->NetCfg), err, TAG, "set ip");
      return;

    case WIFI_EVENT_STA_DISCONNECTED:
      ESP_LOGW(TAG, "wifi disconnected, try to reconnect");
      ESP_GOTO_ON_ERROR(esp_wifi_connect(), err, TAG, "wifi connect");
      return;
    }

  err:
    ESP_LOGE(TAG, "[%d] event failed %s:%ld", ret, eventBase, eventId);
  }
}

esp_err_t NetWiFiSta::Initialize()
{
  memcpy(&netifCfg, ESP_NETIF_BASE_DEFAULT_WIFI_STA, sizeof(netifCfg));
  esp_err_t err = PatchNetifCfg(netifCfg, netCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "patch netif cfg");

  return ESP_OK;
}

esp_netif_config_t NetWiFiSta::NetifConfig() const
{
  return {
    .base = &netifCfg,
    .driver = NULL,
    .stack = ESP_NETIF_NETSTACK_DEFAULT_WIFI_STA,
  };
}

esp_err_t NetWiFiSta::Attach(esp_netif_t* netif)
{
  assert(netif);

  {
    // validate
    bool ok = !netCfg.WiFi.Ssid.empty();
    ESP_RETURN_ON_FALSE(ok, ESP_ERR_INVALID_ARG, TAG, "no SSID provided");
    ok = netCfg.WiFi.Ssid.size() < MAX_SSID_LEN;
    ESP_RETURN_ON_FALSE(ok, ESP_ERR_INVALID_ARG, TAG, "maximum SSID (%d) length exceed: %d", MAX_SSID_LEN, netCfg.WiFi.Ssid.size());
    ok = netCfg.WiFi.Passwd.empty() || netCfg.WiFi.Passwd.size() > 8;
    ESP_RETURN_ON_FALSE(ok, ESP_ERR_INVALID_ARG, TAG, "passphrase must not be 8+ chars");
    ok = netCfg.WiFi.Passwd.size() < MAX_PASSPHRASE_LEN;
    ESP_RETURN_ON_FALSE(ok, ESP_ERR_INVALID_ARG, TAG, "maximum passphrase (%d) length exceed: %d", MAX_PASSPHRASE_LEN, netCfg.WiFi.Passwd.size());
  }

  esp_err_t err = esp_netif_attach_wifi_station(netif);
  ESP_RETURN_ON_ERROR(err, TAG, "netif attach failed");
  err = esp_wifi_set_default_wifi_sta_handlers();
  ESP_RETURN_ON_ERROR(err, TAG, "register wifi handlers failed");

  wifi_init_config_t wifiCfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_RETURN_ON_ERROR(esp_wifi_init(&wifiCfg), TAG, "initialize wifi");

  static EventsCtx eventCtx = {
    .NetCfg = this->netCfg,
    .Netif = netif,
  };
  err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiEventHandler, &eventCtx);
  ESP_RETURN_ON_ERROR(err, TAG, "register event handlers");

  ESP_RETURN_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), TAG, "set sta mode");

  wifi_config_t staCfg = {
    .sta = {
      .threshold = {
        .authmode = WIFI_AUTH_WPA2_PSK
      },
      .pmf_cfg = {
        .capable = true,
        .required = false,
      },
    },
  };
  strlcpy((char*) staCfg.sta.ssid, netCfg.WiFi.Ssid.c_str(), MAX_SSID_LEN);
  if (netCfg.WiFi.Passwd.empty()) {
    staCfg.sta.threshold.authmode = WIFI_AUTH_OPEN;
  } else {
    strlcpy((char*) staCfg.sta.password, netCfg.WiFi.Passwd.c_str(), MAX_PASSPHRASE_LEN);
  }
  ESP_RETURN_ON_ERROR(esp_wifi_set_config(WIFI_IF_STA, &staCfg), TAG, "set wifi config");

  ESP_RETURN_ON_ERROR(esp_wifi_start(), TAG, "wifi start");

  return ESP_OK;
}
