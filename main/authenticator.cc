#include "authenticator.h"
#include "secrets.h"

#include <esp_log.h>

#include <hardware/manager.h>
#include <blob/hash.h>
#include <blob/hex.h>


namespace
{
  static const char *TAG = "main::auth";
  const Blob::Bytes verificationSalt = Blob::Bytes(reinterpret_cast<const unsigned char *>("verify"));

  Hardware::Manager& hw = Hardware::Manager::Instance();
  UI::Manager& ui = UI::Manager::Instance();
}

Error Authenticator::Initialize(Secrets* secrets)
{
  this->secrets = secrets;
  return Error::None;
}

void Authenticator::BuildCredential()
{
  ESP_LOGI(TAG, "request pin");
  credBuilding = true;
  credential = secrets->SecretKey();
  ui.ShowRequestPin();
}

bool Authenticator::HasCredential()
{
  return !credBuilding;
}

std::expected<Blob::Bytes, Error> Authenticator::MakeAssertion(const Blob::Bytes& salt, std::string& client)
{
  if (credBuilding) {
    ESP_LOGE(TAG, "unable to get makeAssertion w/o final credential");
    return std::unexpected<Error>{Error::NoCredential};
  }

  std::expected<Blob::Bytes, Error> out = makeAssertion(salt);
  if (out) {
    ui.ShowAssertation(client);
  }

  return std::move(out.value());
}

void Authenticator::OnPinEnter(uint8_t ch)
{
  if (!credBuilding) {
    ESP_LOGE(TAG, "unexpected OnPinChar calling");
    return;
  }

  Blob::Bytes salt(&ch, 1);
  std::expected<Blob::Bytes, Error> ret = makeAssertion(salt);
  if (!ret) {
    return;
  }

  credential = ret.value();
}

void Authenticator::OnPinEntered(bool ok)
{
  if (!credBuilding) {
    ESP_LOGE(TAG, "unexpected OnPinEntered calling");
    return;
  }

  if (ok) {
    std::expected<Blob::Bytes, Error> ret = makeAssertion(verificationSalt);
    if (ret) {
      std::string verification = Blob::HexEncode(ret.value());
      ui.ShowVerifyPin(verification);
      return;
    }
  }

  BuildCredential();
}

void Authenticator::OnPinVerified(bool ok)
{
  if (!credBuilding) {
    ESP_LOGE(TAG, "unexpected OnPinVerified calling");
    return;
  }

  if (ok) {
    ui.ShowIdle();
    credBuilding = false;
    return;
  }

  BuildCredential();
}

std::expected<Blob::Bytes, Error> Authenticator::makeAssertion(const Blob::Bytes& salt)
{
  std::expected<Blob::Bytes, Blob::Error> ret = Blob::HMACSum(credential, salt, Blob::HashType::SHA256);
  if (!ret) {
    ESP_LOGE(TAG, "hamc fail: %d",(int)ret.error());
    return std::unexpected<Error>{Error::ShitHappens};
  }

  return std::move(ret.value());
}
