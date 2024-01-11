#include <sdkconfig.h>
#include "hardware/net.h"

#include "net_common.h"
#include "net_usb.h"
#include "net_wifi.h"
#include "net_eth.h"

#include <esp_netif.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>


using namespace Hardware;

namespace
{
  static const char* TAG = "hardware::net";
  static bool netReady = false;
  static esp_ip4_addr_t localIP;

  void ipEventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
  {
    ip_event_got_ip_t* event = reinterpret_cast<ip_event_got_ip_t *>(event_data);
    const esp_netif_ip_info_t* ip_info = &event->ip_info;

    switch (event_id) {
      case IP_EVENT_ETH_LOST_IP:
      case IP_EVENT_STA_LOST_IP:
        netReady = false;
        localIP.addr = ZERO_IP;
        break;
      case IP_EVENT_ETH_GOT_IP:
      case IP_EVENT_STA_GOT_IP:
        netReady = true;
        localIP = ip_info->ip;

        switch (event_id) {
        case IP_EVENT_ETH_GOT_IP:
          ESP_LOGI(TAG, "Ethernet connected");
          break;
        case IP_EVENT_STA_GOT_IP:
          ESP_LOGI(TAG, "Wifi connected");
          break;
        default:
          ESP_LOGI(TAG, "Something connected");
        }

        ESP_LOGI(TAG, "~~~~~~~~~~~");

        if (!ip4_addr_isany_val(ip_info->ip)) {
          ESP_LOGI(TAG, "IP: " IPSTR, IP2STR(&ip_info->ip));
        }

        if (!ip4_addr_isany_val(ip_info->netmask)) {
          ESP_LOGI(TAG, "Mask: " IPSTR, IP2STR(&ip_info->netmask));
        }

        if (!ip4_addr_isany_val(ip_info->gw)) {
          ESP_LOGI(TAG, "Gateway: " IPSTR, IP2STR(&ip_info->gw));
        }

        ESP_LOGI(TAG, "~~~~~~~~~~~");
        break;
      case IP_EVENT_AP_STAIPASSIGNED:
        ESP_LOGI(TAG, "New client connected");
        ESP_LOGI(TAG, "IP: " IPSTR, IP2STR(&ip_info->ip));
      default:
        return;
    }
  }
}

esp_err_t Net::Initialize()
{
#if CONFIG_BBHW_NETKIND_USB
  impl = std::make_unique<NetUsb>();
  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize usb network");

#elif CONFIG_BBHW_NETKIND_ETH
  impl = std::make_unique<NetEth>();
  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize ethernet network");

#elif CONFIG_BBHW_NETKIND_WIFI_STA
  impl = std::make_unique<NetWiFiSta>();
  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize wifi network");

#else
  #error Network is not configured
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
  esp_netif_set_hostname(netif, CONFIG_BBHW_HOSTNAME);

  esp_err_t err = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ipEventHandler, nullptr);
  ESP_RETURN_ON_ERROR(err, TAG, "attach got ip handler");

  err = impl->Attach(netif);
  ESP_RETURN_ON_ERROR(err, TAG, "attach");

  return ESP_OK;
}

esp_ip4_addr_t Net::LocalIP()
{
  return localIP;
}

bool Net::Ready()
{
  return netReady;
}
