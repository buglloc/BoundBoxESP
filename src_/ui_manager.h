#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "gui.h"
#include "board_manager.h"
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
    OnPinEnteredCb OnPinEntered;
    OnPinVerifiedCb OnPinVerified;
  };

public:
  static TUIManager &Instance();
  bool Begin(EventHandlers handlers);
  void Tick(const TBoardManager::BoardInfo& boardInfo);
  void ShowRequestPin();
  void ShowVerifyPin(const String& verification);
  void ShowNotify(const String& msg);
  void ShowIdle();

private:
  TUIManager() = default;
  void tickHomeButton();
  void tickStateTransition();
  void tickBoardInfo(const TBoardManager::BoardInfo& boardInfo);
  void toState(State state);

private:
  TGUI gui;
  State curState;
  State targetState;
  uint32_t lastStateChange;
  TBoardManager::BoardInfo lastBoardInfo;

  EventHandlers callbacks;
  String notifyMsg;
  String pinVerification;
};

#endif