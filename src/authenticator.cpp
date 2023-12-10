#include "authenticator.h"
#include "board_config.h"
#include "defaults.h"
#include "ui_manager.h"
#include "secrets.h"

#include <hmac.h>
#include <ArduinoLog.h>

namespace
{
  static TUIManager& ui = TUIManager::Instance();
  static TSecrets& secrets = TSecrets::Instance();
  const BBU::Bytes verificationSalt = BBU::Bytes(reinterpret_cast<const unsigned char *>("verify"));
}

TAuthenticator& TAuthenticator::Instance()
{
  static TAuthenticator instance;
  return instance;
}

bool TAuthenticator::Begin()
{
  Log.infoln("authenticator starts");
  requestPin();
  Log.infoln("authenticator setup complete");
  return true;
}

cpp::result<BBU::Bytes, TAuthenticator::Error> TAuthenticator::Attest(const BBU::Bytes& salt, const String& client)
{
  if (credBuilding) {
    Log.errorln("authenticator: unable to attest w/o final credential");
    return cpp::fail(TAuthenticator::Error::NoCredential);
  }

  auto out = attest(salt);
  if (!out.has_error()) {
    ui.ShowNotify(R"(\(o_o)/)", client);
  }

  return std::move(out);
}

void TAuthenticator::OnPinChar(uint8_t ch)
{
  if (!credBuilding) {
    Log.errorln("authenticator: unexpected OnPinChar calling");
    return;
  }

  BBU::Bytes salt(&ch, 1);
  auto attestRes = attest(salt);
  if (attestRes.has_error()) {
    return;
  }

  credential = attestRes.value();
}

void TAuthenticator::OnPinEntered(bool ok)
{
  if (!credBuilding) {
    Log.errorln("authenticator: unexpected OnPinEntered calling");
    return;
  }

  if (ok) {
    auto attestRes = attest(verificationSalt);
    if (!attestRes.has_error()) {
      String verification = BBU::BytesToHex(attestRes.value());
      ui.ShowVerifyPin(verification);
      return;
    }
  }

  requestPin();
}

void TAuthenticator::OnPinVerified(bool ok)
{
  if (!credBuilding) {
    Log.errorln("authenticator: unexpected OnPinVerified calling");
    return;
  }

  if (ok) {
    ui.ShowIdle();
    credBuilding = false;
    return;
  }

  requestPin();
}

cpp::result<BBU::Bytes, TAuthenticator::Error> TAuthenticator::attest(const BBU::Bytes& salt)
{
  auto hmacRes = HMAC::Sum(credential, salt, HMAC::Type::SHA256);
  if (hmacRes.has_error()) {
    Log.infoln("authenticator: hmac fail: %d", hmacRes.error());
    return cpp::fail(Error::Internal);
  }

  return std::move(hmacRes.value());
}

void TAuthenticator::requestPin()
{
  Log.infoln("authenticator: request pin");
  credBuilding = true;
  credential = secrets.SecretKey();
  ui.ShowRequestPin();
}