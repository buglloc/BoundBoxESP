#pragma once

#include <esp_adc/adc_oneshot.h>

#include <esp_err.h>


namespace LilyGo
{
  class BatteryController
  {
  public:
    BatteryController() = default;
    ~BatteryController();
    esp_err_t Initialize();
    uint32_t BattVoltage();

  private:
    adc_unit_t adcUnit;
    adc_channel_t adcChannel;
    adc_oneshot_unit_handle_t adcHandle = nullptr;
    adc_cali_handle_t caliHandle = nullptr;
    bool doCalibration = false;
  };
}
