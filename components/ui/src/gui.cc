#include "gui.h"

#include <lvgl.h>
#include <functional>
#include <string>
#include <algorithm>


LV_FONT_DECLARE(font_roboto_black_20);
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


#define ADDRSTR "%d.%d.%d.%d"
#define ADDR2STR(addr) (uint8_t)(addr & 0xFF), \
  (uint8_t)((addr >> 8) & 0xFF), \
  (uint8_t)((addr >> 16) & 0xFF), \
  (uint8_t)((addr >> 24) & 0xFF)


using namespace UI;

namespace
{
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

namespace
{
  lv_obj_t* createPadButton(lv_obj_t* parent, bool clickable, size_t idx)
  {
    static const lv_color_t panBgColor = lv_color_hex(0xf6f6f6);
    static const lv_color_t pressedColor = lv_color_hex(0x939ea3);

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

  void setBoardStateLabel(lv_obj_t* label, BoardState state)
  {
    switch (state) {
      case BoardState::Boot:
        lv_label_set_text_static(label, "Booting...");
        break;

      case BoardState::WaitNet:
        lv_label_set_text_static(label, "Waiting for network...");
        break;

      case BoardState::WaitCredential:
        lv_label_set_text_static(label, "Waiting for credential...");
        break;

      case BoardState::Process:
        lv_label_set_text_static(label, "Process incoming request...");
        break;

      case BoardState::Idle:
        lv_label_set_text_static(label, "Waiting for connection...");
        break;

      case BoardState::Restart:
        lv_label_set_text_static(label, "Restarting...");
        break;

      default:
        lv_label_set_text_fmt(label, "Unknown[%d]", (int)state);
        break;
    }
  }

  lv_style_t* mainStyle()
  {
    static lv_color_t bgColor = lv_color_hex(0xdcdcdc);
    static lv_color_t textColor = lv_color_hex(0x111111);
    static lv_style_t mainStyle;
    static bool inited = false;
    if (inited) {
      return &mainStyle;
    }

    lv_style_set_border_width(&mainStyle, 0);
    lv_style_set_bg_color(&mainStyle, bgColor);
    lv_style_set_text_font(&mainStyle, &font_roboto_mono_24);
    lv_style_set_text_color(&mainStyle, textColor);
    inited = true;
    return &mainStyle;
  }
}

GUI::GUI()
{}

void GUI::ShowScreenPinEnter()
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

void GUI::ShowScreenPinVerify(const std::string& verification)
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

