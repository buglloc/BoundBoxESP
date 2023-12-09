#include "ui_manager.h"
#include "board_config.h"
#include "defaults.h"

#include <ArduinoLog.h>

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>

namespace
{
  static LilyGo_Class amoled;
  static lv_obj_t *label;
  static uint32_t homeButtonPressedAt;
}

TUIManager& TUIManager::Instance()
{
  static TUIManager instance;
  return instance;
}

bool TUIManager::Begin(EventHandlers handlers)
{
  callbacks = std::move(handlers);

  Log.infoln("UI manager starts");
  if (!amoled.beginAMOLED_191()) {
    Log.infoln("unable to start amoled display");
    return false;
  }
  beginLvglHelper(amoled);

  if (callbacks.OnPinEnter != nullptr) {
    lv_msg_subscribe(GUI_MESSAGE_PIN_PROMPT,
      [](void* s, lv_msg_t* m) -> void {
        const int8_t* value = reinterpret_cast<const int8_t*>(lv_msg_get_payload(m));
        OnPinCharCb* cb = reinterpret_cast<OnPinCharCb*>(lv_msg_get_user_data(m));
        (*cb)(*value);
      },
      &callbacks.OnPinEnter
    );
  }

  gui.Begin();
  gui.ShowScreenIdle();
  amoled.setBrightness(DISPLAY_BRIGHTNESS);
  Log.infoln("UI manager setup complete");
  return true;
}

void TUIManager::Tick()
{
  tickHomeButton();
  tickStateTransition();
  lv_task_handler();
}

void TUIManager::ShowRequestPin()
{
  toState(State::PinRequest);
}

void TUIManager::ShowVerifyPin(const String& toVerify)
{
  pinVerification = toVerify;
  toState(State::PinVerify);
}

void TUIManager::ShowNotify(const String& title, const String& msg)
{
  notifyTitle = title;
  notifyMsg = msg;
  toState(State::Notify);
}

void TUIManager::ShowIdle()
{
  toState(State::Idle);
}

void TUIManager::toState(State state)
{
  targetState = state;
  curState = State::None;
}

void TUIManager::tickHomeButton()
{
  // https://github.com/Xinyuan-LilyGO/LilyGo-AMOLED-Series/blob/36186b2cc6da7648064a4ce290142bd25268d19e/libdeps/SensorLib/src/TouchDrvCSTXXX.hpp#L143
  const int16_t homeButtonX = 600;
  const int16_t homeButtonY = 120;

  const uint32_t longPressMs = 500;
  enum class PressState {
    None, Short, Long
  };

  static int16_t x, y = 0;
  static uint32_t pressedTime = 0;
  static bool seenPress = false;

  bool wasPressed = amoled.getPoint(&x, &y) && x == homeButtonX && y == homeButtonY;
  if (wasPressed == seenPress) {
    return;
  }

  PressState press = PressState::None;
  if (wasPressed && !seenPress) {
    pressedTime = millis();
  } else if (!wasPressed && seenPress) {
    press = millis() - pressedTime < longPressMs ? PressState::Short : PressState::Long;
  }

  seenPress = wasPressed;
  if (press == PressState::None) {
    return;
  }

  switch (curState) {
    case State::PinRequest: {
      if (callbacks.onPinEntered != nullptr) {
        Log.infoln("aaaa: %d", press == PressState::Short);
        callbacks.onPinEntered(press == PressState::Short);
      }
      break;
    }
    case State::PinVerify: {
      if (callbacks.onPinVerified != nullptr) {
        callbacks.onPinVerified(press == PressState::Short);
      }
      break;
    }
    case State::Idle: {
      static uint32_t checkMs = 0;
      static uint8_t lastBri = 0;
      if (millis() > checkMs) {
        if (amoled.getBrightness()) {
            lastBri = amoled.getBrightness();
            amoled.setBrightness(0);
        } else {
            amoled.setBrightness(lastBri);
        }
      }
      checkMs = millis() + 200;
      break;
    }
    default:
      Log.infoln("ui: unexpected state: %d", curState);
      return;
  }
}

void TUIManager::tickStateTransition()
{
  if (curState == targetState) {
    return;
  }

  curState = targetState;
  switch (curState) {
    case State::PinRequest:
      gui.ShowScreenPinEnter();
      break;
    case State::PinVerify:
      gui.ShowScreenPinVerify(pinVerification);
      break;
    case State::Idle:
      gui.ShowScreenNotification(notifyTitle, notifyMsg);
      break;
    default:
      Log.infoln("ui: unexpected state: %d", curState);
      return;
  }
}

#else

TUIManager& TUIManager::Instance()
{
  static TUIManager instance;
  return instance;
}

bool TUIManager::Begin()
{
  Log.infoln("no UI used");
  return true;
}

void TUIManager::Tick()
{}

void TUIManager::RequestPin()
{
  pinDoneCb(false);
}

void TUIManager::Notify(const String& title, const String& msg)
{}

#endif
