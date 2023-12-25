#pragma once

#include <expected>
#include <string>
#include <expected>

#include <blob/bytes.h>
#include "common.h"


namespace SSH
{
  enum class KeyType: uint8_t
  {
    None = 0,
    RSA,
    ECDSA,
    ED25519
  };

  class PrivateKey
  {
  public:
    Error Generate(KeyType keyType, uint32_t bits);

    Error Wrap(ssh_key keyPtr);
    Error Load(const std::string& blob, const std::string& passphrase = std::string());
    std::expected<std::string, Error> Marshal(const std::string& passphrase = std::string()) const;

    bool Empty() const {
      return keyType == KeyType::None || keyPtr == nullptr;
    }

    ssh_key Get() const;
    ssh_key Copy() const;

    ~PrivateKey();

  private:
    KeyType keyType = KeyType::None;
    ssh_key keyPtr = nullptr;
  };
}
