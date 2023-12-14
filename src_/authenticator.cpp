#include "authenticator.h"
#include "board_config.h"
#include "defaults.h"
#include "ui_manager.h"
#include "secrets.h"

#include <hmac.h>
#include <hex.h>
#include <ArduinoLog.h>

#define LOG_PREFIX "authenticator: "

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
  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

void TAuthenticator::BuildCredential()
{
  Log.infoln(LOG_PREFIX "request pin");
  credBuilding = true;
  credential = secrets.SecretKey();
  ui.ShowRequestPin();
}

bool TAuthenticator::HasCredential()
{
  return !credBuilding;
}

cpp::result<BBU::Bytes, TAuthenticator::Error> TAuthenticator::MakeAssertion(const BBU::Bytes& salt, const String& client)
{
  if (credBuilding) {
    Log.errorln(LOG_PREFIX "unable to get makeAssertion w/o final credential");
    return cpp::fail(TAuthenticator::Error::NoCredential);
  }

  auto out = makeAssertion(salt);
  if (!out.has_error()) {
    ui.ShowNotify(client);
  }

  return std::move(out);
}

void TAuthenticator::OnPinChar(uint8_t ch)
{
  if (!credBuilding) {
    Log.errorln(LOG_PREFIX "unexpected OnPinChar calling");
    return;
  }

  BBU::Bytes salt(&ch, 1);
  auto result = makeAssertion(salt);
  if (result.has_error()) {
    return;
  }

  credential = result.value();
}

void TAuthenticator::OnPinEntered(bool ok)
{
  if (!credBuilding) {
    Log.errorln(LOG_PREFIX "unexpected OnPinEntered calling");
    return;
  }

  if (ok) {
    auto result = makeAssertion(verificationSalt);
    if (!result.has_error()) {
      String verification = BBU::HexEncode(result.value());
      ui.ShowVerifyPin(verification);
      return;
    }
  }

  BuildCredential();
}

void TAuthenticator::OnPinVerified(bool ok)
{
  if (!credBuilding) {
    Log.errorln(LOG_PREFIX "unexpected OnPinVerified calling");
    return;
  }

  if (ok) {
    ui.ShowIdle();
    credBuilding = false;
    return;
  }

  BuildCredential();
}

cpp::result<BBU::Bytes, TAuthenticator::Error> TAuthenticator::makeAssertion(const BBU::Bytes& salt)
{
  auto hmacRes = HMAC::Sum(credential, salt, HMAC::Type::SHA256);
  if (hmacRes.has_error()) {
    Log.infoln(LOG_PREFIX "hmac fail: %d", hmacRes.error());
    return cpp::fail(Error::Internal);
  }

  return std::move(hmacRes.value());
}
