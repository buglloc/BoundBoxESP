idf_component_register(
SRCS
  "main.cc"
  "secrets.cc"
PRIV_REQUIRES
  esp_timer heap # assets lvgl
  hardware ssh preferences
)
