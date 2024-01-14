#pragma once

#include "hardware/net.h"

#include <string.h>

#include <tinyusb.h>
#include <lwip/esp_netif_net_stack.h>

#include <esp_err.h>


namespace Hardware
{
  class NetUsb final: public NetImpl
  {
  public:
    explicit NetUsb(const NetConfig& cfg) : netCfg(cfg) {};

    esp_err_t Initialize() override;
    esp_netif_config_t NetifConfig() const override;
    esp_err_t Attach(esp_netif_t* netif) override;

    ~NetUsb()
    {
      tinyusb_driver_uninstall();
    }

  private:
    const NetConfig& netCfg;
    esp_netif_t* netif = nullptr;
    esp_netif_ip_info_t ipInfo;
    esp_netif_inherent_config_t netifCfg;
    esp_netif_driver_ifconfig_t driverCfg;
    struct esp_netif_netstack_config stackCfg;
  };
}
