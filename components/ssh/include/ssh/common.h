#pragma once

#include <stdint.h>
#include <functional>
#include <vector>
#include <expected>

#include <blob/bytes.h>

#include "libssh_esp.h"
#include "stream.h"


namespace SSH
{
  enum class Error: uint8_t
  {
    None = 0,
    MalformedKey,
    UnexpectedKey,
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

  enum class UserRole: uint8_t
  {
    User = 0,
    SysOp
  };

  struct UserInfo
  {
    std::string Name;
    Blob::Bytes Key;
    std::string KeyFingerprint;
    UserRole Role;
  };

  struct SessionInfo
  {
    std::string Id;
    std::string ClientIP;
    UserInfo User;
  };

  using HandlerCallback = std::function<int(const SessionInfo& sessInfo, std::string_view cmd, Stream& stream)>;
}
