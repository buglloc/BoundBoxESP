#include "net_common.h"

#include <lwip/inet.h>

#include <esp_err.h>
#include <esp_check.h>
#include <esp_event.h>
#include <esp_netif.h>

namespace
{
  static const char* TAG = "net::common";
}

namespace Hardware
{
  esp_err_t PatchNetifCfg(esp_netif_inherent_config_t& netifCfg, const NetConfig& netCfg)
  {
    switch (netCfg.DHCP)
    {
    case DhcpKind::None:
      netifCfg.flags = static_cast<esp_netif_flags_t>(netifCfg.flags & ~(ESP_NETIF_DHCP_CLIENT|ESP_NETIF_DHCP_SERVER));
      break;

    case DhcpKind::Client:
      netifCfg.flags = static_cast<esp_netif_flags_t>((netifCfg.flags & ~ESP_NETIF_DHCP_SERVER) | ESP_NETIF_DHCP_CLIENT);
      break;

    case DhcpKind::Server:
      netifCfg.flags = static_cast<esp_netif_flags_t>((netifCfg.flags & ~ESP_NETIF_DHCP_CLIENT) | ESP_NETIF_DHCP_SERVER);
      break;

    default:
      ESP_LOGE(TAG, "unexpected dhcp setting: %d", (int)netCfg.DHCP);
      return ESP_ERR_NOT_SUPPORTED;
    }

    return ESP_OK;
  }

  const esp_netif_ip_info_t* NetifIP(const NetConfig& netCfg)
  {
    if (!netCfg.StaticIP.Enabled) {
      return nullptr;
    }

    // ???
    static esp_netif_ip_info_t ip = {};
    if (ip.ip.addr == 0) {
      ip.ip.addr = ipaddr_addr(netCfg.StaticIP.IPv4Addr.c_str());
      ip.netmask.addr = ipaddr_addr(netCfg.StaticIP.IPv4Subnet.c_str());
      ip.gw.addr = ipaddr_addr(netCfg.StaticIP.IPv4Gateway.c_str());
    }
    return &ip;
  }

  esp_err_t SendGotIP(esp_netif_t *netif, const esp_netif_ip_info_t* ip)
  {
    if (ip == nullptr) {
      // no static IP - that's fine
      return ESP_OK;
    }

    ip_event_got_ip_t evt = {
      .esp_netif = netif,
      .ip_info = *ip,
      .ip_changed = true,
    };

    return esp_event_post(IP_EVENT, IP_EVENT_STA_GOT_IP, &evt, sizeof(evt), 0);
  }

  esp_err_t SetPrimaryDns(esp_netif_t *netif, const NetConfig& netCfg)
  {
    if (netCfg.StaticIP.PrimaryDNS.empty()) {
      return ESP_OK;
    }

    esp_netif_dns_info_t dns;
    dns.ip.u_addr.ip4.addr = ipaddr_addr(netCfg.StaticIP.PrimaryDNS.c_str());
    dns.ip.type = ESP_IPADDR_TYPE_V4;
    return esp_netif_set_dns_info(netif, ESP_NETIF_DNS_MAIN, &dns);
  }

  esp_err_t SetIPInfo(esp_netif_t *netif, const NetConfig& netCfg)
  {
    assert(netif);

    const esp_netif_ip_info_t* ip = NetifIP(netCfg);
    if (ip == nullptr) {
      // no static IP - that's fine
      return ESP_OK;
    }

    esp_err_t err = esp_netif_set_ip_info(netif, ip);
    if (err != ESP_OK) {
      return err;
    }

    err = SetPrimaryDns(netif, netCfg);
    if (err != ESP_OK) {
      return err;
    }

    return SendGotIP(netif, ip);
  }
}
