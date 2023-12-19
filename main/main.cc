/* WOLFSSL_USER_SETTINGS is defined here only for the syntax highlighter
 * see CMakeLists.txt
#define WOLFSSL_USER_SETTINGS
 */

#include <sdkconfig.h>

#include <expected>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_check.h>
#include <esp_err.h>
#include <esp_log.h>

#include <hardware/manager.h>
#include <ssh/server.h>

#include "errors.h"
#include "secrets.h"

namespace {
  static const char *TAG = "main";
  Hardware::Manager& hw = Hardware::Manager::Instance();
  SSH::Server sshd;

  void sshdTask(void *arg)
  {
    ESP_LOGI(TAG, "SSH task started");
    SSH::Server* srv = reinterpret_cast<SSH::Server *>(arg);
    assert(srv);

    const TickType_t sshDelay = 500 / portTICK_PERIOD_MS;
    SSH::ListenError listenErr;
    for (;;) {
      listenErr = srv->Listen([](const SSH::UserInfo& userInfo, const std::string_view cmd, SSH::Stream& stream) -> bool {
        ESP_LOGI(TAG, "new command: %s", cmd.cbegin());
        return true;
      });

      if (listenErr != SSH::ListenError::None) {
        ESP_LOGE(TAG, "listen failed: %d", (int)listenErr);
      }

      taskYIELD();
      vTaskDelay(sshDelay);
    }
  }
}

extern "C" void app_main(void)
{
  ESP_LOGI(TAG, "initialize hardware");
  ESP_SHUTDOWN_ON_ERROR(hw.Initialize(), TAG, "initialize hardware");

  ESP_LOGI(TAG, "initialize secrets");
  Secrets secrets;
  SHUTDOWN_ON_ERROR(secrets.Initalize(), TAG, "secrets initialize");

  ESP_LOGI(TAG, "initialize sshd");
  {
    SSH::ServerConfig sshCfg = {
      .RootUser = CONFIG_ROOT_USERNAME,
      .RootKeys = {CONFIG_ROOT_KEY},
    };
    HALT_ASSERT(sshd.Initialize(sshCfg) == SSH::Error::None, TAG, "ssh initialize");
  }

  ESP_LOGI(TAG, "attach network");
  {
    ESP_SHUTDOWN_ON_ERROR(hw.Net().Attach(), TAG, "network attach");

    // Block for 500ms.
    const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
    do {
      ESP_LOGI(TAG, "Wait network");
      taskYIELD();
      vTaskDelay(xDelay);
    } while (!hw.Net().Ready());
  }

  xTaskCreate(sshdTask, "sshd", CONFIG_SSHD_TASK_STACK_SIZE, &sshd, tskIDLE_PRIORITY, nullptr);

  // TODO(buglloc): do something useful
  ESP_LOGI(TAG, "app initialized, switched to busy looping");
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  for (;;) {
      taskYIELD();
      vTaskDelay(xDelay);
  }
}
