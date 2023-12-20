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
#include <ui/manager.h>
#include <ssh/server.h>

#include "errors.h"
#include "secrets.h"
#include "authenticator.h"
#include "commands.h"


namespace {
  static const char *TAG = "main";
  const TickType_t xWaitDelay = 100 / portTICK_PERIOD_MS;
  Hardware::Manager& hw = Hardware::Manager::Instance();
  UI::Manager& ui = UI::Manager::Instance();
  SSH::Server sshd;

  struct SshdCtx {
    SSH::Server& Srv;
    Commands& Handler;
  };

  void sshdTask(void *arg)
  {
    ESP_LOGI(TAG, "SSH task started");
    SshdCtx* ctx = reinterpret_cast<SshdCtx *>(arg);
    assert(ctx);

    const TickType_t sshDelay = 500 / portTICK_PERIOD_MS;
    SSH::ListenError listenErr;
    for (;;) {
      listenErr = ctx->Srv.Listen([ctx](const SSH::UserInfo& userInfo, const std::string_view cmd, SSH::Stream& stream) -> int {
        ui.SetAppState(UI::AppState::Process);

        Error err = ctx->Handler.Dispatch(userInfo, cmd, stream);
        if (err != Error::None) {
          ESP_LOGE(TAG, "command '%s' process failed: %d", cmd.cbegin(), (int)err);
        }

        ui.SetAppState(UI::AppState::Idle);
        return err != Error::None ? 1 : 0;
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

  ESP_LOGI(TAG, "initialize authenticator");
  Authenticator auth;
  SHUTDOWN_ON_ERROR(auth.Initialize(&secrets), TAG, "secrets initialize");

  ESP_LOGI(TAG, "initialize commands handler");
  Commands commandHandler;
  SHUTDOWN_ON_ERROR(commandHandler.Initialize(&auth), TAG, "commands handler");

  ESP_LOGI(TAG, "initialize UI");
  ESP_SHUTDOWN_ON_ERROR(ui.Initialize(&auth), TAG, "initialize UI");

  ESP_LOGI(TAG, "initialize sshd");
  {
    SSH::ServerConfig sshCfg = {
      .RootUser = CONFIG_ROOT_USERNAME,
      .RootKeys = {CONFIG_ROOT_KEY},
      .HostKey = secrets.HostKey(),
    };
    HALT_ASSERT(sshd.Initialize(sshCfg) == SSH::Error::None, TAG, "ssh initialize");
  }

  ESP_LOGI(TAG, "attach network");
  {
    ui.SetAppState(UI::AppState::WaitNet);
    ESP_SHUTDOWN_ON_ERROR(hw.Net().Attach(), TAG, "network attach");

    do {
      taskYIELD();
      vTaskDelay(xWaitDelay);
    } while (!hw.Net().Ready());
  }

  ESP_LOGI(TAG, "wait credentials");
  {
    ui.SetAppState(UI::AppState::WaitCredential);
    auth.BuildCredential();

    do {
      taskYIELD();
      vTaskDelay(xWaitDelay);
    } while (!auth.HasCredential());
  }

  ui.SetAppState(UI::AppState::Idle);
  SshdCtx sshdCtx = {
    .Srv = sshd,
    .Handler = commandHandler,
  };
  xTaskCreate(sshdTask, "sshd", CONFIG_SSHD_TASK_STACK_SIZE, &sshdCtx, tskIDLE_PRIORITY, nullptr);

  ESP_LOGI(TAG, "app initialized, switched to busy looping");
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  for (;;) {
      taskYIELD();
      vTaskDelay(xDelay);
  }
}
