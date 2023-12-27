#include <sdkconfig.h>
#include "ssh/server.h"
#include "ssh/common.h"
#include "ssh/keys.h"

#include <freertos/FreeRTOS.h>

#include <esp_check.h>
#include <esp_log.h>

#include <lwip/netdb.h>
#include <lwip/sockets.h>

#include <libssh/server.h>

#include <defer.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::server";

  int acceptUserKey(ssh_message message)
  {
    switch (ssh_message_auth_publickey_state(message)) {
      case SSH_PUBLICKEY_STATE_NONE:
        ssh_message_auth_reply_pk_ok_simple(message);
        return 1;
      case SSH_PUBLICKEY_STATE_VALID:
        ssh_message_auth_reply_success(message, 0);
        return 0;
      default:
        return -1;
    }
  }

  std::string getClientIp(ssh_session session)
  {
    struct sockaddr_storage tmp;
    socklen_t len = 100;

    getpeername(ssh_get_fd(session), (struct sockaddr*)&tmp, &len);
    struct sockaddr_in *sock = (struct sockaddr_in *)&tmp;
    
    std::string out(INET_ADDRSTRLEN, '\xff');
    inet_ntop(AF_INET, &sock->sin_addr, out.data(), INET_ADDRSTRLEN);
    return out;
  }

  std::expected<std::string, int> keyFingerprint(const ssh_key key)
  {
    unsigned char *hash = nullptr;
    char* pHash = nullptr;
    size_t hlen = 0;
    int rc = ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA256, &hash, &hlen);
    if (rc != SSH_OK) {
      return std::unexpected<int>{rc};
    }

    pHash = ssh_get_fingerprint_hash(SSH_PUBLICKEY_HASH_SHA256, hash, hlen);
    std::string out(pHash);

    ssh_string_free_char(pHash);
    ssh_clean_pubkey_hash(&hash);
    return out;
  }
}

Error Server::Initialize(const ServerConfig& cfg)
{
  ESP_LOGI(TAG, "setup libssh");
  libssh_begin();

  ESP_LOGI(TAG, "setup host key");
  if (cfg.HostKey.Empty()) {
    ESP_LOGE(TAG,"trying to inialize sshd server w/o host key: abort");
    return Error::ShitHappens;
  }
  hostKey.Wrap(cfg.HostKey.Copy());

  ESP_LOGI(TAG, "setup auth logic");
  Error err = auth.Initialize(cfg);
  if (err != Error::None) {
    ESP_LOGE(TAG,"unable to initialize auth logic: %d", (int)err);
    return Error::ShitHappens;
  }

  return Error::None;
}

