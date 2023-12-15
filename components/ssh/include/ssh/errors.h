#pragma once

#include <stdint.h>

namespace SSH
{
  enum class Error: uint8_t
  {
    None,
    MalformedKey,
    Unsupported,
    ShitHappens
  };

  enum class ListenError: uint8_t
  {
    None,
    Sock,
    Bind,
    Accept,
    ShitHappens
  };
}
