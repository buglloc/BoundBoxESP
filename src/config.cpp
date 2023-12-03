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
  XSSH::Begin();
  return true;
}

cpp::result<std::unique_ptr<TConfig>, TConfig::Error>
TConfig::LoadOrStore(const String& key) noexcept
{
#ifndef USE_PERSISTENT_CONFIG
  Log.infoln("config persistence disabled: use default one");
  return TConfig::Default();
#else
  if (preferences.HasKey(key.c_str())) {
    Log.infoln("no stored runtime config '%s' exists: load default", key);
    auto result = TConfig::Default();
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

cpp::result<void, TConfig::Error>
TConfig::Store(const String& key) noexcept
{
#ifndef USE_PERSISTENT_CONFIG
  return cpp::fail(TConfig::Error::Unsupported);
#else
  auto result = Marshal();
  if (result.has_error()) {
    return cpp::fail(result.error());
  }

  String data = std::move(result.value());
  auto res = preferences.StoreBytes(key.c_str(), data.c_str(), data.length());
  if (res.has_error()) {
    return cpp::fail(TConfig::Error::PrefError);
  }

  return {};
#endif
}

cpp::result<std::unique_ptr<TConfig>, TConfig::Error>
TConfig::Load(const String& key) noexcept
{
  auto res = preferences.GetBytes(key.c_str());
  if (res.has_error()) {
    return cpp::fail(TConfig::Error::PrefError);
  }

  char* blob = std::move(res.value());
  auto out = Unmarshal(blob);
  free(blob);
  return out;
}

cpp::result<std::unique_ptr<TConfig>, TConfig::Error>
TConfig::FromJson(const JsonObjectConst& obj) noexcept
{
  auto netCfg = TNetConfig::FromJson(obj["net"].as<JsonObjectConst>());
  if (netCfg.has_error()) {
    return cpp::fail(TConfig::Error::InvalidNetConfig);
  }

  auto sshCfg = TSshConfig::FromJson(obj["ssh"].as<JsonObjectConst>());
  if (sshCfg.has_error()) {
    return cpp::fail(TConfig::Error::InvalidSshConfig);
  }

  std::unique_ptr<TConfig> cfg(new TConfig());
  cfg->Hostname = obj["hostname"] | DEFAULT_HOSTNAME,
  cfg->Net = std::move(netCfg.value());
  cfg->Ssh = std::move(sshCfg.value());

  return std::move(cfg);
}

cpp::result<void, TConfig::Error>
TConfig::ToJson(JsonObject& out) const noexcept
{
  out["hostname"] = Hostname;
  JsonObject netCfg = out.createNestedObject("net");
  auto netError = Net->ToJson(netCfg);
  if (netError.has_error()) {
    Log.errorln("runtime config: unable to serialize net config: %d", netError.error());
    return cpp::fail(TConfig::Error::ShitHappens);
  }

  JsonObject sshCfg = out.createNestedObject("ssh");
  auto sshError = Ssh->ToJson(sshCfg);
  if (sshError.has_error()) {
    Log.errorln("runtime config: unable to serialize ssh config: %d", sshError.error());
    return cpp::fail(TConfig::Error::ShitHappens);
  }

  return {};
}

cpp::result<String, TConfig::Error>
TConfig::Marshal() const noexcept
{
  StaticJsonDocument<4096> doc;
  JsonObject obj = doc.as<JsonObject>();
  auto jsonErr = ToJson(obj);
  if (jsonErr.has_error()) {
    Log.errorln("runtime config: unable to jsonify");
    return cpp::fail(TConfig::Error::ShitHappens);
  }

  String out;
  if (serializeJson(doc, out) == 0) {
    Log.errorln("runtime config: unable to serialize json");
    return cpp::fail(TConfig::Error::ShitHappens);
  }

  return out;
}

cpp::result<std::unique_ptr<TConfig>, TConfig::Error>
TConfig::Unmarshal(char* buf) noexcept
{
  StaticJsonDocument<4096> doc;
  DeserializationError jsonErr = deserializeJson(doc, buf);
  if (jsonErr) {
    Log.errorln("runtime config: trying to load invalid json: %s", jsonErr.c_str());
    return cpp::fail(TConfig::Error::InvalidJson);
  }

  return FromJson(doc.as<JsonObjectConst>());
}

cpp::result<std::unique_ptr<TConfig>, TConfig::Error>
TConfig::Default() noexcept
{
  StaticJsonDocument<0> doc;
  return FromJson(doc.as<JsonObjectConst>());
}
