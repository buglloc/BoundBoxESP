#pragma once

#include <string>


#define ZERO_IP ((uint32_t)0xffffffffUL)

namespace Hardware
{
  enum class NetKind: uint8_t
  {
    None = 0,
    USB,
    Ethernet,
    WiFiSTA,
  };

  enum class DhcpKind: uint8_t
  {
    None = 0,
    Client,
    Server,
  };

  struct IPConfig
  {
    bool Enabled;
    std::string IPv4Addr;
    std::string IPv4Subnet;
    std::string IPv4Gateway;
    std::string PrimaryDNS;
  };

  struct WiFiConfig
  {
    std::string Ssid;
    std::string Passwd;
  };

  struct NetConfig
  {
    NetKind Kind;
    DhcpKind DHCP;
    std::string Hostname;
    IPConfig StaticIP;
    WiFiConfig WiFi;
  };
}
