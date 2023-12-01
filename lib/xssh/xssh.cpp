#include "xssh.h"
#include "libssh_esp.h"

namespace XSsh
{
  namespace
  {
    ssh_keytypes_e sshKeyType(KeyType keyType)
    {
      switch (keyType) {
      case KeyType::Rsa:
        return SSH_KEYTYPE_RSA;
    #ifdef HAVE_ECC
      case KeyType::Ecdsa:
        return SSH_KEYTYPE_ECDSA;
    #endif
      case KeyType::Ed25519:
        return SSH_KEYTYPE_ED25519;

      default:
        return SSH_KEYTYPE_UNKNOWN;
      }
    }
  } // anonymous namespace

  void Begin()
  {
    libssh_begin();
  }

  cpp::result<Key, GenError> GenKey(KeyType keyType, int bits)
  {
    ssh_keytypes_e pkiKeyType = sshKeyType(keyType);
    if (pkiKeyType == SSH_KEYTYPE_UNKNOWN) {
      return cpp::fail(GenError::UnsupportedType);
    }

    ssh_key pKey = nullptr;
    int rc = ssh_pki_generate(pkiKeyType, bits, &pKey);
    if (rc != SSH_OK) {
      return cpp::fail(GenError::ShitHappens);
    }

    return cpp::result<Key, GenError>{cpp::in_place, pKey};
  }

  cpp::result<Key, ParseError> ParsePublicKey(const String& in)
  {
    int typeEnd = in.indexOf(' ');
    if (typeEnd == -1) {
      return cpp::fail(ParseError::Malformed);
    }
    String rawKeyType = in.substring(0, typeEnd);

    int bodyEnd = in.indexOf(' ', typeEnd + 1);
    if (bodyEnd == -1) {
      bodyEnd = in.length();
    }
    String rawKeyBody = in.substring(typeEnd + 1, bodyEnd);

    ssh_keytypes_e keyType = ssh_key_type_from_name(rawKeyType.c_str());
    if (keyType == SSH_KEYTYPE_UNKNOWN) {
      return cpp::fail(ParseError::UnsupportedType);
    }

    ssh_key pKey;
    int rc = ssh_pki_import_pubkey_base64(rawKeyBody.c_str(), keyType, &pKey);
    if (rc != SSH_OK) {
      return cpp::fail(ParseError::UnsupportedType);
    }

    return cpp::result<Key, ParseError>{cpp::in_place, pKey};
  }

  cpp::result<Key, ParseError> ParsePrivateKey(const String& in, const String& passphrase)
  {
    const char* pPassphrase = passphrase.isEmpty() ? nullptr : passphrase.c_str();
    ssh_key pKey;
    int rc = ssh_pki_import_privkey_base64(in.c_str(), pPassphrase, NULL, NULL, &pKey);
    if (rc != SSH_OK) {
      return cpp::fail(ParseError::Malformed);
    }

    return cpp::result<Key, ParseError>{cpp::in_place, pKey};
  }

  cpp::result<String, Error> KeyFingerprint(const Key& key)
  {
    return KeyFingerprint(key.get());
  }

  cpp::result<String, Error> KeyFingerprint(const ssh_key key)
  {
    unsigned char *hash = nullptr;
    char* pHash = nullptr;
    size_t hlen = 0;
    int rc = ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA256, &hash, &hlen);
    if (rc != SSH_OK) {
      return cpp::fail(Error::ShitHappens);
    }

    pHash = ssh_get_fingerprint_hash(SSH_PUBLICKEY_HASH_SHA256, hash, hlen);
    String out = pHash;

    ssh_string_free_char(pHash);
    ssh_clean_pubkey_hash(&hash);
    return std::move(out);
  }

  cpp::result<String, Error> MarshalPrivateKey(const Key& key, const String& passphrase)
  {
    return MarshalPrivateKey(key.get(), passphrase);
  }

  cpp::result<String, Error> MarshalPrivateKey(const ssh_key key, const String& passphrase)
  {
    char* blob;
    const char* pPassphrase = passphrase.isEmpty() ? nullptr : passphrase.c_str();
    int rc = ssh_pki_export_privkey_base64(key, pPassphrase, nullptr, nullptr, &blob);
    if (rc != SSH_OK) {
      return cpp::fail(Error::ShitHappens);
    }

    String out = String(blob);
    ssh_string_from_char(blob);
    return out;
  }

  cpp::result<String, Error> MarshalAuthorizedKey(const Key& key)
  {
    return MarshalAuthorizedKey(key.get());
  }

  cpp::result<String, Error> MarshalAuthorizedKey(const ssh_key key)
  {
    char key_buf[4096];
    char *b64_key;
    int rc;

    if (key == nullptr) {
        return cpp::fail(Error::ShitHappens);
    }

    rc = ssh_pki_export_pubkey_base64(key, &b64_key);
    if (rc != SSH_OK) {
      return cpp::fail(Error::ShitHappens);
    }

    rc = snprintf(key_buf, sizeof(key_buf),
                  "%s %s",
                  ssh_key_type_to_char(ssh_key_type(key)),
                  b64_key);
    free(b64_key);
    if (rc < 0) {
        return cpp::fail(Error::ShitHappens);
    }

    return key_buf;
  }
}
