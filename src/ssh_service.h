#ifndef BB_SSH_SERVICE_H
#define BB_SSH_SERVICE_H

#include <libssh_esp.h>
#include <xssh.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Result.h>

struct TSshConfig
{
  String RootUser;
  XSsh::Keyring RootKeys;

  enum class MarshalErr
  {
    None,
    ShitHappens
  };

  static cpp::result<TSshConfig&, MarshalErr> FromJson(const JsonObjectConst& obj) noexcept;
  cpp::result<JsonObject, MarshalErr> ToJson() noexcept;
};

struct TSshAuthInfo
{
  String User;
  String Key;
  bool IsSysop;
};

using TSshActionCallback = std::function<bool(const TSshAuthInfo& sess, const String& cmd, const Stream& r, Print& w)>;

class TSshService
{
public:
  static TSshService &Instance();
  bool Begin(const TSshConfig& cfg);
  void Tick(TSshActionCallback actionCallback);

private:
  TSshService() = default;
  cpp::result<TSshAuthInfo&,int> authenticate(ssh_session session);

private:
  XSsh::Key hostKey;
  String rootLogin;
  XSsh::Keyring rootKeys;
};

#endif
