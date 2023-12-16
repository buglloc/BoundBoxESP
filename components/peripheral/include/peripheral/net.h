#pragma once

#include <memory>
#include <string>

#include <esp_netif.h>
#include <esp_err.h>

#define IPADDR_NONE ((uint32_t)0xffffffffUL)

namespace Peripheral
{
  class IP4Address
  {
  public:
    IP4Address() : addr({.addr = IPADDR_NONE}) {};

    esp_err_t FromString(std::string_view in)
    {
      esp_err_t ret = esp_netif_str_to_ip4(in.cbegin(), &addr);
      if (ret == ESP_OK) {
        addrStr = in;
        return ret;
      }

      return ESP_ERR_INVALID_ARG;
    }

    std::string ToString() const
    {
      return addrStr;
    }

    const char* c_str() const
    {
      return addrStr.c_str();
    }

    esp_ip4_addr_t Addr() const
    {
      return addr;
    }

    bool Empty() const
    {
      return addr.addr != IPADDR_NONE;
    }

  private:
    esp_ip4_addr_t addr;
    std::string addrStr;
  };

  enum class NetKind: uint8_t
  {
    WiFiSta = 0,
    Ethernet,
  };

  struct NetConfig
  {
    NetKind Kind;
    std::string Hostname;
    IP4Address IP;
    IP4Address Subnet;
    IP4Address DNS;
    IP4Address Gateway;
  };

  class NetImpl
  {
  public:
    virtual esp_err_t Initialize() = 0;
    virtual esp_netif_config_t NetifConfig() const = 0;
    virtual esp_err_t Attach(esp_netif_t* netif, const NetConfig& netCfg) = 0;
  };

  class Net
  {
  public:
    Net() = default;
    esp_err_t Initialize(const NetConfig& cfg);
    esp_err_t Attach();
    bool IsConnected();

  private:
    std::unique_ptr<NetImpl> impl;
    NetConfig netCfg;
    bool connected;
  };
}
