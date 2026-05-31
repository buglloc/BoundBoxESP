#include <sdkconfig.h>
#include "net_usb.h"
#include "net_common.h"

#include <assert.h>
#include <atomic>
#include <cstring>

#include <tinyusb.h>
#include <tinyusb_default_config.h>
#include <tinyusb_net.h>

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
  static const char* TAG = "hardware::net::usb";
  constexpr size_t RX_POOL_SIZE = 8;
  constexpr size_t RX_BUFFER_SIZE = 1600;

  struct RxBuffer
  {
    std::atomic<bool> used{false};
    uint8_t data[RX_BUFFER_SIZE];
  };

  RxBuffer rxPool[RX_POOL_SIZE];

  void *rxBufferAlloc(size_t len)
  {
    if (len > RX_BUFFER_SIZE) {
      return nullptr;
    }

    for (auto& buf : rxPool) {
      bool expected = false;
      if (buf.used.compare_exchange_strong(expected, true)) {
        return buf.data;
      }
    }

    return nullptr;
  }

  bool rxBufferFree(void *buffer)
  {
    for (auto& buf : rxPool) {
      if (buf.data == buffer) {
        buf.used.store(false);
        return true;
      }
    }

    return false;
  }

  esp_err_t wired_send(void *buffer, uint16_t len, void *buff_free_arg)
  {
    return tinyusb_net_send_sync(buffer, len, buff_free_arg, pdMS_TO_TICKS(100));
  }

  static void l2_free(void *h, void *buffer)
  {
    if (!rxBufferFree(buffer)) {
      ESP_LOGW(TAG, "ignore unknown RX buffer free: %p", buffer);
    }
  }

  static esp_err_t netif_transmit (void *h, void *buffer, size_t len)
  {
    esp_err_t err = wired_send(buffer, len, NULL);
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "failed to send buffer to USB: %s", esp_err_to_name(err));
    }
    return err;
  }

  esp_err_t netif_recv_callback(void *buffer, uint16_t len, void *ctx)
  {
    esp_netif_t* netif = reinterpret_cast<esp_netif_t *>(ctx);
    if (!netif) {
      return ESP_OK;
    }

    void *buf_copy = rxBufferAlloc(len);
    if (!buf_copy) {
      ESP_LOGW(TAG, "drop RX packet: no buffer for %u bytes", static_cast<unsigned>(len));
      return ESP_ERR_NO_MEM;
    }
    std::memcpy(buf_copy, buffer, len);
    esp_err_t err = esp_netif_receive(netif, buf_copy, len, NULL);
    if (err != ESP_OK) {
      rxBufferFree(buf_copy);
    }
    return err;
  }
}

esp_err_t NetUsb::Initialize()
{
  tinyusb_config_t usbCfg = TINYUSB_CONFIG_FULL_SPEED(nullptr, nullptr);
  usbCfg.task.xCoreID = 0;
  esp_err_t err = tinyusb_driver_install(&usbCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "install TinyUSB driver");

  this->netifCfg = {
    .flags = static_cast<esp_netif_flags_t>(ESP_NETIF_FLAG_AUTOUP | ESP_NETIF_FLAG_EVENT_IP_MODIFIED),
    .ip_info = NetifIP(netCfg),
    .get_ip_event = IP_EVENT_STA_GOT_IP,
    .lost_ip_event = IP_EVENT_STA_LOST_IP,
    .if_key = "wired",
    .if_desc = "usb ncm config device",
    .route_prio = 10
  };

  err = PatchNetifCfg(netifCfg, netCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "patch netif cfg");

  this->driverCfg = {
    .handle = (void *)1,                // not using an instance, USB-NCM is a static singleton (must be != NULL)
    .transmit = netif_transmit,         // point to static Tx function
    .driver_free_rx_buffer = l2_free    // point to Free Rx buffer function
  };

  this->stackCfg = {
    .lwip = {
      .init_fn = ethernetif_init,
      .input_fn = ethernetif_input
    }
  };

  return ESP_OK;
}

esp_netif_config_t NetUsb::NetifConfig() const
{
  return {
    .base = &netifCfg,
    .driver = &driverCfg,
    .stack = &stackCfg,
  };
}

esp_err_t NetUsb::Attach(esp_netif_t* netif)
{
  assert(netif);

  tinyusb_net_config_t tinyNetCfg = {
    .on_recv_callback = netif_recv_callback,
    .user_context = netif,
  };

  uint8_t efuseMac[6];
  esp_err_t err = esp_efuse_mac_get_default(efuseMac);
  ESP_RETURN_ON_ERROR(err, TAG, "get EFUSE MAC");
  err = esp_derive_local_mac(tinyNetCfg.mac_addr, efuseMac);
  ESP_RETURN_ON_ERROR(err, TAG, "derive local MAC");

  err = tinyusb_net_init(&tinyNetCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "initialize USB Net device");

  uint8_t netifMac[6];
  err = esp_read_mac(netifMac, ESP_MAC_WIFI_SOFTAP);
  ESP_RETURN_ON_ERROR(err, TAG, "read softap mac");

  err = esp_netif_set_mac(netif, netifMac);
  ESP_RETURN_ON_ERROR(err, TAG, "set netif mac");

  // start the interface manually (as the driver has been started already)
  esp_netif_action_start(netif, 0, 0, 0);
  esp_netif_action_connected(netif, NULL, 0, NULL);
  SendGotIP(netif, NetifIP(netCfg));

  return ESP_OK;
}
