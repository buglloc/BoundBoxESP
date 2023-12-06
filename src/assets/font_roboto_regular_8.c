/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts:
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_ROBOTO_REGULAR_8
#define FONT_ROBOTO_REGULAR_8 1
#endif

#if FONT_ROBOTO_REGULAR_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x54, 0xc0,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x5f, 0x6f, 0x60,

    /* U+0024 "$" */
    0x4d, 0xcf, 0x3b, 0x60,

    /* U+0025 "%" */
    0x61, 0xc1, 0x8d, 0x18,

    /* U+0026 "&" */
    0x67, 0x19, 0x6f, 0x0,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x5a, 0xa4,

    /* U+0029 ")" */
    0xa5, 0x58,

    /* U+002A "*" */
    0x5f, 0x0,

    /* U+002B "+" */
    0x44, 0xf4,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x29, 0x29, 0x0,

    /* U+0030 "0" */
    0x69, 0x99, 0x60,

    /* U+0031 "1" */
    0xd5, 0x40,

    /* U+0032 "2" */
    0x7d, 0x36, 0xf0,

    /* U+0033 "3" */
    0x71, 0x21, 0x70,

    /* U+0034 "4" */
    0x26, 0xaf, 0x20,

    /* U+0035 "5" */
    0x77, 0x1d, 0x60,

    /* U+0036 "6" */
    0x6e, 0x99, 0x60,

    /* U+0037 "7" */
    0xf3, 0x26, 0x40,

    /* U+0038 "8" */
    0x75, 0x65, 0x70,

    /* U+0039 "9" */
    0xe9, 0xf3, 0x60,

    /* U+003A ":" */
    0xc3,

    /* U+003B ";" */
    0xc1, 0x40,

    /* U+003C "<" */
    0x3c, 0x71,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0x87, 0xe0,

    /* U+003F "?" */
    0xeb, 0x64, 0x60,

    /* U+0040 "@" */
    0x3d, 0xbe, 0xad, 0x5f, 0xcf, 0x0,

    /* U+0041 "A" */
    0x33, 0x94, 0xfc, 0x80,

    /* U+0042 "B" */
    0xf9, 0xe9, 0xf0,

    /* U+0043 "C" */
    0x79, 0x89, 0x70,

    /* U+0044 "D" */
    0xe9, 0x99, 0xe0,

    /* U+0045 "E" */
    0xf8, 0xe8, 0xf0,

    /* U+0046 "F" */
    0xf3, 0xc8,

    /* U+0047 "G" */
    0x74, 0xef, 0x37, 0x80,

    /* U+0048 "H" */
    0x8c, 0x7f, 0x18, 0x80,

    /* U+0049 "I" */
    0xf8,

    /* U+004A "J" */
    0x11, 0x15, 0x70,

    /* U+004B "K" */
    0xba, 0xea, 0xb0,

    /* U+004C "L" */
    0x92, 0x4e,

    /* U+004D "M" */
    0xcf, 0x3f, 0xed, 0xb4,

    /* U+004E "N" */
    0x8e, 0x6b, 0x38, 0x80,

    /* U+004F "O" */
    0x74, 0x63, 0x17, 0x0,

    /* U+0050 "P" */
    0xf9, 0xf8, 0x80,

    /* U+0051 "Q" */
    0x74, 0x63, 0x17, 0x4,

    /* U+0052 "R" */
    0xf9, 0xfb, 0x90,

    /* U+0053 "S" */
    0x76, 0x9d, 0x2f, 0x0,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x0,

    /* U+0055 "U" */
    0x99, 0x99, 0xf0,

    /* U+0056 "V" */
    0xca, 0xd4, 0xe3, 0x0,

    /* U+0057 "W" */
    0xd7, 0xe9, 0xb3, 0x66, 0xc0,

    /* U+0058 "X" */
    0xda, 0x88, 0xad, 0x80,

    /* U+0059 "Y" */
    0xda, 0x88, 0x42, 0x0,

    /* U+005A "Z" */
    0xf9, 0x98, 0x8f, 0x80,

    /* U+005B "[" */
    0xff,

    /* U+005C "\\" */
    0xc4, 0x46, 0x23,

    /* U+005D "]" */
    0xff,

    /* U+005E "^" */
    0x4e, 0x80,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x40,

    /* U+0061 "a" */
    0x6f, 0xbf,

    /* U+0062 "b" */
    0x88, 0xe9, 0x9e,

    /* U+0063 "c" */
    0x7b, 0xb7,

    /* U+0064 "d" */
    0x11, 0x79, 0x97,

    /* U+0065 "e" */
    0x7f, 0xc7,

    /* U+0066 "f" */
    0x6b, 0xa4, 0x80,

    /* U+0067 "g" */
    0x79, 0x97, 0xf0,

    /* U+0068 "h" */
    0x88, 0xf9, 0x99,

    /* U+0069 "i" */
    0xc5, 0x50,

    /* U+006A "j" */
    0xc5, 0x5c,

    /* U+006B "k" */
    0x88, 0xac, 0xea,

    /* U+006C "l" */
    0xfc,

    /* U+006D "m" */
    0xff, 0x26, 0x4c, 0x90,

    /* U+006E "n" */
    0xf9, 0x99,

    /* U+006F "o" */
    0x69, 0x96,

    /* U+0070 "p" */
    0xe9, 0x9e, 0x80,

    /* U+0071 "q" */
    0x79, 0x97, 0x10,

    /* U+0072 "r" */
    0xea,

    /* U+0073 "s" */
    0xe8, 0x6e,

    /* U+0074 "t" */
    0x5d, 0x26,

    /* U+0075 "u" */
    0x99, 0x9f,

    /* U+0076 "v" */
    0xd7, 0x66,

    /* U+0077 "w" */
    0xbf, 0xe7, 0x96,

    /* U+0078 "x" */
    0xf6, 0x6f,

    /* U+0079 "y" */
    0xd7, 0x66, 0x40,

    /* U+007A "z" */
    0xf6, 0x4f,

    /* U+007B "{" */
    0x69, 0x44, 0x98,

    /* U+007C "|" */
    0xfc,

    /* U+007D "}" */
    0xc9, 0x14, 0x90,

    /* U+007E "~" */
    0xd5, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 32, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 35, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 41, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 4, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 74, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 95, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 20, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 20, .adv_w = 45, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 22, .adv_w = 45, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 26, .adv_w = 68, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 28, .adv_w = 35, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 58, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 30, .adv_w = 39, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 45, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 34, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 74, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 37, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 66, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 75, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 65, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 81, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 84, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 39, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 69, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 112, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 135, .adv_w = 84, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 111, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 36, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 171, .adv_w = 55, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 174, .adv_w = 36, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 175, .adv_w = 57, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 177, .adv_w = 57, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 178, .adv_w = 43, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 179, .adv_w = 68, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 46, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 197, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 35, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 35, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 204, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 35, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 110, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 72, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 72, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 219, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 222, .adv_w = 49, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 44, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 72, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 93, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 66, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 239, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 244, .adv_w = 33, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 245, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 248, .adv_w = 81, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 1}
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
    -4, -2, -2, -7, -3, -4, -4, -4,
    -4, -1, -1, -6, -1, -4, -6, 1,
    -2, -2, -7, -3, -4, -4, -4, -4,
    -1, -1, -6, -1, -4, -6, 1, 1,
    2, 1, -18, -18, -18, -18, -15, -7,
    -7, -5, -1, -1, -1, -1, -7, -1,
    -5, -2, -9, -3, -3, -1, -3, -1,
    -1, -3, -2, -3, 1, -2, -1, -3,
    -2, -2, -1, -1, -8, -8, -1, -5,
    -1, -1, -3, -1, 1, -1, -1, -1,
    -1, -1, -1, -1, -1, -2, -1, -2,
    -17, -17, -12, -13, 1, -2, -1, -1,
    -1, -1, -1, -1, -2, -1, -1, -1,
    1, -2, 1, -2, 1, -2, 1, -2,
    -1, -10, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -1, -2, -4, -2,
    -18, -18, 1, -4, -4, -4, -4, -13,
    -1, -13, -6, -17, -1, -8, -3, -8,
    1, -2, 1, -2, 1, -2, 1, -2,
    -8, -8, -1, -5, -1, -1, -3, -1,
    -25, -25, -11, -11, -3, -2, -1, -1,
    -1, -1, -1, -1, -1, 1, 1, 1,
    -2, -2, -1, -2, -3, -1, -3, -4,
    -16, -17, -16, -7, -2, -2, -13, -2,
    -2, -1, 1, 1, 1, 1, -10, -6,
    -6, -6, -6, -6, -6, -13, -6, -6,
    -4, -5, -4, -5, -3, -5, -5, -4,
    -1, 1, -13, -10, -13, -5, -1, -1,
    -1, -1, 1, -3, -3, -3, -3, -3,
    -3, -3, -2, -2, -1, -1, 1, 1,
    -9, -4, -9, -3, 1, 1, -2, -2,
    -2, -2, -2, -2, -2, -1, -1, 1,
    -10, -2, -2, -2, -2, 1, -2, -2,
    -2, -2, -1, -2, -1, -2, -2, -2,
    1, -3, -14, -9, -14, -9, -2, -2,
    -6, -2, -2, -1, 1, -6, 1, 1,
    1, 1, 1, -4, -4, -4, -4, -1,
    -4, -2, -2, -4, -2, -4, -2, -4,
    -1, -2, -1, -1, -1, -2, 1, 1,
    -2, -2, -2, -2, -1, -1, -1, -1,
    -1, -1, -1, -2, -2, -2, -1, -1,
    -1, -1, -1, -1, -2, -2, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    1, 1, 1, 1, -1, -1, -1, -1,
    -1, 1, -5, -5, -1, -1, -1, -1,
    -1, -5, -5, -5, -5, -5, -5, -1,
    -1, -1, -1, -2, -2, -1, -1, -1,
    -1, 1, 1, -11, -11, -2, -1, -1,
    -1, 1, -1, -2, -1, 3, 1, 1,
    1, -2, 1, 1, -10, -10, -1, -1,
    -1, -1, 1, -1, -1, -1, -8, -8,
    -1, -1, -1, -1, -2, -1, 1, 1,
    -10, -10, -1, -1, -1, -1, 1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1
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
const lv_font_t font_roboto_regular_8 = {
#else
lv_font_t font_roboto_regular_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONT_ROBOTO_REGULAR_8*/
