#pragma once

#include <memory>
#include <functional>
#include <string>

#include "auth_provider.h"
#include "stream.h"


namespace SSH
{

  using UserInfoHolder = std::unique_ptr<UserInfo>;
  using HandlerCallback = std::function<bool(const UserInfo& userInfo, const std::string& cmd, Stream& stream)>;
}
