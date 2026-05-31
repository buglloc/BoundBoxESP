#include "ssh/keys.h"

#include <string>

#include <esp_log.h>
#include <esp_check.h>

#include <blob/base64.h>
#include <defer.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::keys";

  ssh_keytypes_e pkiKeyType(KeyType keyType)
  {
    switch (keyType) {
      case KeyType::RSA:
        return SSH_KEYTYPE_RSA;

  #ifdef HAVE_ECC
      case KeyType::ECDSA:
        return SSH_KEYTYPE_ECDSA;
  #endif

      case KeyType::ED25519:
        return SSH_KEYTYPE_ED25519;

      default:
        return SSH_KEYTYPE_UNKNOWN;
    }
  }

  KeyType sshKeyType(ssh_keytypes_e keyType)
  {
    switch (keyType) {
      case SSH_KEYTYPE_RSA:
        return KeyType::RSA;

  #ifdef HAVE_ECC
      case SSH_KEYTYPE_ECDSA:
      case SSH_KEYTYPE_ECDSA_P256:
      case SSH_KEYTYPE_ECDSA_P384:
      case SSH_KEYTYPE_ECDSA_P521:
        return KeyType::ECDSA;
  #endif

      case SSH_KEYTYPE_ED25519:
        return KeyType::ED25519;

      default:
        return KeyType::None;
    }
  }
}

Error PrivateKey::Generate(KeyType keyType, uint32_t bits)
{
  if (!Empty()) {
    return Error::InvalidState;
  }

  ssh_keytypes_e targetType = pkiKeyType(keyType);
  if (targetType == SSH_KEYTYPE_UNKNOWN) {
    ESP_LOGE(TAG, "generate: unsupported key type: %d", (int)keyType);
    return Error::Unsupported;
  }

  int rc = ssh_pki_generate(targetType, bits, &keyPtr);
  if (rc != SSH_OK) {
    keyPtr = nullptr;
    ESP_LOGE(TAG, "ssh pki generate failed: %d", rc);
    return Error::ShitHappens;
  }

  this->keyType = keyType;
  return Error::None;
}

Error PrivateKey::Load(const std::string& blob, const std::string& passphrase)
{
  if (!Empty()) {
    return Error::InvalidState;
  }

  const char* passPtr = passphrase.empty() ? nullptr : passphrase.c_str();
  int rc = ssh_pki_import_privkey_base64(blob.c_str(), passPtr, NULL, NULL, &keyPtr);
  if (rc != SSH_OK) {
    keyPtr = nullptr;
    ESP_LOGE(TAG, "pki import fail: %d", rc);
    return Error::MalformedKey;
  }

  rc = ssh_key_is_private(keyPtr);
  if (rc != 1) {
    ESP_LOGE(TAG, "tries to load not a priv key into priv key");
    return Error::UnexpectedKey;
  };

  ssh_keytypes_e targetType = ssh_key_type(keyPtr);
  this->keyType = sshKeyType(targetType);
  if (this->keyType == KeyType::None) {
    ESP_LOGE(TAG, "unsupported key type: %s", ssh_key_type_to_char(targetType));
    ssh_key_free(keyPtr);
    keyPtr = nullptr;
    return Error::Unsupported;
  }

  return Error::None;
}

Error PrivateKey::Wrap(ssh_key keyPtr)
{
  if (!Empty()) {
    return Error::InvalidState;
  }

  return Own(keyPtr);
}

Error PrivateKey::Own(ssh_key keyPtr)
{
  ssh_keytypes_e targetType = ssh_key_type(keyPtr);
  this->keyType = sshKeyType(targetType);
  if (this->keyType == KeyType::None) {
    ESP_LOGE(TAG, "unsupported key type: %s", ssh_key_type_to_char(targetType));
    return Error::Unsupported;
  }

  if (this->keyPtr != nullptr) {
    ssh_key_free(this->keyPtr);
    this->keyPtr = nullptr;
  }

  this->keyPtr = keyPtr;
  return Error::None;
}

std::expected<std::string, Error> PrivateKey::Marshal(const std::string& passphrase) const
{
  char* blob = nullptr;
  const char* passPtr = passphrase.empty() ? nullptr : passphrase.c_str();
  int rc = ssh_pki_export_privkey_base64(keyPtr, passPtr, nullptr, nullptr, &blob);
  if (rc != SSH_OK) {
    ESP_LOGE(TAG, "pki export fail: %d", rc);
    return std::unexpected<Error>{Error::Internal};
  }

  std::string out(blob);
  ssh_string_free_char(blob);
  return out;
}

std::expected<std::string, Error> SSH::PublicKeySHA256Fingerprint(const ssh_key key)
{
  unsigned char *hash = nullptr;
  char* pHash = nullptr;
  size_t hlen = 0;
  int rc = ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA256, &hash, &hlen);
  if (rc != SSH_OK) {
    return std::unexpected<Error>{Error::Internal};
  }

  pHash = ssh_get_fingerprint_hash(SSH_PUBLICKEY_HASH_SHA256, hash, hlen);
  if (!pHash) {
    ssh_clean_pubkey_hash(&hash);
    return std::unexpected<Error>{Error::Internal};
  }

  std::string out(pHash);

  ssh_string_free_char(pHash);
  ssh_clean_pubkey_hash(&hash);
  return out;
}

std::expected<Blob::Bytes, Error> SSH::ExportPublicKeyBase64(const ssh_key key)
{
  char* b64Key = nullptr;
  int rc = ssh_pki_export_pubkey_base64(key, &b64Key);
  if (rc != SSH_OK) {
    return std::unexpected<Error>{Error::Internal};
  }

  Blob::Bytes keyBytes{reinterpret_cast<const uint8_t*>(b64Key)};
  ssh_string_free_char(b64Key);
  return keyBytes;
}

ssh_key PrivateKey::Get() const
{
  return keyPtr;
}

ssh_key PrivateKey::Copy() const
{
  return ssh_key_dup(keyPtr);
}

PrivateKey::~PrivateKey()
{
  ssh_key_free(keyPtr);
  keyPtr = nullptr;
}
