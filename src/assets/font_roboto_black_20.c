/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts:
 ******************************************************************************/

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
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xfc, 0x1, 0xf8,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0023 "#" */
    0xd, 0x81, 0xb0, 0x26, 0xc, 0xc7, 0xfe, 0xff,
    0xc6, 0xc0, 0xd8, 0x1b, 0x1f, 0xfb, 0xff, 0x19,
    0x83, 0x60, 0x6c, 0xd, 0x80,

    /* U+0024 "$" */
    0xc, 0x3, 0x3, 0xf0, 0xfe, 0x73, 0xdc, 0x77,
    0x1, 0xe0, 0x3e, 0xf, 0xe0, 0xf8, 0xf, 0xe1,
    0xf8, 0x7f, 0x1d, 0xfe, 0x3f, 0x3, 0x0, 0xc0,

    /* U+0025 "%" */
    0x78, 0x7, 0xe0, 0x33, 0x19, 0x99, 0x8c, 0xdc,
    0x7e, 0xc1, 0xec, 0x0, 0x60, 0x6, 0xf0, 0x6f,
    0xc3, 0x66, 0x33, 0x33, 0x19, 0x80, 0xfc, 0x3,
    0xc0,

    /* U+0026 "&" */
    0x1e, 0x1, 0xf8, 0x1c, 0xe0, 0xe7, 0x7, 0x38,
    0x3f, 0x80, 0xfc, 0x7, 0x80, 0x7e, 0x77, 0xfb,
    0xb9, 0xfd, 0xcf, 0xce, 0x3e, 0x3f, 0xf0, 0xff,
    0xc0,

    /* U+0027 "'" */
    0xff, 0xfe,

    /* U+0028 "(" */
    0x8, 0x73, 0x8c, 0x71, 0xce, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x86, 0x1c, 0x70, 0xe1, 0x83,

    /* U+0029 ")" */
    0x43, 0x87, 0xc, 0x38, 0xe1, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0x8e, 0x39, 0xc6, 0x30,

    /* U+002A "*" */
    0xc, 0x6, 0x13, 0x2f, 0xf3, 0xf0, 0xe0, 0xf8,
    0x66, 0x2, 0x0,

    /* U+002B "+" */
    0x1c, 0x7, 0x1, 0xc0, 0x70, 0xff, 0xff, 0xf1,
    0xc0, 0x70, 0x1c, 0x7, 0x0,

    /* U+002C "," */
    0x77, 0x77, 0x6e,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0xe, 0x18, 0x30, 0x61, 0xc3, 0x6, 0x1c, 0x30,
    0x61, 0xc3, 0x6, 0x1c, 0x38, 0x60,

    /* U+0030 "0" */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0x73,
    0x9f, 0xe1, 0xe0,

    /* U+0031 "1" */
    0xc, 0xff, 0xff, 0x9c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc0,

    /* U+0032 "2" */
    0x1f, 0x1f, 0xe7, 0x3f, 0x87, 0xe1, 0xc0, 0x70,
    0x3c, 0x1e, 0xf, 0x7, 0xc1, 0xe0, 0xf0, 0x78,
    0x3f, 0xff, 0xfc,

    /* U+0033 "3" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0x1, 0xc0, 0xf1,
    0xf8, 0x7e, 0x3, 0xc0, 0x70, 0x1f, 0x87, 0xf3,
    0xdf, 0xe3, 0xe0,

    /* U+0034 "4" */
    0x3, 0x80, 0xf0, 0x1e, 0x7, 0xc1, 0xf8, 0x3f,
    0xe, 0xe1, 0xdc, 0x73, 0x9e, 0x73, 0xff, 0xff,
    0xf0, 0x38, 0x7, 0x0, 0xe0,

    /* U+0035 "5" */
    0x7f, 0xdf, 0xf7, 0x1, 0x80, 0xe0, 0x3f, 0xcf,
    0xf9, 0x8f, 0x1, 0xc0, 0x70, 0x1f, 0x87, 0xf3,
    0x9f, 0xe1, 0xe0,

    /* U+0036 "6" */
    0x7, 0x7, 0xc3, 0xc1, 0xc0, 0x60, 0x3b, 0xcf,
    0xfb, 0xcf, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0x73,
    0x9f, 0xe1, 0xe0,

    /* U+0037 "7" */
    0xff, 0xff, 0xf0, 0x3c, 0xe, 0x3, 0x81, 0xc0,
    0x70, 0x3c, 0xe, 0x3, 0x81, 0xe0, 0x70, 0x3c,
    0xe, 0x3, 0x80,

    /* U+0038 "8" */
    0x3e, 0x1f, 0xce, 0x3b, 0x8e, 0xe3, 0xb8, 0xe7,
    0xf1, 0xfe, 0xf3, 0xb8, 0x7e, 0x1f, 0x87, 0xf3,
    0xdf, 0xe3, 0xf0,

    /* U+0039 "9" */
    0x1e, 0x1f, 0xc7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0xc7, 0x7f, 0xcf, 0xf0, 0x38, 0xe, 0x7,
    0xf, 0x83, 0x80,

    /* U+003A ":" */
    0xfc, 0x0, 0x0, 0x1f, 0x80,

    /* U+003B ";" */
    0xfc, 0x0, 0x7, 0xff, 0xfd, 0x80,

    /* U+003C "<" */
    0x1, 0x83, 0xc7, 0xff, 0xcf, 0x7, 0xc1, 0xfc,
    0x3f, 0x7, 0x80, 0x40,

    /* U+003D "=" */
    0xff, 0xff, 0xc0, 0x0, 0x0, 0x7, 0xff, 0xfe,

    /* U+003E ">" */
    0x80, 0x78, 0x3f, 0xf, 0xe0, 0xf8, 0x7d, 0xfd,
    0xf8, 0xe0, 0x40, 0x0,

    /* U+003F "?" */
    0x3e, 0x3f, 0xbc, 0xfc, 0x70, 0x38, 0x3c, 0x1e,
    0x1e, 0x1e, 0xe, 0x7, 0x0, 0x0, 0x0, 0xe0,
    0x70,

    /* U+0040 "@" */
    0x3, 0xe0, 0xc, 0x18, 0x18, 0xc, 0x30, 0x6,
    0x60, 0x6, 0x61, 0xe3, 0xc7, 0xf3, 0xc7, 0x63,
    0xce, 0x63, 0xce, 0x63, 0xcc, 0x63, 0xcc, 0x63,
    0xcc, 0x66, 0xee, 0xe6, 0x67, 0xbc, 0x70, 0x0,
    0x38, 0x0, 0x1f, 0xe0, 0x7, 0xc0,

    /* U+0041 "A" */
    0x7, 0x80, 0x1e, 0x0, 0xf8, 0x3, 0xf0, 0xf,
    0xc0, 0x7f, 0x1, 0xde, 0x7, 0x38, 0x3c, 0xe0,
    0xe3, 0xc3, 0xff, 0x1f, 0xfc, 0x70, 0x7b, 0xc0,
    0xef, 0x3, 0x80,

    /* U+0042 "B" */
    0xff, 0x1f, 0xfb, 0x87, 0xf0, 0x7e, 0xf, 0xc1,
    0xf8, 0x7f, 0xfe, 0xff, 0xdc, 0x3f, 0x83, 0xf0,
    0x7e, 0x1f, 0xff, 0xbf, 0xe0,

    /* U+0043 "C" */
    0xf, 0x83, 0xfc, 0x70, 0xe7, 0x7, 0xe0, 0x7e,
    0x0, 0xe0, 0xe, 0x0, 0xe0, 0xe, 0x0, 0xe0,
    0x77, 0x7, 0x70, 0xe3, 0xfe, 0x1f, 0x80,

    /* U+0044 "D" */
    0xfe, 0x1f, 0xf3, 0x8f, 0x70, 0xee, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x1f, 0x83, 0xf0,
    0xee, 0x3d, 0xff, 0x3f, 0x80,

    /* U+0045 "E" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0xfe, 0xff, 0xb8, 0xe, 0x3, 0x80, 0xe0,
    0x3f, 0xff, 0xfc,

    /* U+0046 "F" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0xfe, 0xff, 0xb8, 0xe, 0x3, 0x80, 0xe0,
    0x38, 0xe, 0x0,

    /* U+0047 "G" */
    0xf, 0x83, 0xfe, 0x78, 0xe7, 0x7, 0xe0, 0x7e,
    0x0, 0xe0, 0xe, 0x3f, 0xe3, 0xfe, 0x7, 0xe0,
    0x77, 0x7, 0x78, 0x73, 0xff, 0xf, 0xc0,

    /* U+0048 "H" */
    0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7f, 0xff, 0xff, 0xfe, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x70,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,

    /* U+004A "J" */
    0x1, 0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0x70,
    0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1f, 0x87, 0xe3,
    0x9f, 0xe3, 0xe0,

    /* U+004B "K" */
    0xe1, 0xee, 0x3c, 0xe3, 0xce, 0x78, 0xef, 0xe,
    0xf0, 0xfe, 0xf, 0xe0, 0xff, 0xf, 0xf0, 0xe7,
    0x8e, 0x38, 0xe3, 0xce, 0x1e, 0xe1, 0xe0,

    /* U+004C "L" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x80, 0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0,
    0x3f, 0xff, 0xfc,

    /* U+004D "M" */
    0xf0, 0x1f, 0xf0, 0x7f, 0xe0, 0xff, 0xc1, 0xff,
    0xc7, 0xff, 0x8f, 0xfb, 0x1b, 0xf7, 0x77, 0xee,
    0xef, 0xcd, 0x9f, 0x9f, 0x3f, 0x3e, 0x7e, 0x38,
    0xfc, 0x71, 0xf8, 0xe3, 0x80,

    /* U+004E "N" */
    0xe0, 0x7f, 0x7, 0xf8, 0x7f, 0x87, 0xfc, 0x7f,
    0xe7, 0xee, 0x7e, 0xf7, 0xe7, 0x7e, 0x7f, 0xe3,
    0xfe, 0x1f, 0xe1, 0xfe, 0xf, 0xe0, 0x70,

    /* U+004F "O" */
    0xf, 0x3, 0xfc, 0x71, 0xe7, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x77, 0xe, 0x79, 0xe3, 0xfc, 0x1f, 0x0,

    /* U+0050 "P" */
    0xff, 0x1f, 0xfb, 0x87, 0x70, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0xe, 0xff, 0xdf, 0xe3, 0x80, 0x70,
    0xe, 0x1, 0xc0, 0x38, 0x0,

    /* U+0051 "Q" */
    0xf, 0x3, 0xfc, 0x71, 0xe7, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x77, 0xe, 0x79, 0xe3, 0xfc, 0xf, 0xc0, 0xf,
    0x0, 0x60,

    /* U+0052 "R" */
    0xff, 0xf, 0xfc, 0xe1, 0xee, 0xe, 0xe0, 0xee,
    0xe, 0xe0, 0xee, 0x1e, 0xff, 0xcf, 0xf8, 0xe3,
    0x8e, 0x3c, 0xe1, 0xce, 0x1e, 0xe0, 0xe0,

    /* U+0053 "S" */
    0xf, 0x87, 0xf9, 0xc7, 0xb8, 0x77, 0x0, 0xf8,
    0xf, 0xc1, 0xfe, 0xf, 0xc0, 0x7f, 0x83, 0xf0,
    0x7f, 0xe, 0xff, 0x87, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xe, 0x0, 0xe0, 0xe, 0x0,
    0xe0, 0xe, 0x0, 0xe0, 0xe, 0x0, 0xe0, 0xe,
    0x0, 0xe0, 0xe, 0x0, 0xe0, 0xe, 0x0,

    /* U+0055 "U" */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x1f, 0x83, 0xf0,
    0x77, 0x1c, 0xff, 0x87, 0xc0,

    /* U+0056 "V" */
    0xf0, 0x7f, 0x83, 0xdc, 0x1c, 0xf1, 0xe7, 0x8f,
    0x1c, 0x78, 0xf3, 0x87, 0xbc, 0x1d, 0xe0, 0xee,
    0x7, 0xf0, 0x1f, 0x80, 0xf8, 0x7, 0xc0, 0x1e,
    0x0,

    /* U+0057 "W" */
    0xf1, 0xc3, 0xb8, 0xe3, 0xdc, 0x79, 0xee, 0x7c,
    0xe7, 0x3e, 0x73, 0xdf, 0x38, 0xef, 0xdc, 0x76,
    0xfe, 0x3f, 0x7e, 0x1f, 0xbf, 0xf, 0xcf, 0x83,
    0xe7, 0xc1, 0xe3, 0xe0, 0xf1, 0xe0, 0x78, 0xf0,

    /* U+0058 "X" */
    0xf0, 0xf3, 0xc7, 0x9e, 0x78, 0x7b, 0xc1, 0xdc,
    0xf, 0xe0, 0x3e, 0x1, 0xf0, 0xf, 0x80, 0xfe,
    0xf, 0x70, 0x7b, 0xc7, 0x8e, 0x3c, 0x7b, 0xc1,
    0xc0,

    /* U+0059 "Y" */
    0x70, 0x73, 0xc7, 0x8e, 0x38, 0x71, 0xc1, 0xdc,
    0xe, 0xe0, 0x3f, 0x1, 0xf0, 0xf, 0x80, 0x38,
    0x1, 0xc0, 0xe, 0x0, 0x70, 0x3, 0x80, 0x1c,
    0x0,

    /* U+005A "Z" */
    0xff, 0xff, 0xfc, 0xf, 0x1, 0xe0, 0x78, 0xf,
    0x3, 0xc0, 0x70, 0x1e, 0x7, 0x80, 0xf0, 0x3c,
    0x7, 0x81, 0xff, 0xff, 0xf8,

    /* U+005B "[" */
    0xff, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
    0xee, 0xff,

    /* U+005C "\\" */
    0xe0, 0x78, 0x1c, 0xf, 0x7, 0x81, 0xc0, 0xf0,
    0x38, 0x1c, 0xf, 0x3, 0x81, 0xe0, 0xf0, 0x38,
    0x1e, 0x7,

    /* U+005D "]" */
    0xff, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
    0x77, 0xff,

    /* U+005E "^" */
    0x1c, 0xe, 0xf, 0x7, 0xc3, 0x63, 0xb9, 0x8c,
    0xc6,

    /* U+005F "_" */
    0xff, 0xff, 0xc0,

    /* U+0060 "`" */
    0xe1, 0x80,

    /* U+0061 "a" */
    0x3e, 0x3f, 0xb8, 0xe0, 0x73, 0xfb, 0xff, 0x8f,
    0xc7, 0xe3, 0xbf, 0xcf, 0xe0,

    /* U+0062 "b" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xff, 0x3f, 0xee,
    0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe3,
    0xbf, 0xef, 0xf0,

    /* U+0063 "c" */
    0x3e, 0x3f, 0x9c, 0xfc, 0x7e, 0x7, 0x3, 0x81,
    0xc7, 0x73, 0xbf, 0x87, 0x80,

    /* U+0064 "d" */
    0x1, 0xc0, 0x70, 0x1c, 0x7, 0x3d, 0xdf, 0xf7,
    0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0x71,
    0xdf, 0xf3, 0xfc,

    /* U+0065 "e" */
    0x1f, 0xf, 0xe7, 0x1d, 0xc7, 0x7f, 0xff, 0xf7,
    0x1, 0xc0, 0x79, 0x8f, 0xf1, 0xf0,

    /* U+0066 "f" */
    0x1e, 0x7c, 0xe1, 0xcf, 0xff, 0xce, 0x1c, 0x38,
    0x70, 0xe1, 0xc3, 0x87, 0xe, 0x0,

    /* U+0067 "g" */
    0x3f, 0xdf, 0xf7, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x71, 0xdf, 0xf3, 0xfc, 0x7, 0x63,
    0xdf, 0xe3, 0xe0,

    /* U+0068 "h" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0xf7, 0xfb, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f,
    0x8e,

    /* U+0069 "i" */
    0xfc, 0xf, 0xff, 0xff, 0xff, 0xf8,

    /* U+006A "j" */
    0x1c, 0x70, 0x0, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1f, 0xef, 0x0,

    /* U+006B "k" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe7, 0xb9, 0xee,
    0xf3, 0xf8, 0xfc, 0x3f, 0x8f, 0xe3, 0xbc, 0xe7,
    0x39, 0xee, 0x3c,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,

    /* U+006D "m" */
    0xef, 0x3d, 0xff, 0xff, 0x8e, 0x3f, 0x1c, 0x7e,
    0x38, 0xfc, 0x71, 0xf8, 0xe3, 0xf1, 0xc7, 0xe3,
    0x8f, 0xc7, 0x1f, 0x8e, 0x38,

    /* U+006E "n" */
    0xef, 0x7f, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xe0,

    /* U+006F "o" */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x73, 0x9f, 0xe1, 0xe0,

    /* U+0070 "p" */
    0xff, 0x3f, 0xee, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe3, 0xbf, 0xef, 0xf3, 0x80, 0xe0,
    0x38, 0xe, 0x0,

    /* U+0071 "q" */
    0x3d, 0xdf, 0xf7, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x71, 0xdf, 0xf3, 0xfc, 0x7, 0x1,
    0xc0, 0x70, 0x1c,

    /* U+0072 "r" */
    0xff, 0xff, 0xc7, 0xe, 0x1c, 0x38, 0x70, 0xe1,
    0xc3, 0x80,

    /* U+0073 "s" */
    0x3e, 0x3f, 0xb8, 0xfc, 0xf, 0xc3, 0xf8, 0x7e,
    0x7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+0074 "t" */
    0x71, 0xc7, 0x3f, 0xfd, 0xc7, 0x1c, 0x71, 0xc7,
    0x1c, 0x7c, 0xf0,

    /* U+0075 "u" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbf, 0xde, 0xe0,

    /* U+0076 "v" */
    0xf1, 0xfc, 0xf7, 0x3d, 0xce, 0x7b, 0x8f, 0xe3,
    0xf0, 0xfc, 0x1f, 0x7, 0x81, 0xe0,

    /* U+0077 "w" */
    0xe3, 0x9d, 0xce, 0x77, 0x79, 0xdd, 0xe6, 0x77,
    0xf9, 0xdb, 0xe3, 0xef, 0x8f, 0x3e, 0x3c, 0xf0,
    0xf1, 0xc1, 0xc7, 0x0,

    /* U+0078 "x" */
    0x73, 0xdc, 0xe3, 0xf8, 0xfc, 0x1f, 0x7, 0x83,
    0xf0, 0xfc, 0x7b, 0x9c, 0xff, 0x1c,

    /* U+0079 "y" */
    0xe3, 0xfc, 0xff, 0x39, 0xce, 0x77, 0x9f, 0xc3,
    0xf0, 0xfc, 0x3e, 0x7, 0x81, 0xc0, 0x70, 0x1c,
    0x1e, 0x7, 0x0,

    /* U+007A "z" */
    0xff, 0xff, 0xc3, 0xc1, 0xe1, 0xe0, 0xe0, 0xf0,
    0xf0, 0x78, 0x7f, 0xff, 0xe0,

    /* U+007B "{" */
    0x4, 0x71, 0xce, 0x38, 0xe3, 0x8e, 0x3b, 0xcf,
    0xe, 0x38, 0xe3, 0x8e, 0x38, 0x71, 0xc1,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0x83, 0x8e, 0x1c, 0x71, 0xc7, 0x1c, 0x70, 0xf3,
    0xdc, 0x71, 0xc7, 0x1c, 0x73, 0x8e, 0x20,

    /* U+007E "~" */
    0x78, 0xff, 0x9f, 0x9f, 0xf1, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 88, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 101, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 11, .adv_w = 186, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 185, .box_w = 10, .box_h = 19, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 238, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 216, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 49, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 108, .adv_w = 113, .box_w = 6, .box_h = 20, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 123, .adv_w = 113, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 138, .adv_w = 149, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 149, .adv_w = 171, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 162, .adv_w = 86, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 165, .adv_w = 144, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 167, .adv_w = 97, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 112, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 182, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 185, .box_w = 6, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 185, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 96, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 92, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 378, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 390, .adv_w = 187, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 398, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 410, .adv_w = 163, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 287, .box_w = 16, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 465, .adv_w = 218, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 206, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 210, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 207, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 179, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 175, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 218, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 225, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 97, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 205, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 173, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 280, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 225, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 221, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 208, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 221, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 830, .adv_w = 209, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 200, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 874, .adv_w = 202, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 213, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 211, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 943, .adv_w = 278, .box_w = 17, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 975, .adv_w = 204, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1000, .adv_w = 201, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1025, .adv_w = 195, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1046, .adv_w = 90, .box_w = 4, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1056, .adv_w = 136, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1074, .adv_w = 90, .box_w = 4, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1084, .adv_w = 143, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1093, .adv_w = 141, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1096, .adv_w = 109, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 1098, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1130, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1143, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 174, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1176, .adv_w = 116, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1190, .adv_w = 184, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1209, .adv_w = 181, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 88, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1232, .adv_w = 86, .box_w = 6, .box_h = 19, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 1247, .adv_w = 175, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1266, .adv_w = 88, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1272, .adv_w = 276, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1293, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1306, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1320, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1339, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1358, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1368, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1381, .adv_w = 110, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1392, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1405, .adv_w = 165, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1419, .adv_w = 232, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1439, .adv_w = 165, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1453, .adv_w = 166, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1472, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1485, .adv_w = 104, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1500, .adv_w = 82, .box_w = 2, .box_h = 17, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1505, .adv_w = 104, .box_w = 6, .box_h = 20, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1520, .adv_w = 202, .box_w = 11, .box_h = 4, .ofs_x = 1, .ofs_y = 4}
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
    -9, -6, -6, -19, -8, -9, -9, -9,
    -9, -3, -3, -14, -3, -9, -14, 2,
    -6, -6, -19, -8, -9, -9, -9, -9,
    -3, -3, -14, -3, -9, -14, 2, 3,
    6, 3, -45, -45, -45, -45, -39, -19,
    -19, -13, -3, -3, -3, -3, -19, -3,
    -12, -6, -23, -7, -7, -2, -7, -3,
    -2, -8, -5, -8, 2, -4, -4, -9,
    -4, -5, -2, -3, -19, -19, -3, -13,
    -3, -3, -7, -4, 3, -3, -3, -3,
    -3, -3, -3, -3, -3, -4, -3, -4,
    -43, -43, -30, -32, 3, -5, -3, -3,
    -3, -3, -3, -3, -4, -3, -4, -4,
    3, -5, 3, -4, 3, -5, 3, -4,
    -3, -26, -5, -5, -5, -5, -4, -4,
    -4, -4, -4, -4, -4, -6, -10, -6,
    -45, -45, 3, -10, -10, -10, -10, -32,
    -4, -32, -15, -44, -2, -19, -8, -19,
    3, -5, 3, -4, 3, -5, 3, -4,
    -19, -19, -3, -13, -3, -3, -7, -4,
    -63, -63, -28, -29, -8, -6, -2, -2,
    -2, -2, -2, -2, -2, 2, 2, 2,
    -5, -4, -3, -5, -8, -3, -7, -9,
    -40, -42, -40, -19, -4, -4, -34, -4,
    -4, -2, 3, 3, 2, 3, -26, -14,
    -14, -14, -14, -14, -14, -32, -14, -14,
    -10, -12, -10, -13, -7, -12, -13, -9,
    -3, 3, -34, -25, -34, -12, -2, -2,
    -2, -2, 3, -7, -7, -7, -7, -7,
    -7, -7, -5, -4, -2, -2, 3, 2,
    -22, -9, -22, -7, 2, 2, -5, -5,
    -5, -5, -5, -5, -5, -3, -3, 2,
    -24, -4, -4, -4, -4, 2, -4, -4,
    -4, -4, -3, -4, -3, -5, -5, -5,
    3, -8, -36, -24, -36, -23, -5, -5,
    -15, -5, -5, -2, 3, -15, 3, 3,
    2, 3, 3, -10, -10, -10, -10, -3,
    -10, -6, -6, -10, -6, -10, -6, -9,
    -3, -6, -3, -4, -3, -5, 3, 2,
    -4, -4, -4, -4, -3, -3, -3, -3,
    -3, -3, -3, -4, -4, -4, -3, -3,
    -3, -3, -2, -2, -5, -5, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    3, 3, 3, 3, -4, -4, -4, -4,
    -4, 3, -12, -12, -3, -3, -3, -3,
    -3, -12, -12, -12, -12, -14, -14, -2,
    -3, -2, -2, -5, -5, -2, -2, -2,
    -2, 3, 3, -27, -27, -5, -3, -3,
    -3, 3, -3, -6, -3, 8, 3, 3,
    3, -5, 2, 2, -26, -26, -2, -2,
    -2, -2, 2, -2, -2, -2, -19, -19,
    -3, -3, -3, -3, -6, -3, 2, 2,
    -26, -26, -2, -2, -2, -2, 2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -3, -3
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
const lv_font_t font_roboto_black_20 = {
#else
lv_font_t font_roboto_black_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 21,          /*The maximum line height required by the font*/
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
