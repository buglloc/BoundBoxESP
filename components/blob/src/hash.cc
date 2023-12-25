#include "blob/hash.h"

#include <expected>


#include <mbedtls/md.h>


using namespace Blob;

HMAC::HMAC(const Bytes& key, HashType hashType)
{
  const mbedtls_md_info_t* mdInfo = nullptr;
  switch (hashType) {
  case HashType::SHA1:
    mdInfo = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
    break;
  case HashType::SHA256:
    mdInfo = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    break;
  case HashType::SHA512:
    mdInfo = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
    break;
  default:
    err = Error::Unsupported;
    return;
  }

  if (mdInfo == nullptr) {
    err = Error::Unsupported;
    return;
  }

  ctx = static_cast<mbedtls_md_context_t*>(malloc(sizeof(mbedtls_md_context_t)));
  if (ctx == nullptr) {
    err = Error::ShitHappens;
    return;
  }

  mbedtls_md_init(ctx);
  int rc = mbedtls_md_setup(ctx, mdInfo, 1);
  if (rc != 0) {
    mbedtls_md_free(ctx);
    free(ctx);
    err = Error::InitFailed;
    return;
  }

  rc = mbedtls_md_hmac_starts(ctx, key.c_str(), key.size());
  if (rc != 0) {
    mbedtls_md_free(ctx);
    free(ctx);
    err = Error::InitFailed;
    return;
  }
}

Error HMAC::Write(const Bytes& data)
{
  if (err != Error::None) {
    return err;
  }

  if (mbedtls_md_hmac_update(ctx, data.c_str(), data.length())) {
    return Error::ShitHappens;
  }

  return Error::None;
}

std::expected<Bytes, Error> HMAC::Sum()
{
  if (err != Error::None) {
    return std::unexpected<Error>{err};
  }

  size_t hashLen = static_cast<size_t>(mbedtls_md_get_size(mbedtls_md_info_from_ctx(ctx)));
  if (hashLen == 0) {
    return std::unexpected<Error>{Error::ShitHappens};
  }

  Bytes out(hashLen, '\xff');
  int ret = mbedtls_md_hmac_finish(ctx, out.data());
  if (ret != 0) {
    return std::unexpected<Error>{Error::ShitHappens};
  }

  return out;
}

HMAC::~HMAC()
{
  if (ctx == nullptr) {
    return;
  }

  mbedtls_md_free(ctx);
  free(ctx);
  ctx = nullptr;
}

std::expected<Bytes, Error> HMAC::Sum(const Bytes& key, const Bytes& msg, HashType type)
{
  HMAC hmac(key, type);
  Error err = hmac.Write(msg);
  if (err != Error::None) {
    return std::unexpected<Error>(err);
  }

  return hmac.Sum();
}
