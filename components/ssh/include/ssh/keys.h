#pragma once

#include <expected>
#include <string>
#include <expected>

#include <blob/bytes.h>
#include "common.h"

#define RSAKEY_DEFAULT_SIZE 2048
#define RSAKEY_DEFAULT_E    65537
#define ECDSAKEY_PRIME256   256
#define ECDSAKEY_PRIME384   384
#define ECDSAKEY_PRIME521   521


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
    Error ImportPem(const Blob::Bytes& pem);
    std::expected<Blob::Bytes, Error> ExportPem() const;

    Error ImportDer(KeyType keyType, Blob::Bytes& blob);
    std::expected<Blob::Bytes, Error> ExportDer() const;

    const Blob::Bytes& Ref() const
    {
      return keyDer;
    }

    KeyType Type() const
    {
      return keyType;
    }

    bool IsEmpty() const {
      return keyType == KeyType::None || keyDer.empty();
    }

  private:
    KeyType keyType;
    Blob::Bytes keyDer;
  };

  std::expected<std::string, Error> KeyFingerprint(const Blob::Bytes& pubKey);
  std::expected<PrivateKey, Error> KeyGen(KeyType keyType, uint32_t bits);
}
