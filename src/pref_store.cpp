#include "pref_store.h"
#include "board_config.h"
#include "defaults.h"

#include <esp_err.h>
#include <ArduinoLog.h>


TPrefStore& TPrefStore::Instance()
{
  static TPrefStore instance;
  return instance;
}

bool TPrefStore::Begin()
{
  Log.infoln("preferences manager starts");
  bool ok = prefs.begin(PREFERENCES_NAMESPACE, false);
  if (!ok) {
    Log.errorln("unable to open preferences");
    return false;
  }

  Log.infoln("preferences manager setup complete");
  return true;
}

bool TPrefStore::HasKey(const char* key)
{
  return prefs.isKey(key);
}

cpp::result<BBU::Bytes, TPrefStore::Error> TPrefStore::GetBytes(const char* key)
{
  if (!HasKey(key)) {
    return cpp::fail(TPrefStore::Error::NotExist);
  }

  size_t size = prefs.getBytesLength(key);
  if (size == 0) {
    return cpp::fail(TPrefStore::Error::NotExist);
  }

  BBU::Bytes out(size, '\xff');
  size_t actualSize = prefs.getBytes(key, &out[0], size);
  if (actualSize == 0) {
    Log.errorln("read pref '%s' failed: sero size", key);
    return cpp::fail(TPrefStore::Error::Internal);
  }

  return out;
}

cpp::result<void, TPrefStore::Error> TPrefStore::StoreBytes(const char* key, const BBU::Bytes& data)
{
  size_t expectedSize = sizeof(uint8_t) * data.size();
  size_t actualSize = prefs.putBytes(key, data.data(), expectedSize);
  if (actualSize != expectedSize) {
    return cpp::fail(TPrefStore::Error::PartialWrite);
  }

  return {};
}

cpp::result<char*, TPrefStore::Error> TPrefStore::GetStringBytes(const char* key)
{
  if (!HasKey(key)) {
    return cpp::fail(TPrefStore::Error::NotExist);
  }

  size_t size = prefs.getBytesLength(key);
  if (size == 0) {
    return cpp::fail(TPrefStore::Error::NotExist);
  }

  char* blob = (char *)malloc(sizeof(char) * (size + 1));
  if (!blob) {
    return cpp::fail(TPrefStore::Error::NoMem);
  }

  size_t actualSize = prefs.getBytes(key, blob, size);
  if (actualSize == 0) {
    Log.errorln("read pref '%s' failed: sero size", key);
    return cpp::fail(TPrefStore::Error::Internal);
  }

  return blob;
}

cpp::result<void, TPrefStore::Error> TPrefStore::StoreStringBytes(const char* key, const char* data, size_t size)
{
  size_t expectedSize = sizeof(uint8_t) * size;
  size_t actualSize = prefs.putBytes(key, data, expectedSize);
  if (actualSize != expectedSize) {
    return cpp::fail(TPrefStore::Error::PartialWrite);
  }

  return {};
}

cpp::result<String, TPrefStore::Error> TPrefStore::GetString(const char* key)
{
  if (!HasKey(key)) {
    return cpp::fail(TPrefStore::Error::NotExist);
  }

  return prefs.getString(key);
}

cpp::result<void, TPrefStore::Error> TPrefStore::StoreString(const char* key, const String& data)
{
  size_t actualSize = prefs.putString(key, data);
  if (actualSize != data.length()) {
    return cpp::fail(TPrefStore::Error::PartialWrite);
  }

  return {};
}
