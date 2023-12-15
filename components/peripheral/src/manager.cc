#include "peripheral/manger.h"
#include "peripheral_config.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#include <esp_event.h>
#include <esp_check.h>
#include <esp_log.h>


using namespace Peripheral;

namespace
{
  static const char* TAG = "peripheral";
}

esp_err_t Manager::Initialize()
{
  if (initialized) {
    return ESP_OK;
  }

  ESP_RETURN_ON_ERROR(esp_event_loop_create_default(), TAG, "failed to initialize default event loop");
  // ESP_RETURN_ON_ERROR(board.Initialize(), TAG, "failed to initialize T-Amoled board");
  ESP_RETURN_ON_ERROR(spi.Initialize(), TAG, "failed to initialize SPI");
  NetConfig netCfg;
  ESP_RETURN_ON_ERROR(net.Initialize(netCfg), TAG, "failed to initialize Network");

  initialized = true;
  return ESP_OK;
}
