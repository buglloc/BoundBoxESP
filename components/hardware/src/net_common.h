#pragma once
#include "hardware/net.h"

#include <esp_err.h>
#include <esp_netif.h>


namespace Hardware
{
  const esp_netif_ip_info_t* NetifIP(const NetConfig& netCfg);

  esp_err_t PatchNetifCfg(esp_netif_inherent_config_t& netifCfg, const NetConfig& netCfg);

  esp_err_t SendGotIP(esp_netif_t *netif, const esp_netif_ip_info_t* ip);
  esp_err_t SetPrimaryDns(esp_netif_t *netif, const NetConfig& netCfg);
  esp_err_t SetIPInfo(esp_netif_t *netif, const NetConfig& netCfg);
}
