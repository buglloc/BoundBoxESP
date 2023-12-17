#pragma once

#include "peripheral/net.h"

#include <string.h>

#include <esp_wifi.h>
#include <esp_err.h>


namespace Peripheral
{
  class NetWiFiSta final: public NetImpl
  {
  public:
    NetWiFiSta() = default;
    virtual esp_err_t Initialize() override;
    virtual esp_netif_config_t NetifConfig() const override;
    virtual esp_err_t Attach(esp_netif_t* netif) override;

    ~NetWiFiSta()
    {
      esp_wifi_stop();
    }

  private:
    esp_netif_inherent_config_t netifCfg;
  };
}
