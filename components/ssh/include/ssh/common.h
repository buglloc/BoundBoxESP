#pragma once

#include <stdint.h>

#include "libssh_esp.h"



namespace SSH
{
  enum class Error: uint8_t
  {
    None = 0,
    MalformedKey,
    Unsupported,
    InvalidState,
    Internal,
    ShitHappens
  };

  enum class ListenError: uint8_t
  {
    None = 0,
    Bind,
    Listen,
    Accept,
    Auth,
    Internal,
    Unsupported,
    ShitHappens
  };
}