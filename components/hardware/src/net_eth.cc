#include "config.h"
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


using namespace Hardware;

namespace
{
  static const char* TAG = "hardware::net::eth";

  typedef struct {
    uint8_t spi_cs_gpio;
    uint8_t int_gpio;
    int8_t phy_reset_gpio;
    uint8_t phy_addr;
    uint8_t *mac_addr;
  } spi_eth_module_config_t;

  // copied from esp-idf ethernet example
  esp_eth_handle_t ethInitSpi(const spi_eth_module_config_t& cfg, esp_eth_mac_t** mac_out, esp_eth_phy_t** phy_out)
  {
    esp_eth_handle_t ret = NULL;

    // Init common MAC and PHY configs to default
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();

    // Update PHY config based on board specific configuration
    phy_config.phy_addr = cfg.phy_addr;
    phy_config.reset_gpio_num = cfg.phy_reset_gpio;

    // Configure SPI interface for specific SPI module
    spi_device_interface_config_t spi_devcfg = {
      .mode = 0,
      .clock_speed_hz = CONFIG_BBHW_ETH_SPI_CLOCK_MHZ * 1000 * 1000,
      .spics_io_num = cfg.spi_cs_gpio,
      .queue_size = 20,
    };

    eth_w5500_config_t w5500_config = ETH_W5500_DEFAULT_CONFIG(BBHW_SPI_HOSTID, &spi_devcfg);
    w5500_config.int_gpio_num = cfg.int_gpio;
    esp_eth_mac_t* mac = esp_eth_mac_new_w5500(&w5500_config, &mac_config);
    esp_eth_phy_t* phy = esp_eth_phy_new_w5500(&phy_config);

    // Init Ethernet driver to default and install it
    esp_eth_handle_t eth_handle = nullptr;
    esp_eth_config_t eth_config_spi = ETH_DEFAULT_CONFIG(mac, phy);
    ESP_GOTO_ON_FALSE(esp_eth_driver_install(&eth_config_spi, &eth_handle) == ESP_OK, NULL, err, TAG, "SPI Ethernet driver install failed");

    // The SPI Ethernet module might not have a burned factory MAC address, we can set it manually.
    if (cfg.mac_addr != NULL) {
      ESP_GOTO_ON_FALSE(esp_eth_ioctl(eth_handle, ETH_CMD_S_MAC_ADDR, cfg.mac_addr) == ESP_OK,
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
    uint8_t mac_addr[6] = {0};
    /* we can get the ethernet driver handle from event data */
    esp_eth_handle_t* eth_handle = reinterpret_cast<esp_eth_handle_t *>(event_data);
    esp_netif_t* netif =  reinterpret_cast<esp_netif_t *>(arg);

    switch (event_id) {
    case ETHERNET_EVENT_CONNECTED:
      esp_eth_ioctl(*eth_handle, ETH_CMD_G_MAC_ADDR, mac_addr);
      ESP_LOGI(TAG, "Ethernet Link Up");
      ESP_LOGI(TAG, "Ethernet HW Addr %02x:%02x:%02x:%02x:%02x:%02x",
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
      SetIPInfo(netif);
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
  }
}

esp_err_t NetEth::Initialize()
{
  memcpy(&netifCfg, ESP_NETIF_BASE_DEFAULT_ETH, sizeof(netifCfg));
  PatchNetifCfg(netifCfg);

  spi_eth_module_config_t spi_eth_module_config = {
    .spi_cs_gpio = CONFIG_BBHW_ETH_CS_GPIO,
    .int_gpio = CONFIG_BBHW_ETH_INT_GPIO,
    .phy_reset_gpio = CONFIG_BBHW_ETH_RST_GPIO,
    .phy_addr = CONFIG_BBHW_ETH_PHY_ADDR,
  };

  // The SPI Ethernet module(s) might not have a burned factory MAC address, hence use manually configured address(es).
  // In this example, Locally Administered MAC address derived from ESP32x base MAC address is used.
  // Note that Locally Administered OUI range should be used only when testing on a LAN under your control!
  uint8_t base_mac_addr[ETH_ADDR_LEN];
  ESP_RETURN_ON_ERROR(esp_efuse_mac_get_default(base_mac_addr), TAG, "get EFUSE MAC failed");
  uint8_t local_mac_1[ETH_ADDR_LEN];
  esp_derive_local_mac(local_mac_1, base_mac_addr);
  spi_eth_module_config.mac_addr = local_mac_1;

  ethHandle = ethInitSpi(spi_eth_module_config, nullptr, nullptr);
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
  ESP_RETURN_ON_ERROR(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, ethEventHandler, (void *)netif), TAG, "attach eth events");

  // Start network
  ESP_RETURN_ON_ERROR(esp_eth_start(ethHandle), TAG, "eth start");
  return ESP_OK;
}
