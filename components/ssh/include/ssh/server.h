#pragma once

#include <memory>
#include <string>
#include <vector>

#include <result.h>

#include "handler.h"
#include "errors.h"

// fwd
struct WOLFSSH_CTX;
struct WOLFSSH;
class Auth;

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
    cpp::result<void, Error> Initialize(const ServerConfig& cfg);
    cpp::result<void, ListenError> Listen(const HandlerCallback& handler);

    ~Server();
  private:
    cpp::result<void, Error> SetupWolfSSH(const ServerConfig& cfg);
    cpp::result<void, Error> AcceptConnection(const WOLFSSH* ssh, std::string clientIP);

  private:
    WOLFSSH_CTX* wolfCtx = nullptr;
    Auth auth;
  };
}
