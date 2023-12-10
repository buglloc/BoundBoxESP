#ifndef GUI_H
#define GUI_H

#include "board_manager.h"
#include <Arduino.h>
#include <lvgl.h>
#include <functional>

#define GUI_MESSAGE_PIN_PROMPT 100
#define GUI_MESSAGE_UPDATE_BOARD_INFO 100

class TGUI
{
public:
  void Begin();
  void ShowScreenPinEnter();
  void ShowScreenPinVerify(const String& verification);
  void ShowScreenNotification(const String& title, const String& msg);
  void ShowScreenIdle(TBoardManager::BoardInfo boardInfo);

private:
  lv_obj_t* createPage();
  lv_obj_t* switchScreen();

private:
  lv_style_t mainStyle;
};

#endif