set(HW_SRCS
  "src/manager.cc"
  "src/net_common.cc"
  "src/net_usb.cc"
  "src/net_wifi.cc"
  "src/net.cc"
)

if(CONFIG_BBHW_HAS_ETH)
  list(APPEND HW_SRCS "src/net_eth.cc")
endif(CONFIG_BBHW_HAS_ETH)

idf_component_register(
SRCS
  ${HW_SRCS}
INCLUDE_DIRS
  "include"
REQUIRES
  esp_netif lilygo
PRIV_REQUIRES
  driver esp_eth esp_wifi esp_timer esp_tinyusb nvs_flash
)
