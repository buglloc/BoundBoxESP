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

  void wifiEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
  {
    esp_err_t ret = ESP_OK;
    switch (eventId)
    {
    case WIFI_EVENT_STA_START:
      ESP_LOGI(TAG, "wifi starts");
      ESP_GOTO_ON_ERROR(esp_wifi_connect(), err, TAG, "wifi connect");
      return;

    case WIFI_EVENT_STA_CONNECTED:
      ESP_LOGI(TAG, "wifi connected");
      SetIPInfo(reinterpret_cast<esp_netif_t *>(arg));
      return;

    case WIFI_EVENT_STA_DISCONNECTED:
      ESP_LOGW(TAG, "wifi disconnected, try to reconnect");
      ESP_GOTO_ON_ERROR(esp_wifi_connect(), err, TAG, "wifi connect");
      return;
    }

  err:
    ESP_LOGI(TAG, "[%d] got event %s:%ld", ret, eventBase, eventId);
  }
}

esp_err_t NetWiFiSta::Initialize()
{
  memcpy(&netifCfg, ESP_NETIF_BASE_DEFAULT_WIFI_STA, sizeof(netifCfg));
  PatchNetifCfg(netifCfg);

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

  ESP_RETURN_ON_ERROR(esp_netif_attach_wifi_station(netif), TAG, "netif attach failed");
  ESP_RETURN_ON_ERROR(esp_wifi_set_default_wifi_sta_handlers(), TAG, "register wifi handlers failed");

  wifi_init_config_t wifiCfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_RETURN_ON_ERROR(esp_wifi_init(&wifiCfg), TAG, "initialize wifi");

  ESP_RETURN_ON_ERROR(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiEventHandler, (void *)netif), TAG, "register event handlers");

  wifi_config_t staCfg = {
      .sta = {
        #ifdef CONFIG_BBHW_WIFI_SSID
          .ssid = CONFIG_BBHW_WIFI_SSID,
          .password = CONFIG_BBHW_WIFI_PASSWORD,
        #endif
          .threshold = {
            .authmode = WIFI_AUTH_WPA2_PSK
          },
      },
  };
  ESP_RETURN_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), TAG, "set sta mode");
  ESP_RETURN_ON_ERROR(esp_wifi_set_config(WIFI_IF_STA, &staCfg), TAG, "set wifi config");
  ESP_RETURN_ON_ERROR(esp_wifi_start(), TAG, "wifi start");

  return ESP_OK;
}
