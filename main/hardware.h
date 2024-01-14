#pragma once

#include <hardware/manager.h>


Hardware::Config HwConfig()
{
  Hardware::NetConfig netCfg = {
    #if CONFIG_NET_KIND_USB
    .Kind = Hardware::NetKind::USB,
    #elif CONFIG_NET_KIND_WIFI_STA
    .Kind = Hardware::NetKind::WiFiSTA,
    #elif CONFIG_NET_KIND_ETH
    .Kind = Hardware::NetKind::Ethernet,
    #else
      #error NET_KIND is not configured
    #endif

    #if CONFIG_NET_DHCP_KIND_NONE
    .DHCP = Hardware::DhcpKind::None,
    #elif CONFIG_NET_DHCP_KIND_CLIENT
    .DHCP = Hardware::DhcpKind::Client,
    #elif CONFIG_NET_DHCP_KIND_SERVER
    .DHCP = Hardware::DhcpKind::Server,
    #else
      #error NET_DHCP_KIND is not configured
    #endif

    .Hostname = CONFIG_HOSTNAME,

    #if CONFIG_NET_USE_STATIC_IP
    .StaticIP = {
      .Enabled = true,
      .IPv4Addr = CONFIG_NET_IP,
      .IPv4Subnet = CONFIG_NET_SUBNET,
      .IPv4Gateway = CONFIG_NET_GW,
      .PrimaryDNS = CONFIG_NET_DNS,
    },
    #endif

    #if CONFIG_NET_KIND_WIFI_STA
    .WiFi = {
      .Ssid = CONFIG_WIFI_SSID,
      .Passwd = CONFIG_WIFI_PASSWORD,
    },
    #endif
  };

  return {
    .Net = netCfg,
  };
}
