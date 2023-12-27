#pragma once

#include <string>
#include <vector>
#include <expected>

#include <blob/bytes.h>

#include "common.h"
#include "keyring.h"


namespace SSH
{
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
    std::string ClientIP;
    UserRole Role;
  };

  // fwd
  struct ServerConfig;

  class AuthProvider
  {
  public:
    AuthProvider() = default;
    Error Initialize(const ServerConfig& cfg);
    bool Authenticate(const std::string_view user, const ssh_key key) const;
    UserRole Role(const std::string_view user) const;

  private:
    std::string rootUser;
    Keyring rootKeyring;
  };
}
