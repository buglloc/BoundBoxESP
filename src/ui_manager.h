#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "gui.h"
#include <Arduino.h>
#include <result.h>
#include <functional>

class TUIManager
{
public:
  enum class Error: uint8_t
  {
    None,
    Internal
  };

  enum class State: uint8_t
  {
    None,
    PinRequest,
    PinVerify,
    Notify,
    Idle,
  };

  using OnPinCharCb = std::function<void(uint8_t ch)>;
  using OnPinEnteredCb = std::function<void(bool ok)>;
  using OnPinVerifiedCb = std::function<void(bool ok)>;

  struct EventHandlers
  {
    OnPinCharCb OnPinEnter;
    OnPinEnteredCb onPinEntered;
    OnPinVerifiedCb onPinVerified;
  };

public:
  static TUIManager &Instance();
  bool Begin(EventHandlers handlers);
  void Tick();
  void ShowRequestPin();
  void ShowVerifyPin(const String& verification);
  void ShowNotify(const String& title, const String& msg);
  void ShowIdle();

private:
  TUIManager() = default;
  void tickHomeButton();
  void tickStateTransition();
  void toState(State state);

private:
  TGUI gui;
  State curState;
  State targetState;

  EventHandlers callbacks;
  String notifyTitle;
  String notifyMsg;
  String pinVerification;
};

#endif