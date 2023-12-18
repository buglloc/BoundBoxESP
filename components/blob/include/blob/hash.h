#pragma once

#include <expected>

#include "wolfssl_init.h"
#include <wolfssl/wolfcrypt/hmac.h>

#include "bytes.h"
#include "errors.h"

namespace Blob
{
  enum class HashType: uint8_t
  {
    None = 0,
    SHA1,
    SHA256,
    SHA512,
  };

  struct HKDFConfig
  {
    const Blob::Bytes& Key;
    const Blob::Bytes& Salt;
    HashType HashType = HashType::SHA256;
  };

  std::expected<Bytes, Error> HMACSum(const Blob::Bytes& key, const Blob::Bytes& msg, HashType hashType = HashType::SHA256);
  std::expected<Bytes, Error> HKDF(const Blob::Bytes& info, size_t outLen, const HKDFConfig& cfg);

  class HMAC
  {
  public:
    explicit HMAC(const Blob::Bytes& key, HashType type = HashType::SHA256);
    Error Write(const Blob::Bytes& data);
    std::expected<Blob::Bytes, Error> Sum();

    ~HMAC();
  private:
    Error err = Error::None;
    Hmac ctx;
  };
}
