#pragma once

#include <string>


namespace Hash
{
  enum class Error: uint8_t
  {
    None = 0,
    Unsupported,
    InitFailed,
    InvalidKey,
    ShitHappens,
  };

  enum class HashType: uint8_t
  {
    None = 0,
    SHA1,
    SHA256,
    SHA512,
  };

  typedef std::basic_string<uint8_t> Bytes;
}
