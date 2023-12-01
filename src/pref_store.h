#ifndef BB_PREF_STORE_H
#define BB_PREF_STORE_H

#include "defaults.h"
#include <Arduino.h>
#include <Result.h>
#include <Preferences.h>

class TPrefStore
{
public:
  enum class Error
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
  cpp::result<char*, Error> GetBytes(const char* key);
  cpp::result<void, Error> StoreBytes(const char* key, const char* data, size_t size);

  cpp::result<String, Error> GetString(const char* key);
  cpp::result<void, Error> StoreString(const char* key, const String& data);

private:
  TPrefStore() = default;
  Preferences prefs;

};

#endif