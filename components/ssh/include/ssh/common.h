#pragma once

#include <string>
#include <expected>

namespace SSH
{
  typedef std::basic_string<uint8_t> Bytes;

  enum class Error: uint8_t
  {
    None = 0,
    MalformedKey,
    Unsupported,
    ShitHappens
  };

  enum class ListenError: uint8_t
  {
    None = 0,
    Sock,
    Bind,
    Accept,
    Unsupported,
    ShitHappens
  };

  std::expected<std::string, Error> KeyFingerprint(const Bytes& key);
}