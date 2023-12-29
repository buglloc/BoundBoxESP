#pragma once

#include <string>

#include "common.h"
#include "keyring.h"


namespace SSH
{
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
