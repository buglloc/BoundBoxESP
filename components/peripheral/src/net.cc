#include "peripheral/net.h"
#include "sdkconfig.h"
#if CONFIG_BBP_HAS_ETH
#include "net_eth.h"
#endif
#if CONFIG_BBP_HAS_WIFI
#include "net_wifi.h"
#endif

#include <esp_netif.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>


using namespace Peripheral;

namespace
{
  static const char* TAG = "peripheral::net";

  void ipEventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
  {
    ip_event_got_ip_t* event = reinterpret_cast<ip_event_got_ip_t *>(event_data);
    const esp_netif_ip_info_t* ip_info = &event->ip_info;
    bool* ready = reinterpret_cast<bool *>(arg);

    switch (event_id)
    {
      case IP_EVENT_ETH_LOST_IP:
      case IP_EVENT_STA_LOST_IP:
        *ready = false;
        return;
      case IP_EVENT_ETH_GOT_IP:
      case IP_EVENT_STA_GOT_IP:
        *ready = true;
        ESP_LOGI(TAG, "%s IP Address", event_id == IP_EVENT_ETH_GOT_IP ? "Ethernet" : "WiFi");
        ESP_LOGI(TAG, "~~~~~~~~~~~");
        ESP_LOGI(TAG, "IP: " IPSTR, IP2STR(&ip_info->ip));
        ESP_LOGI(TAG, "Mask: " IPSTR, IP2STR(&ip_info->netmask));
        ESP_LOGI(TAG, "Gateway: " IPSTR, IP2STR(&ip_info->gw));
        ESP_LOGI(TAG, "~~~~~~~~~~~");
      default:
        return;
    }
  }
}

esp_err_t Net::Initialize()
{
#if CONFIG_BBP_NETKIND_ETH
  impl = std::make_unique<NetEth>();
  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize ethernet network");

#elif CONFIG_BBP_NETKIND_WIFI_STA
  impl = std::make_unique<NetWiFiSta>();
  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize wifi network");

#else
  ESP_LOGE(TAG, "no network configured");
  return ESP_FAIL;
#endif

  ESP_RETURN_ON_ERROR(esp_netif_init(), TAG, "failed to initialize netif");
  return ESP_OK;
}

esp_err_t Net::Attach()
{
  if (!impl) {
    return ESP_ERR_INVALID_STATE;
  }

  esp_netif_config_t netifCfg = impl->NetifConfig();
  esp_netif_t* netif = esp_netif_new(&netifCfg);
  esp_netif_set_hostname(netif, CONFIG_BBP_HOSTNAME);

  ESP_RETURN_ON_ERROR(esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ipEventHandler, (void *)&ready), TAG, "attach got ip handler");
  return impl->Attach(netif);
}

bool Net::Ready()
{
  return ready;
}
