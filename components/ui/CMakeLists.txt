file(GLOB_RECURSE IMAGE_SOURCES assets/*.c)

idf_component_register(
SRCS
  "src/button.cc"
  "src/gui.cc"
  "src/manager.cc"
  "src/scene.cc"
  ${IMAGE_SOURCES}
INCLUDE_DIRS
  "include"
REQUIRES
  hardware
PRIV_REQUIRES
  esp_timer
  defer
  lvgl
)
