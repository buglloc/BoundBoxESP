#include "blob/hex.h"

namespace
{
  int hex_value(uint8_t hex_digit)
  {
    static const signed char hex_values[256] = {
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
      -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    return hex_values[hex_digit];
  }
}

namespace Blob
{
  std::string HexEncode(const Bytes& bytes)
  {
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string out;
    out.reserve(bytes.length() * 2);
    for (unsigned char c: bytes)
    {
        out += hex_digits[c >> 4];
        out += hex_digits[c & 15];
    }
    return out;
  }

  Bytes HexDecode(const std::string_view hex)
  {
    Bytes out;
    const auto len = hex.length();
    if (hex.length() & 1) {
      return out;
    }

    out.reserve(len / 2);
    for (auto it = hex.cbegin(); it != hex.cend(); ) {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        out.push_back(hi << 4 | lo);
    }
    return out;
  }
}
