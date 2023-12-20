#pragma once

#include <memory>
#include <string>
#include <vector>
#include <expected>

#include "common.h"
#include "keys.h"
#include "handler.h"
#include "auth_provider.h"


struct WOLFSSH_CTX;
struct WOLFSSH;

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

    ~Server();
  private:
    Error SetupWolfSSH(const ServerConfig& cfg);
    std::expected<int, ListenError> HandleConnection(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);
    std::expected<int, ListenError> DoExec(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);

  private:
    WOLFSSH_CTX* wolfCtx = nullptr;
    AuthProvider auth;
  };
}
