#include "authenticator.h"
#include "secrets.h"

#include <esp_log.h>

#include <hardware/manager.h>
#include <ui/manager.h>
#include <blob/hash.h>
#include <blob/hex.h>


namespace
{
  static const char *TAG = "main::auth";
  const Blob::Bytes verificationSalt = Blob::Bytes(reinterpret_cast<const unsigned char *>(CONFIG_PIN_VERIFICATION_SALT));

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

std::expected<Blob::Bytes, Error> Authenticator::MakeHmacSecret(const Blob::Bytes& salt, const std::string& client)
{
  if (credBuilding) {
    ESP_LOGE(TAG, "unable to bake HMAC secret w/o final credential");
    return std::unexpected<Error>{Error::NoCredential};
  }

  std::expected<Blob::Bytes, Error> out = makeHmacSecret(salt);
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
  std::expected<Blob::Bytes, Error> ret = makeHmacSecret(salt);
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
    std::expected<Blob::Bytes, Error> ret = makeHmacSecret(verificationSalt);
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

std::expected<Blob::Bytes, Error> Authenticator::makeHmacSecret(const Blob::Bytes& salt)
{
  std::expected<Blob::Bytes, Blob::Error> ret = Blob::HMAC::Sum(credential, salt, Blob::HashType::SHA256);
  if (!ret) {
    ESP_LOGE(TAG, "hmac fail: %d",(int)ret.error());
    return std::unexpected<Error>{Error::ShitHappens};
  }

  return std::move(ret.value());
}
