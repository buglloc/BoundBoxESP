#include <sdkconfig.h>
#include "ui/manager.h"
#include "gui.h"

#include <hardware/manager.h>
#include <defer.h>
#include <lvgl.h>

#include <esp_check.h>
#include <esp_log.h>


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
  this->gui = std::make_unique<GUI>();
  this->handler = handler;

  // use lvgl timer instead of esp timer due to:
  // If you want to use a task to create the graphic, you NEED to create a Pinned task
  // Otherwise there can be problem such as memory corruption and so on.
  // source: https://github.com/lvgl/lv_port_esp32/blob/cffa173c6e410965da12875103b934ec9d28f4e5/main/main.c#L64-L66
  ESP_LOGI(TAG, "initialize ui task timer");
  if (!hw.Board().GuiLock()) {
    return ESP_FAIL;
  }
  lv_timer_create([](lv_timer_t *t) {
    reinterpret_cast<Manager *>(lv_timer_get_user_data(t))->Tick();
  }, CONFIG_UI_PERIOD_TIME_MS, this);
  hw.Board().GuiUnlock();

  gui->SetPinPromptHandler([this](int8_t value) {
    if (this->handler != nullptr) {
      this->handler->OnPinEnter(value);
    }
  });

  ShowBoot();
  hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
  return ESP_OK;
}

void Manager::SetBoardState(UI::BoardState newState)
{
  boardState = newState;
}

UI::BoardState Manager::BoardState()
{
  return boardState.load();
}

void Manager::ShowBoot()
{
  sceneManager.SwitchTo(SceneId::Boot);
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

void Manager::ShowAssertation(const std::string& client)
{
  assertations++;
  notifyMsg = client;
  sceneManager.SwitchTo(SceneId::Notify);
}

void Manager::ShowInfo()
{
  sceneManager.SwitchTo(SceneId::Idle);
}

void Manager::Tick()
{
  tickHomeButton();
  tickStateTransition();
  tickBoardState();
  tickAssertations();
  tickBoardInfo();
}

void Manager::tickHomeButton()
{
  if (!homeButton.UpdateState(hw.Board().TouchSensor().HomePressed())) {
    // nothing to do
    return;
  }

  switch (sceneManager.Id()) {
  case SceneId::Boot:
    // do nothing
    break;

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
    ShowInfo();
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
  if (ticksToUpdate > 0) {
    ticksToUpdate--;
    return;
  }

  uint32_t newLocalAddr = hw.Net().LocalIP().addr;
  if (newLocalAddr != lastLocalAddr) {
    lastLocalAddr = newLocalAddr;
    if (gui != nullptr) {
      gui->UpdateLocalAddr(lastLocalAddr);
    }
  }

  uint32_t battVoltage = hw.Board().BattVoltage();
  if (battVoltage > 0) {
    if (gui != nullptr) {
      gui->UpdateBattVoltage(battVoltage);
    }
  }

  uint32_t coreTemp = hw.Board().CoreTemp();
  if (coreTemp > 0) {
    if (gui != nullptr) {
      gui->UpdateCoreTemp(coreTemp);
    }
  }

  ticksToUpdate = (CONFIG_UI_UPDATE_INFO_PERIOD_MS /CONFIG_UI_PERIOD_TIME_MS);
}

void Manager::tickBoardState()
{
  UI::BoardState newState = BoardState();
  if (newState == displayedBoardState) {
    return;
  }

  displayedBoardState = newState;
  if (gui != nullptr) {
    gui->UpdateBoardState(newState);
  }
}

void Manager::tickAssertations()
{
  uint32_t newAssertations = assertations.load();
  if (newAssertations == lastAssertations) {
    return;
  }

  lastAssertations = newAssertations;
  if (gui != nullptr) {
    gui->UpdateAssertations(newAssertations);
  }
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
    hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
    gui->ShowScreenPinEnter();
    break;
  case SceneId::PinVerify:
    ESP_LOGI(TAG, "switch to pin verify screen");
    hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
    gui->ShowScreenPinVerify(pinVerification);
    break;
  case SceneId::Notify:
    ESP_LOGI(TAG, "switch to notify screen");
    hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
    gui->ShowScreenNotification(notifyMsg);
    break;
  case SceneId::Boot:
    hw.Board().Display().SetBrightness(CONFIG_UI_DEFAULT_BRIGHTNESS);
    [[fallthrough]];
  case SceneId::Idle:
    ESP_LOGI(TAG, "switch to info screen");
    gui->ShowInfoScreen();
    gui->UpdateLocalAddr(hw.Net().LocalIP().addr);
    gui->UpdateAssertations(assertations.load());
    break;
  default:
    ESP_LOGE(TAG, "unexpected scene: %d", (int)sceneManager.Id());
    break;
  }
}
