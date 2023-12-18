#pragma once

#include <memory>
#include <string>
#include <vector>
#include <expected>

#include "common.h"
#include "handler.h"
#include "auth_provider.h"


struct WOLFSSH_CTX;
struct WOLFSSH;

namespace SSH
{
  struct ServerConfig
  {
    std::string RootUser;
    std::vector<std::string> RootKeys;
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
    ListenError AcceptConnection(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);
    ListenError ProcessSessionCommand(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);

  private:
    WOLFSSH_CTX* wolfCtx = nullptr;
    AuthProvider auth;
  };
}
