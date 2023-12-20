#pragma once

#include <esp_err.h>

#include <t_amoled/board.h>

#include "net.h"

namespace Hardware
{
  class Manager
  {
  public:
    static Manager& Instance();

    esp_err_t Initialize();

    Amoled::Board& Board()
    {
      return board;
    }

    Hardware::Net& Net()
    {
      return net;
    }

  private:
    Manager() = default;

  private:
    bool initialized;
    Amoled::Board board;
    Hardware::Net net;
  };
}
