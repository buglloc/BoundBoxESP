/*******************************************************************************
 * Size: 8 px
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

#ifndef FONT_UBUNTU_REGULAR_8
#define FONT_UBUNTU_REGULAR_8 1
#endif

#if FONT_UBUNTU_REGULAR_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xf8,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x57, 0xd5, 0xf5, 0x0,

    /* U+0024 "$" */
    0x46, 0x86, 0x2e, 0x40,

    /* U+0025 "%" */
    0xf2, 0xc6, 0x8d, 0x5c,

    /* U+0026 "&" */
    0x71, 0x46, 0x16, 0x78,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xa4,

    /* U+0029 ")" */
    0xa5, 0x58,

    /* U+002A "*" */
    0x46, 0x20,

    /* U+002B "+" */
    0x21, 0x3e, 0x40,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x4, 0xa5, 0x24,

    /* U+0030 "0" */
    0x69, 0x99, 0x60,

    /* U+0031 "1" */
    0x75, 0x40,

    /* U+0032 "2" */
    0xe5, 0x4e,

    /* U+0033 "3" */
    0xe1, 0x61, 0xf0,

    /* U+0034 "4" */
    0x6a, 0xaf, 0x20,

    /* U+0035 "5" */
    0x74, 0x31, 0x70,

    /* U+0036 "6" */
    0x7e, 0x99, 0x60,

    /* U+0037 "7" */
    0xf2, 0x24, 0x40,

    /* U+0038 "8" */
    0xea, 0x6a, 0xe0,

    /* U+0039 "9" */
    0xea, 0x62, 0xc0,

    /* U+003A ":" */
    0xc3,

    /* U+003B ";" */
    0xc1, 0x40,

    /* U+003C "<" */
    0x3c, 0x60,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0xc3, 0x60,

    /* U+003F "?" */
    0xe5, 0x4,

    /* U+0040 "@" */
    0x7d, 0x36, 0xad, 0x5d, 0xc7, 0x0,

    /* U+0041 "A" */
    0x22, 0x94, 0xf8, 0x80,

    /* U+0042 "B" */
    0xf9, 0xe9, 0xf0,

    /* U+0043 "C" */
    0x78, 0x88, 0x70,

    /* U+0044 "D" */
    0xf4, 0x63, 0x1f, 0x0,

    /* U+0045 "E" */
    0xf8, 0xe8, 0xf0,

    /* U+0046 "F" */
    0xf8, 0xe8, 0x80,

    /* U+0047 "G" */
    0x78, 0x89, 0x70,

    /* U+0048 "H" */
    0x99, 0xf9, 0x90,

    /* U+0049 "I" */
    0xf8,

    /* U+004A "J" */
    0x11, 0x11, 0x70,

    /* U+004B "K" */
    0x95, 0x31, 0x49, 0x0,

    /* U+004C "L" */
    0x88, 0x88, 0xf0,

    /* U+004D "M" */
    0xcf, 0x3b, 0x6d, 0x84,

    /* U+004E "N" */
    0x8e, 0x6b, 0x38, 0x80,

    /* U+004F "O" */
    0x74, 0x63, 0x17, 0x0,

    /* U+0050 "P" */
    0xf9, 0xe8, 0x80,

    /* U+0051 "Q" */
    0x74, 0x63, 0x17, 0x8,

    /* U+0052 "R" */
    0xe9, 0xfa, 0x90,

    /* U+0053 "S" */
    0xf8, 0x61, 0xf0,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x0,

    /* U+0055 "U" */
    0x99, 0x99, 0x60,

    /* U+0056 "V" */
    0x8a, 0x54, 0xa2, 0x0,

    /* U+0057 "W" */
    0x83, 0x25, 0xab, 0x66, 0x40,

    /* U+0058 "X" */
    0x52, 0x88, 0xa8, 0x80,

    /* U+0059 "Y" */
    0x8a, 0x88, 0x42, 0x0,

    /* U+005A "Z" */
    0xf2, 0x24, 0xf0,

    /* U+005B "[" */
    0xea, 0xac,

    /* U+005C "\\" */
    0x92, 0x24, 0x89,

    /* U+005D "]" */
    0xd5, 0x5c,

    /* U+005E "^" */
    0x25, 0x90,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x10,

    /* U+0061 "a" */
    0x77, 0x97,

    /* U+0062 "b" */
    0x88, 0xe9, 0x9e,

    /* U+0063 "c" */
    0x72, 0x30,

    /* U+0064 "d" */
    0x11, 0x79, 0x97,

    /* U+0065 "e" */
    0x6e, 0x86,

    /* U+0066 "f" */
    0xf3, 0xc9, 0x0,

    /* U+0067 "g" */
    0x79, 0x97, 0xf0,

    /* U+0068 "h" */
    0x93, 0xdb, 0x40,

    /* U+0069 "i" */
    0x3c,

    /* U+006A "j" */
    0x5, 0x5c,

    /* U+006B "k" */
    0x88, 0xac, 0xaa,

    /* U+006C "l" */
    0xaa, 0xb0,

    /* U+006D "m" */
    0xfd, 0x6b, 0x50,

    /* U+006E "n" */
    0xf6, 0xd0,

    /* U+006F "o" */
    0x69, 0x96,

    /* U+0070 "p" */
    0xe9, 0x9e, 0x80,

    /* U+0071 "q" */
    0x79, 0x97, 0x10,

    /* U+0072 "r" */
    0xf2, 0x40,

    /* U+0073 "s" */
    0xf1, 0xf0,

    /* U+0074 "t" */
    0x9e, 0x4e,

    /* U+0075 "u" */
    0xb6, 0xf0,

    /* U+0076 "v" */
    0x9a, 0x66,

    /* U+0077 "w" */
    0x96, 0xd7, 0x92,

    /* U+0078 "x" */
    0xa6, 0x69,

    /* U+0079 "y" */
    0x9a, 0x62, 0xc0,

    /* U+007A "z" */
    0xe5, 0x70,

    /* U+007B "{" */
    0x69, 0x44, 0x98,

    /* U+007C "|" */
    0xff,

    /* U+007D "}" */
    0xc9, 0x14, 0xb0,

    /* U+007E "~" */
    0x5b
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 30, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 35, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 54, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 3, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 72, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 11, .adv_w = 110, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 85, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 31, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 20, .adv_w = 41, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 22, .adv_w = 41, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 61, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 26, .adv_w = 72, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 31, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 38, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 31, .adv_w = 31, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 72, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 31, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 31, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 66, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 72, .adv_w = 52, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 122, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 80, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 79, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 91, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 73, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 69, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 86, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 34, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 66, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 111, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 93, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 100, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 100, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 136, .adv_w = 81, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 68, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 72, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 119, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 77, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 73, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 42, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 171, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 174, .adv_w = 42, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 176, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 178, .adv_w = 63, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 179, .adv_w = 48, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 180, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 75, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 60, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 75, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 72, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 49, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 198, .adv_w = 73, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 32, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 32, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 204, .adv_w = 67, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 35, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 110, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 73, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 75, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 219, .adv_w = 75, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 222, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 57, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 51, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 73, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 99, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 240, .adv_w = 60, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 245, .adv_w = 36, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 246, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 249, .adv_w = 72, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1}
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
    0, 0, 0, -10, -3, -3, -16, 0,
    -3, 0, 0, 0, 2, 1, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 10, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -4, 0, 0, -4,
    -2, 1, -1, 2, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -2, -2, -2, 0, -2, -2,
    -4, 0, -4, -2, -4, -6, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, -1, -1, -16, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    -4, -4, 4, 0, -4, 2, -9, -3,
    -10, -5, 1, -10, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, -6, 0, -2,
    0, -4, -6, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, -3, -3,
    -9, 0, -3, 0, 4, 0, 4, 3,
    3, 4, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, -1, 0, -11, -2, -3, -2, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -1, -1, -3, 0,
    -1, -2, -6, -2, -5, -3, -5, -7,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, -2, 0, -8, 3, 0, 2, 0,
    0, -2, 4, -2, -2, 4, 0, -2,
    2, -8, -1, -8, -2, 3, -10, 2,
    0, -3, 0, -2, -2, -2, 0, -2,
    0, 0, -2, -2, 2, 0, -2, -3,
    -2, 3, -2, 2, -3, -1, 0, -1,
    -1, -3, -1, -1, 0, -3, -1, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, -2, -3, -3, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -3, 0, 0, -3,
    0, 0, 3, -4, 0, 0, 2, -2,
    3, -3, -3, 3, 0, -3, 1, 2,
    0, 2, 0, 2, 2, 1, -1, 0,
    0, -2, -2, -2, 0, -2, 0, 0,
    -2, -2, 0, 0, -3, -2, -2, 2,
    -2, 0, -4, 0, -2, -3, -2, -4,
    0, -4, 0, -6, 0, -5, -1, -2,
    0, 0, -3, 0, 0, -1, -3, 0,
    -2, -2, -3, -5, -2, -1, -5, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, -2, -3, 0, -2,
    1, 0, 0, 0, 0, -2, 2, -4,
    -4, 2, 0, -4, 0, 0, -3, 0,
    0, 0, 0, 0, -2, -6, 0, -2,
    -2, -2, 0, -3, 0, 0, -2, -2,
    0, -2, -2, -3, -3, 1, -3, 0,
    -2, -3, -1, 0, -3, 0, 0, -8,
    0, -8, -2, 2, -2, -6, -2, -2,
    -10, 0, -2, 0, 2, 0, 2, 0,
    0, 3, 0, -2, -5, -7, -2, -2,
    -2, 0, -2, 0, -4, -2, -2, 0,
    0, -3, 0, 0, -5, 0, -3, 0,
    0, 0, 0, 0, -1, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -2, 0, 0, -1,
    0, 0, 0, -1, 0, -1, 0, -5,
    0, 0, 0, -1, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -2, 0,
    0, -2, 0, -4, 2, -6, 2, 0,
    1, -2, 4, -4, -4, 3, 0, -4,
    0, 2, 0, 3, 1, 3, 3, 3,
    0, -3, 0, -3, -3, -3, 0, -3,
    0, 0, -3, -3, 2, 0, -2, -2,
    -6, 3, -1, 2, -2, 0, 0, -16,
    -1, 0, -18, 3, -9, 2, 0, 0,
    0, 4, -6, -6, 4, 0, -6, 2,
    -15, -2, -13, -6, 3, -15, 2, 0,
    -4, 0, -2, -2, -2, 0, -2, 0,
    0, -2, -2, 0, 0, 0, -5, -5,
    3, -3, 1, -3, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -3, -2, -4,
    0, -4, 0, -5, 0, -4, -1, -2,
    0, 0, -3, 0, 0, -1, -3, 0,
    -2, -2, -3, -5, -2, -1, -5, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -1, 0, -2, -3, 0,
    -12, 0, -8, 0, 0, 0, -6, 0,
    0, -12, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -2, -5, -2, -3,
    -3, -4, 0, -3, 0, 0, -3, -1,
    0, 0, 0, 1, 1, 0, 1, 0,
    0, -3, -2, -3, -2, 0, 0, -4,
    0, 0, 0, -4, -1, -2, 0, 0,
    -3, 0, 0, -1, -3, 0, -2, -2,
    -3, -5, -2, -1, 0, -2, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 2, 0,
    2, 0, -2, -2, 4, -1, -1, 3,
    0, -1, 0, 0, 0, -1, 0, 2,
    -2, 2, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 0, 1, -2, -2,
    0, 0, -3, 2, 0, -10, -6, -11,
    -11, 3, -7, -8, -3, -3, -12, 0,
    -3, 0, 3, 0, 3, 2, 2, 4,
    0, 0, -4, -6, -7, -7, -7, 0,
    -7, 0, -5, -7, -7, -6, 0, -4,
    -3, -10, -2, -3, -4, -3, 0, 0,
    0, -1, 0, 0, -1, 0, -5, -1,
    0, 0, -1, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -5, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -1, -3, 0, 0,
    0, 0, 0, -10, 0, 0, 0, 0,
    0, -8, -2, -2, -12, -1, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -6, -6, -6, 0, -6, 0,
    -4, -6, -6, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, -2,
    0, 0, -5, 0, -6, -1, 2, -2,
    -2, -2, -2, -8, 0, -2, 0, 2,
    0, 3, 2, 1, 3, 0, 0, -5,
    -4, -3, -3, -3, 0, -3, 0, -3,
    -3, -3, -2, 0, -2, 0, 0, 0,
    0, 0, -2, 0, 0, 0, -3, 0,
    -3, 2, -4, 1, 0, 0, -3, 3,
    -3, -3, 3, 0, -3, 0, 2, 0,
    2, 0, 2, 2, 2, 0, -4, 0,
    -2, -2, -2, 0, -2, 0, 0, -2,
    -2, 0, 0, -1, -1, -5, 2, -1,
    0, -3, 0, 0, 0, -5, 2, 0,
    -8, -6, -10, -5, 3, -7, -10, -5,
    -5, -15, -1, -5, 0, 4, 0, 4,
    3, 3, 4, 1, 0, -3, -5, -6,
    -6, -6, 0, -6, 0, -5, -6, -6,
    -3, 0, -4, 0, 0, -2, 0, -4,
    -3, 0, 0, 0, -3, 0, 0, 1,
    -8, 0, 0, 0, -2, 2, -5, -5,
    2, 0, -5, 0, 0, -2, 1, 0,
    0, 2, 0, -2, -6, 0, -2, -2,
    -2, 0, -3, 0, 0, -2, -2, 0,
    -2, -2, -3, -3, 1, -3, 0, -4,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -6, -6, -4,
    0, -6, -3, -4, -5, -4, -5, -5,
    -3, -5, 0, 10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, 0, 0,
    -1, 0, 0, 0, 0, -1, -1, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -3, -3, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -2, 0, -2, 0, 0, -3, 0, -5,
    0, -3, 0, 0, 0, -3, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    -2, -2, -3, 0, -3, 0, 0, 0,
    0, 0, 1, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, -2, 0, 0, -2, 0, 0,
    -2, 0, 0, 0, 0, 1, 1, 2,
    1, 0, -3, 0, 0, 0, 0, 5,
    1, -7, -4, -5, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 2, 2, 2,
    0, 0, 5, 0, -5, 0, -3, -3,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -2, 0, -2, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    1, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -3, -3, -3,
    0, -4, 0, 0, -4, -3, 0, 0,
    0, 0, 0, 2, 0, 0, -2, 0,
    0, -4, 0, -3, -3, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, -2, 0, -2, 0, 0, -3, 0,
    -4, 0, -3, -3, 0, 0, -3, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -2, -2, -2, -3, 0, -3, 0, -4,
    0, -3, -3, 0, 0, -3, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    -2, -2, -2, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -7, -4, -6, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 3, 2, 2, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -2,
    -2, -1, 0, -1, 0, 0, -2, -2,
    0, 0, 0, 0, 0, 2, 0, 0,
    -3, 0, 0, 0, 0, 0, 1, -4,
    0, -4, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -2, -2,
    -2, 0, -2, 0, 0, -2, -2, 0,
    0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 0, 0, 0, 1, -4, 0,
    -4, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -2, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 2, 2, 2, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -3, -3, -3, 0,
    -3, 0, 0, -3, -3, 0, 0, 0,
    0, 0, 2, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -2, -3, -2, -2, -3,
    0, 0, -3, -2, 0, -2, -2, 0,
    0, 0, 0, 0, -4, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -3, -4, -2, 0, -4, -3,
    0, -3, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, -3, 0, 0, -2, -3,
    -1, -3, -2, -4, -3, -4, 0, 0,
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
const lv_font_t font_ubuntu_regular_8 = {
#else
lv_font_t font_ubuntu_regular_8 = {
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
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONT_UBUNTU_REGULAR_8*/
