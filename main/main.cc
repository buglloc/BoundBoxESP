/* WOLFSSL_USER_SETTINGS is defined here only for the syntax highlighter
 * see CMakeLists.txt
#define WOLFSSL_USER_SETTINGS
 */

#include "sdkconfig.h"


#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_event.h>
#include <esp_log.h>

#include <peripheral/manager.h>

namespace {
  static const char *TAG = "main";
  static Peripheral::Manager peripheral;
}

extern "C" void app_main(void)
{
  ESP_ERROR_CHECK(peripheral.Initialize());
  ESP_ERROR_CHECK(peripheral.Net().Attach());

  // Block for 500ms.
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  do {
    ESP_LOGI(TAG, "Wait network");
    taskYIELD();
    vTaskDelay(xDelay);
  } while (!peripheral.Net().Ready());

  for (;;) {
    ESP_LOGI(TAG, "heartbit");
    taskYIELD();
    vTaskDelay(xDelay);
  }
}
