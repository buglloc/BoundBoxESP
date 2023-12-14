#ifndef BB_UTIL_BYTES_BASE64_H
#define BB_UTIL_BYTES_BASE64_H

#include "bytes.h"

namespace BBU
{
  String Base64Encode(const Bytes& bytes);
  Bytes Base64Decode(const String& b64);
}

#endif
