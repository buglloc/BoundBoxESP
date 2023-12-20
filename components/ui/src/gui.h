#pragma once

#include <functional>
#include <string>

#include <lvgl.h>


#define GUI_MESSAGE_PIN_PROMPT 100
#define GUI_MESSAGE_UPDATE_BOARD_INFO 101
#define GUI_MESSAGE_NOTIFY 102

namespace UI
{
  enum class BoardState: uint8_t
  {
    None,
    Boot,
    WaitNet,
    WaitCredential,
    Process,
    Idle,
  };

  struct BoardInfo
  {
    BoardState State;
    uint32_t LocalAddr;
    uint32_t BattVoltage;
    float CoreTemp;
  };

  class GUI
  {
  public:
    GUI();
    void ShowScreenPinEnter();
    void ShowScreenPinVerify(const std::string& verification);
    void ShowScreenNotification(const std::string& msg);
    void ShowScreenIdle();

    ~GUI();
  private:
    lv_obj_t* createPage(lv_obj_t *screen);
    lv_obj_t* switchScreen(lv_obj_t *targetScreen);
    bool isPersistentScreen(lv_obj_t* scr);

  private:
    lv_style_t mainStyle;
    lv_obj_t* notifyScreen = nullptr;
    lv_obj_t* idleScreen = nullptr;
  };
}
