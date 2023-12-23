idf_component_register(
SRCS
  "src/manager.cc"
  "src/net_eth.cc"
  "src/net_wifi.cc"
  "src/net.cc"
INCLUDE_DIRS
  "include"
REQUIRES
  esp_netif t_amoled
PRIV_REQUIRES
  driver esp_eth esp_wifi esp_timer nvs_flash
)
