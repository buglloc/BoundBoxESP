#pragma once

#include <memory>
#include <functional>
#include <string>

namespace SSH
{
  struct AuthInfo
  {
    std::string User;
    std::string KeyFingerprint;
    std::string ClientIP;
    bool IsSysop;
  };

  // using TSshReader = XSSH::ChanReader;
  // using TSshWriter = XSSH::ChanWriter;
  using AuthInfoHolder = std::unique_ptr<AuthInfo>;
  using HandlerCallback = std::function<bool(const AuthInfo& auth, const std::string& cmd, TSshReader& r, TSshWriter& w)>;
}
