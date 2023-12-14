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

    Display& GetDisplay()
    {
      return display;
    }

    TouchSensor& GetTouchSensor()
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
