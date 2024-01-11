#pragma once

#include <sdkconfig.h>

#include <lwip/inet.h>

#include <esp_err.h>
#include <esp_check.h>
#include <esp_event.h>
#include <esp_netif.h>


namespace Hardware
{
  inline void PatchNetifCfg(esp_netif_inherent_config_t& netifCfg)
  {
  #if CONFIG_BBHW_NET_DHCP_CLIENT
    netifCfg.flags = static_cast<esp_netif_flags_t>((netifCfg.flags & ~ESP_NETIF_DHCP_SERVER) | ESP_NETIF_DHCP_CLIENT);
  #elif CONFIG_BBHW_NET_DHCP_SERVER
    netifCfg.flags = static_cast<esp_netif_flags_t>((netifCfg.flags & ~ESP_NETIF_DHCP_CLIENT) | ESP_NETIF_DHCP_SERVER);
  #else
    netifCfg.flags = static_cast<esp_netif_flags_t>(netifCfg.flags & ~(ESP_NETIF_DHCP_CLIENT|ESP_NETIF_DHCP_SERVER));
  #endif
  }

  inline const esp_netif_ip_info_t* StaticIP()
  {
    #if !CONFIG_BBHW_NET_USE_STATIC_IP
      return nullptr;
    #else
      static esp_netif_ip_info_t ip = {};
      if (ip.ip.addr == 0) {
        ip.ip.addr = ipaddr_addr(CONFIG_BBHW_NET_IP);
        ip.netmask.addr = ipaddr_addr(CONFIG_BBHW_NET_SUBNET);
        ip.gw.addr = ipaddr_addr(CONFIG_BBHW_NET_GW);
      }

      return &ip;
    #endif
  }

  inline void SendGotIP(esp_netif_t *netif, const esp_netif_ip_info_t* ip)
  {
    if (ip == nullptr) {
      // no static IP - that's fine
      return;
    }

    ip_event_got_ip_t evt = {
      .esp_netif = netif,
      .ip_info = *ip,
      .ip_changed = true,
    };

    esp_err_t err = esp_event_post(IP_EVENT, IP_EVENT_STA_GOT_IP, &evt, sizeof(evt), 0);
    ESP_ERROR_CHECK(err);
  }

  inline void SetDnsServer(esp_netif_t *netif, esp_netif_dns_type_t type)
  {
  #ifndef CONFIG_BBHW_NET_DNS
    return;
  #else

    esp_netif_dns_info_t dns;
    dns.ip.u_addr.ip4.addr = ipaddr_addr(CONFIG_BBHW_NET_DNS);
    dns.ip.type = ESP_IPADDR_TYPE_V4;
    ESP_ERROR_CHECK(esp_netif_set_dns_info(netif, type, &dns));
  #endif
  }

  inline void SetIPInfo(esp_netif_t *netif)
  {
    assert(netif);

    const esp_netif_ip_info_t* ip = StaticIP();
    if (ip == nullptr) {
      // no static IP - that's fine
      return;
    }

    esp_err_t err = esp_netif_set_ip_info(netif, ip);
    ESP_ERROR_CHECK(err);

    SetDnsServer(netif, ESP_NETIF_DNS_MAIN);
    SendGotIP(netif, ip);
  }
}
