#ifndef BB_UTIL_BYTES_H
#define BB_UTIL_BYTES_H

#include <Arduino.h>

namespace BBU
{
  typedef std::basic_string<uint8_t> Bytes;

  String BytesToHex(const Bytes& bytes);
  Bytes BytesFromHex(const String& hex);
}

#endif