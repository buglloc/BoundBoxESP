#pragma once

#include "config.h"

#include <lwip/inet.h>

#include <esp_check.h>
#include <esp_netif.h>


namespace Hardware
{
  inline void PatchNetifCfg(esp_netif_inherent_config_t& netifCfg)
  {
  #if CONFIG_BBHW_NET_USE_STATIC_IP
    netifCfg.flags = static_cast<esp_netif_flags_t>(netifCfg.flags & ~ESP_NETIF_DHCP_CLIENT);
  #endif
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

  inline void BuildIPInfo(esp_netif_ip_info_t *ip, bool force)
  {
  #if !CONFIG_BBHW_NET_USE_STATIC_IP
    if (!force) {
      // doesn't use static IP - nothing to do
      return;
    }
  #else
    assert(ip);

    memset(ip, 0 , sizeof(esp_netif_ip_info_t));
    ip->ip.addr = ipaddr_addr(CONFIG_BBHW_NET_IP);
    ip->netmask.addr = ipaddr_addr(CONFIG_BBHW_NET_SUBNET);
    ip->gw.addr = ipaddr_addr(CONFIG_BBHW_NET_GW);
  #endif
  }

  inline void SetIPInfo(esp_netif_t *netif)
  {
  #if !CONFIG_BBHW_NET_USE_STATIC_IP
    // doesn't use static IP - nothing to do
    return;
  #else
    assert(netif);

    esp_netif_ip_info_t ip;
    memset(&ip, 0 , sizeof(esp_netif_ip_info_t));
    BuildIPInfo(&ip, false);
    ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip));

    SetDnsServer(netif, ESP_NETIF_DNS_MAIN);
  #endif
  }
}