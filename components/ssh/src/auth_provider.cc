#include "ssh/auth_provider.h"
#include "ssh/server.h"
#include "ssh/keys.h"
#include "ssh/common.h"

#include <algorithm>


#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::auth";

  std::expected<ssh_key, Error> ParseAuthorizedKey(const std::string& in)
  {
    size_t typePos = in.find(' ');
    if (typePos == std::string::npos) {
      ESP_LOGE(TAG, "unable to parse authorized key: no type pos");
      return std::unexpected<Error>{Error::MalformedKey};
    }

    std::string keyTypeName = in.substr(0, typePos);
    ssh_keytypes_e keyType = ssh_key_type_from_name(keyTypeName.c_str());
    if (keyType == SSH_KEYTYPE_UNKNOWN) {
      ESP_LOGE(TAG, "unable to parse authorized key: unsupported key type %s", keyTypeName.c_str());
      return std::unexpected<Error>{Error::Unsupported};
    }

    typePos++;
    size_t keyPos = in.find(' ', typePos);
    if (keyPos == std::string::npos) {
      keyPos = in.length();
    }

    std::string rawKeyBody = in.substr(typePos, keyPos - typePos);
    ssh_key keyPtr;
    int rc = ssh_pki_import_pubkey_base64(rawKeyBody.c_str(), keyType, &keyPtr);
    if (rc != SSH_OK) {
      ESP_LOGE(TAG, "pki import failed for key type: %s", keyTypeName.c_str());
      return std::unexpected<Error>{Error::Unsupported};
    }

    return keyPtr;
  };
}

Error AuthProvider::Initialize(const ServerConfig& cfg)
{
  rootUser = cfg.RootUser;
  for (const auto& key : cfg.RootKeys) {
    if (key.empty()) {
      continue;
    }

    std::expected<ssh_key, Error> parsedKey = ParseAuthorizedKey(key);
    if (!parsedKey) {
      ESP_LOGW(TAG, "skip invalid key (%d): %s", (int)parsedKey.error(), key.c_str());
      continue;
    }

    ESP_LOGI(TAG, "loaded root user '%s' key: %s", rootUser.c_str(), key.c_str());
    rootKeyring.Own(std::move(parsedKey.value()));
  }

  return Error::None;
}

bool AuthProvider::Authenticate(const std::string_view user, const ssh_key key) const
{
  if (user != rootUser) {
    return true;
  }

  if (rootUser.empty()) {
    return false;
  }

  return rootKeyring.Contains(key);
}

UserRole AuthProvider::Role(const std::string_view user) const
{
  return user == rootUser && !rootUser.empty() ? UserRole::SysOp : UserRole::User;
}
