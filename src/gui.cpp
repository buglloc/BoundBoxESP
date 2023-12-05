#include "gui.h"

#include <lvgl.h>
#include <Esp.h>

LV_FONT_DECLARE(font_ubuntu_regular_12);
LV_FONT_DECLARE(font_ubuntu_regular_10);
LV_FONT_DECLARE(font_ubuntu_regular_12);
LV_FONT_DECLARE(font_ubuntu_regular_14);
LV_FONT_DECLARE(font_ubuntu_regular_16);
LV_FONT_DECLARE(font_ubuntu_regular_24);

LV_IMG_DECLARE(pad_icon_00);
LV_IMG_DECLARE(pad_icon_01);
LV_IMG_DECLARE(pad_icon_02);
LV_IMG_DECLARE(pad_icon_03);
LV_IMG_DECLARE(pad_icon_04);
LV_IMG_DECLARE(pad_icon_05);
LV_IMG_DECLARE(pad_icon_06);
LV_IMG_DECLARE(pad_icon_07);
LV_IMG_DECLARE(pad_icon_012);
LV_IMG_DECLARE(pad_icon_09);
LV_IMG_DECLARE(pad_icon_10);
LV_IMG_DECLARE(pad_icon_11);
LV_IMG_DECLARE(pad_icon_12);
LV_IMG_DECLARE(pad_icon_13);
LV_IMG_DECLARE(pad_icon_14);
LV_IMG_DECLARE(pad_icon_15);

#define TILE_STATUS_ID 0
#define TILE_PIN_ID 1
#define TILE_NOTIFY_ID 2

#define PAD_SPACE 12

namespace {
  static lv_color_t bgColor = lv_color_hex(0xe6e6e6);
  static lv_color_t textColor = lv_color_hex(0x030303);
  static lv_color_t pressedColor = lv_color_hex(0x2c3136);
}

