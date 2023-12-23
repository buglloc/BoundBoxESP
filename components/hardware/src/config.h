#pragma once

#include <sdkconfig.h>


#define ESP_INTR_FLAG_DEFAULT 0
#define BBHW_SPI_HOSTID NeedTooChooseSpiHost
#ifdef CONFIG_BBHW_USE_SPI2_HOST
  #undef BBHW_SPI_HOSTID
  #define BBHW_SPI_HOSTID SPI3_HOST
#endif
#ifdef CONFIG_BBHW_USE_SPI3_HOST
  #undef BBHW_SPI_HOSTID
  #define BBHW_SPI_HOSTID SPI3_HOST
#endif