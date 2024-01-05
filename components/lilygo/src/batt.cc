#include "lilygo/batt.h"
#include "board_config.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>

using namespace LilyGo;

namespace
{
  static const char* TAG = "lilygo::batt";

  bool iniAdcCalibration(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *outHandle)
  {
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

  #if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
      ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
      adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = unit,
        .chan = channel,
        .atten = atten,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
      };
      ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
      if (ret == ESP_OK) {
        calibrated = true;
      }
    }
  #endif

  #if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
      ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
      adc_cali_line_fitting_config_t cali_config = {
        .unit_id = unit,
        .atten = atten,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
      };
      ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
      if (ret == ESP_OK) {
        calibrated = true;
      }
    }
  #endif

    *outHandle = handle;
    if (ret == ESP_OK) {
      ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
      ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
      ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
  }
}

esp_err_t BatteryController::Initialize()
{
  adc_oneshot_unit_init_cfg_t initCfg = {
      .unit_id = BATT_ADC_UNIT,
  };
  esp_err_t err = adc_oneshot_new_unit(&initCfg, &adcHandle);
  ESP_RETURN_ON_ERROR(err, TAG, "create one shot unit");

  adc_oneshot_chan_cfg_t chanCfg = {
    .atten = BATT_ADC_ATTEN,
    .bitwidth = BATT_ADC_WIDTH_BIT,
  };
  err = adc_oneshot_config_channel(adcHandle, BATT_ADC_CHANNEL, &chanCfg);
  ESP_RETURN_ON_ERROR(err, TAG, "configure channel");

  doCalibration = iniAdcCalibration(BATT_ADC_UNIT, BATT_ADC_CHANNEL, BATT_ADC_ATTEN, &caliHandle);

  return ESP_OK;
}

uint32_t BatteryController::BattVoltage()
{
  if (!doCalibration) {
    return 0;
  }

  int adcRaw = 0;
  int voltage = 0;
  esp_err_t err = adc_oneshot_read(adcHandle, BATT_ADC_CHANNEL, &adcRaw);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "adc read fail: %d", err);
    return 0;
  }

  err = adc_cali_raw_to_voltage(caliHandle, adcRaw, &voltage);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "adc calibration failed: %d", err);
    return 0;
  }

  return voltage * 2;
}

BatteryController::~BatteryController()
{
  adc_oneshot_del_unit(adcHandle);
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  adc_cali_delete_scheme_curve_fitting(caliHandle);

#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
  adc_cali_delete_scheme_line_fitting(caliHandle);
#endif
}
