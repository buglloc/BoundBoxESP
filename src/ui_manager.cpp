#include "ui_manager.h"
#include "board_config.h"
#include "defaults.h"

#include <ArduinoLog.h>

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>

namespace
{
  static LilyGo_Class amoled;
  static lv_obj_t *label;
}

TUIManager& TUIManager::Instance()
{
  static TUIManager instance;
  return instance;
}

bool TUIManager::Begin()
{
  Log.infoln("UI manager starts");
  if (!amoled.beginAMOLED_191()) {
    Log.infoln("unable to start amoled display");
    return false;
  }

  beginLvglHelper(amoled);

  gui.Begin();
  // label = lv_label_create(lv_scr_act());
  // lv_label_set_text(label, "Touch test");
  // lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
  // lv_obj_center(label);

  amoled.setBrightness(DISPLAY_BRIGHTNESS);
  amoled.setHomeButtonCallback([](void *ptr) {
      static uint32_t checkMs = 0;
      static uint8_t lastBri = 0;
      if (millis() > checkMs) {
          if (amoled.getBrightness()) {
              lastBri = amoled.getBrightness();
              amoled.setBrightness(0);
          } else {
              amoled.setBrightness(lastBri);
          }
      }
      checkMs = millis() + 200;
  }, nullptr);

  Log.infoln("UI manager setup complete");
  return true;
}

void TUIManager::Tick()
{
    static int16_t x, y;
    // bool touched = amoled.getPoint(&x, &y);
    // if ( touched ) {
    //     Serial.printf("X:%d Y:%d\n", x, y);
    //     lv_label_set_text_fmt(label, "X:%d Y:%d", x, y);
    //     lv_obj_center(label);
    // }
    lv_task_handler();
}

#else

TUIManager& TUIManager::Instance()
{
  static TUIManager instance;
  return instance;
}

bool TUIManager::Begin()
{
  Log.infoln("no UI used=");
  return true;
}

void TUIManager::Tick()
{}
#endif