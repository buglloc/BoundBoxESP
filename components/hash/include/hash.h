#pragma once

#include <expected>

#include "wolfssl_init.h"
#include <wolfssl/wolfcrypt/hmac.h>
#include "types.h"


namespace Hash
{
  std::expected<Bytes, Error> Sum(const Bytes& key, const Bytes& msg, HashType hashType = HashType::SHA256);
  std::expected<Bytes, Error> HKDF(const Bytes& key, const Bytes& salt, const Bytes& info, size_t outLen, HashType hashType = HashType::SHA256);

  class HMAC
  {
  public:
    explicit HMAC(const Bytes& key, HashType type = HashType::SHA256);
    std::expected<void, Error> Write(const Bytes& data);
    std::expected<Bytes, Error> Sum();

    ~HMAC();
  private:
    Error err = Error::None;
    Hmac ctx;
  };


}
