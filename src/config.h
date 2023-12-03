#ifndef BB_CONFIG_H
#define BB_CONFIG_H

#include "net_manager.h"
#include "ssh_service.h"

#include <Result.h>

class TConfig
{
public:
  enum class Error: uint8_t
  {
    None,
    InvalidJson,
    InvalidNetConfig,
    InvalidSshConfig,
    InvalidConfig,
    PrefError,
    Unsupported,
    ShitHappens
  };

public:
  String Hostname;
  std::unique_ptr<TNetConfig> Net;
  std::unique_ptr<TSshConfig> Ssh;

public:
  TConfig() = default;

  static bool Begin();
  static cpp::result<std::unique_ptr<TConfig>, Error> Load(const String& key) noexcept;
  static cpp::result<std::unique_ptr<TConfig>, Error> LoadOrStore(const String& key) noexcept;
  cpp::result<void, Error> Store(const String& key) noexcept;

  static cpp::result<std::unique_ptr<TConfig>, Error> FromJson(const JsonObjectConst& obj) noexcept;
  cpp::result<void, Error> ToJson(JsonObject& out) const noexcept;

private:
  static cpp::result<std::unique_ptr<TConfig>, Error> Default() noexcept;
  static cpp::result<std::unique_ptr<TConfig>, Error> Unmarshal(char* buf) noexcept;
  cpp::result<String, Error> Marshal() const noexcept;
};

#endif