  std::string labelsText = verification;
  std::transform(labelsText.begin(), labelsText.end(), labelsText.begin(), ::toupper);
  size_t maxPad = labelsText.size() < maxPassword ? labelsText.size() : maxPassword;
  if (maxPad % 2 != 0) {
    maxPad++;
    labelsText += 'X';
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
    lv_label_set_text(padLabel, labelsText.substr(i, 2).c_str());
    lv_obj_set_style_text_font(padLabel, &font_roboto_mono_24, 0);
    lv_obj_set_style_text_align(padLabel, LV_TEXT_ALIGN_CENTER, 0);

    prev = cur;
  }
}

void GUI::ShowScreenNotification(const std::string& msg)
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

void GUI::ShowInfoScreen()
{
  if (infoScreen != nullptr) {
    switchScreen(infoScreen);
    return;
  }

  infoScreen = switchScreen(nullptr);
  lv_obj_t* cont = createPage(infoScreen);

  lv_obj_t* stateLabel = lv_label_create(cont);
  lv_obj_center(stateLabel);
  lv_obj_set_style_text_font(stateLabel, &font_roboto_mono_32, 0);
  lv_obj_set_style_text_align(stateLabel, LV_TEXT_ALIGN_CENTER, 0);
  setBoardStateLabel(stateLabel, BoardState::Boot);

  lv_obj_add_event_cb(stateLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto boardState = reinterpret_cast<const BoardState*>(lv_msg_get_payload(m));
      if (boardState != nullptr) {
        setBoardStateLabel(label, *boardState);
      }
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NEW_BOARD_STATE, stateLabel, nullptr);

  lv_obj_t* ipLabel = lv_label_create(cont);
  lv_obj_align(ipLabel, LV_ALIGN_TOP_LEFT, 24, 24);
  lv_obj_set_style_text_font(ipLabel, &font_roboto_mono_20, 0);
  lv_obj_set_style_text_align(ipLabel, LV_TEXT_ALIGN_LEFT, 0);
  lv_label_set_text_static(ipLabel, "IP: N/A");

  lv_obj_add_event_cb(ipLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto addr = reinterpret_cast<const uint32_t*>(lv_msg_get_payload(m));
      if (addr == nullptr || *addr == 0) {
        lv_label_set_text_static(label, "IP: N/A");
      } else {
        lv_label_set_text_fmt(label, "IP: " ADDRSTR, ADDR2STR(*addr));
      }
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NEW_ADDR, ipLabel, nullptr);

  lv_obj_t* assesLabel = lv_label_create(cont);
  lv_obj_align(assesLabel, LV_ALIGN_TOP_RIGHT, -24, 24);
  lv_obj_set_style_text_font(assesLabel, &font_roboto_mono_20, 0);
  lv_obj_set_style_text_align(assesLabel, LV_TEXT_ALIGN_LEFT, 0);
  lv_label_set_text_static(assesLabel, "Asses: 0000");

  lv_obj_add_event_cb(assesLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto asses = reinterpret_cast<const uint32_t*>(lv_msg_get_payload(m));
      if (asses == nullptr || *asses == 0) {
        lv_label_set_text_static(label, "Asses: 0000");
      } else {
        lv_label_set_text_fmt(label, "Asses: %4lu", *asses);
      }
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NEW_ASSERTATIONS, assesLabel, nullptr);

  lv_obj_t* tempLabel = lv_label_create(cont);
  lv_obj_align(tempLabel, LV_ALIGN_BOTTOM_LEFT, 24, -24);
  lv_obj_set_style_text_font(tempLabel, &font_roboto_mono_20, 0);
  lv_obj_set_style_text_align(tempLabel, LV_TEXT_ALIGN_LEFT, 0);
  lv_label_set_text_static(tempLabel, "Core: N/A");

  lv_obj_add_event_cb(tempLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto temp = reinterpret_cast<const uint32_t*>(lv_msg_get_payload(m));
      if (temp != nullptr && *temp > 0.0) {
        lv_label_set_text_fmt(label, "Core: %lu°C", *temp);
      }
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NEW_CORE_TEMP, tempLabel, nullptr);

  lv_obj_t* battLabel = lv_label_create(cont);
  lv_obj_align(battLabel, LV_ALIGN_BOTTOM_RIGHT, -24, -24);
  lv_obj_set_style_text_font(battLabel, &font_roboto_mono_20, 0);
  lv_obj_set_style_text_align(battLabel, LV_TEXT_ALIGN_RIGHT, 0);
  lv_label_set_text_static(battLabel, "Batt: N/A");

  lv_obj_add_event_cb(battLabel,
    [](lv_event_t* e) -> void {
      lv_msg_t* m = lv_event_get_msg(e);
      lv_obj_t* label = lv_event_get_target(e);

      auto voltage = reinterpret_cast<const uint32_t*>(lv_msg_get_payload(m));
      if (voltage && *voltage != 0) {
        lv_label_set_text_fmt(label, "Batt: %lumV", *voltage);
      }
    },
    LV_EVENT_MSG_RECEIVED,
    nullptr
  );
  lv_msg_subsribe_obj(GUI_MESSAGE_NEW_BATT_VOLTAGE, battLabel, nullptr);
}

GUI::~GUI()
{
  if (notifyScreen != nullptr) {
    lv_obj_clean(notifyScreen);
    lv_obj_del(notifyScreen);
  }

  if (infoScreen != nullptr) {
    lv_obj_clean(infoScreen);
    lv_obj_del(infoScreen);
  }
}

lv_obj_t* GUI::createPage(lv_obj_t *screen)
{
  lv_obj_t *cont = lv_obj_create(screen);
  lv_obj_set_size(cont, lv_disp_get_physical_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
  lv_obj_add_style(cont, mainStyle(), LV_PART_MAIN);
  lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
  lv_obj_set_style_pad_all(cont, 0, 0);
  lv_obj_set_style_border_width(cont, 0, 0);
  // lv_obj_set_style_bg_color(cont, bgColor, 0);

  lv_obj_center(cont);
  return cont;
}

lv_obj_t* GUI::switchScreen(lv_obj_t *targetScreen)
{
  lv_obj_t* prevScr = lv_scr_act();
  if (targetScreen == nullptr) {
    targetScreen = lv_obj_create(nullptr);
  }
  assert(targetScreen);

  if (prevScr == targetScreen) {
    return targetScreen;
  }

  if (prevScr != nullptr) {
    bool autoDel = !isPersistentScreen(prevScr);
    lv_scr_load_anim(targetScreen, LV_SCR_LOAD_ANIM_FADE_OUT, 60, 20, autoDel);
    return targetScreen;
  }

  lv_scr_load_anim(targetScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  return targetScreen;
}

bool GUI::isPersistentScreen(lv_obj_t* scr)
{
  return scr == notifyScreen || scr == infoScreen;
}
