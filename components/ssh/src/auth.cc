#include "auth.h"

#include <esp_log.h>

#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/coding.h>

#include "common.h"


using namespace SSH;

namespace
{
  static const char* TAG = "ssh_auth";

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

  cpp::result<std::string, Error> AuhotizedKeyFingerprint(const std::string_view in)
  {
    size_t typePos = in.find(' ');
    if (typePos == std::string::npos) {
      return cpp::fail(Error::MalformedKey);
    }

    std::string_view keyType = in.substr(0, typePos);
    if (!isAllowedType(keyType)) {
      return cpp::fail(Error::Unsupported);
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
      &keyMaterialLen,
    );
    if (ret!= 0) {
      return cpp::fail(Error::MalformedKey);
    }

    keyMaterial.resize(keyMaterialLen);
    return KeyFingerprint(keyMaterial);
  }
}

cpp::result<void, Error> Auth::Initialize(const ServerConfig& cfg)
{
  rootUser = cfg.RootUser;
  rootFingerprints.reserve(cfg.RootKeys.size());
  for (const auto& key : cfg.RootKeys) {
    auto keyFp = AuhotizedKeyFingerprint(key);
    if (keyFp.has_error()) {
      ESP_LOGW(TAG, "skip invalid key (%d): %s", keyFp.error(), key.c_str());
      continue;
    }
    
    rootFingerprints.push_back(std::move(keyFp.value()));
  }

  return {};
}

bool Auth::Authenticate(const std::string& user, const Bytes& key, AuthInfo& out)
{
  auto fpRes = KeyFingerprint(key);
  if (fpRes.has_error()) {
    ESP_LOGW(TAG, "unable to create user key fingeprint: %d", fpRes.error());
    return false;
  }

  if (user != rootUser) {
    out.IsSysop = false;
    out.User = user;
    out.KeyFingerprint = std::move(fpRes.value());
    return true;
  }
  
  std::string targetFp = std::move(fpRes.value());
  bool containsFp = std::find(rootFingerprints.cbegin(), rootFingerprints.cend(), targetFp) != rootFingerprints.cend();
  if (containsFp) {
    out.IsSysop = true;
    out.User = user;
    out.KeyFingerprint = std::move(targetFp);
    return true;
  }

  return false;
}
