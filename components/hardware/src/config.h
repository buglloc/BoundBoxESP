#pragma once

#include <sdkconfig.h>


#define ESP_INTR_FLAG_DEFAULT 0

#if CONFIG_BBHW_USE_SPI2_HOST
  #define BBHW_SPI_HOSTID SPI2_HOST
#elif CONFIG_BBHW_USE_SPI3_HOST
  #define BBHW_SPI_HOSTID SPI3_HOST
#else
  #error SPI host not configured
#endif

#if CONFIG_BBHW_NETKIND_ETH
  #define BBHW_SETUP_SPI 1
#endif
