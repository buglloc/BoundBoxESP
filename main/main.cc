/* WOLFSSL_USER_SETTINGS is defined here only for the syntax highlighter
 * see CMakeLists.txt
#define WOLFSSL_USER_SETTINGS
 */

#include "sdkconfig.h"

#include <expected>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_timer.h>
#include <esp_check.h>
#include <esp_err.h>
#include <esp_log.h>

#include <hardware/manager.h>
#include <ssh/server.h>

#include "common.h"


namespace {
  static const char *TAG = "main";
  Hardware::Manager& hw = Hardware::Manager::Instance();
  SSH::Server sshd;
}

extern "C" void app_main(void)
{
  ESP_SHUTDOWN_ON_ERROR(hw.Initialize(), TAG, "initialize hardware");

  SSH::ServerConfig sshCfg = {
    .RootUser = "buglloc",
    .RootKeys = {"ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDD5skB0CnUQOBUMFdiwQRzf0Zg/B9gKsAsB+3IuPPP+OS5qeq1YkFjq3BtQiV+AwhKUIk/72+H4usTul2Z2BQ+BQeuzua9/Ht7VhdlqJYgC4h2mJ/hPeWnSPjzzjvY5Ar9G+EuGEtYyMaQ3fZ+0XqnvrXs4ENEpQ5angPfD77XDX1xzTw3JjjdIFqnFH/F/P3VJuypx9eTwVLqCH0yFQsUC+qFy1pQJYB8DUrMHtVPsl27Zd2EwZnCyC1ADEQiV1xTb+kiBK6jejydWpZqjHEDVaU8TDkkfk11NzhJx8+3hvcsA4/y5L+VECkUhQB3JhloOuQd0QKSrEMrcdEzp+o7 buglloc@bogs"},
  };
  SSH::Error sshErr = sshd.Initialize(sshCfg);
  TRUE_OR_SHUTDOWN(sshErr != SSH::Error::None, TAG, "ssh initialize");

  ESP_SHUTDOWN_ON_ERROR(hw.Net().Attach(), TAG, "network attach");

  // Block for 500ms.
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  do {
    ESP_LOGI(TAG, "Wait network");
    taskYIELD();
    vTaskDelay(xDelay);
  } while (!hw.Net().Ready());

  const TickType_t sshDelay = 100 / portTICK_PERIOD_MS;
  SSH::ListenError listenErr;
  for (;;) {
    listenErr = sshd.Listen([](const SSH::UserInfo& userInfo, const std::string& cmd, SSH::Stream& stream) -> bool {
      ESP_LOGI(TAG, "new command: %s", cmd.c_str());
      return true;
    });

    if (listenErr != SSH::ListenError::None) {
      ESP_LOGE(TAG, "listen failed: %d", (int)listenErr);
    }

    taskYIELD();
    vTaskDelay(sshDelay);
  }
}
