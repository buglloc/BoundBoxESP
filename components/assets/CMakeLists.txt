file(GLOB_RECURSE IMAGE_SOURCES *.c)

idf_component_register(
INCLUDE_DIRS
  "."
REQUIRES
  lvgl
)
