#ifndef BB_PREF_STORE_H
#define BB_PREF_STORE_H

#include "defaults.h"
#include <bytes.h>
#include <Arduino.h>
#include <result.h>
#include <Preferences.h>

class TPrefStore
{
public:
  enum class Error: uint8_t
  {
    None,
    NoMem,
    PartialWrite,
    Unsupported,
    NotExist,
    Internal
  };

public:
  static TPrefStore &Instance();
  bool Begin();

  bool HasKey(const char* key);
  cpp::result<void, Error> RemoveKey(const char* key);

  cpp::result<BBU::Bytes, Error> GetBytes(const char* key);
  cpp::result<void, Error> StoreBytes(const char* key, const BBU::Bytes& datq);

  cpp::result<char*, Error> GetStringBytes(const char* key);
  cpp::result<void, Error> StoreStringBytes(const char* key, const char* data, size_t size);

  cpp::result<String, Error> GetString(const char* key);
  cpp::result<void, Error> StoreString(const char* key, const String& data);

private:
  TPrefStore() = default;
  Preferences prefs;

};

#endif
