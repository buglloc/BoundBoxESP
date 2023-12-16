#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <Arduino.h>
#include <bytes.h>
#include <result.h>

class TAuthenticator
{
public:
  enum class Error: uint8_t
  {
    None = 0,
    Internal,
    NoCredential
  };

public:
  static TAuthenticator &Instance();
  bool Begin();
  void BuildCredential();
  bool HasCredential();

  cpp::result<BBU::Bytes, Error> MakeAssertion(const BBU::Bytes& salt, const String& client);
  void OnPinChar(uint8_t ch);
  void OnPinEntered(bool ok);
  void OnPinVerified(bool ok);

private:
  TAuthenticator() = default;
  cpp::result<BBU::Bytes, Error> makeAssertion(const BBU::Bytes& salt);

private:
  BBU::Bytes credential;
  bool credBuilding;
};

#endif