void TGUI::Begin()
{
  static  lv_style_t bgStyle;
  lv_style_set_border_width(&bgStyle, 0);
  lv_style_set_bg_color(&bgStyle, bgColor);

  tileView = lv_tileview_create(lv_scr_act());
  lv_obj_add_style(tileView, &bgStyle, LV_PART_MAIN);
  lv_obj_set_size(tileView, lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
  lv_obj_set_scrollbar_mode(tileView, LV_SCROLLBAR_MODE_OFF);

  lv_obj_t* statusTile = lv_tileview_add_tile(tileView, TILE_STATUS_ID, 0, LV_DIR_HOR | LV_DIR_BOTTOM);
  lv_obj_t* pinTile = lv_tileview_add_tile(tileView, TILE_PIN_ID, 0, LV_DIR_HOR | LV_DIR_BOTTOM);
  lv_obj_t* notifyTile = lv_tileview_add_tile(tileView, 1, 0, TILE_NOTIFY_ID | LV_DIR_BOTTOM);

  initializeStatusTile(statusTile);
  initializePinpadTile(pinTile);
  initializeNotifyTile(notifyTile);
}

void TGUI::initializeStatusTile(lv_obj_t* parent)
{
  lv_obj_t *cont = lv_obj_create(parent);
  lv_obj_set_style_border_width(cont, 0, 0);
  lv_obj_set_style_bg_color(cont, bgColor, 0);
  lv_obj_set_size(cont, lv_disp_get_physical_hor_res(NULL), lv_disp_get_ver_res(NULL) );
  lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
  lv_obj_center(cont);
  lv_obj_set_style_border_width(cont, 0, 0);

  static lv_style_t fontStyle;
  lv_style_init(&fontStyle);
  lv_style_set_text_color(&fontStyle, textColor);
  lv_style_set_text_font(&fontStyle, &font_ubuntu_regular_16);

  static lv_style_t padStyle;
  lv_style_init(&padStyle);
  lv_style_set_bg_color(&padStyle, bgColor);
  lv_style_set_border_color(&padStyle, textColor);
  lv_style_set_border_width(&padStyle, 2);

  static lv_style_t padStylePressed;
  lv_style_init(&padStylePressed);
  lv_style_set_bg_color(&padStyle, pressedColor);
  lv_style_set_border_color(&padStyle, textColor);
  lv_style_set_border_width(&padStyle, 2);

  lv_obj_t *pad00 = lv_img_create(parent);
  lv_img_set_src(pad00, &pad_icon_00);
  lv_obj_add_style(pad00, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad00, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad00, textColor, 0);
  lv_obj_align(pad00, LV_ALIGN_TOP_LEFT, PAD_SPACE, PAD_SPACE);

  lv_obj_t *pad01 = lv_img_create(parent);
  lv_img_set_src(pad01, &pad_icon_01);
  lv_obj_add_style(pad01, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad01, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad01, textColor, 0);
  lv_obj_align_to(pad01, pad00, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  lv_obj_t *pad02 = lv_img_create(parent);
  lv_img_set_src(pad02, &pad_icon_02);
  lv_obj_add_style(pad02, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad02, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad02, textColor, 0);
  lv_obj_align_to(pad02, pad01, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  lv_obj_t *pad03 = lv_img_create(parent);
  lv_img_set_src(pad03, &pad_icon_03);
  lv_obj_add_style(pad03, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad03, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad03, textColor, 0);
  lv_obj_align_to(pad03, pad02, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  lv_obj_t *pad04 = lv_img_create(parent);
  lv_img_set_src(pad04, &pad_icon_04);
  lv_obj_add_style(pad04, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad04, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad04, textColor, 0);
  lv_obj_align_to(pad04, pad00, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_SPACE);

  lv_obj_t *pad05 = lv_img_create(parent);
  lv_img_set_src(pad05, &pad_icon_05);
  lv_obj_add_style(pad05, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad05, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad05, textColor, 0);
  lv_obj_align_to(pad05, pad04, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  lv_obj_t *pad06 = lv_img_create(parent);
  lv_img_set_src(pad06, &pad_icon_06);
  lv_obj_add_style(pad06, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad06, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad06, textColor, 0);
  lv_obj_align_to(pad06, pad05, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  lv_obj_t *pad07 = lv_img_create(parent);
  lv_img_set_src(pad07, &pad_icon_07);
  lv_obj_add_style(pad07, &padStyle, LV_STATE_DEFAULT);
  lv_obj_add_style(pad07, &padStylePressed, LV_STATE_PRESSED);
  lv_obj_set_style_img_recolor(pad07, textColor, 0);
  lv_obj_align_to(pad07, pad06, LV_ALIGN_OUT_RIGHT_MID, PAD_SPACE, 0);

  // createPad(cont, &pad_icon_00, LV_ALIGN_TOP_LEFT);
  // createPad(cont, &pad_icon_01, LV_ALIGN_TOP_MID);
  // createPad(cont, &pad_icon_02, LV_ALIGN_TOP_RIGHT);

  // createPad(cont, &pad_icon_03, LV_ALIGN_LEFT_MID);
  // createPad(cont, &pad_icon_04, LV_ALIGN_CENTER);
  // createPad(cont, &pad_icon_05, LV_ALIGN_RIGHT_MID);

  // createPad(cont, &pad_icon_06, LV_ALIGN_BOTTOM_LEFT);
  // createPad(cont, &pad_icon_07, LV_ALIGN_BOTTOM_MID);
  // createPad(cont, &pad_icon_012, LV_ALIGN_BOTTOM_RIGHT);
//   lv_obj_t *pad01 = lv_img_create(cont);
//   lv_img_set_src(pad01, &pad_icon_00);
//   lv_obj_set_style_img_recolor(pad01, textColor, 0);
// // lv_obj_set_style_img_recolor_opa(pad01, textColor, 0);
//   lv_obj_align(pad01, LV_ALIGN_LEFT_MID, 55, -50);

  // lv_obj_t *label = lv_label_create(cont);
  // lv_obj_add_style(label, &fontStyle, 0);
  // lv_label_set_text(label, ESP.getChipModel());
  // lv_obj_align_to(label, pad01, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
}


void TGUI::initializePinpadTile(lv_obj_t* statusTile)
{
}

void TGUI::initializeNotifyTile(lv_obj_t* statusTile)
{
}