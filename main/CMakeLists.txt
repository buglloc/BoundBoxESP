idf_component_register(
SRCS
  "authenticator.cc"
  "commands.cc"
  "main.cc"
  "secrets.cc"
REQUIRES
  esp_timer heap
  hardware ssh preferences defer
  arduinojson ui
)
