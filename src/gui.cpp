#include "gui.h"
#include <lvgl.h>
#include <functional>
#include <string>
#include <algorithm>

LV_FONT_DECLARE(font_roboto_black_14);
LV_FONT_DECLARE(font_roboto_black_20);
LV_FONT_DECLARE(font_roboto_black_24);

LV_FONT_DECLARE(font_roboto_mono_20);
LV_FONT_DECLARE(font_roboto_mono_24);
LV_FONT_DECLARE(font_roboto_mono_32);

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
  static const lv_color_t bgColor = lv_color_hex(0xd4d4d4);
  static const lv_color_t panBgColor = lv_color_hex(0xfafafa);
  static const lv_color_t textColor = lv_color_hex(0x030303);
  static const lv_color_t pressedColor = lv_color_hex(0x939ea3);

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

    static uint8_t pinBufIdx;
    static char pinBuf[16];
    pinBufIdx = 0;
    pinBuf[pinBufIdx] = '\0';

    lv_label_set_text_static(label, "");
    lv_obj_add_event_cb(label,
      [](lv_event_t* e) -> void {
        if (pinBufIdx > 14) {
          return;
        }

        if (pinBufIdx > 0) {
          pinBuf[pinBufIdx++] = '\n';
        }
        pinBuf[pinBufIdx++] = '*';
        pinBuf[pinBufIdx] = '\0';
        lv_obj_t* label = lv_event_get_target(e);
        lv_label_set_text_static(label, pinBuf);
      },
      LV_EVENT_MSG_RECEIVED,
      nullptr
    );
    lv_msg_subsribe_obj(GUI_MESSAGE_PIN_PROMPT, label, nullptr);

    return cont;
  }

  void setBoardStateLabel(lv_obj_t* label, TBoardManager::BoardState state)
  {
    switch (state) {
      case TBoardManager::BoardState::Boot:
        lv_label_set_text_static(label, "Booting...");
        break;

      case TBoardManager::BoardState::WaitNet:
        lv_label_set_text_static(label, "Waiting for network...");
        break;

      case TBoardManager::BoardState::WaitCredential:
        lv_label_set_text_static(label, "Waiting for credential...");
        break;

      case TBoardManager::BoardState::Process:
        lv_label_set_text_static(label, "Process incoming request...");
        break;

      case TBoardManager::BoardState::Idle:
        lv_label_set_text_static(label, "Waiting for connection...");
        break;

      default:
        lv_label_set_text_fmt(label, "Unknown[%d]", state);
        break;
    }
  }
}

void TGUI::Begin()
{
  lv_style_set_border_width(&mainStyle, 0);
  lv_style_set_bg_color(&mainStyle, bgColor);
  lv_style_set_text_font(&mainStyle, &font_roboto_mono_24);
  lv_style_set_text_color(&mainStyle, textColor);
  lv_style_set_border_width(&mainStyle, 0);
}

void TGUI::ShowScreenPinEnter()
{
  const size_t padPadding = 12;
  const size_t pagePadding = 18;

  lv_obj_t* screen = switchScreen(nullptr);
  lv_obj_t* cont = createPage(screen);
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
}

void TGUI::ShowScreenPinVerify(const String& verification)
{
  const size_t maxPassword = 10;
  const size_t maxIcon = 15;
  const size_t pagePadding = 12;
  const size_t iconPadding = 8;
  const size_t iconSize = 96;

  lv_obj_t* screen = switchScreen(nullptr);
  lv_obj_t* cont = createPage(screen);
  lv_obj_t* topLabel = lv_label_create(cont);
  lv_obj_align(topLabel, LV_ALIGN_TOP_MID, 0, 24);
  lv_label_set_text_static(topLabel, "is OK?!");
  lv_obj_set_style_text_font(topLabel, &font_roboto_mono_32, 0);
  lv_obj_set_style_text_align(topLabel, LV_TEXT_ALIGN_CENTER, 0);

  String labelsText = verification;
  labelsText.toUpperCase();
  size_t maxPad = labelsText.length() < maxPassword ? labelsText.length() : maxPassword;
  if (maxPad % 2 != 0) {
    maxPad++;
    labelsText.concat('X');
  }

  lv_obj_t* prev = nullptr;
  lv_obj_t* cur = nullptr;
  for (uint8_t i=0; i < maxPad; i+=2) {
    cur = createPadButton(cont, false, verification[i] % maxIcon);
    if (prev == nullptr) {
      lv_obj_align(cur, LV_ALIGN_LEFT_MID, pagePadding, 0);
    } else {
      lv_obj_align_to(cur, prev, LV_ALIGN_OUT_RIGHT_MID, iconPadding, 0);
    }

    lv_obj_t* padLabel = lv_label_create(cont);
    lv_obj_set_width(padLabel, iconSize);
    lv_obj_align_to(padLabel, cur, LV_ALIGN_OUT_BOTTOM_MID, 0, iconPadding);
    lv_label_set_text(padLabel, labelsText.substring(i, i+2).c_str());
    lv_obj_set_style_text_font(padLabel, &font_roboto_mono_24, 0);
    lv_obj_set_style_text_align(padLabel, LV_TEXT_ALIGN_CENTER, 0);

    prev = cur;
  }
}

