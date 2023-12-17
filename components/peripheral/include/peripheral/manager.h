#pragma once

#include <esp_err.h>

#include <t_amoled/board.h>

#include "net.h"

namespace Peripheral
{
  class Manager
  {
  public:
    static Manager &Instance();

    esp_err_t Initialize();

    Amoled::Board& Board()
    {
      return board;
    }

    Peripheral::Net& Net()
    {
      return net;
    }

  private:
    Manager() = default;

  private:
    bool initialized;
    Amoled::Board board;
    Peripheral::Net net;
  };
}
