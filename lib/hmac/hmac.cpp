#include "hmac.h"
#include <mbedtls/md.h>

namespace HMAC
{
  HMAC::HMAC(const BBU::Bytes& key, Type type)
  {
    const mbedtls_md_info_t *md_info = nullptr;
    int rc;

    ctx = static_cast<mbedtls_md_context_t*>(malloc(sizeof(mbedtls_md_context_t)));
    if (ctx == nullptr) {
      goto error;
    }

    switch (type) {
      case Type::SHA1:
        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
        break;
      case Type::SHA256:
        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
        break;
      case Type::SHA512:
        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
        break;
      default:
        goto error;
    }

    mbedtls_md_init(ctx);
    if (md_info == nullptr) {
      goto error;
    }

    rc = mbedtls_md_setup(ctx, md_info, 1);
    if (rc != 0) {
        goto error;
    }

    rc = mbedtls_md_hmac_starts(ctx, key.c_str(), key.size());
    if (rc != 0) {
        goto error;
    }

    return;

  error:
    err = Error::InitFailed;
    if (ctx != nullptr) {
      mbedtls_md_free(ctx);
      free(ctx);
      ctx = nullptr;
    }
  }

  cpp::result<void, Error> HMAC::Write(const BBU::Bytes& data)
  {
    if (ctx == nullptr) {
      return cpp::fail(Error::NoCtx);
    }

    if (mbedtls_md_hmac_update(ctx, data.c_str(), data.length())) {
      return cpp::fail(Error::ShitHappens);
    }

    return {};
  }

  cpp::result<BBU::Bytes, Error> HMAC::Sum()
  {
    if (ctx == nullptr) {
      return cpp::fail(Error::NoCtx);
    }

    size_t len = static_cast<size_t>(mbedtls_md_get_size(ctx->md_info));
    if (len == 0) {
      return cpp::fail(Error::ShitHappens);
    }

    BBU::Bytes out(len, '\xff');
    if (mbedtls_md_hmac_finish(ctx, &out[0])) {
      return cpp::fail(Error::ShitHappens);
    }

    return out;
  }

  HMAC::~HMAC()
  {
    if (ctx != nullptr) {
      mbedtls_md_free(ctx);
      free(ctx);
      ctx = nullptr;
    }
  }
}
