#pragma once

#include <ArduinoJson.hpp>
#include <preferences.h>
#include <blob/bytes.h>

#include "errors.h"


class Secrets
{
public:
  Secrets() = default;
  Error Initalize();

  Error Store();

  // Error FromJson(const JsonObjectConst& obj) noexcept;
  // Error ToJson(JsonObject& out) const noexcept;

  const Blob::Bytes HostKey() const
  {
    return hostKey;
  }

  const Blob::Bytes SecretKey() const
  {
    return secretKey;
  }

private:
  Error migrate();

private:
  Preferences prefs;
  Blob::Bytes hostKey;
  Blob::Bytes secretKey;
};