#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl.h>
#include <functional>

#define GUI_MESSAGE_PIN_PROMPT 100

class TGUI
{
public:
  void Begin();
  void ShowScreenPinEnter();
  void ShowScreenPinVerify(const String& verification);
  void ShowScreenNotification(const String& title, const String& msg);
  void ShowScreenIdle();

  ~TGUI();
private:
  lv_obj_t* createPage();
  void clearScreen();

private:
  lv_obj_t* screen = nullptr;
  lv_style_t mainStyle;
};

#endif