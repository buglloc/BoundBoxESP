/*******************************************************************************
 * Size: 14 px
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

#ifndef FONT_UBUNTU_REGULAR_14
#define FONT_UBUNTU_REGULAR_14 1
#endif

#if FONT_UBUNTU_REGULAR_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0xc0,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x32, 0x22, 0xff, 0x24, 0x24, 0x24, 0xff, 0x44,
    0x4c, 0x48,

    /* U+0024 "$" */
    0x23, 0xe1, 0xc, 0x30, 0xc1, 0x8, 0x7c, 0x42,
    0x0,

    /* U+0025 "%" */
    0x61, 0x92, 0x62, 0x48, 0x4b, 0x6, 0x5c, 0x1c,
    0x42, 0x88, 0x91, 0x12, 0x24, 0x38,

    /* U+0026 "&" */
    0x38, 0x22, 0x11, 0xd, 0x83, 0x82, 0xca, 0x35,
    0xc, 0xc7, 0x3c, 0x80,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0xd, 0x29, 0x24, 0x92, 0x24, 0xc8,

    /* U+0029 ")" */
    0x19, 0x22, 0x49, 0x24, 0xa5, 0xa0,

    /* U+002A "*" */
    0x25, 0x5c, 0xa5, 0x0,

    /* U+002B "+" */
    0x10, 0x41, 0x3f, 0x10, 0x41, 0x0,

    /* U+002C "," */
    0x55,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x20, 0x86, 0x10, 0x43, 0x8, 0x21, 0x84,
    0x10, 0xc3, 0x8, 0x0,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xc0,

    /* U+0031 "1" */
    0x13, 0x51, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0xf2, 0x20, 0x82, 0x10, 0xc6, 0x10, 0xc3, 0xf0,

    /* U+0033 "3" */
    0xf2, 0x20, 0x82, 0x70, 0x30, 0x41, 0xf, 0xe0,

    /* U+0034 "4" */
    0x8, 0x30, 0xa3, 0x44, 0x91, 0x3f, 0x84, 0x8,
    0x10,

    /* U+0035 "5" */
    0xfe, 0x31, 0xf, 0xc, 0x21, 0x1f, 0x80,

    /* U+0036 "6" */
    0x1c, 0x84, 0x3e, 0x8e, 0x18, 0x61, 0x49, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x30, 0x84, 0x10, 0xc2, 0x8, 0x21, 0x80,

    /* U+0038 "8" */
    0x7b, 0x38, 0x61, 0x79, 0x68, 0x61, 0x85, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x28, 0x61, 0xc5, 0xf0, 0x42, 0x1b, 0x80,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0x5, 0x70,

    /* U+003C "<" */
    0x4, 0x77, 0x30, 0x70, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x83, 0x81, 0x3b, 0x88, 0x0,

    /* U+003F "?" */
    0xf0, 0x42, 0x22, 0x21, 0x0, 0x63, 0x0,

    /* U+0040 "@" */
    0x1f, 0x4, 0x19, 0x3d, 0x6c, 0x99, 0x13, 0x22,
    0x64, 0x4c, 0xcb, 0xcf, 0xc8, 0x0, 0x80, 0xf,
    0x80,

    /* U+0041 "A" */
    0x8, 0xe, 0x5, 0x6, 0xc2, 0x21, 0x19, 0xfc,
    0x82, 0x41, 0xe0, 0x40,

    /* U+0042 "B" */
    0xf9, 0x1a, 0x14, 0x6f, 0x90, 0xe0, 0xc1, 0x87,
    0xf0,

    /* U+0043 "C" */
    0x3e, 0xc7, 0x4, 0x8, 0x10, 0x20, 0x60, 0x60,
    0x7c,

    /* U+0044 "D" */
    0xf8, 0x86, 0x82, 0x81, 0x81, 0x81, 0x81, 0x82,
    0x86, 0xf8,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x82, 0x0,

    /* U+0047 "G" */
    0x3e, 0xc7, 0x4, 0x8, 0x10, 0x60, 0xe1, 0x62,
    0x7c,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0x83,
    0x4,

    /* U+0049 "I" */
    0xff, 0xc0,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x21, 0x1f, 0x80,

    /* U+004B "K" */
    0x85, 0x12, 0x65, 0x8e, 0x1c, 0x24, 0x44, 0x8d,
    0xc,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0x87, 0xc0,

    /* U+004D "M" */
    0xc0, 0xf0, 0x3e, 0x1e, 0x85, 0xb3, 0x64, 0x99,
    0xe6, 0x31, 0x8c, 0x60, 0x10,

    /* U+004E "N" */
    0x81, 0xc1, 0xe1, 0xb1, 0x99, 0x8d, 0x85, 0x87,
    0x83, 0x81,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x83, 0x63, 0x1f, 0x0,

    /* U+0050 "P" */
    0xf9, 0xe, 0xc, 0x18, 0x7f, 0x20, 0x40, 0x81,
    0x0,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x83, 0x63, 0x1f, 0x3, 0x0, 0xf0, 0x0,

    /* U+0052 "R" */
    0xf8, 0x86, 0x82, 0x82, 0x86, 0xfc, 0x88, 0x84,
    0x86, 0x82,

    /* U+0053 "S" */
    0x7e, 0x8, 0x30, 0x70, 0x60, 0x41, 0x7, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0056 "V" */
    0xc1, 0xa0, 0xd0, 0x4c, 0x62, 0x21, 0x10, 0xd8,
    0x28, 0x1c, 0x4, 0x0,

    /* U+0057 "W" */
    0xc0, 0x1a, 0x10, 0x90, 0x84, 0x8a, 0x26, 0x53,
    0x32, 0xd8, 0xa2, 0x85, 0x14, 0x38, 0xe0, 0x82,
    0x0,

    /* U+0058 "X" */
    0x43, 0x31, 0xd, 0x82, 0x81, 0x80, 0xe0, 0xd0,
    0x44, 0x63, 0x20, 0x80,

    /* U+0059 "Y" */
    0x83, 0x8d, 0x13, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0xc1, 0x6, 0x18, 0x20, 0xc1,
    0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+005C "\\" */
    0x82, 0xc, 0x10, 0x41, 0x82, 0x8, 0x30, 0x41,
    0x6, 0x8, 0x20, 0xc0,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+005E "^" */
    0x30, 0xc4, 0xb2, 0x86, 0x10,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x34,

    /* U+0061 "a" */
    0x78, 0x30, 0x5f, 0xc6, 0x18, 0x5f,

    /* U+0062 "b" */
    0x82, 0x8, 0x20, 0xfa, 0x28, 0x61, 0x86, 0x18,
    0xbc,

    /* U+0063 "c" */
    0x3a, 0x21, 0x8, 0x41, 0x7,

    /* U+0064 "d" */
    0x4, 0x10, 0x41, 0x7d, 0x18, 0x61, 0x86, 0x14,
    0x4f,

    /* U+0065 "e" */
    0x39, 0x3c, 0x7f, 0x83, 0x4, 0xf,

    /* U+0066 "f" */
    0x78, 0x8f, 0x88, 0x88, 0x88, 0x80,

    /* U+0067 "g" */
    0x3d, 0x18, 0x61, 0x86, 0x14, 0x5f, 0x4, 0x3f,
    0x80,

    /* U+0068 "h" */
    0x82, 0x8, 0x20, 0xfa, 0x38, 0x61, 0x86, 0x18,
    0x61,

    /* U+0069 "i" */
    0xdf, 0xe0,

    /* U+006A "j" */
    0x24, 0x12, 0x49, 0x24, 0x93, 0x80,

    /* U+006B "k" */
    0x82, 0x8, 0x20, 0x9a, 0x4a, 0x30, 0xe2, 0xc9,
    0xa2,

    /* U+006C "l" */
    0xaa, 0xaa, 0xab,

    /* U+006D "m" */
    0xf7, 0x4c, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x23,
    0x11,

    /* U+006E "n" */
    0xfa, 0x38, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0xbe, 0x82, 0x8,
    0x0,

    /* U+0071 "q" */
    0x3d, 0x18, 0x61, 0x86, 0x14, 0x5f, 0x4, 0x10,
    0x40,

    /* U+0072 "r" */
    0xf8, 0x88, 0x88, 0x88,

    /* U+0073 "s" */
    0x7c, 0x21, 0xc3, 0x84, 0x3e,

    /* U+0074 "t" */
    0x88, 0xf8, 0x88, 0x88, 0x87,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0x5f,

    /* U+0076 "v" */
    0xc6, 0x89, 0x13, 0x62, 0x85, 0xe, 0x8,

    /* U+0077 "w" */
    0xc4, 0x68, 0x89, 0x39, 0x25, 0x66, 0xa8, 0x55,
    0xc, 0x61, 0x88,

    /* U+0078 "x" */
    0x44, 0xd8, 0xa0, 0x83, 0x85, 0x11, 0x63,

    /* U+0079 "y" */
    0xc6, 0x89, 0x13, 0x22, 0xc5, 0xe, 0xc, 0x10,
    0x63, 0x80,

    /* U+007A "z" */
    0xfc, 0x21, 0x8c, 0x21, 0x8c, 0x3f,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x13, 0x4, 0x21, 0x8, 0x42,
    0xc,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x64, 0x21, 0x8, 0x42,
    0x60,

    /* U+007E "~" */
    0xe6, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 52, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 62, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 94, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 126, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 54, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 51, .adv_w = 73, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 57, .adv_w = 73, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 63, .adv_w = 108, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 67, .adv_w = 126, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 73, .adv_w = 55, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 67, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 75, .adv_w = 55, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 86, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 88, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 126, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 126, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 126, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 55, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 170, .adv_w = 126, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 176, .adv_w = 126, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 179, .adv_w = 126, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 185, .adv_w = 90, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 213, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 209, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 158, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 60, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 195, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 163, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 174, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 367, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 147, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 208, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 74, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 468, .adv_w = 86, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 480, .adv_w = 74, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 486, .adv_w = 126, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 491, .adv_w = 110, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 492, .adv_w = 84, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 493, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 132, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 132, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 86, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 129, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 543, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 57, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 57, .box_w = 3, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 560, .adv_w = 117, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 61, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 193, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 603, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 612, .adv_w = 86, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 90, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 174, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 111, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 667, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 75, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 682, .adv_w = 62, .box_w = 1, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 684, .adv_w = 75, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 693, .adv_w = 126, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3}
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
    0, 0, 0, -18, -6, -6, -28, 0,
    -6, 0, 0, 0, 3, 2, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 18, 0, 0, 0, 0, 0,
    0, 0, 0, -7, -7, 0, 0, -7,
    -4, 2, -2, 3, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -3, -3, -3, 0, -3, -3,
    -6, 0, -8, -4, -6, -10, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, -2, -2, -27, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 6,
    -6, -6, 6, 0, -7, 3, -16, -5,
    -17, -9, 2, -18, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, -11, 0, -3,
    0, -7, -11, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, -6, -6,
    -16, 0, -6, 0, 6, 0, 7, 5,
    4, 8, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, -2, 0,
    0, -2, 0, -19, -3, -5, -3, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -2, -2, -6, 0,
    -2, -4, -10, -3, -8, -5, -9, -12,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, -4, 0, -14, 6, 0, 4, 0,
    0, -3, 7, -4, -4, 6, 0, -4,
    4, -14, -2, -14, -4, 6, -18, 4,
    0, -6, 0, -3, -3, -3, 0, -4,
    0, 0, -3, -3, 3, 0, -3, -5,
    -4, 6, -3, 3, -4, -2, 0, -2,
    -2, -6, -2, -2, 0, -5, -2, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -3, -5, -6, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -5, 0, 0, -5,
    0, 0, 5, -7, 0, 0, 3, -4,
    5, -4, -4, 5, 0, -4, 2, 4,
    0, 4, 0, 3, 4, 2, -2, 0,
    0, -3, -3, -3, 0, -3, 0, 0,
    -3, -3, 0, 0, -4, -4, -4, 3,
    -4, 0, -6, 0, -3, -6, -3, -7,
    0, -7, 0, -10, 0, -9, -2, -4,
    0, 0, -6, 0, 0, -2, -6, 0,
    -4, -4, -5, -9, -3, -2, -9, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, -4, -5, 0, -3,
    2, 0, 0, 0, 0, -4, 4, -6,
    -6, 4, 0, -6, 0, 0, -5, 0,
    0, 0, 0, 0, -4, -10, 0, -4,
    -4, -4, 0, -5, 0, 0, -4, -3,
    0, -3, -4, -6, -6, 2, -6, 0,
    -4, -5, -2, 0, -5, 0, 0, -15,
    0, -13, -4, 3, -4, -10, -3, -3,
    -18, 0, -3, 0, 3, 0, 4, 0,
    0, 4, 0, -3, -9, -11, -3, -3,
    -3, 0, -3, 0, -6, -3, -3, 0,
    0, -6, 0, 0, -8, 0, -6, 0,
    0, 0, 0, 0, -2, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -4, 0, 0, -2,
    0, 0, 0, -2, 0, -2, 0, -8,
    0, 0, 0, -2, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, 0,
    0, -4, 0, -7, 4, -11, 4, 0,
    2, -4, 8, -8, -8, 6, 0, -8,
    0, 4, 0, 4, 2, 6, 5, 5,
    0, -6, 0, -5, -5, -5, 0, -5,
    0, 0, -5, -5, 3, 0, -3, -3,
    -11, 6, -2, 4, -4, 0, 0, -28,
    -2, 0, -31, 5, -15, 3, 0, 0,
    0, 6, -10, -10, 6, 0, -10, 3,
    -26, -4, -22, -10, 4, -26, 3, 0,
    -7, 0, -3, -3, -3, 0, -3, 0,
    0, -3, -3, 0, 0, 0, -9, -8,
    5, -4, 2, -5, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -5, -3, -6,
    0, -7, 0, -9, 0, -8, -2, -4,
    0, 0, -6, 0, 0, -2, -6, 0,
    -4, -4, -5, -9, -3, -2, -9, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, -2, 0, -3, -5, 0,
    -20, 0, -14, 0, 0, 0, -11, 0,
    0, -21, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -3, -9, -4, -5,
    -5, -7, 0, -5, 0, 0, -5, -2,
    0, 0, 0, 2, 2, 0, 2, 0,
    0, -5, -3, -5, -3, 0, 0, -7,
    0, 0, 0, -8, -2, -4, 0, 0,
    -6, 0, 0, -2, -6, 0, -4, -4,
    -5, -9, -3, -2, 0, -3, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 3, 0,
    3, 0, -3, -3, 6, -2, -2, 5,
    0, -2, 0, 0, 0, -2, 0, 4,
    -4, 3, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 5, 0, 2, -4, -4,
    0, 0, -6, 3, 0, -17, -11, -19,
    -19, 5, -11, -14, -6, -6, -20, 0,
    -6, 0, 5, 0, 6, 4, 3, 6,
    0, 0, -7, -10, -12, -12, -12, 0,
    -12, 0, -9, -12, -12, -10, 0, -8,
    -5, -18, -4, -5, -7, -5, 0, 0,
    0, -2, 0, 0, -2, 0, -9, -2,
    0, 0, -2, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -8, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -2, -5, 0, 0,
    0, 0, 0, -17, 0, 0, 0, 0,
    0, -14, -4, -4, -21, -1, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -10, -10, -10, 0, -10, 0,
    -7, -10, -10, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, -4,
    0, 0, -8, 0, -11, -2, 4, -4,
    -4, -4, -4, -13, 0, -4, 0, 4,
    0, 5, 3, 2, 5, 0, 0, -8,
    -6, -5, -5, -5, 0, -6, 0, -5,
    -5, -5, -4, 0, -4, 0, 0, 0,
    0, 0, -4, 0, 0, 0, -6, 0,
    -6, 3, -6, 2, 0, 0, -6, 6,
    -5, -5, 4, 0, -5, 0, 3, 0,
    4, 0, 4, 4, 3, 0, -8, 0,
    -4, -4, -4, 0, -4, 0, 0, -4,
    -4, 0, 0, -2, -2, -8, 4, -2,
    0, -6, 0, 0, 0, -9, 4, 0,
    -15, -11, -18, -9, 6, -13, -18, -9,
    -9, -26, -2, -9, 0, 7, 0, 7,
    5, 5, 8, 2, 0, -6, -9, -11,
    -11, -11, 0, -11, 0, -9, -11, -11,
    -4, 0, -8, 0, 0, -3, 0, -6,
    -5, 0, 0, 0, -5, 0, 0, 2,
    -13, 0, 0, 0, -4, 4, -8, -8,
    4, 0, -8, 0, 0, -3, 2, 0,
    0, 3, 0, -4, -10, 0, -4, -4,
    -4, 0, -5, 0, 0, -4, -3, 0,
    -3, -4, -5, -5, 2, -5, 0, -8,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -10, -10, -6,
    0, -10, -6, -7, -9, -6, -8, -8,
    -6, -9, 0, 18, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, 0,
    -2, 0, 0, 0, 0, -2, -2, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -5, -4, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -3, 0, -3, 0, 0, -5, 0, -8,
    0, -6, 0, 0, 0, -5, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -3,
    -4, -3, -4, 0, -5, 0, 0, 0,
    0, 0, 2, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, -3, 0, 0, -4, 0, 0,
    -3, 0, 0, 0, 0, 2, 2, 4,
    2, 0, -5, 0, 0, 0, 0, 9,
    2, -12, -8, -9, 0, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 3, 4,
    0, 0, 9, 0, -8, 0, -5, -5,
    0, 0, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -3, 0, -4, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    2, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -6, -6, -6,
    0, -6, 0, 0, -6, -6, 0, 0,
    0, 0, 0, 4, 0, 0, -4, 0,
    0, -7, 0, -6, -5, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -3, 0, -4, 0, 0, -5, 0,
    -7, 0, -6, -4, 0, 0, -5, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    -3, -4, -3, -4, 0, -5, 0, -7,
    0, -6, -4, 0, 0, -5, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -3,
    -4, -3, -4, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, -12, -7, -10, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 5, 4, 4, 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -3,
    -3, -2, 0, -2, 0, 0, -3, -3,
    0, 0, 0, 0, 0, 4, 0, 0,
    -5, 0, 0, 0, 0, 0, 2, -8,
    0, -7, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -3, -3,
    -3, 0, -3, 0, 0, -3, -3, 0,
    0, 0, 4, 4, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 2, -7, 0,
    -6, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -3, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 4, 4, 3, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, -5, -5, -5, 0,
    -5, 0, 0, -5, -5, 0, 0, 0,
    0, 0, 4, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, -4, -4, -4, -3, -5,
    0, 0, -4, -4, 0, -3, -3, 0,
    0, 0, 0, 0, -6, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -6, -7, -3, 0, -7, -5,
    0, -5, 0, 0, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 18, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, -5, 0, 0, -4, -6,
    -2, -6, -4, -6, -5, -8, 0, 0,
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
const lv_font_t font_ubuntu_regular_14 = {
#else
lv_font_t font_ubuntu_regular_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONT_UBUNTU_REGULAR_14*/
