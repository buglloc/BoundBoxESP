#include "ssh/keys.h"

#include <string>

#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/rsa.h>
#ifdef HAVE_ECC
  #include <wolfssl/wolfcrypt/ecc.h>
#endif
#ifdef HAVE_ED25519
  #include <wolfssl/wolfcrypt/ed25519.h>
#endif
#include <wolfssl/wolfcrypt/asn_public.h>

#include <esp_log.h>
#include <esp_check.h>

#include <blob/base64.h>
#include <defer.h>

namespace
{
  static const char* TAG = "ssh::keys";

  std::expected<Blob::Bytes, SSH::Error> makeRsaKey(uint32_t bits)
  {
    WC_RNG rng;
    int ret = wc_InitRng(&rng);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to generate wolf rng: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_FreeRng(&rng));

    RsaKey key;
    ret = wc_InitRsaKey(&key, nullptr);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to init wolf RSA key: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_FreeRsaKey(&key));

    ret = wc_MakeRsaKey(&key, bits, RSAKEY_DEFAULT_E, &rng);
    if (ret != 0) {
      ESP_LOGE(TAG, "RSA generation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    uint8_t derBuf[1536];
    int derSize = 1536;
    derSize = wc_RsaKeyToDer(&key, derBuf, derSize);
    if (derSize < 0) {
      ESP_LOGE(TAG, "RSA key to DER convertation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    return Blob::Bytes(derBuf, derSize);
  }

  std::expected<Blob::Bytes, SSH::Error> makeEcdsaKey(uint32_t bits)
  {
  #if defined(HAVE_ECC) && defined(HAVE_ECC_KEY_EXPORT)

    WC_RNG rng;
    int ret = wc_InitRng(&rng);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to generate wolf rng: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_FreeRng(&rng));

    ecc_key key;
    ret = wc_ecc_init(&key);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to init wolf ECDSA key: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_ecc_free(&key));

    ret = wc_ecc_make_key(&rng, bits/8, &key);
    if (ret != 0) {
      ESP_LOGE(TAG, "ECDSA generation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    uint8_t derBuf[512];
    int derSize = 512;
    derSize = wc_EccKeyToDer(&key, derBuf, derSize);
    if (derSize < 0) {
      ESP_LOGE(TAG, "ECDSA key to DER convertation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    return Blob::Bytes(derBuf, derSize);
  #else

    return std::unexpected<SSH::Error>{SSH::Error::Internal};
  #endif
  }

  std::expected<Blob::Bytes, SSH::Error> makeEd25519Key()
  {
  #if defined(HAVE_ED25519) && defined(HAVE_ED25519_KEY_EXPORT)

    WC_RNG rng;
    int ret = wc_InitRng(&rng);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to generate wolf rng: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_FreeRng(&rng));

    ed25519_key key;
    ret = wc_ed25519_init(&key);
    if (ret != 0) {
      ESP_LOGE(TAG, "unable to init wolf ED25519 key: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }
    REF_DEFER(wc_ed25519_free(&key));

    ret = wc_ed25519_make_key(&rng, ED25519_KEY_SIZE, &key);
    if (ret != 0) {
      ESP_LOGE(TAG, "ED25519 generation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    uint8_t derBuf[512];
    int derSize = 512;
    derSize = wc_Ed25519KeyToDer(&key, derBuf, derSize);
    if (derSize < 0) {
      ESP_LOGE(TAG, "ED25519 key to DER convertation failed: %d", ret);
      return std::unexpected<SSH::Error>{SSH::Error::Internal};
    }

    return Blob::Bytes(derBuf, derSize);
  #else

    return std::unexpected<SSH::Error>{SSH::Error::Internal};
  #endif
  }
}

namespace SSH
{
  std::expected<std::string, Error> KeyFingerprint(const Blob::Bytes& pubKey)
  {
    wc_Sha256 sha;
    if (wc_InitSha256(&sha) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    if (wc_Sha256Update(&sha, pubKey.c_str(), pubKey.size()) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    uint8_t digest[WC_SHA256_DIGEST_SIZE];
    if (wc_Sha256Final(&sha, digest) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    std::string out("SHA256:");
    out += Blob::Base64Encode({digest, sizeof(digest)});

    return out;
  }

  std::expected<Blob::Bytes, Error> KeyGen(KeyType keyType, uint32_t bits)
  {
    switch (keyType)
    {
    case KeyType::RSA:
      return makeRsaKey(bits);
    case KeyType::ECDSA:
      return makeEcdsaKey(bits);
    case KeyType::ED25519:
      return makeEd25519Key();
    default:
      ESP_LOGE(TAG, "requested unsupported key type %d generation", (int)keyType);
      return std::unexpected<Error>{Error::Unsupported};
    }
  }
}
