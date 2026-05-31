#include <sdkconfig.h>
#include "hardware/net.h"

#include "net_common.h"
#include "net_usb.h"
#include "net_wifi.h"
#include "net_eth.h"

#include <atomic>

#include <esp_netif.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>


using namespace Hardware;

namespace
{
  static const char* TAG = "hardware::net";
  static std::atomic<bool> netReady{false};
  static std::atomic<uint32_t> localIPAddr{ZERO_IP};

  void ipEventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
  {
    ESP_LOGI(TAG, "got event %s:%ld", event_base, event_id);
    switch (event_id) {
      case IP_EVENT_ETH_LOST_IP:
      case IP_EVENT_STA_LOST_IP:
        netReady.store(false);
        localIPAddr.store(ZERO_IP);
        break;

      case IP_EVENT_ETH_GOT_IP:
      case IP_EVENT_STA_GOT_IP: {
        const auto* event = reinterpret_cast<const ip_event_got_ip_t*>(event_data);
        const esp_netif_ip_info_t* ip_info = &event->ip_info;

        localIPAddr.store(ip_info->ip.addr);
        netReady.store(true);

        ESP_LOGI(TAG, "%s connected", event_id == IP_EVENT_ETH_GOT_IP ? "ethernet" : "wifi");
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
      }

      case IP_EVENT_AP_STAIPASSIGNED: {
        const auto* event = reinterpret_cast<const ip_event_ap_staipassigned_t*>(event_data);
        ESP_LOGI(TAG, "new client connected");
        ESP_LOGI(TAG, "IP: " IPSTR, IP2STR(&event->ip));
        break;
      }

      default:
        break;
    }
  }
}

esp_err_t Net::Initialize(NetConfig cfg)
{
  this->cfg = std::move(cfg);

  // esp_netif must be initialized before any impl that builds netif configs.
  ESP_RETURN_ON_ERROR(esp_netif_init(), TAG, "failed to initialize netif");

  switch (this->cfg.Kind)
  {
  case NetKind::USB:
    ESP_LOGI(TAG, "will use USB CBC network");
    impl = std::make_unique<NetUsb>(this->cfg);
    break;

  case NetKind::WiFiSTA:
    ESP_LOGI(TAG, "will use WiFi Station network");
    impl = std::make_unique<NetWiFiSta>(this->cfg);
    break;

#ifdef CONFIG_BBHW_HAS_ETH
  case NetKind::Ethernet:
    ESP_LOGI(TAG, "will use Ethernet network");
    impl = std::make_unique<NetEth>(this->cfg);
    break;
#endif

  default:
    ESP_LOGE(TAG, "unsupported network kind: %d", (int)this->cfg.Kind);
    return ESP_ERR_INVALID_ARG;
  }

  ESP_RETURN_ON_ERROR(impl->Initialize(), TAG, "failed to initialize network impl");
  return ESP_OK;
}

esp_err_t Net::Attach()
{
  if (!impl) {
    return ESP_ERR_INVALID_STATE;
  }

  esp_netif_config_t netifCfg = impl->NetifConfig();
  esp_netif_t* netif = esp_netif_new(&netifCfg);
  esp_netif_set_hostname(netif, cfg.Hostname.c_str());

  esp_err_t err = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ipEventHandler, nullptr);
  ESP_RETURN_ON_ERROR(err, TAG, "attach got ip handler");

  err = impl->Attach(netif);
  ESP_RETURN_ON_ERROR(err, TAG, "attach");

  return ESP_OK;
}

esp_ip4_addr_t Net::LocalIP()
{
  esp_ip4_addr_t out = {
    .addr = localIPAddr.load()
  };
  return out;
}

bool Net::Ready()
{
  return netReady.load();
}
