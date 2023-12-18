#include "t_amoled/temp.h"
#include "board_config.h"

#include <driver/temperature_sensor.h>

#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>

using namespace Amoled;

namespace
{
  static const char* TAG = "amoled::temp";
}

esp_err_t TempSensor::Initialize()
{
  temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);

  esp_err_t err = temperature_sensor_install(&temp_sensor_config, &sensor);
  ESP_RETURN_ON_ERROR(err, TAG, "install temp sensor");

  err = temperature_sensor_enable(sensor);
  ESP_RETURN_ON_ERROR(err, TAG, "enable temp sensor");
  return ESP_OK;
}

float TempSensor::CoreTemp()
{
  float out = 0.0;
  temperature_sensor_get_celsius(sensor, &out);
  return out;
}

TempSensor::~TempSensor()
{
  temperature_sensor_disable(sensor);
  temperature_sensor_uninstall(sensor);
}