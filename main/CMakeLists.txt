set(SRCS
  main.cc
)

idf_component_register(
SRCS
  "${SRCS}"
REQUIRES
  esp_timer heap esp_netif esp_eth esp_wifi t_amoled nvs_flash # assets lvgl
PRIV_REQUIRES
  wolfssh wolfssl peripheral
)
