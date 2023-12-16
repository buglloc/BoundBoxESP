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

#include <peripheral/manger.h>

namespace {
  static const char *TAG = "main";
  Peripheral::Manager peripheral;

  void init()
  {
    ESP_ERROR_CHECK(peripheral.Initialize());

  }
}

extern "C" void app_main(void)
{
  init();

  // Block for 500ms.
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  for (;;) {
    /* we're not actually doing anything here, other than a heartbeat message */
    ESP_LOGI(TAG,"wolfSSH Server main loop heartbeat!");

    taskYIELD();
    vTaskDelay(xDelay); /* Minimum delay = 1 tick */
  }
}
