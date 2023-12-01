#ifndef BB_CONFIG_H
#define BB_CONFIG_H

#include "net_manager.h"
#include "ssh_service.h"

#include <Result.h>


class TConfig
{
public:
  enum Err
  {
    None,
    InvalidJson,
    InvalidTNetConfig,
    InvalidConfig,
    PrefError,
    Unsupported,
    ShitHappens
  };

public:
  String Hostname;
  TNetConfig Net;
  TSshConfig Ssh;

public:
  TConfig() = default;

  static bool Begin();
  static cpp::result<TConfig, Err> Load(const String& key) noexcept;
  static cpp::result<TConfig, Err> LoadOrStore(const String& key) noexcept;
  cpp::result<void, Err> Store(const String& key) noexcept;

private:
  static cpp::result<TConfig, Err> Unmarshal(char* buf) noexcept;
  cpp::result<String, Err> Marshal() noexcept;
};

#endif
