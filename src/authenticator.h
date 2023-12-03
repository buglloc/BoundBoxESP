#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <result.h>

class TAuthenticator
{
public:
  enum class Error: uint8_t
  {
    None,
    Internal
  };

public:
  static TAuthenticator &Instance();
  bool Begin();

private:
  TAuthenticator() = default;

};

#endif