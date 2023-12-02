#ifndef BB_SSH_HANDLER_H
#define BB_SSH_HANDLER_H

#include "ssh_service.h"
#include <ArduinoJson.h>

class TCommandDispatcher
{
public:
  static TCommandDispatcher &Instance();
  bool Begin();
  void Handle(const TSshAuthInfoHolder& sess, const String& cmd, const JsonObjectConst& req, JsonObject& rsp);

private:
   TCommandDispatcher() = default;
};

#endif
