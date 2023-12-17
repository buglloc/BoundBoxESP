#pragma once

#include "bytes.h"

namespace Blob
{
  std::string Base64Encode(const Bytes& bytes);
  Bytes Base64Decode(const std::string& b64);
}