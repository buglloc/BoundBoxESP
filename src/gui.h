#ifndef GUI_H
#define GUI_H

#include <lvgl.h>

class TGUI
{
public:
  void Begin();

private:
  void initializeStatusTile(lv_obj_t* parent);
  void initializePinpadTile(lv_obj_t* parent);
  void initializeNotifyTile(lv_obj_t* parent);

private:
  lv_obj_t* tileView = nullptr;
};

#endif