ListenError Server::Listen(const HandlerCallback& handler)
{
  ESP_LOGD(TAG, "bind ssh");
  ssh_bind sshBind = ssh_bind_new();
  if (!sshBind) {
    ESP_LOGE(TAG, "unable to allocate ssh bind");
    return ListenError::Bind;
  }
  REF_DEFER(ssh_bind_free(sshBind));

  int rc = ssh_bind_options_set(sshBind, SSH_BIND_OPTIONS_IMPORT_KEY, hostKey.Copy());
  if (rc != SSH_OK) {
    ESP_LOGE(TAG, "bind host key failed: %s", ssh_get_error(sshBind));
    return ListenError::Internal;
  }

  rc = ssh_bind_listen(sshBind);
  if (rc != SSH_OK) {
    ESP_LOGE(TAG, "listen failed: %s", ssh_get_error(sshBind));
    return ListenError::Listen;
  }

  ESP_LOGD(TAG, "starts new session");
  ssh_session sshSession = ssh_new();
  if (!sshSession) {
    ESP_LOGE(TAG, "unable to allocate ssh session");
    return ListenError::Internal;
  }
  REF_DEFER(ssh_disconnect(sshSession); ssh_free(sshSession));

  ESP_LOGD(TAG, "wait for connection...");
  rc = ssh_bind_accept(sshBind, sshSession);
  if (rc != SSH_OK) {
    ESP_LOGE(TAG,  "unable to accept connection: %s", ssh_get_error(sshBind));
    return ListenError::Accept;
  }

  ESP_LOGI(TAG, "new connection");

  ESP_LOGD(TAG, "starts key exchange...");
  rc = ssh_handle_key_exchange(sshSession);
  if (rc != SSH_OK) {
    ESP_LOGD(TAG, "key exchange failed: %s", ssh_get_error(sshSession));
    return ListenError::Accept;
  }

  ESP_LOGD(TAG, "auth client...");
  auto userInfo = authenticate(sshSession);
  if (!userInfo) {
    ESP_LOGD(TAG, "auth failed, abort");
    return ListenError::Auth;
  }

  ESP_LOGD(TAG, "wait for a channel session...");
  ssh_message message = nullptr;
  ssh_channel chan = nullptr;
  do {
    message = ssh_message_get(sshSession);
    if (!message) {
      ESP_LOGE(TAG, "no message received: %s", ssh_get_error(sshSession));
      return ListenError::Accept;
    }

    ESP_LOGD(TAG, "requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

    if (ssh_message_type(message) != SSH_REQUEST_CHANNEL_OPEN) {
      ssh_message_reply_default(message);
      ssh_message_free(message);
      continue;
    }

    if (ssh_message_subtype(message) != SSH_CHANNEL_SESSION) {
      ssh_message_reply_default(message);
      ssh_message_free(message);
      continue;
    }

    chan = ssh_message_channel_request_open_reply_accept(message);
    ssh_message_free(message);
    break;
  } while(!chan);

  if (!chan) {
    ESP_LOGW(TAG, "client did not ask for a channel session: %s", ssh_get_error(sshSession));
    return ListenError::Accept;
  }
  REF_DEFER(ssh_channel_send_eof(chan); ssh_channel_close(chan));

  ESP_LOGD(TAG, "wait for a exec request...");
  while (true) {
    message = ssh_message_get(sshSession);
    if (!message) {
      ESP_LOGE(TAG, "no message received: %s", ssh_get_error(sshSession));
      return ListenError::Accept;
    }

    ESP_LOGD(TAG, "requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

    if (ssh_message_type(message) != SSH_REQUEST_CHANNEL) {
      ssh_message_reply_default(message);
      ssh_message_free(message);
      continue;
    }

    if (ssh_message_subtype(message) != SSH_CHANNEL_REQUEST_EXEC) {
      ssh_message_reply_default(message);
      ssh_message_free(message);
      continue;
    }

    ssh_message_channel_request_reply_success(message);
    ssh_set_blocking(sshSession, 0);

    Stream stream(chan);
    std::string cmd = ssh_message_channel_request_command(message);

    int status = handler(std::move(userInfo.value()), cmd, stream);
    if (status) {
      ESP_LOGW(TAG,  "failed to execute action [%d]: %s", status, cmd.c_str());
    }

    ssh_message_free(message);
    ssh_channel_request_send_exit_status(chan, status);
    break;
  }

  return ListenError::None;
}

std::expected<UserInfo, ListenError> Server::authenticate(ssh_session session)
{
  #define REPLY_AGAIN(m) { \
    ssh_message_auth_set_methods(m, SSH_AUTH_METHOD_PUBLICKEY); \
    ssh_message_reply_default(m); \
    ssh_message_free(m); \
  }

  ssh_set_auth_methods(session, SSH_AUTH_METHOD_PUBLICKEY);

  ssh_key userKey = nullptr;
  ssh_message message = nullptr;
  for (int patience = 0; patience < CONFIG_SSH_AUTH_RETRIES; ++patience) {
    message = ssh_message_get(session);
    if (!message) {
      ESP_LOGW(TAG, "no more auth");
      return std::unexpected<ListenError>{ListenError::Auth};
    }

    ESP_LOGD(TAG, "[%d] trying %d:%d...", patience, ssh_message_type(message), ssh_message_subtype(message));
    // only pubkey auth support
    if (ssh_message_type(message) != SSH_REQUEST_AUTH) {
      ssh_message_reply_default(message);
      ssh_message_free(message);
      continue;
    }

    if (ssh_message_subtype(message) != SSH_AUTH_METHOD_PUBLICKEY) {
      REPLY_AGAIN(message);
      continue;
    }

    userKey = ssh_message_auth_pubkey(message);
    if (!userKey) {
      ESP_LOGE(TAG, "no ssh key provided while auth");
      REPLY_AGAIN(message);
      continue;
    }

    if (!auth.Authenticate(ssh_message_auth_user(message), userKey)) {
      REPLY_AGAIN(message);
      continue;
    }

    switch (acceptUserKey(message)) {
      case 0: {
        UserInfo userInfo = {
          .Name = ssh_message_auth_user(message),
          .ClientIP = getClientIp(session),
          .Role = auth.Role(ssh_message_auth_user(message))
        };

        auto keyFp = keyFingerprint(userKey);
        if (keyFp) {
          userInfo.KeyFingerprint = keyFp.value();
        } else {
          ESP_LOGW(TAG, "unable to make user key fingerprint: %d", keyFp.error());
          userInfo.KeyFingerprint = "N/A";
        }

        ESP_LOGI(TAG,
          "user '%s' was authenticated by key '%s' from %s",
          userInfo.Name.c_str(), userInfo.KeyFingerprint.c_str(), userInfo.ClientIP.c_str()
        );
        ssh_message_free(message);
        return userInfo;
      }
      case 1: {
        ESP_LOGD(TAG, "pubkey accepted");
        ssh_message_free(message);
        continue;
      }
    }

    REPLY_AGAIN(message);
  }

  ESP_LOGW(TAG, "too much auth failures, aborting");
  return std::unexpected<ListenError>{ListenError::Auth};
}
