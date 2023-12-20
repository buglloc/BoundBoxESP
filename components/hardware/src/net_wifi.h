#pragma once

#include "hardware/net.h"

#include <string.h>

#include <esp_wifi.h>
#include <esp_err.h>


namespace Hardware
{
  class NetWiFiSta final: public NetImpl
  {
  public:
    NetWiFiSta() = default;
    esp_err_t Initialize() override;
    esp_netif_config_t NetifConfig() const override;
    esp_err_t Attach(esp_netif_t* netif) override;

    ~NetWiFiSta()
    {
      esp_wifi_stop();
    }

  private:
    esp_netif_inherent_config_t netifCfg;
  };
}
