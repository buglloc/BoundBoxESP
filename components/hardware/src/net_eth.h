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
    NetEth() = default;
    virtual esp_err_t Initialize() override;
    virtual esp_netif_config_t NetifConfig() const override;
    virtual esp_err_t Attach(esp_netif_t* netif) override;

    ~NetEth()
    {
      if (netif != nullptr) {
        esp_eth_stop(netif);
      }

      if (ethHandle != nullptr) {
        esp_eth_driver_uninstall(ethHandle);
      }
    }

  private:
    esp_eth_handle_t ethHandle = nullptr;
    esp_netif_inherent_config_t netifCfg;
    esp_netif_t* netif;
  };
}