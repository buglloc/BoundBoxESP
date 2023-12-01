#ifndef BB_SECRETS_H
#define BB_SECRETS_H

#include <Arduino.h>
#include <Result.h>

class TSecrets
{
public:
  enum Error
  {
    None,
    ShitHappens
  };

public:
  static TSecrets &Instance();
  bool Begin();

  const String HostKey() const;

private:
  TSecrets() = default;
  cpp::result<void, Error> load();
  cpp::result<void, Error> migrate();

private:
  String hostKey;
};

#endif