#pragma once

#include "hardware/net.h"

#include <string.h>

#include <esp_eth_driver.h>
#include <esp_err.h>


namespace Hardware
{
  class NetEth final: public NetImpl
  {
  public:
    explicit NetEth(const NetConfig& cfg) : netCfg(cfg) {};

    esp_err_t Initialize() override;
    esp_netif_config_t NetifConfig() const override;
    esp_err_t Attach(esp_netif_t* netif) override;

    ~NetEth()
    {
      if (ethHandle != nullptr) {
        esp_eth_stop(ethHandle);
        esp_eth_driver_uninstall(ethHandle);
      }
    }

  private:
    const NetConfig& netCfg;
    esp_eth_handle_t ethHandle = nullptr;
    esp_netif_inherent_config_t netifCfg;
  };
}
