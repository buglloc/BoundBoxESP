#ifndef BB_UTIL_BYTES_HEX_H
#define BB_UTIL_BYTES_HEX_H

#include "bytes.h"
#include <Arduino.h>

namespace BBU
{
  String HexEncode(const Bytes& bytes);
  Bytes HexDecode(const String& hex);
}

#endif
