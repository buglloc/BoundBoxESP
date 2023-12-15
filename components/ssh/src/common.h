#pragma once

#include <string>

#include <result.h>

#include "ssh/server.h"
#include "ssh/handler.h"


namespace SSH
{
  typedef std::basic_string<uint8_t> Bytes;
  cpp::result<std::string, Error> KeyFingerprint(const Bytes& key);
}