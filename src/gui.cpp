#include "gui.h"
#include <lvgl.h>

LV_FONT_DECLARE(font_roboto_black_12);
LV_FONT_DECLARE(font_roboto_black_14);
LV_FONT_DECLARE(font_roboto_black_20);
LV_FONT_DECLARE(font_roboto_black_24);
LV_FONT_DECLARE(font_roboto_black_8);

LV_FONT_DECLARE(font_roboto_regular_12);
LV_FONT_DECLARE(font_roboto_regular_14);
LV_FONT_DECLARE(font_roboto_regular_20);
LV_FONT_DECLARE(font_roboto_regular_24);
LV_FONT_DECLARE(font_roboto_regular_8);

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


#define TILE_STATUS_ID 0
#define TILE_PIN_ID 1
#define TILE_NOTIFY_ID 2

#define PAD_PADDING 12
#define PAGE_PADDING 18

namespace {
  static lv_color_t bgColor = lv_color_hex(0xd4d4d4);
  static lv_color_t panBgColor = lv_color_hex(0xfafafa);
  static lv_color_t textColor = lv_color_hex(0x030303);
  static lv_color_t pressedColor = lv_color_hex(0x939ea3);

  lv_obj_t* createPadButton(lv_obj_t* parent, const void* imgSrc)
  {
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_bg_color(cont, pressedColor, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(cont, panBgColor, LV_STATE_DEFAULT);
    lv_obj_set_size(cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_t* img = lv_img_create(cont);
    lv_img_set_src(img, imgSrc);
    return cont;
  }

  lv_obj_t* createPinProgress(lv_obj_t* parent)
  {
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_text_font(cont, &font_roboto_regular_20, LV_STATE_DEFAULT);
    lv_obj_set_width(cont, 52);
    lv_obj_set_height(cont, 180);
    lv_obj_align(cont, LV_ALIGN_TOP_LEFT, PAGE_PADDING, PAGE_PADDING+PAD_PADDING);

    lv_obj_t * label = lv_label_create(cont);
    lv_label_set_text(label, "*\n*\n*\n*\n*\n*\n*");
    lv_obj_center(label);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    return cont;
  }
}

void TGUI::Begin()
{
  static  lv_style_t mainStyle;
  lv_style_set_border_width(&mainStyle, 0);
  lv_style_set_bg_color(&mainStyle, bgColor);
  lv_style_set_text_font(&mainStyle, &font_roboto_regular_14);
  lv_style_set_text_color(&mainStyle, textColor);
  lv_style_set_border_width(&mainStyle, 0);

  tileView = lv_tileview_create(lv_scr_act());
  lv_obj_add_style(tileView, &mainStyle, LV_PART_MAIN);
  lv_obj_remove_style(tileView, 0, LV_PART_SCROLLBAR);
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
  lv_obj_set_size(cont, lv_disp_get_physical_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
  lv_obj_set_style_pad_all(cont, 0, 0);
  lv_obj_set_style_border_width(cont, 0, 0);
  lv_obj_set_style_bg_color(cont, bgColor, 0);
  lv_obj_remove_style(cont, 0, LV_PART_SCROLLBAR);
  lv_obj_center(cont);

  // first row
  lv_obj_t *pad00 = createPadButton(cont, &pad_icon_00);
  lv_obj_align(pad00, LV_ALIGN_TOP_LEFT, PAGE_PADDING+PAD_PADDING+52, PAGE_PADDING);
  lv_obj_t *pad01 = createPadButton(cont, &pad_icon_01);
  lv_obj_align_to(pad01, pad00, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);
  lv_obj_t *pad02 = createPadButton(cont, &pad_icon_02);
  lv_obj_align_to(pad02, pad01, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);
  lv_obj_t *pad03 = createPadButton(cont, &pad_icon_03);
  lv_obj_align_to(pad03, pad02, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);

  // second row
  lv_obj_t *pad04 = createPadButton(cont, &pad_icon_04);
  lv_obj_align_to(pad04, pad00, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_PADDING);
  lv_obj_t *pad05 = createPadButton(cont, &pad_icon_05);
  lv_obj_align_to(pad05, pad04, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);
  lv_obj_t *pad06 = createPadButton(cont, &pad_icon_06);
  lv_obj_align_to(pad06, pad05, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);
  lv_obj_t *pad07 = createPadButton(cont, &pad_icon_07);
  lv_obj_align_to(pad07, pad06, LV_ALIGN_OUT_RIGHT_MID, PAD_PADDING, 0);

  lv_obj_t* pinProgress = createPinProgress(cont);
}

void TGUI::initializePinpadTile(lv_obj_t* statusTile)
{
}

void TGUI::initializeNotifyTile(lv_obj_t* statusTile)
{
}