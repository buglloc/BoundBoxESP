#pragma once

#include <esp_netif.h>
#include <esp_err.h>


namespace Peripheral
{
  class NetImpl
  {
  public:
    virtual esp_err_t Initialize() = 0;
    virtual esp_netif_config_t NetifConfig() const = 0;
    virtual esp_err_t Attach(esp_netif_t* netif, const NetConfig& netCfg) = 0;
    // virtual std::string LocalIP() = 0;
  };
}
