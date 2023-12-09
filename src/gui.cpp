#include "gui.h"
#include <lvgl.h>
#include <functional>
#include <string>
#include <algorithm>

LV_FONT_DECLARE(font_roboto_black_14);
LV_FONT_DECLARE(font_roboto_black_20);
LV_FONT_DECLARE(font_roboto_black_24);

LV_IMG_DECLARE(pad_icon_00);
LV_IMG_DECLARE(pad_icon_01);
LV_IMG_DECLARE(pad_icon_02);
LV_IMG_DECLARE(pad_icon_03);
LV_IMG_DECLARE(pad_icon_04);
LV_IMG_DECLARE(pad_icon_05);
LV_IMG_DECLARE(pad_icon_06);
LV_IMG_DECLARE(pad_icon_07);
LV_IMG_DECLARE(pad_icon_08);
LV_IMG_DECLARE(pad_icon_09);
LV_IMG_DECLARE(pad_icon_10);
LV_IMG_DECLARE(pad_icon_11);
LV_IMG_DECLARE(pad_icon_12);
LV_IMG_DECLARE(pad_icon_13);
LV_IMG_DECLARE(pad_icon_14);
LV_IMG_DECLARE(pad_icon_15);

LV_IMG_DECLARE(bg_notify);


namespace {
  struct padInfo {
    int8_t Value;
    const void* ImgSrc;
  };

  static padInfo pinPads[] = {
    { 1,  &pad_icon_00 },
    { 2,  &pad_icon_01 },
    { 3,  &pad_icon_02 },
    { 4,  &pad_icon_03 },
    { 5,  &pad_icon_04 },
    { 6,  &pad_icon_05 },
    { 7,  &pad_icon_06 },
    { 8,  &pad_icon_07 },
    { 9,  &pad_icon_08 },
    { 10, &pad_icon_09 },
    { 11, &pad_icon_10 },
    { 12, &pad_icon_11 },
    { 13, &pad_icon_12 },
    { 14, &pad_icon_13 },
    { 15, &pad_icon_14 },
    { 16, &pad_icon_15 },
  };
}

namespace {
  static lv_color_t bgColor = lv_color_hex(0xd4d4d4);
  static lv_color_t panBgColor = lv_color_hex(0xfafafa);
  static lv_color_t textColor = lv_color_hex(0x030303);
  static lv_color_t pressedColor = lv_color_hex(0x939ea3);

  lv_obj_t* createPadButton(lv_obj_t* parent, bool clickable, size_t idx)
  {
    lv_obj_t *btn = lv_obj_create(parent);
    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_style_border_width(btn, 0, 0);
    lv_obj_set_style_bg_color(btn, panBgColor, LV_STATE_DEFAULT);
    lv_obj_remove_style(btn, 0, LV_PART_SCROLLBAR);
    lv_obj_set_style_border_width(btn, 0, 0);

    lv_obj_t* img = lv_img_create(btn);
    lv_img_set_src(img, pinPads[idx].ImgSrc);

    if (clickable) {
      lv_obj_set_style_bg_color(btn, pressedColor, LV_STATE_PRESSED);
      lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
      lv_obj_set_user_data(btn, &pinPads[idx].Value);
      lv_obj_add_event_cb(btn,
        [](lv_event_t* event) -> void {
          lv_obj_t* padButton = lv_event_get_target(event);
          int8_t* value = reinterpret_cast<int8_t*>(lv_obj_get_user_data(padButton));
          lv_msg_send(GUI_MESSAGE_PIN_PROMPT, value);
        },
        LV_EVENT_CLICKED, nullptr
      );
    }

    return btn;
  }

