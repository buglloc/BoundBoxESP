#include "peripheral/net.h"
#include "net_eth.h"

#include <esp_netif.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>


using namespace Peripheral;

namespace
{
  static const char* TAG = "peripheral_net";

  void ipEventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
  {
    ip_event_got_ip_t* event = reinterpret_cast<ip_event_got_ip_t *>(event_data);
    const esp_netif_ip_info_t* ip_info = &event->ip_info;
    bool* isConnected = reinterpret_cast<bool *>(arg);

    switch (event_id)
    {
      case IP_EVENT_ETH_LOST_IP:
      case IP_EVENT_STA_LOST_IP:
        *isConnected = false;
        return;
      case IP_EVENT_ETH_GOT_IP:
      case IP_EVENT_STA_GOT_IP:
        *isConnected = true;
        ESP_LOGI(TAG, "%s IP Address", event_id == IP_EVENT_ETH_GOT_IP ? "Ethernet" : "WiFi");
        ESP_LOGI(TAG, "~~~~~~~~~~~");
        ESP_LOGI(TAG, "IP:" IPSTR, IP2STR(&ip_info->ip));
        ESP_LOGI(TAG, "MASK:" IPSTR, IP2STR(&ip_info->netmask));
        ESP_LOGI(TAG, "GW:" IPSTR, IP2STR(&ip_info->gw));
        ESP_LOGI(TAG, "~~~~~~~~~~~");
      default:
        return;
    }
  }
}

esp_err_t Net::Initialize(const NetConfig& cfg)
{
  netCfg = cfg;
  impl = std::make_unique<NetEth>();

  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize net implementation");
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
  if (!netCfg.Hostname.empty()) {
    esp_netif_set_hostname(netif, netCfg.Hostname.c_str());
  }

  ESP_RETURN_ON_ERROR(esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ipEventHandler, reinterpret_cast<void *>(&connected)), TAG, "attach got ip handler");
  return impl->Attach(netif, netCfg);
}

bool Net::IsConnected()
{
  return connected;
}
