#include "ssh/auth_provider.h"
#include "ssh/server.h"
#include "ssh/common.h"

#include <algorithm>

#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/coding.h>

#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::auth";

  bool isAllowedType(const std::string_view keyType)
  {
    static const std::vector<std::string> allowedTypes = {
      {"ssh-rsa"},
      {"ssh-ed25519"},
      {"ecdsa-sha2-nistp256"},
      {"ecdsa-sha2-nistp384"},
      {"ecdsa-sha2-nistp521"},
    };

    return std::find(allowedTypes.cbegin(), allowedTypes.cend(), keyType) != allowedTypes.cend();
  }

  std::expected<std::string, Error> AuhotizedKeyFingerprint(const std::string_view in)
  {
    size_t typePos = in.find(' ');
    if (typePos == std::string::npos) {
      return std::unexpected<Error>{Error::MalformedKey};
    }

    std::string_view keyType = in.substr(0, typePos);
    if (!isAllowedType(keyType)) {
      return std::unexpected<Error>{Error::Unsupported};
    }

    typePos++;
    size_t keyPos = in.find(' ', typePos);
    if (keyPos == std::string::npos) {
      keyPos = in.length();
    }

    std::string_view keyBae64 = in.substr(typePos, keyPos);

    Bytes keyMaterial((keyBae64.size() * 3 + 3) / 4, '\xff');
    size_t keyMaterialLen;
    int ret = Base64_Decode(
      reinterpret_cast<const byte *>(keyBae64.cbegin()),
      keyBae64.size(),
      keyMaterial.data(),
      &keyMaterialLen
    );
    if (ret!= 0) {
      return std::unexpected<Error>{Error::MalformedKey};
    }

    keyMaterial.resize(keyMaterialLen);
    return KeyFingerprint(keyMaterial);
  }
}

std::expected<void, Error> AuthProvider::Initialize(const ServerConfig& cfg)
{
  rootUser = cfg.RootUser;
  rootFingerprints.reserve(cfg.RootKeys.size());
  for (const auto& key : cfg.RootKeys) {
    std::expected<std::string, Error> keyFp = AuhotizedKeyFingerprint(key);
    if (!keyFp) {
      ESP_LOGW(TAG, "skip invalid key (%d): %s", (int)keyFp.error(), key.c_str());
      continue;
    }

    rootFingerprints.push_back(std::move(keyFp.value()));
  }

  return {};
}

bool AuthProvider::Authenticate(const std::string& user, const Bytes& key) const
{
  if (user != rootUser) {
    return key.size() > 0;
  }

  std::expected<std::string, Error> fpRes = KeyFingerprint(key);
  if (!fpRes) {
    ESP_LOGW(TAG, "unable to create user key fingeprint: %d", (int)fpRes.error());
    return false;
  }

  std::string targetFp = std::move(fpRes.value());
  bool containsFp = std::find(rootFingerprints.cbegin(), rootFingerprints.cend(), targetFp) != rootFingerprints.cend();
  return containsFp;
}

UserRole AuthProvider::Role(const std::string& user) const
{
  return user == rootUser ? UserRole::SysOp : UserRole::User;
}
