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

    esp_err_t ScheduleRestart(uint16_t delayMs);
    void Restart();
    void Shutdown();

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
