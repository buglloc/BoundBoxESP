#pragma once

#include <esp_err.h>

#include <t_amoled/board.h>

#include "spi.h"
#include "net.h"

namespace Peripheral
{
  class Manager
  {
  public:
    Manager() = default;
    esp_err_t Initialize();

    Amoled::Board& Board()
    {
      return board;
    }

  private:
    bool initialized;
    Amoled::Board board;
    Spi spi;
    Net net;
  };
}
