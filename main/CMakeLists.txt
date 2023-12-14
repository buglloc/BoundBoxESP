set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWOLFSSL_USER_SETTINGS")

idf_component_register(
SRCS
  "main.cc"
  ${IMAGE_SOURCES}
INCLUDE_DIRS
  "."
REQUIRES
  esp_timer heap t_amoled assets lvgl
)
