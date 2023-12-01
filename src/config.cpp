#include "defaults.h"
#include "config.h"
#include "pref_store.h"

#include <xssh.h>
#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>
#include <Defer.h>

namespace {
  static TPrefStore& preferences = TPrefStore::Instance();
}

bool
TConfig::Begin()
{
  XSsh::Begin();
  return true;
}

cpp::result<TConfig, TConfig::Err>
TConfig::LoadOrStore(const String& key) noexcept
{
#ifndef USE_PERSISTENT_CONFIG
  Log.infoln("config persistence disabled: use default one");
  char empty[3] = "{}";
  return TConfig::Unmarshal(empty);
#else
  if (preferences.HasKey(key.c_str())) {
    Log.infoln("no stored runtime config '%s' exists: load default", key);
    char empty[3] = "{}";
    auto result = TConfig::Unmarshal(empty);
    if (result.has_error()) {
      return cpp::fail(result.error());
    }

    TConfig cfg = result.value();
    auto storeRes = cfg.Store(key);
    if (storeRes.has_error()) {
      return cpp::fail(storeRes.error());
    }

    return std::move(cfg);
  }

  return Load(key);
#endif
}

cpp::result<void, TConfig::Err>
TConfig::Store(const String& key) noexcept
{
#ifndef USE_PERSISTENT_CONFIG
  return cpp::fail(TConfig::Err::Unsupported);
#else
  auto result = Marshal();
  if (result.has_error()) {
    return cpp::fail(result.error());
  }

  String data = std::move(result.value());
  auto res = preferences.StoreBytes(key.c_str(), data.c_str(), data.length());
  if (res.has_error()) {
    return cpp::fail(TConfig::Err::PrefError);
  }

  return {};
#endif
}

cpp::result<TConfig, TConfig::Err>
TConfig::Load(const String& key) noexcept
{
  auto res = preferences.GetBytes(key.c_str());
  if (res.has_error()) {
    return cpp::fail(TConfig::Err::PrefError);
  }

  char* blob = std::move(res.value());
  auto out = Unmarshal(blob);
  free(blob);
  return out;
}

cpp::result<TConfig, TConfig::Err>
TConfig::Unmarshal(char* buf) noexcept
{
  StaticJsonDocument<1024> doc;
  DeserializationError jsonErr = deserializeJson(doc, buf);
  if (jsonErr) {
    Log.errorln("runtime config: trying to load invalid json: %s", jsonErr.c_str());
    return cpp::fail(TConfig::Err::InvalidJson);
  }

  auto netCfg = TNetConfig::FromJson(doc["net"].as<JsonObject>());
  if (netCfg.has_error()) {
    return cpp::fail(TConfig::Err::InvalidTNetConfig);
  }

  TConfig cfg;
  cfg.Hostname = doc["hostname"] | DEFAULT_HOSTNAME,
  cfg.Net = netCfg.value();

  return std::move(cfg);
}

cpp::result<String, TConfig::Err>
TConfig::Marshal() noexcept
{
  auto netCfg = Net.ToJson();
  if (netCfg.has_error()) {
    Log.errorln("runtime config: unable to serialize net config: %d", netCfg.error());
    return cpp::fail(TConfig::Err::ShitHappens);
  }

  StaticJsonDocument<512> doc;
  doc["hostname"] = Hostname;
  doc["net"] = netCfg.value();

  String out;
  if (serializeJson(doc, out) == 0) {
    Log.errorln("runtime config: unable to serialize json");
    return cpp::fail(TConfig::Err::ShitHappens);
  }

  return out;
}
