idf_component_register(
SRCS
  "src/ssh_server.cc"
INCLUDE_DIRS
  "include"
PRIV_REQUIRES
  wolfssh wolfssl result lwip
)
