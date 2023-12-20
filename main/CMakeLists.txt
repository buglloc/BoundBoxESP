idf_component_register(
SRCS
  "commands.cc"
  "main.cc"
  "secrets.cc"
PRIV_REQUIRES
  esp_timer heap
  hardware ssh preferences defer
  arduinojson # assets lvgl
)
