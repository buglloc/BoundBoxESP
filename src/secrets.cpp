#include "secrets.h"
#include "defaults.h"
#include "pref_store.h"

#include <xssh.h>
#include <ArduinoLog.h>

#define HOST_KEY_KEY SECRET_KEY_PREFIX "host_key"

namespace {
  static TPrefStore& preferences = TPrefStore::Instance();
}

TSecrets& TSecrets::Instance()
{
  static TSecrets instance;
  return instance;
}

bool TSecrets::Begin()
{
  Log.infoln("secrets manager starts");
  XSSH::Begin();

  auto res = load();
  if (res.has_error()) {
    Log.errorln("load failed");
    return false;
  }

  Log.infoln("secrets manager complete");
  return true;
}

const String TSecrets::HostKey() const
{
  return hostKey;
}

cpp::result<void, TSecrets::Error> TSecrets::load()
{
  if (preferences.HasKey(HOST_KEY_KEY)) {
    auto prefHostKey = preferences.GetString(HOST_KEY_KEY);
    if (prefHostKey.has_error()) {
      Log.errorln("unable to load host key: %d", prefHostKey.error());
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    hostKey = std::move(prefHostKey.value());
  }

  return migrate();
}

cpp::result<void, TSecrets::Error> TSecrets::migrate()
{
  if (hostKey.isEmpty()) {
    Log.warningln("no host_key found: generate new one");
    auto newKey = XSSH::GenKey(DEFAULT_SSH_HOST_KEY_TYPE, DEFAULT_SSH_HOST_KEY_BITS);
    if (newKey.has_error()) {
      Log.errorln("unable to generate new host key: %d", newKey.error());
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    auto newKeyStr = XSSH::MarshalPrivateKey(newKey.value());
    if (newKeyStr.has_error()) {
      return cpp::fail(TSecrets::Error::ShitHappens);
    }

    hostKey = newKeyStr.value();
    auto keyStore = preferences.StoreString(HOST_KEY_KEY, hostKey);
    if (keyStore.has_error()) {
      Log.errorln("unable to store new host key: %d", keyStore.error());
    } else {
      Log.infoln("new host key stored in: " HOST_KEY_KEY);
    }
  }

  return {};
}
