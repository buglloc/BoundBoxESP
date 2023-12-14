#ifndef GUI_H
#define GUI_H

#include "board_config.h"
#include "board_manager.h"
#include <Arduino.h>
#include <lvgl.h>
#include <functional>

#define GUI_MESSAGE_PIN_PROMPT 100
#define GUI_MESSAGE_UPDATE_BOARD_INFO 101
#define GUI_MESSAGE_NOTIFY 102

class TGUI
{
public:
  void Begin();
  void ShowScreenPinEnter();
  void ShowScreenPinVerify(const String& verification);
  void ShowScreenNotification(const String& msg);
  void ShowScreenIdle(TBoardManager::BoardInfo boardInfo);

  ~TGUI();
private:
  lv_obj_t* createPage(lv_obj_t *screen);
  lv_obj_t* switchScreen(lv_obj_t *targetScreen);
  bool isPersistentScreen(lv_obj_t* scr);

private:
  lv_style_t mainStyle;
  lv_obj_t* notifyScreen = nullptr;
  lv_obj_t* idleScreen = nullptr;
};

#endif