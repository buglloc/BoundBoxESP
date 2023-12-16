#pragma once

#include <string>

namespace Base64
{
  typedef std::basic_string<uint8_t> Bytes;

  std::string Encode(const Bytes& bytes);
  Bytes Decode(const std::string& b64);
}
