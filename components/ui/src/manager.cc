#include <sdkconfig.h>
#include "ui/manager.h"
#include "gui.h"

#include <hardware/manager.h>
#include <lvgl.h>

#include <esp_check.h>


using namespace UI;

namespace
{
  static const char* TAG = "Manager::ui";
  Hardware::Manager& hw = Hardware::Manager::Instance();
}

Manager& Manager::Instance()
{
  static Manager instance;
  return instance;
}

esp_err_t Manager::Initialize(Handler* handler)
{
  ESP_LOGI(TAG, "initialize LVGL");
  ESP_RETURN_ON_ERROR(hw.Board().InitializeLVGL(), TAG, "LVGL initialization");

  ESP_LOGI(TAG, "initialize scene manager");
  ESP_RETURN_ON_ERROR(sceneManager.Initialize(), TAG, "scene manager initialization");

  ESP_LOGI(TAG, "create GUI");
  gui = std::make_unique<GUI>();
  handler = handler;

  ESP_LOGI(TAG, "initialize ui task timer");
  const esp_timer_create_args_t timerArgs = {
    .callback = [](void* arg) -> void {
      reinterpret_cast<Manager *>(arg)->Tick();
    },
    .arg = this,
    .name = "Manager::periodic"
  };
  ESP_RETURN_ON_ERROR(esp_timer_create(&timerArgs, &timer), TAG, "create timer");

  lv_msg_subscribe(GUI_MESSAGE_PIN_PROMPT,
    [](void* s, lv_msg_t* m) -> void {
      const int8_t* value = reinterpret_cast<const int8_t *>(lv_msg_get_payload(m));
      Handler* handler = reinterpret_cast<Handler *>(lv_msg_get_user_data(m));
      handler->OnPinEnter(*value);
    },
    &handler
  );

  ShowIdle();
  hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
  return ESP_OK;
}

void Manager::SetAppState(AppState newState)
{
  appState = newState;
}

void Manager::ShowRequestPin()
{
  sceneManager.SwitchTo(SceneId::PinRequest);
}

void Manager::ShowVerifyPin(const std::string& verification)
{
  pinVerification = verification;
  sceneManager.SwitchTo(SceneId::PinVerify);
}

void Manager::ShowNotify(const std::string& msg)
{
  notifyMsg = msg;
  sceneManager.SwitchTo(SceneId::Notify);
}

void Manager::ShowIdle()
{
  sceneManager.SwitchTo(SceneId::Idle);
}

void Manager::Tick()
{
  tickHomeButton();
  tickBoardInfo();
  tickStateTransition();
}

void Manager::tickHomeButton()
{
  if (!homeButton.UpdateState(hw.Board().TouchSensor().HomePressed())) {
    // nothing to do
    return;
  }

  switch (sceneManager.Id()) {
  case SceneId::PinRequest:
    if (handler != nullptr) {
      handler->OnPinEntered(homeButton.State() == ButtonState::Short);
    }
    break;

  case SceneId::PinVerify:
    if (handler != nullptr) {
      handler->OnPinVerified(homeButton.State() == ButtonState::Short);
    }
    break;

  case SceneId::Notify:
    ShowIdle();
    break;

  case SceneId::Idle:
    if (hw.Board().Display().Brightness()) {
      hw.Board().Display().SetBrightness(0);
    } else {
      hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
    }
    break;

  default:
    ESP_LOGE(TAG, "unexpected state: %d", (int)sceneManager.Id());
  }
}

void Manager::tickBoardInfo()
{
  if (updateTtlTicks > 0) {
    updateTtlTicks--;
    return;
  }

  BoardInfo info = {
    .State = static_cast<BoardState>(appState.load()),
    .LocalAddr = hw.Net().LocalIP().addr,
    .BattVoltage = hw.Board().BattVoltage(),
    .CoreTemp = hw.Board().CoreTemp(),
  };
  lv_msg_send(GUI_MESSAGE_UPDATE_BOARD_INFO, &info);
  updateTtlTicks = (CONFIG_UI_UPDATE_INFO_PERIOD_MS /CONFIG_UI_PERIOD_TIME_MS);
}

void Manager::tickStateTransition()
{
  if (!sceneManager.UpdateState()) {
    // nothing to do
    return;
  }

  switch (sceneManager.Id()) {
  case SceneId::PinRequest:
    ESP_LOGI(TAG, "switch to pin request screen");
    gui->ShowScreenPinEnter();
    break;
  case SceneId::PinVerify:
    ESP_LOGI(TAG, "switch to pin verify screen");
    gui->ShowScreenPinVerify(pinVerification);
    break;
  case SceneId::Notify:
    ESP_LOGI(TAG, "switch to pin notify screen");
    gui->ShowScreenNotification(notifyMsg);
    break;
  case SceneId::Idle:
    ESP_LOGI(TAG, "switch to pin idle screen");
    gui->ShowScreenIdle();
    break;
  default:
    ESP_LOGE(TAG, "unexpected scene: %d", (int)sceneManager.Id());
    break;
  }
}

Manager::~Manager()
{
  esp_timer_stop(timer);
  esp_timer_delete(timer);
}