#pragma once

#include <string>

#include "bytes.h"


namespace Blob
{
  std::string HexEncode(const Bytes& bytes);
  Bytes HexDecode(const std::string_view hex);
}
