/*******************************************************************************
 * Size: 16 px
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

#ifndef FONT_UBUNTU_REGULAR_16
#define FONT_UBUNTU_REGULAR_16 1
#endif

#if FONT_UBUNTU_REGULAR_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xf,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x11, 0x8, 0x8c, 0xdf, 0xf2, 0x21, 0x10, 0x88,
    0x44, 0xff, 0xb3, 0x11, 0x8, 0x80,

    /* U+0024 "$" */
    0x30, 0xc7, 0xb0, 0xc3, 0xf, 0x1e, 0x1c, 0x30,
    0xe3, 0xf8, 0xc3, 0x0,

    /* U+0025 "%" */
    0x70, 0xc8, 0x98, 0x89, 0x88, 0xb0, 0x8b, 0x7,
    0x60, 0x6, 0xe0, 0xd1, 0xd, 0x11, 0x91, 0x19,
    0x13, 0xe,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0x98, 0x3c, 0x6, 0x6,
    0x8b, 0x32, 0xc7, 0xb0, 0xce, 0x38, 0xf3,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xc4, 0x66, 0x31,

    /* U+0029 ")" */
    0x8c, 0x66, 0x23, 0x33, 0x33, 0x32, 0x66, 0xc8,

    /* U+002A "*" */
    0x18, 0x18, 0x5a, 0x7e, 0x3c, 0x24, 0x24,

    /* U+002B "+" */
    0x18, 0x30, 0x67, 0xf1, 0x83, 0x6, 0xc,

    /* U+002C "," */
    0x6d, 0xa4,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x6, 0x8, 0x30, 0x60, 0x83, 0x6, 0x8, 0x30,
    0x60, 0x83, 0x6, 0x8, 0x30, 0x60, 0x80,

    /* U+0030 "0" */
    0x3c, 0x66, 0x42, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x42, 0x66, 0x3c,

    /* U+0031 "1" */
    0x19, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x7d, 0x1c, 0x18, 0x30, 0xe1, 0x86, 0x18, 0x61,
    0xc3, 0x7, 0xf0,

    /* U+0033 "3" */
    0x7c, 0x1c, 0x18, 0x30, 0xc7, 0x3, 0x3, 0x6,
    0xe, 0x37, 0xc0,

    /* U+0034 "4" */
    0x6, 0xe, 0x1e, 0x36, 0x26, 0x66, 0x46, 0xc6,
    0xff, 0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x81, 0x2, 0x6, 0xf, 0x83, 0x83, 0x6,
    0xe, 0x37, 0xc0,

    /* U+0036 "6" */
    0x1c, 0x61, 0x83, 0xc, 0x1f, 0xb3, 0xe3, 0xc7,
    0x8d, 0xb1, 0xc0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x30, 0x41, 0x83, 0x4, 0x18, 0x30,
    0x40, 0x81, 0x0,

    /* U+0038 "8" */
    0x3d, 0x9e, 0x1c, 0x3c, 0xcf, 0x17, 0x47, 0x87,
    0xf, 0x3b, 0xe0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7c, 0xdf, 0x83, 0xc,
    0x18, 0x63, 0x80,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0xf, 0xe8,

    /* U+003C "<" */
    0x2, 0x1c, 0xe7, 0xe, 0x7, 0x3, 0x81,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x81, 0xc0, 0xe0, 0x70, 0xe7, 0x38, 0x40,

    /* U+003F "?" */
    0xf8, 0x30, 0xc3, 0x18, 0xc7, 0x18, 0x0, 0x6,
    0x18,

    /* U+0040 "@" */
    0xf, 0x81, 0xc3, 0x18, 0xc, 0xcf, 0xfc, 0xcd,
    0xec, 0x6f, 0x63, 0x7b, 0x1b, 0xcc, 0xd6, 0x3f,
    0x98, 0x0, 0xe0, 0x3, 0x80, 0x7, 0xe0,

    /* U+0041 "A" */
    0xc, 0x3, 0x80, 0xe0, 0x68, 0x13, 0xc, 0x43,
    0x18, 0x86, 0x7f, 0x98, 0x34, 0xf, 0x1,

    /* U+0042 "B" */
    0xfc, 0xc7, 0xc3, 0xc3, 0xc6, 0xfc, 0xc7, 0xc3,
    0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x98, 0x58, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x30, 0xc, 0x23, 0xf0,

    /* U+0044 "D" */
    0xfc, 0x63, 0x30, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xb1, 0x9f, 0x80,

    /* U+0045 "E" */
    0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0047 "G" */
    0x1f, 0x98, 0x18, 0x18, 0xc, 0x6, 0x3, 0x7,
    0x83, 0xc1, 0xb0, 0xcc, 0x63, 0xf0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,
    0xe, 0x37, 0xc0,

    /* U+004B "K" */
    0xc3, 0x63, 0x31, 0x99, 0x8d, 0x87, 0x83, 0xe1,
    0xb8, 0xce, 0x63, 0x30, 0xd8, 0x30,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+004D "M" */
    0x60, 0x66, 0x6, 0x70, 0xed, 0xb, 0xd9, 0xbc,
    0x9b, 0xc9, 0x3c, 0xf3, 0xc6, 0x3c, 0x63, 0xc0,
    0x3c, 0x3,

    /* U+004E "N" */
    0xc1, 0xf0, 0xf8, 0x7a, 0x3d, 0x9e, 0x4f, 0x37,
    0x8b, 0xc3, 0xe1, 0xf0, 0x78, 0x30,

    /* U+004F "O" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x6c, 0x18, 0xc6, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x6c, 0x18, 0xc6, 0xf,
    0x80, 0x60, 0x7, 0x0, 0x30,

    /* U+0052 "R" */
    0xfc, 0x63, 0x30, 0xd8, 0x6c, 0x36, 0x3b, 0xf9,
    0x98, 0xc6, 0x61, 0x30, 0xd8, 0x20,

    /* U+0053 "S" */
    0x7d, 0x8b, 0x6, 0xe, 0xf, 0xf, 0x7, 0x6,
    0xe, 0x3f, 0xc0,

    /* U+0054 "T" */
    0xff, 0x8c, 0x6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xc0, 0xd0, 0x36, 0xd, 0x82, 0x21, 0x8c, 0x63,
    0x10, 0x4c, 0x1a, 0x7, 0x80, 0xe0, 0x30,

    /* U+0057 "W" */
    0x40, 0x5, 0x4, 0x14, 0x30, 0xd8, 0xe3, 0x62,
    0x8d, 0x8a, 0x22, 0x6c, 0x89, 0x16, 0x34, 0x58,
    0xf1, 0xc1, 0x83, 0x6, 0xc,

    /* U+0058 "X" */
    0x61, 0x98, 0x63, 0x30, 0x48, 0x1e, 0x3, 0x1,
    0xe0, 0x78, 0x33, 0x8, 0x46, 0x19, 0x3,

    /* U+0059 "Y" */
    0xc0, 0xd8, 0x66, 0x18, 0xcc, 0x33, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0x3, 0x6, 0xc, 0x8, 0x18, 0x30, 0x30,
    0x60, 0x40, 0xc0, 0xff,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0x81, 0x3, 0x2, 0x4, 0xc, 0x8, 0x10, 0x30,
    0x20, 0x40, 0xc0, 0x81, 0x3, 0x2, 0x4,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x10, 0x71, 0xb3, 0x2c, 0x70, 0x40,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x88, 0x80,

    /* U+0061 "a" */
    0x7c, 0x1c, 0x18, 0x37, 0xf8, 0xf1, 0xe3, 0x7e,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc6, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0063 "c" */
    0x3e, 0xc3, 0x6, 0xc, 0x18, 0x30, 0x30, 0x3e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3f, 0x63, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x63, 0x3f,

    /* U+0065 "e" */
    0x1c, 0x66, 0x43, 0x43, 0xff, 0x40, 0x40, 0x60,
    0x3e,

    /* U+0066 "f" */
    0x7b, 0x8c, 0x30, 0xfb, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc0,

    /* U+0067 "g" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xb3, 0x3e,
    0xc, 0x1b, 0xe0,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xf, 0xd9, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+0069 "i" */
    0xf0, 0xff, 0xff, 0xc0,

    /* U+006A "j" */
    0x33, 0x0, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0xc, 0x79, 0xb6, 0x78, 0xf1,
    0xb3, 0x36, 0x2c, 0x60,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x76,

    /* U+006D "m" */
    0xff, 0xec, 0xe7, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xfd, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6,
    0xfc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3f, 0x63, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x63,
    0x3f, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7b, 0xc, 0x38, 0x78, 0x70, 0xc3, 0xf8,

    /* U+0074 "t" */
    0xc6, 0x31, 0xfc, 0x63, 0x18, 0xc6, 0x30, 0xf0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xb3, 0x3e,

    /* U+0076 "v" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x24, 0x3c, 0x18,
    0x18,

    /* U+0077 "w" */
    0xc2, 0x34, 0x63, 0x46, 0x36, 0x72, 0x65, 0x62,
    0x96, 0x39, 0xc3, 0x8c, 0x18, 0xc0,

    /* U+0078 "x" */
    0x42, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x24, 0x66,
    0xc3,

    /* U+0079 "y" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x24, 0x3c, 0x18,
    0x18, 0x18, 0x10, 0xe0,

    /* U+007A "z" */
    0xfc, 0x31, 0x84, 0x31, 0x84, 0x30, 0xfc,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x18, 0xd8, 0x31, 0x8c, 0x63,
    0x18, 0xc3,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0xc1, 0x31, 0x8c, 0x63,
    0x18, 0xdc,

    /* U+007E "~" */
    0x63, 0x26, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 71, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 107, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 144, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 220, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 62, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 67, .adv_w = 83, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 75, .adv_w = 83, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 83, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 90, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 97, .adv_w = 63, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 99, .adv_w = 77, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 100, .adv_w = 63, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 98, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 116, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 144, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 63, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 63, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 231, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 238, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 243, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 250, .adv_w = 103, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 243, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 282, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 165, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 183, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 172, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 180, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 133, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 223, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 186, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 199, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 199, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 509, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 176, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 168, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 238, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 153, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 84, .box_w = 4, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 648, .adv_w = 98, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 663, .adv_w = 84, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 671, .adv_w = 144, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 677, .adv_w = 126, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 678, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 680, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 119, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 99, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 148, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 752, .adv_w = 146, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 65, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 65, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 70, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 220, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 147, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 836, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 848, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 103, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 147, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 199, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 131, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 921, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 85, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 938, .adv_w = 71, .box_w = 2, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 943, .adv_w = 85, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 953, .adv_w = 144, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
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
    0, 0, 0, -20, -6, -6, -31, 0,
    -6, 0, 0, 0, 3, 3, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 20, 0, 0, 0, 0, 0,
    0, 0, 0, -8, -8, 0, 0, -8,
    -5, 3, -3, 4, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -3, -3, -3, 0, -3, -3,
    -7, 0, -9, -5, -7, -11, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -16, -3, -3, -31, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 6,
    -7, -7, 7, 0, -8, 4, -18, -6,
    -20, -10, 3, -20, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, -13, 0, -3,
    0, -8, -13, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -13, -7, -7,
    -18, 0, -7, 0, 7, 0, 8, 6,
    5, 9, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, -3, 0,
    0, -3, 0, -22, -3, -5, -3, 0,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, -3, -3, -7, 0,
    -3, -5, -11, -3, -9, -6, -10, -14,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -20, -5, 0, -16, 7, 0, 4, 0,
    0, -4, 8, -5, -5, 7, 0, -5,
    4, -16, -3, -16, -5, 6, -20, 5,
    0, -7, 0, -3, -3, -3, 0, -4,
    0, 0, -3, -3, 3, 0, -4, -5,
    -5, 7, -4, 4, -5, -3, 0, -3,
    -3, -6, -3, -3, 0, -5, -3, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, -3, -5, -6, 0, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -6, 0, 0, -6,
    0, 0, 6, -8, 0, 0, 4, -4,
    6, -5, -5, 6, 0, -5, 3, 4,
    0, 4, 0, 3, 4, 3, -3, 0,
    0, -4, -4, -4, 0, -4, 0, 0,
    -4, -4, 0, 0, -5, -4, -4, 4,
    -4, 0, -7, 0, -4, -7, -3, -8,
    0, -8, 0, -11, 0, -10, -3, -5,
    0, 0, -6, 0, 0, -3, -7, 0,
    -4, -4, -6, -10, -4, -3, -11, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, -4, -5, 0, -3,
    3, 0, 0, 0, 0, -4, 4, -7,
    -7, 4, 0, -7, 0, 0, -6, 0,
    0, 0, 0, 0, -4, -11, 0, -4,
    -4, -4, 0, -6, 0, 0, -4, -4,
    0, -4, -5, -6, -6, 2, -6, 0,
    -5, -6, -3, 0, -6, 0, 0, -17,
    0, -15, -5, 3, -5, -12, -3, -3,
    -20, 0, -3, 0, 4, 0, 5, 0,
    0, 5, 0, -4, -10, -13, -4, -4,
    -4, 0, -4, 0, -7, -4, -4, 0,
    0, -6, 0, 0, -9, 0, -7, 0,
    0, 0, 0, 0, -3, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, -5, 0, 0, -3,
    0, 0, 0, -3, 0, -3, 0, -9,
    0, 0, 0, -3, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -5, 0,
    0, -5, 0, -8, 4, -12, 5, 0,
    3, -5, 9, -9, -9, 7, 0, -9,
    0, 4, 0, 5, 3, 7, 6, 5,
    0, -7, 0, -5, -5, -5, 0, -5,
    0, 0, -5, -5, 4, 0, -3, -4,
    -12, 7, -3, 4, -5, 0, 0, -32,
    -3, 0, -36, 6, -18, 3, 0, 0,
    0, 7, -12, -12, 7, 0, -12, 4,
    -29, -5, -26, -12, 5, -29, 4, 0,
    -8, 0, -3, -3, -3, 0, -3, 0,
    0, -3, -3, 0, 0, 0, -10, -9,
    5, -5, 3, -6, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -6, -3, -7,
    0, -8, 0, -11, 0, -9, -3, -5,
    0, 0, -6, 0, 0, -3, -7, 0,
    -4, -4, -6, -10, -4, -3, -11, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, -3, 0, -3, -6, 0,
    -23, 0, -16, 0, 0, 0, -13, 0,
    0, -24, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, -4, -10, -5, -5,
    -5, -8, 0, -5, 0, 0, -5, -3,
    0, 0, 0, 3, 2, 0, 3, 0,
    0, -6, -4, -6, -3, 0, 0, -8,
    0, 0, 0, -9, -3, -5, 0, 0,
    -6, 0, 0, -3, -7, 0, -4, -4,
    -6, -10, -4, -3, 0, -4, 0, 0,
    0, 0, 0, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 4, 0,
    3, 0, -3, -4, 7, -3, -3, 6,
    0, -3, 0, 0, 0, -3, 0, 5,
    -5, 4, 0, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 5, 0, 2, -4, -4,
    0, 0, -7, 3, 0, -19, -13, -22,
    -22, 6, -13, -16, -7, -7, -23, 0,
    -7, 0, 6, 0, 7, 4, 4, 7,
    0, 0, -8, -12, -14, -14, -14, 0,
    -14, 0, -10, -14, -14, -12, 0, -9,
    -6, -21, -5, -6, -8, -6, 0, 0,
    0, -3, 0, 0, -3, 0, -10, -3,
    0, 0, -3, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -9, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -3, -6, 0, 0,
    0, 0, 0, -19, 0, 0, 0, 0,
    0, -16, -4, -4, -24, -2, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -12, -12, -12, 0, -12, 0,
    -8, -12, -12, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, -4,
    0, 0, -9, 0, -12, -3, 4, -5,
    -5, -4, -4, -15, 0, -4, 0, 5,
    0, 6, 3, 3, 6, 0, 0, -9,
    -7, -6, -6, -6, 0, -7, 0, -5,
    -6, -6, -4, 0, -5, 0, 0, 0,
    0, 0, -4, 0, 0, 0, -6, 0,
    -7, 3, -7, 3, 0, 0, -7, 7,
    -6, -6, 5, 0, -6, 0, 3, 0,
    4, 0, 5, 5, 3, 0, -9, 0,
    -5, -5, -5, 0, -5, 0, 0, -5,
    -5, 0, 0, -3, -3, -9, 5, -2,
    0, -7, 0, 0, 0, -11, 5, 0,
    -17, -13, -21, -10, 6, -15, -20, -10,
    -10, -29, -2, -10, 0, 8, 0, 8,
    6, 5, 9, 3, 0, -7, -10, -13,
    -13, -13, 0, -13, 0, -10, -13, -13,
    -5, 0, -9, 0, 0, -4, 0, -7,
    -6, 0, 0, 0, -5, 0, 0, 3,
    -15, 0, 0, 0, -4, 4, -9, -9,
    4, 0, -9, 0, 0, -4, 3, 0,
    0, 3, 0, -4, -11, 0, -4, -4,
    -4, 0, -6, 0, 0, -4, -4, 0,
    -3, -5, -6, -6, 2, -6, 0, -9,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, -11, -11, -7,
    0, -11, -7, -8, -10, -7, -9, -9,
    -7, -10, 0, 20, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -3, 0, 0,
    -3, 0, 0, 0, 0, -3, -3, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, -6, -5, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -3, 0, -4, 0, 0, -5, 0, -9,
    0, -7, 0, 0, 0, -6, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -3,
    -4, -3, -5, 0, -5, 0, 0, 0,
    0, 0, 3, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, -3, 0, 0, -4, 0, 0,
    -3, 0, 0, 0, 0, 3, 3, 4,
    3, 0, -5, 0, 0, 0, 0, 10,
    3, -13, -9, -11, 0, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 10, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 5, 4, 5,
    0, 0, 10, 0, -9, 0, -6, -5,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, 0, -4, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    3, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -7, -7, -7,
    0, -7, 0, 0, -7, -7, 0, 0,
    0, 0, 0, 5, 0, 0, -5, 0,
    0, -8, 0, -6, -6, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -4, 0, -5, 0, 0, -5, 0,
    -8, 0, -7, -5, 0, 0, -6, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -3, -4, -4, -5, 0, -5, 0, -8,
    0, -7, -5, 0, 0, -6, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, -3,
    -4, -4, -5, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, -14, -8, -12, 0, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 5, 5, 4, 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -3,
    -4, -3, 0, -3, 0, 0, -4, -3,
    0, 0, 0, 0, 0, 4, 0, 0,
    -5, 0, 0, 0, 0, 0, 2, -9,
    0, -8, 0, -10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, -4, -4,
    -4, 0, -3, 0, 0, -4, -4, 0,
    0, 0, 5, 4, 4, 5, 0, 0,
    0, 0, 0, 0, 0, 2, -8, 0,
    -7, 0, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, 0, -3, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 5, 4, 4, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, -5, -5, -5, 0,
    -5, 0, 0, -5, -5, 0, 0, 0,
    0, 0, 4, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, -5, -5, -5, -3, -6,
    0, 0, -5, -5, 0, -3, -3, 0,
    0, 0, 0, 0, -7, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -7, -8, -3, 0, -8, -5,
    0, -6, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 20, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, -5, 0, 0, -5, -6,
    -3, -6, -5, -7, -6, -9, 0, 0,
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
const lv_font_t font_ubuntu_regular_16 = {
#else
lv_font_t font_ubuntu_regular_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
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



#endif /*#if FONT_UBUNTU_REGULAR_16*/
