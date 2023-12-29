#pragma once

#include <memory>
#include <string>
#include <vector>
#include <expected>

#include "common.h"
#include "keys.h"
#include "auth_provider.h"


namespace SSH
{
  struct ServerConfig
  {
    const std::string RootUser;
    const std::vector<std::string> RootKeys;
    const PrivateKey& HostKey;
  };

  class Server
  {
  public:
    Server() = default;
    Error Initialize(const ServerConfig& cfg);
    ListenError Listen(const HandlerCallback& handler);

  private:
    std::expected<UserInfo, ListenError> authenticate(ssh_session session, const SessionInfo& sessInfo);

  private:
    PrivateKey hostKey;
    AuthProvider auth;
  };
}
