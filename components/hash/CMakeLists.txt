set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS")

idf_component_register(
SRCS
  "src/hash.cc"
INCLUDE_DIRS
  "include"
REQUIRES
  result
PRIV_REQUIRES
  wolfssl
)
