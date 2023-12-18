#pragma once

#include "display.h"
#include "touch.h"
#include "temp.h"
#include "batt.h"

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

    uint32_t BattVoltage()
    {
      return batteryController.BattVoltage();
    }

    float CoreTemp()
    {
      return tempSensor.CoreTemp();
    }

    Amoled::Display& Display()
    {
      return display;
    }

    Amoled::TouchSensor& TouchSensor()
    {
      return touchSensor;
    }

    Amoled::TempSensor& TempSensor()
    {
      return tempSensor;
    }

    Amoled::BatteryController& BatteryController()
    {
      return batteryController;
    }

  private:
    void guiTask(void *arg);

  private:
    Amoled::Display display;
    Amoled::TouchSensor touchSensor;
    Amoled::TempSensor tempSensor;
    Amoled::BatteryController batteryController;
  };
}
