#pragma once

#include <string>
#include <vector>
#include <expected>

#include "common.h"

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
    bool Authenticate(const std::string& user, const Blob::Bytes& key) const;
    UserRole Role(const std::string& user) const;

  private:
    std::string rootUser;
    std::vector<std::string> rootFingerprints;
  };
}