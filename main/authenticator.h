#pragma once

#include <expected>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <ui/manager.h>
#include <blob/bytes.h>
#include <hardware/manager.h>

#include "secrets.h"

class Authenticator final: public UI::Handler
{
public:
  Error Initialize(Secrets* secrets);

  void BuildCredential();
  bool HasCredential();
  std::expected<Blob::Bytes, Error> MakeHmacSecret(const Blob::Bytes& salt, const std::string& client);

  void OnPinEnter(uint8_t ch);
  void OnPinEntered(bool ok);
  void OnPinVerified(bool ok);

private:
  std::expected<Blob::Bytes, Error> makeHmacSecretLocked(const Blob::Bytes& salt);

private:
  Blob::Bytes credential;
  bool credBuilding = false;
  SemaphoreHandle_t credMu = nullptr;
  Secrets* secrets = nullptr;
};
