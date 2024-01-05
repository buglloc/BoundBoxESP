#pragma once

#include <esp_err.h>

#include <lilygo/board.h>

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

    LilyGo::Board& Board()
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
    LilyGo::Board board;
    Hardware::Net net;
  };
}
