#include <sdkconfig.h>
#include "secrets.h"
#include "errors.h"

#include <expected>

#include <esp_log.h>
#include <esp_random.h>

#include <blob/bytes.h>
#include <blob/base64.h>
#include <ssh/keys.h>

#define CONFIG_HOST_KEY_TYPE NeedTooChooseHostKeyType()
#define CONFIG_HOST_KEY_BITS NeedTooChooseHostKeyBits()
#ifdef CONFIG_HOSTKEY_TYPE_RSA
  #undef CONFIG_HOST_KEY_TYPE
  #undef CONFIG_HOST_KEY_BITS
  #define CONFIG_HOST_KEY_TYPE SSH::KeyType::RSA
  #define CONFIG_HOST_KEY_BITS CONFIG_HOSTKEY_RSA_BITS
#endif
#ifdef CONFIG_HOSTKEY_TYPE_ECDSA
  #undef CONFIG_HOST_KEY_TYPE
  #undef CONFIG_HOST_KEY_BITS
  #define CONFIG_HOST_KEY_TYPE SSH::KeyType::ECDSA
  #define CONFIG_HOST_KEY_BITS CONFIG_HOSTKEY_ECDSA_BITS
#endif

namespace {
  static const char *TAG = "main::secrets";
  static const char *PREF_NAMESPACE = "bb_secrets";
  static const char *HOST_KEY_KEY = "host_key";
  static const char *SECRET_KEY_KEY = "secret_key";

  Blob::Bytes genSecretKey(size_t len)
  {
    Blob::Bytes out(len, '\xff');
    esp_fill_random(out.data(), len);
    return out;
  }
}

Error Secrets::Initalize()
{
  Preferences::Error prefsErr = prefs.Open(PREF_NAMESPACE);
  if (prefsErr != Preferences::Error::None) {
    ESP_LOGE(TAG, "initialize preferences with namespace '%s' failed: %d", PREF_NAMESPACE, (int)prefsErr);
    return Error::ShitHappens;
  }

  std::expected<std::string, Preferences::Error> storedHostKey = prefs.GetString(HOST_KEY_KEY);
  if (storedHostKey) {
    SSH::Error sshErr = hostKey.ImportPem(std::move(storedHostKey.value()));
    if (sshErr != SSH::Error::None) {
      ESP_LOGE(TAG, "unable to import host key: %d", (int)sshErr);
      return Error::ShitHappens;
    }

  } else if (storedHostKey.error() != Preferences::Error::NotExist) {
    ESP_LOGE(TAG, "read host key: %d", (int)storedHostKey.error());
    return Error::ShitHappens;
  }

  std::expected<Blob::Bytes, Preferences::Error> storedSecretKey = prefs.GetBytes(SECRET_KEY_KEY);
  if (storedSecretKey) {
    secretKey = std::move(storedSecretKey.value());
  } else if (storedSecretKey.error() != Preferences::Error::NotExist) {
    ESP_LOGE(TAG, "read secret key: %d", (int)storedSecretKey.error());
    return Error::ShitHappens;
  }

  return migrate();
}

Error Secrets::Store()
{
  if (!hostKey.IsEmpty()) {
    std::expected<std::string, SSH::Error> hostPem = hostKey.ExportPem();
    if (!hostPem) {
      ESP_LOGE(TAG,  "unable to export generated host key: %d", (int)hostPem.error());
      return Error::ShitHappens;
    }

    Preferences::Error err = prefs.StoreString(HOST_KEY_KEY, std::move(hostPem.value()));
    if (err != Preferences::Error::None) {
      ESP_LOGE(TAG, "unable to store new host key: %d", (int)err);
      return Error::ShitHappens;
    }

    ESP_LOGI(TAG, "host key stored in: %s", HOST_KEY_KEY);
  } else {
    ESP_LOGW(TAG, "ignore empty host key storing");
  }

  if (!secretKey.empty()) {
    Preferences::Error err = prefs.StoreBytes(SECRET_KEY_KEY, secretKey);
    if (err != Preferences::Error::None) {
      ESP_LOGE(TAG, "unable to store new secret key '%s': %d", SECRET_KEY_KEY, (int)err);
      return Error::InvalidSecretKey;
    }
    ESP_LOGI(TAG, "host key stored in: %s",  SECRET_KEY_KEY);
  } else {
    ESP_LOGW(TAG, "ignore empty secret key storing");
  }

  return Error::None;
}

Error Secrets::Erase()
{
  Preferences::Error err = prefs.Remove(HOST_KEY_KEY);
  if (err != Preferences::Error::None) {
    ESP_LOGE(TAG, "unable to remove host key: %d", (int)err);
    return Error::ShitHappens;
  }

  err = prefs.Remove(SECRET_KEY_KEY);
  if (err != Preferences::Error::None) {
    ESP_LOGE(TAG, "unable to remove secret key: %d", (int)err);
    return Error::ShitHappens;
  }

  return Error::None;
}

Error Secrets::FromJson(const JsonObjectConst& obj) noexcept
{
  if (!obj.containsKey("host_key") || !obj.containsKey("secret_key")) {
    return Error::ShitHappens;
  }

  SSH::Error sshErr = hostKey.ImportPem(obj["host_key"].as<std::string>());
  if (sshErr != SSH::Error::None) {
    ESP_LOGE(TAG, "unable to parse host key: %d", (int)sshErr);
    return Error::ShitHappens;
  }

  secretKey = Blob::Base64Decode(obj["secret_key"].as<std::string_view>());
  if (secretKey.empty()) {
    ESP_LOGE(TAG, "unable to secret key");
    return Error::ShitHappens;
  }

  return Error::None;
}

Error Secrets::ToJson(JsonObject& out) const noexcept
{
  std::expected<std::string, SSH::Error> hostPem = hostKey.ExportPem();
  if (!hostPem) {
    ESP_LOGE(TAG,  "unable to export generated host key: %d", (int)hostPem.error());
    return Error::ShitHappens;
  }

  out["host_key"] = hostPem.value();
  out["secret_key"] = Blob::Base64Encode(secretKey);
  return Error::None;
}

Error Secrets::migrate()
{
  bool restore = false;
  if (hostKey.IsEmpty()) {
    ESP_LOGW(TAG, "no %s found: generate new one", HOST_KEY_KEY);
    std::expected<SSH::PrivateKey, SSH::Error> newKey = SSH::KeyGen(CONFIG_HOST_KEY_TYPE, CONFIG_HOST_KEY_BITS);
    if (!newKey) {
      ESP_LOGE(TAG,  "unable to generate new host key: %d", (int)newKey.error());
      return Error::ShitHappens;
    }


    hostKey = std::move(newKey.value());

    ESP_LOGI(TAG, "new host key generated");
    restore = true;
  }

  if (secretKey.empty()) {
    ESP_LOGW(TAG, "no %s found: generate new one", SECRET_KEY_KEY);

    secretKey = genSecretKey(CONFIG_SECRET_KEY_SIZE);
    assert(secretKey[0] != '\xff');

    ESP_LOGI(TAG, "new secret key generated");
    restore = true;
  }

  if (restore) {
    return Store();
  }

  return Error::None;
}
