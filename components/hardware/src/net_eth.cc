#include <sdkconfig.h>
#include "net_eth.h"
#include "net_common.h"

#include <assert.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_netif.h>
#include <esp_eth.h>
#include <esp_eth_driver.h>
#include <esp_mac.h>
#include <esp_log.h>
#include <esp_check.h>
#include <esp_event.h>

#ifdef BBHW_HAS_ETH

using namespace Hardware;

namespace
{
  static const char* TAG = "hardware::net::eth";

  struct EventsCtx
  {
    const NetConfig& NetCfg;
    esp_netif_t *Netif;
  };

  struct SpiModuleCfg
  {
    uint8_t CsGPIO;
    uint8_t IntGPIO;
    int8_t PhyResetGPIO;
    uint8_t PhyAddr;
    uint8_t *MacAddrPtr;
  };

  // copied from esp-idf ethernet example
  esp_eth_handle_t ethInitSpi(const SpiModuleCfg& cfg, esp_eth_mac_t** mac_out, esp_eth_phy_t** phy_out)
  {
    esp_eth_handle_t ret = NULL;

    // Init common MAC and PHY configs to default
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();

    // Update PHY config based on board specific configuration
    phy_config.phy_addr = cfg.PhyAddr;
    phy_config.reset_gpio_num = cfg.PhyResetGPIO;

    // Configure SPI interface for specific SPI module
    spi_device_interface_config_t spi_devcfg = {
      .mode = 0,
      .clock_speed_hz = CONFIG_BBHW_ETH_SPI_CLOCK_MHZ * 1000 * 1000,
      .spics_io_num = cfg.CsGPIO,
      .queue_size = 20,
    };

    eth_w5500_config_t w5500_config = ETH_W5500_DEFAULT_CONFIG(static_cast<spi_host_device_t>(CONFIG_BBHW_SPI_HOST_ID), &spi_devcfg);
    w5500_config.int_gpio_num = cfg.IntGPIO;
    esp_eth_mac_t* mac = esp_eth_mac_new_w5500(&w5500_config, &mac_config);
    esp_eth_phy_t* phy = esp_eth_phy_new_w5500(&phy_config);

    // Init Ethernet driver to default and install it
    esp_eth_handle_t eth_handle = nullptr;
    esp_eth_config_t eth_config_spi = ETH_DEFAULT_CONFIG(mac, phy);
    ESP_GOTO_ON_FALSE(esp_eth_driver_install(&eth_config_spi, &eth_handle) == ESP_OK, NULL, err, TAG, "SPI Ethernet driver install failed");

    // The SPI Ethernet module might not have a burned factory MAC address, we can set it manually.
    if (cfg.MacAddrPtr != NULL) {
      ESP_GOTO_ON_FALSE(esp_eth_ioctl(eth_handle, ETH_CMD_S_MAC_ADDR, cfg.MacAddrPtr) == ESP_OK,
        NULL, err, TAG, "SPI Ethernet MAC address config failed");
    }

    if (mac_out != NULL) {
      *mac_out = mac;
    }
    if (phy_out != NULL) {
      *phy_out = phy;
    }
    return eth_handle;

  err:
    if (eth_handle != NULL) {
        esp_eth_driver_uninstall(eth_handle);
    }
    if (mac != NULL) {
        mac->del(mac);
    }
    if (phy != NULL) {
        phy->del(phy);
    }
    return ret;
  }

  void ethEventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
  {
    ESP_LOGI(TAG, "got event %s:%ld", event_base, event_id);

    EventsCtx* ctx = reinterpret_cast<EventsCtx *>(arg);
    esp_err_t ret = ESP_OK;
    switch (event_id) {
    case ETHERNET_EVENT_CONNECTED:
      ESP_LOGI(TAG, "Ethernet Link Up");
      ESP_GOTO_ON_ERROR(SetIPInfo(ctx->Netif, ctx->NetCfg), err, TAG, "set ip");
      break;

    case ETHERNET_EVENT_DISCONNECTED:
      ESP_LOGI(TAG, "Ethernet Link Down");
      break;

    case ETHERNET_EVENT_START:
      ESP_LOGI(TAG, "Ethernet Started");
      break;

    case ETHERNET_EVENT_STOP:
      ESP_LOGI(TAG, "Ethernet Stopped");
      break;

    default:
      break;
    }

  err:
    ESP_LOGE(TAG, "[%d] event failed %s:%ld", ret, event_base, event_id);
  }
}

esp_err_t NetEth::Initialize()
{
  memcpy(&netifCfg, ESP_NETIF_BASE_DEFAULT_ETH, sizeof(netifCfg));
  esp_err_t err = PatchNetifCfg(netifCfg, netCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "patch netif cfg");

  uint8_t mac[ETH_ADDR_LEN];
  err = esp_read_mac(mac, ESP_MAC_WIFI_STA);
  ESP_RETURN_ON_ERROR(err, TAG, "read sta mac");

  SpiModuleCfg ethSpiCfg = {
    .CsGPIO = CONFIG_BBHW_ETH_CS_GPIO,
    .IntGPIO = CONFIG_BBHW_ETH_INT_GPIO,
    .PhyResetGPIO = CONFIG_BBHW_ETH_RST_GPIO,
    .PhyAddr = CONFIG_BBHW_ETH_PHY_ADDR ,
    .MacAddrPtr = mac,
  };
  ethHandle = ethInitSpi(ethSpiCfg, nullptr, nullptr);
  ESP_RETURN_ON_FALSE(ethHandle, ESP_FAIL, TAG, "SPI Ethernet init failed");

  return ESP_OK;
}

esp_netif_config_t NetEth::NetifConfig() const
{
  return {
    .base = &netifCfg,
    .driver = NULL,
    .stack = ESP_NETIF_NETSTACK_DEFAULT_ETH,
  };
}

esp_err_t NetEth::Attach(esp_netif_t* netif)
{
  assert(netif);
  // Attach Ethernet driver to TCP/IP stack
  ESP_RETURN_ON_ERROR(esp_netif_attach(netif, esp_eth_new_netif_glue(ethHandle)), TAG, "netif attach failed");

  // Register user defined event handers
  static EventsCtx eventCtx = {
    .NetCfg = this->netCfg,
    .Netif = netif,
  };
  ESP_RETURN_ON_ERROR(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, ethEventHandler, &eventCtx), TAG, "attach eth events");

  // Start network
  ESP_RETURN_ON_ERROR(esp_eth_start(ethHandle), TAG, "eth start");
  return ESP_OK;
}

#endif
