#pragma once

#include <driver/temperature_sensor.h>

#include <esp_err.h>


namespace Amoled
{
  class TempSensor
  {
  public:
    TempSensor() = default;
    ~TempSensor();
    esp_err_t Initialize();

    float CoreTemp();

  private:
    temperature_sensor_handle_t sensor = nullptr;
  };
}
