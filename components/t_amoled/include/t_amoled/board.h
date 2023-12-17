#pragma once

#include "display.h"
#include "touch.h"


namespace Amoled
{
  class Board
  {
  public:
    Board() = default;
    esp_err_t Initialize();
    esp_err_t InitializeLVGL();

    void Restart();
    void Shutdown();

    Amoled::Display& Display()
    {
      return display;
    }

    Amoled::TouchSensor& TouchSensor()
    {
      return ts;
    }

  private:
    void guiTask(void *arg);

  private:
    Amoled::Display display;
    Amoled::TouchSensor ts;
  };
}
