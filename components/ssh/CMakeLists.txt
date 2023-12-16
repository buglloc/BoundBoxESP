idf_component_register(
SRCS
  "src/auth.cc"
  "src/common.cc"
  "src/server.cc"
  "src/stream.cc"
INCLUDE_DIRS
  "include"
PRIV_REQUIRES
  wolfssh wolfssl lwip defer base64
)
