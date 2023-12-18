#pragma once

#include <stdint.h>
#include <string>
#include <memory>
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
  ~Preferences();
  Error Open(const std::string_view name = std::string_view());

  Error Remove(const std::string_view key);
  Error Erase();

  std::expected<Blob::Bytes, Error> GetBytes(const std::string_view key);
  Error StoreBytes(const std::string_view key, const Blob::Bytes& data);

  std::expected<std::string, Error> GetString(const std::string_view key);
  Error StoreString(const std::string_view key, const std::string_view data);

private:
  bool opened;
  std::unique_ptr<nvs::NVSHandle> nvs;
};
