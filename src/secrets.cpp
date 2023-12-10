#include "secrets.h"
#include "defaults.h"
#include "pref_store.h"

#include <xssh.h>
#include <bytes.h>
#include <ArduinoLog.h>

#define LOG_PREFIX "perf_store: "
#define HOST_KEY_KEY SECRET_KEY_PREFIX "host_key"
#define SECRET_KEY_KEY SECRET_KEY_PREFIX "secret_key"

namespace {
  static TPrefStore& preferences = TPrefStore::Instance();

  BBU::Bytes genSecretKey()
  {
    BBU::Bytes out(DEFAULT_SECRET_KEY_SIZE, '\xff');
    esp_fill_random(&out[0], DEFAULT_SECRET_KEY_SIZE);
    return out;
  }
}

TSecrets& TSecrets::Instance()
{
  static TSecrets instance;
  return instance;
}

bool TSecrets::Begin()
{
  Log.infoln(LOG_PREFIX "starts");
  XSSH::Begin();

  auto res = load();
  if (res.has_error()) {
    Log.errorln(LOG_PREFIX "load failed");
    return false;
  }

  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

cpp::result<void, TSecrets::Error> TSecrets::Reset()
{
  bool ok = true;
  if (preferences.HasKey(HOST_KEY_KEY)) {
    auto err = preferences.RemoveKey(HOST_KEY_KEY);
    if (err.has_error()) {
      Log.errorln(LOG_PREFIX "unable to remove host key: %d", err.error());
      ok = false;
    } else {
      hostKey.clear();
    }
  }

  if (preferences.HasKey(SECRET_KEY_KEY)) {
    auto err = preferences.RemoveKey(SECRET_KEY_KEY);
    if (err.has_error()) {
      Log.errorln(LOG_PREFIX "unable to remove secret key: %d", err.error());
      ok = false;
    } else {
      secretKey.clear();
    }
  }

  auto err = migrate();
  if (err.has_error()) {
    return err;
  }

  if (ok) {
    return cpp::fail(TSecrets::Error::ShitHappens);
  }

  return {};
}

cpp::result<void, TSecrets::Error> TSecrets::Store()
{
  auto keyStore = preferences.StoreString(HOST_KEY_KEY, hostKey);
  if (keyStore.has_error()) {
    Log.errorln(LOG_PREFIX "unable to store new host key: %d", keyStore.error());
    return cpp::fail(TSecrets::Error::InvalidHostKey);
  } else {
    Log.infoln(LOG_PREFIX "host key stored in: " HOST_KEY_KEY);
  }

  keyStore = preferences.StoreBytes(SECRET_KEY_KEY, secretKey);
  if (keyStore.has_error()) {
    Log.errorln(LOG_PREFIX "unable to store new secret key: %d", keyStore.error());
    return cpp::fail(TSecrets::Error::InvalidSecretKey);
  } else {
    Log.infoln(LOG_PREFIX "host key stored in: " SECRET_KEY_KEY);
  }

  return {};
}

const String TSecrets::HostKey() const
{
  return hostKey;
}

const BBU::Bytes TSecrets::SecretKey() const
{
  return secretKey;
}

cpp::result<void, TSecrets::Error> TSecrets::SetFromJson(const JsonObjectConst& obj) noexcept
{
  if (obj.containsKey("host_key")) {
    String newHostKey = obj["host_key"].as<String>();
    if (newHostKey.isEmpty()) {
      return cpp::fail(TSecrets::Error::InvalidHostKey);
    }

    hostKey = std::move(newHostKey);
  }

  if (obj.containsKey("secret_key")) {
    String newSecretKeyHex = obj["secret_key"].as<String>();
    if (newSecretKeyHex.isEmpty()) {
      return cpp::fail(TSecrets::Error::InvalidSecretKey);
    }

    BBU::Bytes newSecretKey = BBU::BytesFromHex(newSecretKeyHex);
    if (newSecretKey.empty()) {
      return cpp::fail(TSecrets::Error::InvalidSecretKey);
    }

    secretKey = std::move(newSecretKey);
  }

  return {};
}

cpp::result<void, TSecrets::Error> TSecrets::ToJson(JsonObject& out) const noexcept
{
  out["host_key"] = hostKey;
  out["secret_key"] = BBU::BytesToHex(secretKey);
  return {};
}

cpp::result<void, TSecrets::Error> TSecrets::load()
{
  if (preferences.HasKey(HOST_KEY_KEY)) {
    auto prefHostKey = preferences.GetString(HOST_KEY_KEY);
    if (prefHostKey.has_error()) {
      Log.errorln(LOG_PREFIX "unable to load host key: %d", prefHostKey.error());
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    hostKey = std::move(prefHostKey.value());
  }

  if (preferences.HasKey(SECRET_KEY_KEY)) {
    auto prefSecretKey = preferences.GetBytes(SECRET_KEY_KEY);
    if (prefSecretKey.has_error()) {
      Log.errorln(LOG_PREFIX "unable to load secret key: %d", prefSecretKey.error());
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    secretKey = std::move(prefSecretKey.value());
  }

  return migrate();
}

cpp::result<void, TSecrets::Error> TSecrets::migrate()
{
  if (hostKey.isEmpty()) {
    Log.warningln(LOG_PREFIX "no host_key found: generate new one");
    auto newKey = XSSH::GenKey(DEFAULT_SSH_HOST_KEY_TYPE, DEFAULT_SSH_HOST_KEY_BITS);
    if (newKey.has_error()) {
      Log.errorln(LOG_PREFIX "unable to generate new host key: %d", newKey.error());
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    auto newKeyStr = XSSH::MarshalPrivateKey(newKey.value());
    if (newKeyStr.has_error()) {
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    hostKey = newKeyStr.value();
    auto keyStore = preferences.StoreString(HOST_KEY_KEY, hostKey);
    if (keyStore.has_error()) {
      Log.errorln(LOG_PREFIX "unable to store new host key: %d", keyStore.error());
    } else {
      Log.infoln(LOG_PREFIX "new host key stored in: " HOST_KEY_KEY);
    }
  }

  if (secretKey.empty()) {
    Log.warningln(LOG_PREFIX "no secret_key found: generate new one");

    secretKey = genSecretKey();
    auto keyStore = preferences.StoreBytes(SECRET_KEY_KEY, secretKey);
    if (keyStore.has_error()) {
      Log.errorln(LOG_PREFIX "unable to store new secret key: %d", keyStore.error());
    } else {
      Log.infoln(LOG_PREFIX "new host key stored in: " SECRET_KEY_KEY);
    }
  }

  return {};
}
