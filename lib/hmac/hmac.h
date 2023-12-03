#ifndef PBKDF_PBKDF_H
#define PBKDF_PBKDF_H

#include <bytes.h>
#include <Arduino.h>
#include <result.h>

// fwd
struct mbedtls_md_context_t;

namespace HMAC
{
  enum class Error: uint8_t
  {
    None,
    InitFailed,
    NoCtx,
    ShitHappens,
  };

  enum class Type: uint8_t
  {
    None,
    SHA1,
    SHA256,
    SHA512,
  };

  class HMAC
  {
  public:
    explicit HMAC(const BBU::Bytes& key, Type type = Type::SHA256);
    cpp::result<void, Error> Write(const BBU::Bytes& data);
    cpp::result<BBU::Bytes, Error> Sum();

    ~HMAC();
  private:
    Error err = Error::None;
    mbedtls_md_context_t* ctx = nullptr;
  };
}

#endif
