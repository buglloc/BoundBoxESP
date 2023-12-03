#include "authenticator.h"
#include "board_config.h"
#include "defaults.h"

#include <ArduinoLog.h>

TAuthenticator& TAuthenticator::Instance()
{
  static TAuthenticator instance;
  return instance;
}

bool TAuthenticator::Begin()
{
  Log.infoln("authenticator starts");
  Log.infoln("authenticator setup complete");
  return true;
}
