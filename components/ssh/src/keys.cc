#include "ssh/keys.h"

#include <string>

#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/asn.h>
#ifdef HAVE_ECC
  #include <wolfssl/wolfcrypt/ecc.h>
#endif
#ifdef HAVE_ED25519
  #include <wolfssl/wolfcrypt/ed25519.h>
#endif

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

  std::expected<PrivateKey, Error> KeyGen(KeyType keyType, uint32_t bits)
  {
    std::expected<Blob::Bytes, Error> newKey;
    switch (keyType) {
    case KeyType::RSA:
      newKey = makeRsaKey(bits);
      break;
    case KeyType::ECDSA:
      newKey = makeEcdsaKey(bits);
      break;
    case KeyType::ED25519:
      newKey = makeEd25519Key();
      break;
    default:
      ESP_LOGE(TAG, "requested unsupported key type %d generation", (int)keyType);
      return std::unexpected<Error>{Error::Unsupported};
    }

    if (!newKey) {
      return std::unexpected<Error>{newKey.error()};
    }

    PrivateKey out;
    Error err = out.ImportDer(keyType, newKey.value());
    if (err != Error::None) {
      return std::unexpected<Error>{err};
    }

    return out;
  }

  Error PrivateKey::ImportPem(const std::string& pem)
  {
    DerBuffer* der = nullptr;
    int wcType;
    int actualSize = wc_PemToDer(reinterpret_cast<const uint8_t *>(pem.data()), pem.size(), PRIVATEKEY_TYPE, &der, nullptr, nullptr, &wcType);
    if (actualSize < 0) {
      ESP_LOGE(TAG, "wc_KeyPemToDer returns gen zero der");
      return Error::Internal;
    }

    KeyType keyType = KeyType::None;
    switch (wcType) {
    case 645:
      // RSAk
      keyType = KeyType::RSA;
      break;
    case 518:
      // ECDSAk
      keyType = KeyType::ECDSA;
      break;
    case 256:
      // ED25519k
      keyType = KeyType::ED25519;
      break;
    default:
      ESP_LOGE(TAG, "unsupported wolf key type %d to PEM import", wcType);
      return Error::Unsupported;
    }

    Blob::Bytes key(der->buffer, der->length);
    wc_FreeDer(&der);
    return ImportDer(keyType, key);
  }

  std::expected<std::string, Error> PrivateKey::ExportPem() const
  {
    int wcType = 0;
    switch (keyType) {
    case KeyType::RSA:
      wcType = RSA_TYPE;
      break;
    case KeyType::ECDSA:
      wcType = ECC_TYPE;
      break;
    default:
      ESP_LOGE(TAG, "requested unsupported key type %d to PEM export", (int)keyType);
      return std::unexpected<Error>{Error::Unsupported};
    }

    int pemSize = wc_DerToPemEx(keyDer.data(), keyDer.size(), nullptr, 0, nullptr, wcType);
    if (pemSize < 0) {
      ESP_LOGE(TAG, "wc_DerToPemEx returns zero size");
      return std::unexpected<Error>{Error::Internal};
    }

    std::string out(pemSize, '\xff');
    int actualPemSize = wc_DerToPemEx(keyDer.data(), keyDer.size(), reinterpret_cast<uint8_t *>(out.data()), out.size(), nullptr, wcType);
    if (actualPemSize < 0) {
      ESP_LOGE(TAG, "wc_DerToPemEx returns gen zero pem");
      return std::unexpected<Error>{Error::Internal};
    }

    out.resize(actualPemSize);
    return out;
  }

  Error PrivateKey::ImportDer(KeyType keyType, Blob::Bytes& blob)
  {
    switch (keyType) {
    case KeyType::RSA:
    case KeyType::ECDSA:
    case KeyType::ED25519:
      break;
    default:
      ESP_LOGE(TAG, "requested unsupported key type %d to import", (int)keyType);
      return Error::Unsupported;
    }

    this->keyType = keyType;
    this->keyDer = blob;
    return Error::None;
  }

  std::expected<Blob::Bytes, Error> PrivateKey::ExportDer() const
  {
    return keyDer;
  }
}
