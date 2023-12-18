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
    IP4Address() : addr({.addr = ZERO_IP}) {};

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

  private:
    std::unique_ptr<NetImpl> impl;
    bool ready;
  };
}
