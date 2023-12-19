#pragma once

#include <stdint.h>


namespace SSH
{
  enum class Error: uint8_t
  {
    None = 0,
    MalformedKey,
    Unsupported,
    Internal,
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
}