  lv_obj_t* createPinProgressLabel(lv_obj_t* parent)
  {
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_text_font(cont, &font_roboto_black_20, LV_STATE_DEFAULT);
    lv_obj_set_width(cont, 52);
    lv_obj_set_height(cont, 180);

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_center(label);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    static uint8_t cnt;
    static char buf[16];
    cnt = 0;
    buf[cnt] = '\0';
    lv_label_set_text(label, buf);
    lv_msg_subscribe(GUI_MESSAGE_PIN_PROMPT,
      [](void* s, lv_msg_t* m) -> void {
        if (cnt > 14) {
          return;
        }

        if (cnt > 0) {
          buf[cnt++] = '\n';
        }
        buf[cnt++] = '*';
        buf[cnt] = '\0';

        lv_obj_t* label = reinterpret_cast<lv_obj_t*>(lv_msg_get_user_data(m));
        lv_label_set_text(label, buf);
      },
      label
    );

    return cont;
  }

  lv_obj_t* createPadButton(lv_obj_t* parent, size_t idx)
  {
    lv_obj_t *btn = lv_obj_create(parent);
    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_style_border_width(btn, 0, 0);
    lv_obj_set_style_bg_color(btn, pressedColor, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(btn, panBgColor, LV_STATE_DEFAULT);
    lv_obj_remove_style(btn, 0, LV_PART_SCROLLBAR);
    lv_obj_set_style_border_width(btn, 0, 0);

    lv_obj_t* img = lv_img_create(btn);
    lv_img_set_src(img, pinPads[idx].ImgSrc);

    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_user_data(btn, &pinPads[idx].Value);
    lv_obj_add_event_cb(btn,
      [](lv_event_t* event) -> void {
        lv_obj_t* padButton = lv_event_get_target(event);
        int8_t* value = reinterpret_cast<int8_t*>(lv_obj_get_user_data(padButton));
        lv_msg_send(GUI_MESSAGE_PIN_PROMPT, value);
      },
      LV_EVENT_CLICKED, nullptr
    );

    return btn;
  }
}

void TGUI::Begin()
{
  lv_style_set_border_width(&mainStyle, 0);
  lv_style_set_bg_color(&mainStyle, bgColor);
  lv_style_set_text_font(&mainStyle, &font_roboto_black_20);
  lv_style_set_text_color(&mainStyle, textColor);
  lv_style_set_border_width(&mainStyle, 0);
}

void TGUI::ShowScreenPinEnter()
{
  const size_t padPadding = 12;
  const size_t pagePadding = 18;

  lv_obj_t* cont = createPage();
  lv_obj_t* pinProgressLabel = createPinProgressLabel(cont);
  lv_obj_align(pinProgressLabel, LV_ALIGN_TOP_LEFT, pagePadding, pagePadding+padPadding);

  // first row
  lv_obj_t* pad00 = createPadButton(cont, true, 0);
  lv_obj_align(pad00, LV_ALIGN_TOP_LEFT, pagePadding+padPadding+52, pagePadding);

  lv_obj_t* pad01 = createPadButton(cont, true, 1);
  lv_obj_align_to(pad01, pad00, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  lv_obj_t* pad02 = createPadButton(cont, true, 2);
  lv_obj_align_to(pad02, pad01, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  lv_obj_t* pad03 = createPadButton(cont, true, 3);
  lv_obj_align_to(pad03, pad02, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  // second row
  lv_obj_t* pad04 = createPadButton(cont, true, 4);
  lv_obj_align_to(pad04, pad00, LV_ALIGN_OUT_BOTTOM_MID, 0, padPadding);

  lv_obj_t* pad05 = createPadButton(cont, true, 5);
  lv_obj_align_to(pad05, pad04, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  lv_obj_t* pad06 = createPadButton(cont, true, 6);
  lv_obj_align_to(pad06, pad05, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  lv_obj_t* pad07 = createPadButton(cont, true, 7);
  lv_obj_align_to(pad07, pad06, LV_ALIGN_OUT_RIGHT_MID, padPadding, 0);

  // lv_msg_subscribe(GUI_MESSAGE_PIN_PROMPT,
  //   [this](void* s, lv_msg_t* m) -> void {
  //     const int8_t* value = reinterpret_cast<const int8_t*>(lv_msg_get_payload(m));
  //     TPinHandler* fn = reinterpret_cast<TPinHandler*>(lv_msg_get_user_data(m));
  //     fn(*value);
  //   },
  //   &fn
  // );
}

void TGUI::ShowScreenPinCheck(/*std::vector<size_t> values*/)
{

  std::string password = "ASDASD32423ASD123";




  const size_t maxPassword = 10;
  const size_t maxIcon = 15;
  const size_t pagePadding = 12;
  const size_t iconPadding = 8;
  const size_t iconSize = 96;

  lv_obj_t* cont = createPage();
  if (password.length() % 2 != 0) {
    password += "X";
  }

  lv_obj_t* topLabel = lv_label_create(cont);
  lv_obj_align(topLabel, LV_ALIGN_TOP_MID, 0, 24);
  lv_label_set_text(topLabel, "is OK?!");
  lv_obj_set_style_text_font(topLabel, &font_roboto_black_24, 0);
  lv_obj_set_style_text_align(topLabel, LV_TEXT_ALIGN_CENTER, 0);

  lv_obj_t* prev = nullptr;
  lv_obj_t* cur = nullptr;
  size_t maxPad = password.length() < maxPassword ? password.length() : maxPassword;
  for (uint8_t i=0; i < maxPad; i+=2) {
    cur = createPadButton(cont, false, password[i] % maxIcon);
    if (prev == nullptr) {
      lv_obj_align(cur, LV_ALIGN_LEFT_MID, pagePadding, 0);
    } else {
      lv_obj_align_to(cur, prev, LV_ALIGN_OUT_RIGHT_MID, iconPadding, 0);
    }

    lv_obj_t* padLabel = lv_label_create(cont);
    lv_obj_set_width(padLabel, iconSize);
    lv_obj_align_to(padLabel, cur, LV_ALIGN_OUT_BOTTOM_MID, 0, iconPadding);
    lv_label_set_text(padLabel, password.substr(i, 2).c_str());
    lv_obj_set_style_text_font(padLabel, &font_roboto_black_14, 0);
    lv_obj_set_style_text_align(padLabel, LV_TEXT_ALIGN_CENTER, 0);

    prev = cur;
  }
}

void TGUI::ShowScreenNotification()
{
  std::string text = "ASSERT\n10.0.0.12";


  lv_obj_t* cont = createPage();
  lv_obj_t* img = lv_img_create(cont);
  lv_img_set_src(img, &bg_notify);
  lv_obj_set_pos(img, 0, 0);

  lv_obj_t* textLabel = lv_label_create(cont);
  lv_obj_set_width(textLabel, 300);
  lv_obj_align(textLabel, LV_ALIGN_RIGHT_MID, -24, 0);
  lv_obj_set_style_text_font(textLabel, &font_roboto_black_24, 0);
  lv_obj_set_style_text_align(textLabel, LV_TEXT_ALIGN_RIGHT, 0);
  lv_label_set_text(textLabel, text.c_str());
}

lv_obj_t* TGUI::createPage()
{
  clearScreen();

  lv_obj_t *cont = lv_obj_create(lv_scr_act());
  lv_obj_set_size(cont, lv_disp_get_physical_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
  lv_obj_add_style(cont, &mainStyle, LV_PART_MAIN);
  lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
  lv_obj_set_style_pad_all(cont, 0, 0);
  lv_obj_set_style_border_width(cont, 0, 0);
  lv_obj_set_style_bg_color(cont, bgColor, 0);

  lv_obj_center(cont);
  return cont;
}

void TGUI::clearScreen()
{
  if (screen) {
    lv_obj_clean(screen);
    screen = nullptr;
  }

  screen = lv_obj_create(nullptr);
  lv_scr_load(screen);
}

TGUI::~TGUI()
{
  if (screen) {
    lv_obj_clean(screen);
    screen = nullptr;
  }
}
