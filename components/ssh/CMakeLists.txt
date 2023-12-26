idf_component_register(
SRCS
  "src/auth_provider.cc"
  "src/keyring.cc"
  "src/keys.cc"
  "src/server.cc"
  "src/stream.cc"
INCLUDE_DIRS
  "include"
REQUIRES
  blob LibSSH-ESP32
PRIV_REQUIRES
  lwip defer
)
