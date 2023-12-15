#pragma once

#include <esp_err.h>


namespace Peripheral
{
  class Spi
  {
  public:
    Spi() = default;
    esp_err_t Initialize();
  };
}
