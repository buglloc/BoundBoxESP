#pragma once

#include <memory>
#include <functional>
#include <stdint.h>
#include <string>
#include <atomic>

#include <hardware/manager.h>

#include "button.h"
#include "scene.h"

namespace UI
{
  // fwd
  class GUI;

  enum class AppState: uint8_t
  {
    None,
    Boot,
    WaitNet,
    WaitCredential,
    Process,
    Idle,
  };

  class Handler
  {
  public:
    virtual void OnPinEnter(uint8_t ch) = 0;
    virtual void OnPinEntered(bool ok) = 0;
    virtual void OnPinVerified(bool ok) = 0;
  };

  class Manager
  {
  public:
    static Manager& Instance();
    esp_err_t Initialize(Handler* handler);

    void SetAppState(AppState appState);
    void ShowRequestPin();
    void ShowVerifyPin(const std::string& verification);
    void ShowNotify(const std::string& msg);
    void ShowIdle();

    void Tick();

  private:
    void tickHomeButton();
    void tickBoardInfo();
    void tickStateTransition();

  private:
    std::atomic<AppState> appState = AppState::Boot;
    std::unique_ptr<GUI> gui;
    Handler* handler = nullptr;
    SceneManager sceneManager;
    Button homeButton;
    std::string pinVerification;
    std::string notifyMsg;
    uint16_t updateTtlTicks = 0;
  };
}