void TGUI::ShowScreenNotification(const String& msg)
{
  if (notifyScreen != nullptr) {
    lv_msg_send(GUI_MESSAGE_NOTIFY, msg.c_str());
    switchScreen(notifyScreen);
    return;
  }

  notifyScreen = switchScreen(nullptr);
  lv_obj_t* cont = createPage(notifyScreen);
  lv_obj_t* img = lv_img_create(cont);
  lv_img_set_src(img, &bg_notify);
  lv_obj_set_pos(img, 0, 0);

  lv_obj_t* titleLabel = lv_label_create(cont);
  lv_obj_set_width(titleLabel, 300);
  lv_obj_set_style_text_font(titleLabel, &font_roboto_mono_32, 0);
  lv_obj_set_style_text_align(titleLabel, LV_TEXT_ALIGN_RIGHT, 0);
  lv_label_set_text_static(titleLabel, R"(\(o_o)/)");
  lv_obj_align(titleLabel, LV_ALIGN_RIGHT_MID, -48, -24);

  lv_obj_t* msgLabel = lv_label_create(cont);
  lv_obj_set_width(msgLabel, 300);
  lv_obj_set_style_text_font(msgLabel, &font_roboto_mono_32, 0);
  lv_obj_set_style_text_align(msgLabel, LV_TEXT_ALIGN_RIGHT, 0);
  lv_label_set_text(msgLabel, msg.c_str());
  lv_obj_align_to(msgLabel, titleLabel, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);

  lv_obj_add_event_cb(msgLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto msg = reinterpret_cast<const char*>(lv_msg_get_payload(m));
      lv_label_set_text(label, msg);
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NOTIFY, msgLabel, nullptr);
}

void TGUI::ShowScreenIdle(TBoardManager::BoardInfo boardInfo)
{
  if (idleScreen != nullptr) {
    switchScreen(idleScreen);
    return;
  }

  idleScreen = switchScreen(nullptr);
  lv_obj_t* cont = createPage(idleScreen);

  lv_obj_t* stateLabel = lv_label_create(cont);
  lv_obj_center(stateLabel);
  lv_obj_set_style_text_font(stateLabel, &font_roboto_mono_32, 0);
  lv_obj_set_style_text_align(stateLabel, LV_TEXT_ALIGN_CENTER, 0);
  setBoardStateLabel(stateLabel, boardInfo.State);

  lv_obj_add_event_cb(stateLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto info = reinterpret_cast<const TBoardManager::BoardInfo*>(lv_msg_get_payload(m));
      setBoardStateLabel(label, info->State);
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_UPDATE_BOARD_INFO, stateLabel, nullptr);

  lv_obj_t* ipLabel = lv_label_create(cont);
  lv_obj_align(ipLabel, LV_ALIGN_BOTTOM_LEFT, 24, -24);
  lv_obj_set_style_text_font(ipLabel, &font_roboto_mono_20, 0);
  lv_obj_set_style_text_align(ipLabel, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text_fmt(ipLabel, "IP: %s", boardInfo.LocalIP.toString());

  lv_obj_add_event_cb(ipLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto info = reinterpret_cast<const TBoardManager::BoardInfo*>(lv_msg_get_payload(m));
      lv_label_set_text_fmt(label, "IP: %s", info->LocalIP.toString());
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_UPDATE_BOARD_INFO, ipLabel, nullptr);
}

TGUI::~TGUI()
{
  if (notifyScreen != nullptr) {
    lv_obj_clean(notifyScreen);
    lv_obj_del(notifyScreen);
  }

  if (idleScreen != nullptr) {
    lv_obj_clean(idleScreen);
    lv_obj_del(idleScreen);
  }
}

lv_obj_t* TGUI::createPage(lv_obj_t *screen)
{
  lv_obj_t *cont = lv_obj_create(screen);
  lv_obj_set_size(cont, lv_disp_get_physical_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
  lv_obj_add_style(cont, &mainStyle, LV_PART_MAIN);
  lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
  lv_obj_set_style_pad_all(cont, 0, 0);
  lv_obj_set_style_border_width(cont, 0, 0);
  lv_obj_set_style_bg_color(cont, bgColor, 0);

  lv_obj_center(cont);
  return cont;
}

lv_obj_t* TGUI::switchScreen(lv_obj_t *targetScreen)
{
  lv_obj_t* prevScr = lv_scr_act();
  if (targetScreen == nullptr) {
    targetScreen = lv_obj_create(nullptr);
  }

  if (prevScr == targetScreen) {
    return targetScreen;
  }

  if (isPersistentScreen(prevScr)) {
    lv_scr_load_anim(targetScreen, LV_SCR_LOAD_ANIM_FADE_OUT, 150, 50, false);
    return targetScreen;
  }

  if (prevScr != nullptr) {
    lv_obj_clean(prevScr);
    lv_scr_load_anim(targetScreen, LV_SCR_LOAD_ANIM_FADE_OUT, 150, 50, true);
    return targetScreen;
  }

  lv_scr_load_anim(targetScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  return targetScreen;
}

bool TGUI::isPersistentScreen(lv_obj_t* scr)
{
  return scr == notifyScreen || scr == idleScreen;
}
