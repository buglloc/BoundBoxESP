#include "ui_manager.h"
#include "board_config.h"
#include "defaults.h"

#include <ArduinoLog.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>

#define LOG_PREFIX "ui_manager: "

namespace
{
  static LilyGo_Class amoled;

  enum class PressState {
    None, Short, Long
  };

  PressState calcPressState(bool homePressed)
  {
    const uint32_t longPressMs = 500;
    static uint32_t pressedTime = 0;
    static bool seenPress, alreadyFired = false;

    if (homePressed) {
      if (!seenPress) {
        // new press
        pressedTime = millis();
        seenPress = true;
        return PressState::None;
      }

      if (!alreadyFired && millis() - pressedTime > longPressMs) {
        // fire event by long tap
        alreadyFired = true;
        return PressState::Long;
      }

      return PressState::None;
    }

    if (seenPress) {
      // release home button
      seenPress = false;

      if (!alreadyFired) {
        return millis() - pressedTime < longPressMs ? PressState::Short : PressState::Long;
      }

      alreadyFired = false;
      return PressState::None;
    }

    return PressState::None;
  }
}

TUIManager& TUIManager::Instance()
{
  static TUIManager instance;
  return instance;
}

bool TUIManager::Begin(EventHandlers handlers)
{
  callbacks = std::move(handlers);

  Log.infoln(LOG_PREFIX "starts");
  if (!amoled.beginAMOLED_191()) {
    Log.infoln(LOG_PREFIX "unable to start amoled display");
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
  ShowIdle();
  amoled.setBrightness(DISPLAY_BRIGHTNESS);
  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

void TUIManager::Tick(const TBoardManager::BoardInfo& boardInfo)
{
  tickHomeButton();
  tickBoardInfo(boardInfo);
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

void TUIManager::ShowNotify(const String& msg)
{
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

  static int16_t x, y = 0;

  bool homePressed = amoled.getPoint(&x, &y) && x == homeButtonX && y == homeButtonY;
  PressState pressState = calcPressState(homePressed);
  if (pressState == PressState::None) {
    return;
  }

  switch (curState) {
    case State::PinRequest: {
      if (callbacks.OnPinEntered != nullptr) {
        callbacks.OnPinEntered(pressState == PressState::Short);
      }
      break;
    }
    case State::PinVerify: {
      if (callbacks.OnPinVerified != nullptr) {
        callbacks.OnPinVerified(pressState == PressState::Short);
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
      Log.infoln(LOG_PREFIX "unexpected state: %d", curState);
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
      Log.verboseln(LOG_PREFIX "switch to pin request screen");
      gui.ShowScreenPinEnter();
      break;
    case State::PinVerify:
      Log.verboseln(LOG_PREFIX "switch to pin verify screen");
      gui.ShowScreenPinVerify(pinVerification);
      break;
    case State::Notify:
      Log.verboseln(LOG_PREFIX "switch to notify screen");
      gui.ShowScreenNotification(notifyMsg);
      break;
    case State::Idle:
      Log.verboseln(LOG_PREFIX "switch to idle");
      gui.ShowScreenIdle(lastBoardInfo);
      break;
    default:
      Log.infoln(LOG_PREFIX "unexpected state: %d", curState);
      return;
  }
}

void TUIManager::tickBoardInfo(const TBoardManager::BoardInfo& boardInfo)
{
  if (lastBoardInfo == boardInfo) {
    return;
  }

  lastBoardInfo = boardInfo;
  lv_msg_send(GUI_MESSAGE_UPDATE_BOARD_INFO, &lastBoardInfo);
}
