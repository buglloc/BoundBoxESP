#pragma once

#include <string>
#include <vector>

#include <result.h>

#include "ssh/server.h"
#include "ssh/handler.h"


namespace SSH
{
  class Auth
  {
  public:
    Auth() = default;
    cpp::result<void, Error> Initialize(const ServerConfig& cfg);
    bool Authenticate(const std::string& user, const Bytes& key, AuthInfo& out);

  private:
    std::string rootUser;
    std::vector<std::string> rootFingerprints;
  };
}