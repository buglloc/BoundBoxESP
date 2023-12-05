/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
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

#ifndef FONT_UBUNTU_REGULAR_12
#define FONT_UBUNTU_REGULAR_12 1
#endif

#if FONT_UBUNTU_REGULAR_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x24, 0xaf, 0xd2, 0x49, 0x2f, 0xd6, 0x90,

    /* U+0024 "$" */
    0x21, 0x1f, 0x8, 0x30, 0x41, 0xf, 0x88, 0x40,

    /* U+0025 "%" */
    0x62, 0x4b, 0x25, 0xd, 0x80, 0xb0, 0xe4, 0x52,
    0x69, 0x23, 0x0,

    /* U+0026 "&" */
    0x30, 0x91, 0x23, 0x87, 0x12, 0x63, 0x46, 0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x69, 0x49, 0x24, 0x89, 0x30,

    /* U+0029 ")" */
    0xc9, 0x12, 0x49, 0x29, 0x60,

    /* U+002A "*" */
    0x25, 0x5c, 0xa5, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x10,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0xc4, 0x23, 0x10, 0x8c, 0x42, 0x11, 0x8,
    0x0,

    /* U+0030 "0" */
    0x76, 0xa3, 0x18, 0xc6, 0x3a, 0x70,

    /* U+0031 "1" */
    0x2e, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x74, 0x42, 0x11, 0x11, 0x18, 0xf8,

    /* U+0033 "3" */
    0xe1, 0x16, 0x31, 0x11, 0xe0,

    /* U+0034 "4" */
    0x8, 0x62, 0x9a, 0x4a, 0x2f, 0xc2, 0x8,

    /* U+0035 "5" */
    0x7a, 0x10, 0xc3, 0x4, 0x21, 0xf0,

    /* U+0036 "6" */
    0x3a, 0x21, 0xe8, 0xc6, 0x3b, 0x70,

    /* U+0037 "7" */
    0xf8, 0xc4, 0x62, 0x10, 0x88, 0x40,

    /* U+0038 "8" */
    0x74, 0x63, 0x97, 0x46, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x66, 0xe0,

    /* U+003A ":" */
    0xc6,

    /* U+003B ";" */
    0xc7, 0x80,

    /* U+003C "<" */
    0x9, 0xf9, 0x83, 0x4,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x87, 0xe, 0x36, 0x40,

    /* U+003F "?" */
    0xe1, 0x12, 0x44, 0x4, 0x40,

    /* U+0040 "@" */
    0x1e, 0x18, 0x64, 0xee, 0x49, 0x92, 0x64, 0x99,
    0x2e, 0x3e, 0x40, 0x18, 0x1, 0xe0,

    /* U+0041 "A" */
    0x18, 0x18, 0x3c, 0x24, 0x24, 0x66, 0x7e, 0x42,
    0xc3,

    /* U+0042 "B" */
    0xfa, 0x38, 0x63, 0xfa, 0x18, 0x63, 0xf8,

    /* U+0043 "C" */
    0x3d, 0x8, 0x20, 0x82, 0x8, 0x10, 0x3c,

    /* U+0044 "D" */
    0xf9, 0x1a, 0xc, 0x18, 0x30, 0x61, 0xc2, 0xf8,

    /* U+0045 "E" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0xf8,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0x80,

    /* U+0047 "G" */
    0x3d, 0x8, 0x20, 0x82, 0x18, 0x51, 0x3c,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x84,

    /* U+0049 "I" */
    0xff, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x21, 0xf0,

    /* U+004B "K" */
    0x8e, 0x6b, 0x38, 0xe2, 0xc9, 0xa2, 0x84,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+004D "M" */
    0xc1, 0xe0, 0xf8, 0xf4, 0x5b, 0x6c, 0xa6, 0x73,
    0x11, 0x80, 0x80,

    /* U+004E "N" */
    0x83, 0x87, 0x8d, 0x99, 0xb1, 0x63, 0xc3, 0x82,

    /* U+004F "O" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c, 0x8, 0x6,

    /* U+0052 "R" */
    0xf9, 0x1a, 0x14, 0x6f, 0x92, 0x22, 0x42, 0x84,

    /* U+0053 "S" */
    0x7c, 0x21, 0x87, 0xc, 0x21, 0xf0,

    /* U+0054 "T" */
    0xfc, 0x41, 0x4, 0x10, 0x41, 0x4, 0x10,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x78,

    /* U+0056 "V" */
    0xc3, 0x42, 0x42, 0x66, 0x24, 0x24, 0x38, 0x18,
    0x18,

    /* U+0057 "W" */
    0xc0, 0x28, 0x8d, 0x19, 0x25, 0x24, 0xa4, 0xd4,
    0x8c, 0x61, 0x8c, 0x31, 0x80,

    /* U+0058 "X" */
    0x46, 0xc8, 0xb0, 0xc1, 0x87, 0x9, 0x23, 0x42,

    /* U+0059 "Y" */
    0xc6, 0x89, 0xb1, 0x43, 0x2, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfc, 0x31, 0x84, 0x21, 0x84, 0x30, 0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20,
    0x80,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x22, 0x95, 0x18, 0x80,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x70, 0x42, 0xf8, 0xc5, 0xe0,

    /* U+0062 "b" */
    0x84, 0x21, 0xe9, 0xc6, 0x31, 0x9f, 0x80,

    /* U+0063 "c" */
    0x76, 0x21, 0x8, 0x61, 0xe0,

    /* U+0064 "d" */
    0x8, 0x42, 0xfc, 0xc6, 0x31, 0xcb, 0xc0,

    /* U+0065 "e" */
    0x39, 0x14, 0x7f, 0x41, 0x3, 0xc0,

    /* U+0066 "f" */
    0x78, 0x8e, 0x88, 0x88, 0x88,

    /* U+0067 "g" */
    0x7e, 0x63, 0x18, 0xe5, 0xe1, 0xf0,

    /* U+0068 "h" */
    0x84, 0x21, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0x9f, 0xc0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0xe0,

    /* U+006B "k" */
    0x84, 0x21, 0x2b, 0x73, 0x94, 0x94, 0xc0,

    /* U+006C "l" */
    0xaa, 0xaa, 0xb0,

    /* U+006D "m" */
    0xf7, 0x44, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xf4, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xf4, 0xe3, 0x18, 0xcf, 0xd0, 0x80,

    /* U+0071 "q" */
    0x7e, 0x63, 0x18, 0xe5, 0xe1, 0x8,

    /* U+0072 "r" */
    0xf2, 0x49, 0x20,

    /* U+0073 "s" */
    0x78, 0x86, 0x11, 0xe0,

    /* U+0074 "t" */
    0x88, 0xe8, 0x88, 0x88, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xc5, 0xe0,

    /* U+0076 "v" */
    0xc5, 0x24, 0x92, 0x30, 0xc3, 0x0,

    /* U+0077 "w" */
    0xc8, 0xa4, 0x53, 0x4a, 0xa7, 0x51, 0x98, 0x88,

    /* U+0078 "x" */
    0x49, 0x23, 0xc, 0x39, 0x2c, 0xc0,

    /* U+0079 "y" */
    0xcd, 0x24, 0x92, 0x30, 0xc1, 0x8, 0xe0,

    /* U+007A "z" */
    0xf8, 0xcc, 0x44, 0x63, 0xe0,

    /* U+007B "{" */
    0x29, 0x24, 0xa2, 0x49, 0x22,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0x89, 0x24, 0x8a, 0x49, 0x28,

    /* U+007E "~" */
    0x64, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 53, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 108, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 20, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 46, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 40, .adv_w = 62, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 45, .adv_w = 62, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 92, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 54, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 58, .adv_w = 47, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 57, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 60, .adv_w = 47, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 74, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 108, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 108, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 108, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 47, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 47, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 131, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 135, .adv_w = 108, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 138, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 142, .adv_w = 78, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 161, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 135, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 52, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 167, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 285, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 108, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 132, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 178, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 63, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 363, .adv_w = 74, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 372, .adv_w = 63, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 108, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 381, .adv_w = 94, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 382, .adv_w = 72, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 383, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 89, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 74, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 111, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 424, .adv_w = 110, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 49, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 49, .box_w = 3, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 438, .adv_w = 100, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 52, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 473, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 479, .adv_w = 74, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 77, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 149, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 95, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 523, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 64, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 533, .adv_w = 54, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 535, .adv_w = 64, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 540, .adv_w = 108, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 3, 4, 0, 5, 6, 5,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 8, 0, 0, 0,
    0, 9, 10, 11, 12, 13, 14, 15,
    16, 0, 0, 17, 18, 19, 20, 0,
    21, 22, 23, 24, 0, 25, 26, 27,
    28, 29, 30, 31, 32, 0, 33, 0,
    0, 0, 34, 35, 36, 0, 0, 37,
    0, 38, 0, 39, 40, 0, 41, 41,
    42, 43, 44, 45, 0, 46, 0, 47,
    48, 49, 0, 50, 51, 0, 52, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 0, 0, 0,
    2, 3, 4, 5, 0, 6, 7, 6,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 9, 0, 0, 0,
    10, 11, 12, 0, 13, 0, 0, 0,
    14, 0, 0, 15, 0, 0, 16, 0,
    17, 0, 17, 0, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 0, 27, 0,
    0, 0, 28, 0, 29, 30, 31, 32,
    33, 0, 0, 34, 0, 0, 35, 35,
    36, 35, 37, 35, 38, 39, 40, 41,
    42, 43, 44, 45, 46, 0, 47, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -15, -5, -5, -24, 0,
    -5, 0, 0, 0, 2, 2, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 15, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -6, 0, 0, -6,
    -3, 2, -2, 3, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -2, -2, -2, 0, -2, -2,
    -5, 0, -7, -3, -5, -8, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, -2, -2, -23, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 5,
    -6, -6, 5, 0, -6, 3, -13, -4,
    -15, -8, 2, -15, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, -10, 0, -2,
    0, -6, -10, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -10, -5, -5,
    -14, 0, -5, 0, 6, 0, 6, 4,
    4, 7, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, -2, 0,
    0, -2, 0, -16, -2, -4, -2, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -2, -2, -5, 0,
    -2, -3, -8, -2, -7, -4, -7, -10,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -15, -4, 0, -12, 5, 0, 3, 0,
    0, -3, 6, -4, -4, 6, 0, -4,
    3, -12, -2, -12, -3, 5, -15, 4,
    0, -5, 0, -2, -2, -2, 0, -3,
    0, 0, -2, -2, 2, 0, -3, -4,
    -4, 5, -3, 3, -4, -2, 0, -2,
    -2, -5, -2, -2, 0, -4, -2, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -2, -4, -5, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -4, 0, 0, -4,
    0, 0, 4, -6, 0, 0, 3, -3,
    4, -4, -4, 4, 0, -4, 2, 3,
    0, 3, 0, 2, 3, 2, -2, 0,
    0, -3, -3, -3, 0, -3, 0, 0,
    -3, -3, 0, 0, -4, -3, -3, 3,
    -3, 0, -5, 0, -3, -5, -2, -6,
    0, -6, 0, -8, 0, -7, -2, -4,
    0, 0, -5, 0, 0, -2, -5, 0,
    -3, -3, -5, -8, -3, -2, -8, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, -3, -4, 0, -2,
    2, 0, 0, 0, 0, -3, 3, -5,
    -5, 3, 0, -5, 0, 0, -4, 0,
    0, 0, 0, 0, -3, -8, 0, -3,
    -3, -3, 0, -4, 0, 0, -3, -3,
    0, -3, -4, -5, -5, 2, -5, 0,
    -4, -4, -2, 0, -5, 0, 0, -12,
    0, -12, -3, 2, -3, -9, -2, -2,
    -15, 0, -2, 0, 3, 0, 3, 0,
    0, 4, 0, -3, -8, -10, -3, -3,
    -3, 0, -3, 0, -5, -3, -3, 0,
    0, -5, 0, 0, -7, 0, -5, 0,
    0, 0, 0, 0, -2, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, -3, 0, 0, -2,
    0, 0, 0, -2, 0, -2, 0, -7,
    0, 0, 0, -2, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -4, 0,
    0, -3, 0, -6, 3, -9, 3, 0,
    2, -4, 7, -7, -7, 5, 0, -7,
    0, 3, 0, 4, 2, 5, 4, 4,
    0, -5, 0, -4, -4, -4, 0, -4,
    0, 0, -4, -4, 3, 0, -2, -3,
    -9, 5, -2, 3, -4, 0, 0, -24,
    -2, 0, -27, 4, -13, 2, 0, 0,
    0, 5, -9, -9, 5, 0, -9, 3,
    -22, -3, -19, -9, 4, -22, 3, 0,
    -6, 0, -2, -2, -2, 0, -2, 0,
    0, -2, -2, 0, 0, 0, -8, -7,
    4, -4, 2, -5, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -4, -2, -5,
    0, -6, 0, -8, 0, -7, -2, -4,
    0, 0, -5, 0, 0, -2, -5, 0,
    -3, -3, -5, -8, -3, -2, -8, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, -2, 0, -2, -5, 0,
    -17, 0, -12, 0, 0, 0, -10, 0,
    0, -18, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, -3, -8, -4, -4,
    -4, -6, 0, -4, 0, 0, -4, -2,
    0, 0, 0, 2, 2, 0, 2, 0,
    0, -5, -3, -4, -2, 0, 0, -6,
    0, 0, 0, -7, -2, -4, 0, 0,
    -5, 0, 0, -2, -5, 0, -3, -3,
    -5, -8, -3, -2, 0, -3, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 3, 0,
    2, 0, -2, -3, 5, -2, -2, 4,
    0, -2, 0, 0, 0, -2, 0, 4,
    -4, 3, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 0, 2, -3, -3,
    0, 0, -5, 2, 0, -14, -9, -17,
    -16, 4, -10, -12, -5, -5, -17, 0,
    -5, 0, 5, 0, 5, 3, 3, 6,
    0, 0, -6, -9, -11, -11, -11, 0,
    -11, 0, -8, -11, -11, -9, 0, -7,
    -4, -16, -3, -4, -6, -5, 0, 0,
    0, -2, 0, 0, -2, 0, -8, -2,
    0, 0, -2, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -7, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -2, -4, 0, 0,
    0, 0, 0, -14, 0, 0, 0, 0,
    0, -12, -3, -3, -18, -1, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -9, -9, -9, 0, -9, 0,
    -6, -9, -9, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, -3,
    0, 0, -7, 0, -9, -2, 3, -4,
    -3, -3, -3, -12, 0, -3, 0, 4,
    0, 4, 2, 2, 5, 0, 0, -7,
    -6, -4, -4, -4, 0, -5, 0, -4,
    -4, -4, -3, 0, -4, 0, 0, 0,
    0, 0, -3, 0, 0, 0, -5, 0,
    -5, 2, -5, 2, 0, 0, -5, 5,
    -5, -5, 4, 0, -5, 0, 2, 0,
    3, 0, 3, 4, 2, 0, -7, 0,
    -3, -3, -3, 0, -3, 0, 0, -3,
    -3, 0, 0, -2, -2, -7, 4, -1,
    0, -5, 0, 0, 0, -8, 3, 0,
    -12, -9, -16, -7, 5, -11, -15, -8,
    -8, -22, -2, -8, 0, 6, 0, 6,
    4, 4, 7, 2, 0, -5, -8, -9,
    -9, -9, 0, -9, 0, -8, -9, -9,
    -4, 0, -7, 0, 0, -3, 0, -5,
    -4, 0, 0, 0, -4, 0, 0, 2,
    -12, 0, 0, 0, -3, 3, -7, -7,
    3, 0, -7, 0, 0, -3, 2, 0,
    0, 2, 0, -3, -8, 0, -3, -3,
    -3, 0, -4, 0, 0, -3, -3, 0,
    -2, -4, -4, -5, 2, -4, 0, -7,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -8, -8, -5,
    0, -8, -5, -6, -7, -6, -7, -7,
    -5, -8, 0, 15, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, 0,
    -2, 0, 0, 0, 0, -2, -2, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, -5, -4, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -2, 0, -3, 0, 0, -4, 0, -7,
    0, -5, 0, 0, 0, -4, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    -3, -2, -4, 0, -4, 0, 0, 0,
    0, 0, 2, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, -2, 0, 0, -3, 0, 0,
    -2, 0, 0, 0, 0, 2, 2, 3,
    2, 0, -4, 0, 0, 0, 0, 7,
    2, -10, -7, -8, 0, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 3, 3, 4,
    0, 0, 7, 0, -7, 0, -5, -4,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -2, 0, -3, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    2, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -5, -5, -5,
    0, -6, 0, 0, -6, -5, 0, 0,
    0, 0, 0, 4, 0, 0, -4, 0,
    0, -6, 0, -5, -4, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, 0, -3, 0, 0, -4, 0,
    -6, 0, -5, -4, 0, 0, -4, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -2, -3, -3, -4, 0, -4, 0, -6,
    0, -5, -4, 0, 0, -4, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -2,
    -3, -3, -3, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -11, -6, -9, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 4, 4, 3, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -2,
    -3, -2, 0, -2, 0, 0, -3, -2,
    0, 0, 0, 0, 0, 3, 0, 0,
    -4, 0, 0, 0, 0, 0, 2, -7,
    0, -6, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -3, -3,
    -3, 0, -2, 0, 0, -3, -3, 0,
    0, 0, 3, 3, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 2, -6, 0,
    -5, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -2, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 3, 3, 3, 3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, -4, -4, -4, 0,
    -4, 0, 0, -4, -4, 0, 0, 0,
    0, 0, 3, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, -4, -4, -4, -2, -4,
    0, 0, -4, -3, 0, -2, -2, 0,
    0, 0, 0, 0, -5, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -5, -6, -2, 0, -6, -4,
    0, -4, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 15, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, -4, 0, 0, -3, -5,
    -2, -5, -4, -6, -5, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 52,
    .right_class_cnt     = 47,
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
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
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
const lv_font_t font_ubuntu_regular_12 = {
#else
lv_font_t font_ubuntu_regular_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if FONT_UBUNTU_REGULAR_12*/
