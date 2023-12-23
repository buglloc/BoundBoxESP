#pragma once

#include <ssh/handler.h>

#include <ArduinoJson.h>

#include "errors.h"
#include "authenticator.h"
#include "secrets.h"


class Commands
{
public:
  Error Initialize(Authenticator* auth, Secrets* secrets);
  Error Dispatch(const SSH::UserInfo& userInfo, std::string_view cmdName, SSH::Stream& stream);

private:
  bool Handle(const SSH::UserInfo& userInfo, std::string_view cmdName, const JsonObjectConst& req, JsonObject& rsp);

private:
  Authenticator* auth;
  Secrets* secrets;
};
