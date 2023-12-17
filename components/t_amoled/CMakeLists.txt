idf_component_register(
SRCS
  "src/board.cc"
  "src/display.cc"
  "src/touch.cc"
INCLUDE_DIRS
  "include"
REQUIRES
  driver esp_lcd esp_lcd_touch_cst816s
  lvgl
PRIV_REQUIRES
  esp_timer heap esp_hw_support
)

# TODO(buglloc): fix me
idf_build_set_property(COMPILE_OPTIONS "-Wno-missing-field-initializers" APPEND)
