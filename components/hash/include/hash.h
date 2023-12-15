#pragma once

#include <result.h>
#include "wolfssl_init.h"
#include <wolfssl/wolfcrypt/hmac.h>
#include "types.h"


namespace Hash
{
  cpp::result<Bytes, Error> Sum(const Bytes& key, const Bytes& msg, HashType hashType = HashType::SHA256);
  cpp::result<Bytes, Error> HKDF(const Bytes& key, const Bytes& salt, const Bytes& info, size_t outLen, HashType hashType = HashType::SHA256);

  class HMAC
  {
  public:
    explicit HMAC(const Bytes& key, HashType type = HashType::SHA256);
    cpp::result<void, Error> Write(const Bytes& data);
    cpp::result<Bytes, Error> Sum();

    ~HMAC();
  private:
    Error err = Error::None;
    Hmac ctx;
  };


}
