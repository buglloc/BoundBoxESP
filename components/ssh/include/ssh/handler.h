#pragma once

#include <memory>
#include <functional>
#include <string>

#include "auth_provider.h"
#include "stream.h"


namespace SSH
{
  using UserInfoHolder = std::unique_ptr<UserInfo>;
  using HandlerCallback = std::function<int(const UserInfo& userInfo, std::string_view cmd, Stream& stream)>;
}
