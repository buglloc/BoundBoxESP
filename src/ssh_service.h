#ifndef BB_SSH_SERVICE_H
#define BB_SSH_SERVICE_H

#include <libssh_esp.h>
#include <xssh.h>
#include <Result.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Printable.h>

struct TSshConfig
{
  String RootUser;
  XSSH::Keyring RootKeys;

  enum class MarshalErr: uint8_t
  {
    None,
    ShitHappens
  };

  static cpp::result<std::unique_ptr<TSshConfig>, MarshalErr> FromJson(const JsonObjectConst& obj) noexcept;
  cpp::result<void, MarshalErr> ToJson(JsonObject& out) const noexcept;
};

struct TSshAuthInfo: public Printable
{
  String User;
  String KeyFingerprint;
  bool IsSysop;

  size_t printTo(Print& p) const override;
};

using TSshReader = XSSH::ChanStream;
using TSshWriter = XSSH::ChanPrinter;
using TSshAuthInfoHolder = std::unique_ptr<TSshAuthInfo>;
using TSshActionCallback = std::function<bool(const TSshAuthInfoHolder& sess, const String& cmd, TSshReader& r, TSshWriter& w)>;

class TSshService
{
public:
  static TSshService &Instance();
  bool Begin(const TSshConfig& cfg);
  void Tick(TSshActionCallback actionCallback);

private:
  TSshService() = default;
  std::unique_ptr<TSshAuthInfo> authenticate(ssh_session session);

private:
  XSSH::Key hostKey;
  String rootLogin;
  XSSH::Keyring rootKeys;
};

#endif
