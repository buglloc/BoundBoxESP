#pragma once
#include "net_config.h"

#include <memory>
#include <string>

#include <esp_netif.h>
#include <esp_err.h>


namespace Hardware
{
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
    esp_err_t Initialize(NetConfig cfg);
    esp_err_t Attach();
    bool Ready();
    esp_ip4_addr_t LocalIP();

  private:
    NetConfig cfg;
    std::unique_ptr<NetImpl> impl;
  };
}
