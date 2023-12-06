/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts:
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_ROBOTO_BLACK_14
#define FONT_ROBOTO_BLACK_14 1
#endif

#if FONT_ROBOTO_BLACK_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x3c,

    /* U+0022 "\"" */
    0xff, 0xff,

    /* U+0023 "#" */
    0x14, 0x14, 0x14, 0x7f, 0x7f, 0x2c, 0xfe, 0xfe,
    0x28, 0x28, 0x28,

    /* U+0024 "$" */
    0x10, 0x21, 0xf3, 0x36, 0x6e, 0xe, 0xe, 0xf,
    0x8f, 0x1b, 0xe3, 0x82, 0x0,

    /* U+0025 "%" */
    0x70, 0x7c, 0x36, 0x9f, 0x87, 0x40, 0x40, 0x6c,
    0x2f, 0x25, 0x83, 0xc0, 0xc0,

    /* U+0026 "&" */
    0x38, 0x3e, 0x1b, 0xd, 0x87, 0x81, 0x81, 0xed,
    0xbe, 0xce, 0x7f, 0x1e, 0xc0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xc4, 0x62, 0x30,

    /* U+0029 ")" */
    0x8c, 0x66, 0x33, 0x33, 0x33, 0x32, 0x64, 0xc0,

    /* U+002A "*" */
    0x10, 0x21, 0xf9, 0xc2, 0x8d, 0x80, 0x0,

    /* U+002B "+" */
    0x30, 0x63, 0xff, 0xf3, 0x6, 0xc, 0x0,

    /* U+002C "," */
    0x6d, 0xa4,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0x8c, 0x63, 0x11, 0x8c, 0x46, 0x31, 0x0,

    /* U+0030 "0" */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xf8, 0xe0,

    /* U+0031 "1" */
    0xb, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc6,

    /* U+0032 "2" */
    0x3c, 0xff, 0x1e, 0x30, 0x61, 0x86, 0x18, 0x71,
    0xff, 0xf8,

    /* U+0033 "3" */
    0x3c, 0xff, 0x98, 0x31, 0xc3, 0x81, 0x83, 0x66,
    0xfc, 0xf0,

    /* U+0034 "4" */
    0xc, 0x1c, 0x1c, 0x3c, 0x2c, 0x6c, 0xcc, 0xff,
    0xff, 0xc, 0xc,

    /* U+0035 "5" */
    0x7e, 0xfd, 0x83, 0x7, 0xcf, 0xc1, 0x83, 0x66,
    0xfc, 0xf0,

    /* U+0036 "6" */
    0x1c, 0x79, 0xc7, 0xf, 0xdf, 0xf1, 0xe3, 0xc6,
    0xf8, 0xe0,

    /* U+0037 "7" */
    0xff, 0xfc, 0x38, 0x60, 0xc3, 0x6, 0x1c, 0x30,
    0x61, 0xc0,

    /* U+0038 "8" */
    0x7d, 0xff, 0x1e, 0x37, 0xcf, 0xb1, 0xe3, 0xc7,
    0xfd, 0xf0,

    /* U+0039 "9" */
    0x38, 0xfb, 0x9e, 0x3c, 0x78, 0xff, 0xbf, 0xc,
    0xf1, 0xc0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xfc, 0x0, 0x1b, 0x78, 0x0,

    /* U+003C "<" */
    0x4, 0x7f, 0xb0, 0xf8, 0xf0, 0xc0,

    /* U+003D "=" */
    0xff, 0xf0, 0x3f, 0xfc,

    /* U+003E ">" */
    0x83, 0x87, 0xc3, 0x7f, 0xcc, 0x0,

    /* U+003F "?" */
    0x7b, 0xfe, 0xc3, 0x1c, 0x63, 0xc, 0x0, 0xc3,
    0x0,

    /* U+0040 "@" */
    0xf, 0x83, 0xc, 0x60, 0x66, 0x72, 0xcf, 0x3d,
    0xd3, 0xd9, 0x3d, 0x93, 0xd9, 0x7d, 0xfe, 0xec,
    0xc7, 0x0, 0x3f, 0x1, 0xf0,

    /* U+0041 "A" */
    0x1c, 0x7, 0x1, 0xe0, 0xf8, 0x36, 0xd, 0xc7,
    0x31, 0xfc, 0x7f, 0xb8, 0x6e, 0x18,

    /* U+0042 "B" */
    0xfd, 0xff, 0x1e, 0x3c, 0x7f, 0xbf, 0xe3, 0xc7,
    0xff, 0xf0,

    /* U+0043 "C" */
    0x3c, 0x7e, 0xe3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3,
    0xe3, 0x7e, 0x3c,

    /* U+0044 "D" */
    0xf8, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc6, 0xfe, 0xf8,

    /* U+0045 "E" */
    0xff, 0xff, 0x6, 0xc, 0x1f, 0xbf, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+0046 "F" */
    0xff, 0xff, 0x6, 0xc, 0x1f, 0xff, 0xe0, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x3c, 0x7e, 0xe3, 0xc3, 0xc0, 0xcf, 0xcf, 0xc3,
    0xe3, 0x7f, 0x3e,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xc7,
    0xf9, 0xe0,

    /* U+004B "K" */
    0xc7, 0xce, 0xdc, 0xdc, 0xf8, 0xf8, 0xf8, 0xfc,
    0xce, 0xce, 0xc7,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+004D "M" */
    0xe0, 0xfc, 0x1f, 0xc7, 0xf8, 0xff, 0x1f, 0xb6,
    0xf6, 0xde, 0xdb, 0xce, 0x79, 0xcf, 0x39, 0x80,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xfb, 0xdb, 0xdf, 0xcf,
    0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xfe, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3e, 0x7, 0x2,

    /* U+0052 "R" */
    0xfd, 0xff, 0x1e, 0x3c, 0x7f, 0xbf, 0x66, 0xcd,
    0x9f, 0x18,

    /* U+0053 "S" */
    0x3c, 0xfe, 0xc3, 0xc0, 0x70, 0x3e, 0xf, 0xc3,
    0xc3, 0x7f, 0x3e,

    /* U+0054 "T" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x7e, 0x3c,

    /* U+0056 "V" */
    0xe3, 0xf1, 0xd8, 0xee, 0x67, 0x71, 0xb8, 0xd8,
    0x7c, 0x1e, 0xe, 0x7, 0x0,

    /* U+0057 "W" */
    0xe6, 0x3e, 0x67, 0x67, 0x76, 0xf6, 0x6f, 0x66,
    0xf6, 0x7f, 0xe3, 0x9e, 0x39, 0xc3, 0x9c, 0x39,
    0xc0,

    /* U+0058 "X" */
    0xe3, 0xbb, 0x9d, 0xc7, 0xc3, 0xe0, 0xe0, 0xf8,
    0x6c, 0x77, 0x33, 0xb8, 0xe0,

    /* U+0059 "Y" */
    0xe7, 0xe7, 0x66, 0x7e, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0xff, 0x6, 0xe, 0x1c, 0x18, 0x38, 0x70,
    0x60, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0x6d, 0xb6, 0xdb, 0x6d, 0xf8,

    /* U+005C "\\" */
    0xc3, 0x86, 0x1c, 0x70, 0xc3, 0x86, 0x18, 0x70,
    0xc3,

    /* U+005D "]" */
    0xfd, 0xb6, 0xdb, 0x6d, 0xb7, 0xf8,

    /* U+005E "^" */
    0x30, 0xc3, 0x9e, 0x6b, 0x30,

    /* U+005F "_" */
    0xff, 0xf0,

    /* U+0060 "`" */
    0x63,

    /* U+0061 "a" */
    0x7b, 0xfc, 0xdf, 0xff, 0x3f, 0xdf,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xef, 0xd8, 0xf1, 0xe3, 0xc7,
    0xfb, 0xf0,

    /* U+0063 "c" */
    0x38, 0xfb, 0x36, 0xc, 0x19, 0x9f, 0x1c,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xf7, 0xf8, 0xf1, 0xe3, 0xc6,
    0xfd, 0xf8,

    /* U+0065 "e" */
    0x3c, 0xf9, 0x9f, 0xff, 0xec, 0x1f, 0x9e,

    /* U+0066 "f" */
    0x3b, 0xd9, 0xff, 0xb1, 0x8c, 0x63, 0x18,

    /* U+0067 "g" */
    0x3e, 0xff, 0x9e, 0x3c, 0x78, 0xdf, 0xbf, 0x46,
    0xf9, 0xe0,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0069 "i" */
    0xf3, 0xff, 0xfc,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0xfe,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0xdf, 0x3c, 0x7c, 0xd9,
    0xbb, 0x38,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xdb, 0xbf, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33,

    /* U+006E "n" */
    0xfb, 0xfc, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+006F "o" */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xdf, 0x1c,

    /* U+0070 "p" */
    0xfd, 0xfb, 0x1e, 0x3c, 0x78, 0xff, 0x7c, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x7e, 0xff, 0x1e, 0x3c, 0x78, 0xdf, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xff, 0xf1, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7b, 0xfc, 0xf8, 0x3f, 0x3f, 0xde,

    /* U+0074 "t" */
    0x66, 0xff, 0x66, 0x66, 0x73,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0xbf,

    /* U+0076 "v" */
    0xe7, 0xdd, 0xb3, 0x66, 0xc7, 0x8e, 0x1c,

    /* U+0077 "w" */
    0xcc, 0xfb, 0x36, 0xd9, 0xfe, 0x7f, 0x9e, 0xe3,
    0x38, 0xcc,

    /* U+0078 "x" */
    0xee, 0xd9, 0xf1, 0xc3, 0x8f, 0x9b, 0x73,

    /* U+0079 "y" */
    0xe6, 0xdd, 0xbb, 0x63, 0xc7, 0x8e, 0x1c, 0x38,
    0xe1, 0xc0,

    /* U+007A "z" */
    0xff, 0xf1, 0x8e, 0x71, 0x8f, 0xff,

    /* U+007B "{" */
    0x36, 0x66, 0x66, 0xcc, 0x66, 0x66, 0x63,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc6, 0x66, 0x66, 0x33, 0x66, 0x66, 0x6c,

    /* U+007E "~" */
    0x72, 0xfe, 0xce
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 130, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 130, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 30, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 35, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 57, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 65, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 73, .adv_w = 104, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 80, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 87, .adv_w = 60, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 89, .adv_w = 101, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 90, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 79, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 99, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 130, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 130, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 67, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 65, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 204, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 210, .adv_w = 131, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 214, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 220, .adv_w = 114, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 201, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 250, .adv_w = 153, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 157, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 68, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 143, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 196, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 157, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 155, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 434, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 195, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 63, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 548, .adv_w = 95, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 557, .adv_w = 63, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 563, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 568, .adv_w = 99, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 570, .adv_w = 76, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 571, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 81, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 628, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 60, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 648, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 193, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 694, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 704, .adv_w = 85, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 77, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 163, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 761, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 73, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 774, .adv_w = 57, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 777, .adv_w = 73, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 784, .adv_w = 142, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
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


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 53,
    3, 3,
    3, 8,
    3, 34,
    3, 66,
    3, 68,
    3, 69,
    3, 70,
    3, 72,
    3, 78,
    3, 79,
    3, 80,
    3, 81,
    3, 82,
    3, 84,
    3, 88,
    8, 3,
    8, 8,
    8, 34,
    8, 66,
    8, 68,
    8, 69,
    8, 70,
    8, 72,
    8, 78,
    8, 79,
    8, 80,
    8, 81,
    8, 82,
    8, 84,
    8, 88,
    9, 55,
    9, 56,
    9, 58,
    13, 3,
    13, 8,
    15, 3,
    15, 8,
    16, 16,
    34, 3,
    34, 8,
    34, 32,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 78,
    34, 79,
    34, 80,
    34, 81,
    34, 85,
    34, 86,
    34, 87,
    34, 88,
    34, 90,
    34, 91,
    35, 53,
    35, 55,
    35, 58,
    36, 10,
    36, 53,
    36, 62,
    36, 94,
    37, 13,
    37, 15,
    37, 34,
    37, 53,
    37, 55,
    37, 57,
    37, 58,
    37, 59,
    38, 53,
    38, 68,
    38, 69,
    38, 70,
    38, 71,
    38, 72,
    38, 80,
    38, 82,
    38, 86,
    38, 87,
    38, 88,
    38, 90,
    39, 13,
    39, 15,
    39, 34,
    39, 43,
    39, 53,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 80,
    39, 82,
    39, 83,
    39, 86,
    39, 87,
    39, 90,
    41, 34,
    41, 53,
    41, 57,
    41, 58,
    42, 34,
    42, 53,
    42, 57,
    42, 58,
    43, 34,
    44, 14,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 80,
    44, 82,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 3,
    45, 8,
    45, 34,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 86,
    45, 87,
    45, 88,
    45, 90,
    46, 34,
    46, 53,
    46, 57,
    46, 58,
    47, 34,
    47, 53,
    47, 57,
    47, 58,
    48, 13,
    48, 15,
    48, 34,
    48, 53,
    48, 55,
    48, 57,
    48, 58,
    48, 59,
    49, 13,
    49, 15,
    49, 34,
    49, 43,
    49, 57,
    49, 59,
    49, 66,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 80,
    49, 82,
    49, 85,
    49, 87,
    49, 90,
    50, 53,
    50, 55,
    50, 56,
    50, 58,
    51, 53,
    51, 55,
    51, 58,
    53, 1,
    53, 13,
    53, 14,
    53, 15,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 52,
    53, 53,
    53, 55,
    53, 56,
    53, 58,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 34,
    55, 10,
    55, 13,
    55, 14,
    55, 15,
    55, 34,
    55, 36,
    55, 40,
    55, 48,
    55, 50,
    55, 62,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 80,
    55, 82,
    55, 83,
    55, 86,
    55, 87,
    55, 90,
    55, 94,
    56, 10,
    56, 13,
    56, 14,
    56, 15,
    56, 34,
    56, 53,
    56, 62,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 80,
    56, 82,
    56, 83,
    56, 86,
    56, 94,
    57, 14,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 55,
    57, 68,
    57, 69,
    57, 70,
    57, 72,
    57, 80,
    57, 82,
    57, 86,
    57, 87,
    57, 90,
    58, 7,
    58, 10,
    58, 11,
    58, 13,
    58, 14,
    58, 15,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 52,
    58, 53,
    58, 54,
    58, 55,
    58, 56,
    58, 57,
    58, 58,
    58, 62,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 85,
    58, 86,
    58, 87,
    58, 89,
    58, 90,
    58, 91,
    58, 94,
    59, 34,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 68,
    59, 69,
    59, 70,
    59, 72,
    59, 80,
    59, 82,
    59, 86,
    59, 87,
    59, 88,
    59, 90,
    60, 43,
    60, 54,
    66, 3,
    66, 8,
    66, 87,
    66, 90,
    67, 3,
    67, 8,
    67, 87,
    67, 89,
    67, 90,
    67, 91,
    68, 3,
    68, 8,
    70, 3,
    70, 8,
    70, 87,
    70, 90,
    71, 3,
    71, 8,
    71, 10,
    71, 62,
    71, 68,
    71, 69,
    71, 70,
    71, 72,
    71, 82,
    71, 94,
    73, 3,
    73, 8,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 82,
    78, 3,
    78, 8,
    79, 3,
    79, 8,
    80, 3,
    80, 8,
    80, 87,
    80, 89,
    80, 90,
    80, 91,
    81, 3,
    81, 8,
    81, 87,
    81, 89,
    81, 90,
    81, 91,
    83, 3,
    83, 8,
    83, 13,
    83, 15,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 71,
    83, 72,
    83, 80,
    83, 82,
    83, 85,
    83, 87,
    83, 88,
    83, 90,
    85, 80,
    87, 3,
    87, 8,
    87, 13,
    87, 15,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 71,
    87, 72,
    87, 80,
    87, 82,
    88, 13,
    88, 15,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 80,
    89, 82,
    90, 3,
    90, 8,
    90, 13,
    90, 15,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 71,
    90, 72,
    90, 80,
    90, 82,
    91, 68,
    91, 69,
    91, 70,
    91, 72,
    91, 80,
    91, 82,
    92, 43,
    92, 54
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -7, -4, -4, -13, -5, -6, -6, -6,
    -6, -2, -2, -10, -2, -6, -10, 1,
    -4, -4, -13, -5, -6, -6, -6, -6,
    -2, -2, -10, -2, -6, -10, 1, 2,
    4, 2, -31, -31, -31, -31, -27, -13,
    -13, -9, -2, -2, -2, -2, -13, -2,
    -8, -4, -16, -5, -5, -1, -5, -2,
    -1, -5, -4, -5, 1, -3, -3, -6,
    -3, -3, -1, -2, -13, -13, -2, -9,
    -2, -2, -5, -3, 2, -2, -2, -2,
    -2, -2, -2, -2, -2, -3, -2, -3,
    -30, -30, -21, -23, 2, -4, -2, -2,
    -2, -2, -2, -2, -3, -2, -3, -3,
    2, -3, 2, -3, 2, -3, 2, -3,
    -2, -18, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, -3, -3, -4, -7, -4,
    -31, -31, 2, -7, -7, -7, -7, -22,
    -3, -23, -10, -31, -2, -13, -6, -13,
    2, -3, 2, -3, 2, -3, 2, -3,
    -13, -13, -2, -9, -2, -2, -5, -3,
    -44, -44, -19, -20, -6, -4, -1, -1,
    -1, -1, -1, -1, -1, 2, 2, 2,
    -4, -3, -2, -4, -5, -2, -5, -7,
    -28, -30, -28, -13, -3, -3, -24, -3,
    -3, -2, 2, 2, 2, 2, -18, -10,
    -10, -10, -10, -10, -10, -23, -10, -10,
    -7, -8, -7, -9, -5, -8, -9, -7,
    -2, 2, -24, -17, -24, -8, -1, -1,
    -1, -1, 2, -5, -5, -5, -5, -5,
    -5, -5, -3, -3, -1, -1, 2, 2,
    -16, -7, -16, -5, 2, 1, -4, -3,
    -3, -3, -3, -3, -3, -2, -2, 2,
    -17, -3, -3, -3, -3, 2, -3, -3,
    -3, -3, -2, -3, -2, -3, -3, -3,
    2, -5, -25, -17, -25, -16, -3, -3,
    -10, -3, -3, -2, 2, -10, 2, 2,
    1, 2, 2, -7, -7, -7, -7, -2,
    -7, -4, -4, -7, -4, -7, -4, -6,
    -2, -4, -2, -3, -2, -3, 2, 1,
    -3, -3, -3, -3, -2, -2, -2, -2,
    -2, -2, -2, -3, -3, -3, -2, -2,
    -2, -2, -2, -2, -3, -3, -1, -2,
    -1, -2, -1, -1, -2, -2, -1, -1,
    2, 2, 2, 2, -3, -3, -3, -3,
    -3, 2, -9, -9, -2, -2, -2, -2,
    -2, -9, -9, -9, -9, -10, -10, -2,
    -2, -2, -2, -3, -3, -1, -2, -1,
    -2, 2, 2, -19, -19, -3, -2, -2,
    -2, 2, -2, -4, -2, 5, 2, 2,
    2, -3, 2, 2, -18, -18, -2, -1,
    -1, -1, 1, -1, -2, -1, -14, -14,
    -2, -2, -2, -2, -4, -2, 2, 2,
    -18, -18, -2, -1, -1, -1, 1, -1,
    -2, -1, -2, -2, -2, -2, -2, -2,
    -2, -2
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 434,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
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
const lv_font_t font_roboto_black_14 = {
#else
lv_font_t font_roboto_black_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if FONT_ROBOTO_BLACK_14*/
