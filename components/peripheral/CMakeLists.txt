idf_component_register(
SRCS
  "src/manager.cc"
  "src/net_eth.cc"
  "src/net.cc"
INCLUDE_DIRS
  "include"
PRIV_REQUIRES
  driver esp_eth esp_netif esp_timer t_amoled
)
