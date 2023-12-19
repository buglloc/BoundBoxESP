#pragma once

#include <stdint.h>
#include <string>
#include <memory>
#include <functional>
#include <expected>

#include <nvs_handle.hpp>
#include <blob/bytes.h>

class Preferences
{
public:
  enum class Error: uint8_t
  {
    None = 0,
    InvalidState,
    InvalidArg,
    Unsupported,
    NotExist,
    Internal
  };

public:
  Preferences() = default;
  Error Open(const std::string& name = std::string());

  Error Remove(const std::string& key);
  Error Erase();

  std::expected<Blob::Bytes, Error> GetBytes(const std::string& key);
  Error StoreBytes(const std::string& key, const Blob::Bytes& data);

  std::expected<std::string, Error> GetString(const std::string& key);
  Error StoreString(const std::string& key, const std::string& data);

private:
  bool opened = false;
  std::unique_ptr<nvs::NVSHandle> nvs;
};
