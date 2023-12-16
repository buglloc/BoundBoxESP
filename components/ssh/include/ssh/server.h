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
    std::string Banner;
    std::string RootUser;
    std::vector<std::string> RootKeys;
  };

  class Server
  {
  public:
    Server() = default;
    std::expected<void, Error> Initialize(const ServerConfig& cfg);
    std::expected<void, ListenError> Listen(const HandlerCallback& handler);

    ~Server();
  private:
    std::expected<void, Error> SetupWolfSSH(const ServerConfig& cfg);
    std::expected<void, ListenError> AcceptConnection(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);
    std::expected<void, ListenError> ProcessSessionCommand(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler);

  private:
    WOLFSSH_CTX* wolfCtx = nullptr;
    AuthProvider auth;
  };
}
