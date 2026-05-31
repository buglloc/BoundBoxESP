#include "authenticator.h"
#include "secrets.h"

#include <defer.h>
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
  credMu = xSemaphoreCreateMutex();
  if (credMu == nullptr) {
    ESP_LOGE(TAG, "unable to allocate credential mutex");
    return Error::ShitHappens;
  }

  return Error::None;
}

void Authenticator::BuildCredential()
{
  ESP_LOGI(TAG, "request pin");
  xSemaphoreTake(credMu, portMAX_DELAY);
  {
    REF_DEFER(xSemaphoreGive(credMu));
    credBuilding = true;
    credential = secrets->SecretKey();
  }
  ui.ShowRequestPin();
}

bool Authenticator::HasCredential()
{
  xSemaphoreTake(credMu, portMAX_DELAY);
  REF_DEFER(xSemaphoreGive(credMu));
  return !credBuilding;
}

std::expected<Blob::Bytes, Error> Authenticator::MakeHmacSecret(const Blob::Bytes& salt, const std::string& client)
{
  std::expected<Blob::Bytes, Error> out;
  {
    xSemaphoreTake(credMu, portMAX_DELAY);
    REF_DEFER(xSemaphoreGive(credMu));

    if (credBuilding) {
      ESP_LOGE(TAG, "unable to bake HMAC secret w/o final credential");
      return std::unexpected<Error>{Error::NoCredential};
    }

    out = makeHmacSecretLocked(salt);
  }
  if (!out) {
    return std::unexpected<Error>{out.error()};
  }

  ui.ShowAssertation(client);
  return std::move(out.value());
}

void Authenticator::OnPinEnter(uint8_t ch)
{
  xSemaphoreTake(credMu, portMAX_DELAY);
  REF_DEFER(xSemaphoreGive(credMu));

  if (!credBuilding) {
    ESP_LOGE(TAG, "unexpected OnPinChar calling");
    return;
  }

  Blob::Bytes salt(&ch, 1);
  std::expected<Blob::Bytes, Error> ret = makeHmacSecretLocked(salt);
  if (!ret) {
    return;
  }

  credential = ret.value();
}

void Authenticator::OnPinEntered(bool ok)
{
  std::string verification;
  bool showVerification = false;
  {
    xSemaphoreTake(credMu, portMAX_DELAY);
    REF_DEFER(xSemaphoreGive(credMu));

    if (!credBuilding) {
      ESP_LOGE(TAG, "unexpected OnPinEntered calling");
      return;
    }

    if (ok) {
      std::expected<Blob::Bytes, Error> ret = makeHmacSecretLocked(verificationSalt);
      if (ret) {
        verification = Blob::HexEncode(ret.value());
        showVerification = true;
      }
    }
  }

  if (showVerification) {
    ui.ShowVerifyPin(verification);
    return;
  }

  BuildCredential();
}

void Authenticator::OnPinVerified(bool ok)
{
  bool showInfo = false;
  {
    xSemaphoreTake(credMu, portMAX_DELAY);
    REF_DEFER(xSemaphoreGive(credMu));

    if (!credBuilding) {
      ESP_LOGE(TAG, "unexpected OnPinVerified calling");
      return;
    }

    if (ok) {
      credBuilding = false;
      showInfo = true;
    }
  }

  if (showInfo) {
    ui.ShowInfo();
  } else {
    BuildCredential();
  }
}

std::expected<Blob::Bytes, Error> Authenticator::makeHmacSecretLocked(const Blob::Bytes& salt)
{
  std::expected<Blob::Bytes, Blob::Error> ret = Blob::HMAC::Sum(credential, salt, Blob::HashType::SHA256);
  if (!ret) {
    ESP_LOGE(TAG, "hmac fail: %d",(int)ret.error());
    return std::unexpected<Error>{Error::ShitHappens};
  }

  return std::move(ret.value());
}
