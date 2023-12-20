#pragma once

#include <memory>
#include <string>

#include <esp_netif.h>
#include <esp_err.h>

#define ZERO_IP ((uint32_t)0xffffffffUL)

namespace Hardware
{
  class IP4Address
  {
  public:
    explicit IP4Address(esp_ip4_addr_t addr)
      : addr(std::move(addr))
      {};

    IP4Address()
      : addr({.addr = ZERO_IP})
      {};

    esp_err_t FromString(const std::string_view in)
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
      if (addr.addr == 0) {
        return "N/A";
      }

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
      return addr.addr != ZERO_IP;
    }

  private:
    esp_ip4_addr_t addr;
    std::string addrStr;
  };

  class NetImpl
  {
  public:
    virtual esp_err_t Initialize() = 0;
    virtual esp_netif_config_t NetifConfig() const = 0;
    virtual esp_err_t Attach(esp_netif_t* netif) = 0;
  };

  class Net
  {
  public:
    Net() = default;
    esp_err_t Initialize();
    esp_err_t Attach();
    bool Ready();
    esp_ip4_addr_t LocalIP();

  private:
    std::unique_ptr<NetImpl> impl;
  };
}
