#pragma once

#include <stdint.h>

namespace Blob
{
  enum class Error: uint8_t
  {
    None = 0,
    Unsupported,
    InitFailed,
    InvalidKey,
    ShitHappens,
  };
}
