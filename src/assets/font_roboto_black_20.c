/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts:
 ******************************************************************************/
#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_ROBOTO_BLACK_20
#define FONT_ROBOTO_BLACK_20 1
#endif

#if FONT_ROBOTO_BLACK_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0023 "#" */
    0x0, 0xf1, 0xe0, 0x0, 0xf2, 0xd0, 0x1, 0xe3,
    0xc0, 0x1, 0xe3, 0xc0, 0x3f, 0xff, 0xfc, 0x3f,
    0xff, 0xfc, 0x3, 0xc7, 0x80, 0x3, 0xcb, 0x40,
    0x3, 0xcb, 0x40, 0xbf, 0xff, 0xf4, 0xbf, 0xff,
    0xf4, 0xb, 0x4f, 0x0, 0xf, 0x1e, 0x0, 0xf,
    0x1e, 0x0, 0xf, 0x2d, 0x0,

    /* U+002A "*" */
    0x0, 0xf0, 0x0, 0xe, 0x0, 0x20, 0xe0, 0x4b,
    0xef, 0xfc, 0x1b, 0xfe, 0x40, 0x3f, 0x40, 0xf,
    0x7c, 0x2, 0xe1, 0xf0, 0x8, 0x8, 0x0,

    /* U+0040 "@" */
    0x0, 0x7, 0xff, 0x40, 0x0, 0x7, 0xfe, 0xff,
    0x0, 0x2, 0xf4, 0x0, 0xbd, 0x0, 0x7d, 0x0,
    0x1, 0xf0, 0xf, 0x40, 0x0, 0xb, 0x41, 0xf0,
    0x1f, 0xe0, 0x38, 0x3d, 0x7, 0xff, 0x83, 0xc3,
    0xc0, 0xf4, 0xb8, 0x3c, 0x3c, 0x2f, 0xb, 0x83,
    0xc7, 0xc3, 0xe0, 0xf4, 0x3c, 0x7c, 0x3d, 0xf,
    0x43, 0xc3, 0xc3, 0xd0, 0xf4, 0x3c, 0x3c, 0x3e,
    0x1f, 0x4b, 0x43, 0xd2, 0xff, 0xff, 0xe0, 0x2e,
    0xb, 0xd2, 0xf8, 0x0, 0xf4, 0x0, 0x0, 0x0,
    0x7, 0xe4, 0x1, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x0, 0x0, 0x1f, 0xfe, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 186, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 149, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 68, .adv_w = 287, .box_w = 18, .box_h = 19, .ofs_x = 0, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x7, 0x1d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 35, .range_length = 30, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR >= 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR >= 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_roboto_black_20 = {
#else
lv_font_t font_roboto_black_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONT_ROBOTO_BLACK_20*/
