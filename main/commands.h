#pragma once

#include <ssh/handler.h>

#include <ArduinoJson.h>

#include "errors.h"


class Commands
{
public:
  Error Initialize();
  Error Dispatch(const SSH::UserInfo& userInfo, std::string_view cmdName, SSH::Stream& stream);

private:
  bool Handle(const SSH::UserInfo& userInfo, std::string_view cmdName, const JsonObjectConst& req, JsonObject& rsp);
};
