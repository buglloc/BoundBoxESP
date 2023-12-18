#pragma once

#include <driver/temperature_sensor.h>

#include <esp_err.h>

// fwd
struct adc_oneshot_unit_ctx_t;
typedef struct adc_oneshot_unit_ctx_t *adc_oneshot_unit_handle_t;
struct adc_cali_scheme_t;
typedef struct adc_cali_scheme_t *adc_cali_handle_t;


namespace Amoled
{
  class BatteryController
  {
  public:
    BatteryController() = default;
    ~BatteryController();
    esp_err_t Initialize();
    uint32_t BattVoltage();

  private:
    adc_oneshot_unit_handle_t adcHandle = nullptr;
    adc_cali_handle_t caliHandle = nullptr;
    bool doCalibration = false;
  };
}
