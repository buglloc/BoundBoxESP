#ifndef GUI_H
#define GUI_H

#include <lvgl.h>
#include <vector>
#include <functional>

#define GUI_MESSAGE_PIN_PROMPT 100

class TGUI
{
public:
  using TPinHandler = std::function<void(int8_t val)>;

public:
  void Begin();
  void ShowScreenPinEnter();
  void ShowScreenPinCheck();
  void ShowScreenNotification();
  // void ShowScreenStatus();

  ~TGUI();
private:
  lv_obj_t* createPage();
  void clearScreen();

private:
  lv_obj_t* screen = nullptr;
  lv_style_t mainStyle;
};

#endif