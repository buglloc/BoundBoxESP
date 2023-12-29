#pragma once

#include <functional>
#include <string>

#include <lvgl.h>

#include "ui/manager.h"


#define GUI_MESSAGE_PIN_PROMPT 100
#define GUI_MESSAGE_NOTIFY 101
#define GUI_MESSAGE_NEW_BOARD_STATE 110
#define GUI_MESSAGE_NEW_ADDR 111
#define GUI_MESSAGE_NEW_BATT_VOLTAGE 112
#define GUI_MESSAGE_NEW_CORE_TEMP 113
#define GUI_MESSAGE_NEW_ASSERTATIONS 114


namespace UI
{
  class GUI
  {
  public:
    GUI();
    void ShowScreenPinEnter();
    void ShowScreenPinVerify(const std::string& verification);
    void ShowScreenNotification(const std::string& msg);
    void ShowInfoScreen();

    ~GUI();
  private:
    lv_obj_t* createPage(lv_obj_t *screen);
    lv_obj_t* switchScreen(lv_obj_t *targetScreen);
    bool isPersistentScreen(lv_obj_t* scr);

  private:
    lv_obj_t* notifyScreen = nullptr;
    lv_obj_t* infoScreen = nullptr;
  };
}
