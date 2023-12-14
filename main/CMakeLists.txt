set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS")

set(SRCS
  main.c
  ssh_server.c
  uart_helper.c
  uart_helper.c
  wifi.c
  ssh_server_config.c
  int_to_string.c
  tx_rx_buffer.c
)

idf_component_register(
SRCS
  "${SRCS}"
INCLUDE_DIRS
  "."
REQUIRES
  esp_timer heap esp_netif esp_eth esp_wifi t_amoled nvs_flash # assets lvgl
PRIV_REQUIRES
  wolfssh wolfssl 
)
