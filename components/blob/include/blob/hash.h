#pragma once

#include <expected>


#include "bytes.h"
#include "errors.h"

// fwd
struct mbedtls_md_context_t;


namespace Blob
{
  enum class HashType: uint8_t
  {
    None = 0,
    SHA1,
    SHA256,
    SHA512,
  };

  class HMAC
  {
  public:
    explicit HMAC(const Blob::Bytes& key, HashType type = HashType::SHA256);
    Error Write(const Blob::Bytes& data);
    std::expected<Blob::Bytes, Error> Sum();
    ~HMAC();

  public:
    static std::expected<Bytes, Error> Sum(const Blob::Bytes& key, const Blob::Bytes& msg, HashType hashType = HashType::SHA256);

  private:
    Error err = Error::None;
    mbedtls_md_context_t* ctx = nullptr;
  };
}
