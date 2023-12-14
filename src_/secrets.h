#ifndef BB_SECRETS_H
#define BB_SECRETS_H

#include <hmac.h>
#include <bytes.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <result.h>

class TSecrets
{
public:
  enum class Error: uint8_t
  {
    None,
    InvalidHostKey,
    InvalidSecretKey,
    ShitHappens
  };

public:
  static TSecrets &Instance();
  bool Begin();
  cpp::result<void, Error> Store();
  cpp::result<void, Error> Reset();

  cpp::result<void, Error> SetFromJson(const JsonObjectConst& obj) noexcept;
  cpp::result<void, Error> ToJson(JsonObject& out) const noexcept;

  const String HostKey() const;
  const BBU::Bytes SecretKey() const;

private:
  TSecrets() = default;
  cpp::result<void, Error> load();
  cpp::result<void, Error> migrate();

private:
  String hostKey;
  BBU::Bytes secretKey;
};

#endif
