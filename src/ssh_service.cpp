#include "defaults.h"
#include "secrets.h"
#include "ssh_service.h"

#include <defer.h>
#include <ArduinoLog.h>
#include <libssh_esp.h>
#include <libssh/server.h>

#define IMPATIENCE 10
#define LOG_PREFIX "sshd: "

namespace
{
  static TSecrets& secrets = TSecrets::Instance();

  int acceptUserKey(ssh_message message) {
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

  IPAddress getClientIp(ssh_session session)
  {
    struct sockaddr_storage tmp;
    struct sockaddr_in *sock;
    size_t len = 100;

    getpeername(ssh_get_fd(session), (struct sockaddr*)&tmp, &len);
    struct sockaddr_in *s = (struct sockaddr_in *)&tmp;
    return IPAddress((uint32_t)(s->sin_addr.s_addr));
  }

} // anonymous namespace

TSshService& TSshService::Instance()
{
  static TSshService instance;
  return instance;
}

bool TSshService::Begin(const TSshConfig& cfg)
{
  Log.infoln(LOG_PREFIX "starts");
  libssh_begin();

  auto parsedHostKey = XSSH::ParsePrivateKey(secrets.HostKey());
  if (parsedHostKey.has_error()) {
    Log.errorln(LOG_PREFIX "unable to parse host key: %d", parsedHostKey.error());
    return false;
  }

  hostKey = std::move(parsedHostKey.value());
  rootLogin = cfg.RootUser;
  cfg.RootKeys.Visit([this](const ssh_key key) -> bool {
    rootKeys.Add(key);
    return true;
  });

  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

void TSshService::AcceptConnection(TSshActionCallback actionCallback)
{
  Log.verboseln(LOG_PREFIX "bind ssh");
  ssh_bind sshBind = ssh_bind_new();
  if (!sshBind) {
    Log.errorln(LOG_PREFIX "unable to allocate ssh bind");
    return;
  }
  REF_DEFER(ssh_bind_free(sshBind));

  int rc = ssh_bind_options_set(sshBind, SSH_BIND_OPTIONS_IMPORT_KEY, ssh_key_dup(hostKey.get()));
  if (rc != SSH_OK) {
    Log.errorln(LOG_PREFIX "bind key failed: %s", ssh_get_error(sshBind));
    return;
  }

  rc = ssh_bind_listen(sshBind);
  if (rc != SSH_OK) {
    Log.errorln(LOG_PREFIX "bind listen failed: %s", ssh_get_error(sshBind));
    return;
  }

  Log.verboseln(LOG_PREFIX "starts new session");
  ssh_session sshSession = ssh_new();
  if (!sshSession) {
    Log.errorln(LOG_PREFIX "unable to allocate ssh session");
    return;
  }
  REF_DEFER(ssh_disconnect(sshSession); ssh_free(sshSession));

  Log.verboseln(LOG_PREFIX "wait for connection...");
  rc = ssh_bind_accept(sshBind, sshSession);
  if (rc != SSH_OK) {
    Log.errorln(LOG_PREFIX "unable to accept connection: %s", ssh_get_error(sshBind));
    return;
  }

  Log.infoln(LOG_PREFIX "new connection");
  Log.verboseln(LOG_PREFIX "starts key exchange...");
  rc = ssh_handle_key_exchange(sshSession);
  if (rc != SSH_OK) {
    Log.errorln(LOG_PREFIX "key exchange failed: %s", ssh_get_error(sshSession));
    return;
  }

  Log.verboseln(LOG_PREFIX "auth client...");
  auto authInfo = authenticate(sshSession);
  if (!authInfo) {
    Log.errorln(LOG_PREFIX "auth failed, abort");
    return;
  }

  Log.verboseln(LOG_PREFIX "wait for a channel session...");
  ssh_message message = nullptr;
  ssh_channel chan = nullptr;
  do {
    message = ssh_message_get(sshSession);
    if (!message) {
      Log.errorln(LOG_PREFIX "no message received: %s", ssh_get_error(sshSession));
      return;
    }
    Log.verboseln(LOG_PREFIX "requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

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
    Log.errorln(LOG_PREFIX "client did not ask for a channel session: %s", ssh_get_error(sshSession));
    return;
  }
  REF_DEFER(ssh_channel_send_eof(chan); ssh_channel_close(chan));

  Log.verboseln(LOG_PREFIX "wait for a exec request...");
  while (true) {
    message = ssh_message_get(sshSession);
    if (!message) {
      Log.errorln(LOG_PREFIX "no message received: %s", ssh_get_error(sshSession));
      return;
    }
    Log.verboseln(LOG_PREFIX "requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

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

    TSshReader readStream(chan);
    TSshWriter writeStream(chan);
    String cmd = ssh_message_channel_request_command(message);
    cmd.trim();

    bool ok = actionCallback(authInfo, cmd, readStream, writeStream);
    if (!ok) {
      Log.warningln(LOG_PREFIX "failed to execute action: %s", cmd.c_str());
    }

    ssh_message_free(message);
    ssh_channel_request_send_exit_status(chan, ok ? 0 : 1);
    break;
  }
}

TSshAuthInfoHolder TSshService::authenticate(ssh_session session)
{
  #define REPLY_AGAIN(m) { \
    ssh_message_auth_set_methods(m, SSH_AUTH_METHOD_PUBLICKEY); \
    ssh_message_reply_default(m); \
    ssh_message_free(m); \
  }

  ssh_set_auth_methods(session, SSH_AUTH_METHOD_PUBLICKEY);

  bool isSysop = false;
  ssh_key auth_key = nullptr;
  ssh_message message = nullptr;
  for (int patience = 0; patience < IMPATIENCE; ++patience) {
    message = ssh_message_get(session);
    if (!message) {
      Log.errorln(LOG_PREFIX "no auth message");
      return nullptr;
    }

    Log.verboseln(LOG_PREFIX "[%d] trying %d:%d...", patience, ssh_message_type(message), ssh_message_subtype(message));
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

    auth_key = ssh_message_auth_pubkey(message);
    if (!auth_key) {
      Log.errorln("no ssh key provided while auth");
      REPLY_AGAIN(message);
      continue;
    }

    if (rootLogin.equals(ssh_message_auth_user(message))) {
      if (!rootKeys.Contains(auth_key)) {
        REPLY_AGAIN(message);
        continue;
      }

      isSysop = true;
    }

    switch (acceptUserKey(message)) {
      case 0: {
        TSshAuthInfoHolder out(new TSshAuthInfo());
        out->User = ssh_message_auth_user(message);
        out->ClientIP = getClientIp(session);
        out->IsSysop = isSysop;

        auto keyFp = XSSH::KeyFingerprint(auth_key);
        if (keyFp.has_error()) {
          out->KeyFingerprint = "N/A";
        } else {
          out->KeyFingerprint = keyFp.value();
        }

        Log.infoln(
          "user '%s' was authenticated by key '%s' from %p",
          out->User.c_str(), out->KeyFingerprint.c_str(), out->ClientIP
        );
        ssh_message_free(message);
        return out;
      }
      case 1: {
        Log.verboseln("pubkey accepted");
        ssh_message_free(message);
        continue;
      }
    }

    REPLY_AGAIN(message);
  }

  Log.warningln(LOG_PREFIX "too much auth failures, aborting");
  return nullptr;
}

size_t TSshAuthInfo::printTo(Print& p) const
{
  return p.printf("%s[%s]", (IsSysop ? "admin" : "user"), KeyFingerprint.c_str());
}

cpp::result<std::unique_ptr<TSshConfig>, TSshConfig::MarshalErr> TSshConfig::FromJson(const JsonObjectConst& obj) noexcept
{
  std::unique_ptr<TSshConfig> cfg(new TSshConfig());
  cfg->RootUser = obj["root_user"] | DEFAULT_SSH_ROOT_USER;
  if (!obj.containsKey("root_keys")) {
    auto key = XSSH::ParsePublicKey(DEFAULT_SSH_ROOT_KEY);
    if (!key.has_error()) {
      cfg->RootKeys.Add(key.value());
    }
  } else {
    JsonArrayConst keys = obj["root_keys"].as<JsonArrayConst>();
    for(JsonVariantConst rawKey : keys) {
      auto key = XSSH::ParsePublicKey(rawKey.as<String>());
      if (key.has_error()) {
        Log.errorln(LOG_PREFIX "ignore ivalid key '%s': %d", rawKey.as<String>(), key.error());
        continue;
      }

      cfg->RootKeys.Add(key.value());
    }
  }

  return cfg;
}

cpp::result<void, TSshConfig::MarshalErr> TSshConfig::ToJson(JsonObject& out) const noexcept
{
  out["root_user"] = RootUser;
  JsonArray jsonRootKeys = out.createNestedArray("root_keys");
  RootKeys.Visit([&jsonRootKeys](ssh_key key) -> bool {
    auto authorizedKey = XSSH::MarshalAuthorizedKey(key);
    if (authorizedKey.has_error()) {
      Log.infoln(LOG_PREFIX "unable to marshal authorized key: %d", authorizedKey.error());
    } else {
      jsonRootKeys.add(authorizedKey.value());
    }

    return true;
  });

  return {};
}
