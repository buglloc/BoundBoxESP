#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "display.h"
#include "touch.h"
#include "temp.h"
#include "batt.h"

namespace LilyGo
{
  class Board
  {
  public:
    Board() = default;
    esp_err_t Initialize();
    esp_err_t InitializeLVGL();

    void Restart();
    void Shutdown();

    bool GuiLock();
    void GuiUnlock();

    uint32_t BattVoltage()
    {
      return batteryController.BattVoltage();
    }

    float CoreTemp()
    {
      return tempSensor.CoreTemp();
    }

    LilyGo::Display& Display()
    {
      return display;
    }

    LilyGo::TouchSensor& TouchSensor()
    {
      return touchSensor;
    }

    LilyGo::TempSensor& TempSensor()
    {
      return tempSensor;
    }

    LilyGo::BatteryController& BatteryController()
    {
      return batteryController;
    }

  private:
    void guiTask(void *arg);

  private:
    SemaphoreHandle_t guiMu;
    LilyGo::Display display;
    LilyGo::TouchSensor touchSensor;
    LilyGo::TempSensor tempSensor;
    LilyGo::BatteryController batteryController;
  };
}
