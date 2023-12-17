#pragma once

#include <string>
#include <expected>

#include <blob/bytes.h>

namespace SSH
{
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

  std::expected<std::string, Error> KeyFingerprint(const Blob::Bytes& key);
}