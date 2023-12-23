#pragma once

#include <expected>

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
  std::expected<Blob::Bytes, Error> MakeAssertion(const Blob::Bytes& salt, const std::string& client);

  void OnPinEnter(uint8_t ch);
  void OnPinEntered(bool ok);
  void OnPinVerified(bool ok);

private:
  std::expected<Blob::Bytes, Error> makeAssertion(const Blob::Bytes& salt);

private:
  Blob::Bytes credential;
  bool credBuilding;
  Secrets* secrets = nullptr;
};
