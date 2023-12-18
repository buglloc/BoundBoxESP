#include "bytes/hash.h"

#include <expected>

#include "wolfssl_init.h"
#include "types.h"


namespace Blob
{
  std::expected<Bytes, Error> HMACSum(const Bytes& key, const Bytes& msg, HashType type)
  {
    HMAC hmac(key, type);
    Error err = hmac.Write(msg);
    if (err != Error::None) {
      return err;
    }

    return hmac.Sum();
  }

  std::expected<Bytes, Error> HKDF(const Bytes& key, const Bytes& salt, const Bytes& info, size_t outLen, HashType hashType = HashType::SHA256)
  {
    int wcType;
    switch (hashType)
    {
    case HashType::SHA1:
      wcType = WC_SHA;
      break;
    case HashType::SHA256:
      wcType = WC_SHA256;
      break;
    case HashType::SHA512:
      wcType = WC_SHA512;
      break;

    default:
      return std::unexpected<Error>{Error::Unsupported};
    }

    Bytes out(outLen, '\xff');
    int ret = wc_HKDF(wcType, key.c_str(), key.size(), salt.c_str(), salt.size(), info.c_str(), info.size(), out.data(), outLen);
    if (ret != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    return out;
  }

  HMAC::HMAC(const Bytes& key, HashType hashType)
  {
    int wcType;
    switch (hashType)
    {
    case HashType::SHA1:
      wcType = WC_SHA;
      break;
    case HashType::SHA256:
      wcType = WC_SHA256;
      break;
    case HashType::SHA512:
      wcType = WC_SHA512;
      break;

    default:
      err = Error::Unsupported;
      return;
    }

    int ret = wc_HmacInit(&ctx, nullptr, INVALID_DEVID);
    if (ret != 0) {
      err = Error::InitFailed;
      return;
    }

    ret = wc_HmacSetKey(&ctx, wcType, key.c_str(), key.size());
    if (ret != 0) {
      err = Error::InvalidKey;
      wc_HmacFree(&ctx);
      return;
    }
  }

  Error HMAC::Write(const Bytes& data)
  {
    if (err != Error::None) {
      return err;
    }

    int ret = wc_HmacUpdate(&ctx, data.c_str(), data.size());
    if (ret != 0) {
      return Error::ShitHappens;
    }

    return Error::None;
  }

  std::expected<Bytes, Error> HMAC::Sum()
  {
    if (err != Error::None) {
      return std::unexpected<Error>{err};
    }

    size_t hashLen = wc_HmacSizeByType(ctx.macType);
    if (hashLen <= 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    Bytes out(hashLen, '\xff');
    int ret = wc_HmacFinal(&ctx, out.data());
    if (ret != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    return out;
  }

  HMAC::~HMAC()
  {
    if (err != Error::None) {
      return;
    }

    wc_HmacFree(&ctx);
  }
}
