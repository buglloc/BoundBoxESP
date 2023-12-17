idf_component_register(
SRCS
  "src/manager.cc"
  "src/net_eth.cc"
  "src/net_wifi.cc"
  "src/net.cc"
INCLUDE_DIRS
  "include"
PRIV_REQUIRES
  driver esp_netif esp_eth esp_wifi esp_timer t_amoled nvs_flash
)
