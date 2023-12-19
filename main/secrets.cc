#include <sdkconfig.h>
#include "secrets.h"
#include "errors.h"

#include <expected>

#include <esp_log.h>
#include <esp_random.h>

#include <blob/bytes.h>
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

  std::expected<Blob::Bytes, Preferences::Error> prefBytes = prefs.GetBytes(HOST_KEY_KEY);
  if (prefBytes) {
    hostKey = std::move(prefBytes.value());
  } else if (prefBytes.error() != Preferences::Error::NotExist) {
    ESP_LOGE(TAG, "read host key: %d", (int)prefBytes.error());
    return Error::ShitHappens;
  }

  prefBytes = prefs.GetBytes(SECRET_KEY_KEY);
  if (prefBytes) {
    secretKey = std::move(prefBytes.value());
  } else if (prefBytes.error() != Preferences::Error::NotExist) {
    ESP_LOGE(TAG, "read secret key: %d", (int)prefBytes.error());
    return Error::ShitHappens;
  }

  return migrate();
}

Error Secrets::Store()
{
  Preferences::Error err = prefs.StoreBytes(HOST_KEY_KEY, hostKey);
  if (err != Preferences::Error::None) {
    ESP_LOGE(TAG, "unable to store new host key '%s': %d", HOST_KEY_KEY, (int)err);
    return Error::InvalidHostKey;
  }
  ESP_LOGI(TAG, "host key stored in: %s",  HOST_KEY_KEY);

  err = prefs.StoreBytes(SECRET_KEY_KEY, secretKey);
  if (err != Preferences::Error::None) {
    ESP_LOGE(TAG, "unable to store new secret key '%s': %d", SECRET_KEY_KEY, (int)err);
    return Error::InvalidSecretKey;
  }
  ESP_LOGI(TAG, "host key stored in: %s",  SECRET_KEY_KEY);

  return Error::None;
}

Error Secrets::migrate()
{
  if (hostKey.empty()) {
    ESP_LOGW(TAG, "no %s found: generate new one", HOST_KEY_KEY);
    std::expected<Blob::Bytes, SSH::Error> newKey = SSH::KeyGen(CONFIG_HOST_KEY_TYPE, CONFIG_HOST_KEY_BITS);
    if (!newKey) {
      ESP_LOGE(TAG,  "unable to generate new host key: %d", (int)newKey.error());
      return Error::ShitHappens;
    }

    // ESP_LOGI(TAG, "new key: %s", newKey.value().data());
    // auto newKeyStr = XSSH::MarshalPrivateKey(newKey.value());
    // if (newKeyStr.has_error()) {
    //   return cpp::fail(TSecrets::Error::ShitHappens);
    // }

    // hostKey = newKeyStr.value();
    // auto keyStore = preferences.StoreString(HOST_KEY_KEY, hostKey);
    // if (keyStore.has_error()) {
    //   Log.errorln(LOG_PREFIX "unable to store new host key: %d", keyStore.error());
    // } else {
    //   Log.infoln(LOG_PREFIX "new host key stored in: " HOST_KEY_KEY);
    // }
  }

  if (secretKey.empty()) {
    ESP_LOGW(TAG, "no %s found: generate new one", SECRET_KEY_KEY);

    secretKey = genSecretKey(CONFIG_SECRET_KEY_SIZE);
    assert(secretKey[0] != '\xff');

    Preferences::Error err = prefs.StoreBytes(SECRET_KEY_KEY, secretKey);
    if (err != Preferences::Error::None) {
      ESP_LOGE(TAG, "unable to store new secret key: %d", (int)err);
      return Error::ShitHappens;
    }

    ESP_LOGI(TAG, "new secret key stored in: %s", SECRET_KEY_KEY);
  }

  return Error::None;
}
