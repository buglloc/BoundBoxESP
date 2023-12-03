#include "defaults.h"
#include "secrets.h"
#include "ssh_service.h"

#include <defer.h>
#include <ArduinoLog.h>
#include <libssh_esp.h>
#include <libssh/server.h>

#define IMPATIENCE 10

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
} // anonymous namespace

TSshService& TSshService::Instance()
{
  static TSshService instance;
  return instance;
}

bool TSshService::Begin(const TSshConfig& cfg)
{
  Log.infoln("setup SSHD service");
  libssh_begin();

  auto parsedHostKey = XSSH::ParsePrivateKey(secrets.HostKey());
  if (parsedHostKey.has_error()) {
    Log.errorln("unable to parse host key: %d", parsedHostKey.error());
    return false;
  }

  hostKey = std::move(parsedHostKey.value());
  rootLogin = cfg.RootUser;
  cfg.RootKeys.Visit([this](const ssh_key key) -> bool {
    rootKeys.Add(key);
    return true;
  });

  Log.infoln("SSHD setup complete");
  return true;
}

void TSshService::Tick(TSshActionCallback actionCallback)
{
  Log.verboseln("sshd: bind ssh");
  ssh_bind sshBind = ssh_bind_new();
  if (!sshBind) {
    Log.errorln("sshd: unable to allocate ssh bind");
    return;
  }
  REF_DEFER(ssh_bind_free(sshBind));

  int rc = ssh_bind_options_set(sshBind, SSH_BIND_OPTIONS_IMPORT_KEY, ssh_key_dup(hostKey.get()));
  if (rc != SSH_OK) {
    Log.errorln("sshd: bind key failed: %s", ssh_get_error(sshBind));
    return;
  }

  rc = ssh_bind_listen(sshBind);
  if (rc != SSH_OK) {
    Log.errorln("sshd: bind listen failed: %s", ssh_get_error(sshBind));
    return;
  }

  Log.verboseln("sshd: starts new session");
  ssh_session sshSession = ssh_new();
  if (!sshSession) {
    Log.errorln("sshd: unable to allocate ssh session");
    return;
  }
  REF_DEFER(ssh_disconnect(sshSession); ssh_free(sshSession));

  Log.verboseln("sshd: wait for connection...");
  rc = ssh_bind_accept(sshBind, sshSession);
  if (rc != SSH_OK) {
    Log.errorln("sshd: unable to accept connection: %s", ssh_get_error(sshBind));
    return;
  }

  Log.infoln("sshd: new connection");
  Log.verboseln("sshd: starts key exchange...");
  rc = ssh_handle_key_exchange(sshSession);
  if (rc != SSH_OK) {
    Log.errorln("sshd: key exchange failed: %s", ssh_get_error(sshSession));
    return;
  }

  Log.verboseln("sshd: auth client...");
  auto authInfo = authenticate(sshSession);
  if (!authInfo) {
    Log.errorln("sshd: auth failed, abort");
    return;
  }

  Log.verboseln("sshd: wait for a channel session...");
  ssh_message message = nullptr;
  ssh_channel chan = nullptr;
  do {
    message = ssh_message_get(sshSession);
    if (!message) {
      Log.errorln("sshd: no message received: %s", ssh_get_error(sshSession));
      return;
    }
    Log.verboseln("requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

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
    Log.errorln("sshd: client did not ask for a channel session: %s", ssh_get_error(sshSession));
    return;
  }
  REF_DEFER(ssh_channel_close(chan));

  Log.verboseln("sshd: wait for a exec request...");
  while (true) {
    message = ssh_message_get(sshSession);
    if (!message) {
      Log.errorln("sshd: no message received: %s", ssh_get_error(sshSession));
      return;
    }
    Log.verboseln("requested channel %d:%d", ssh_message_type(message), ssh_message_subtype(message));

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
      Log.warningln("failed to execute action: %s", cmd.c_str());
    }

    ssh_message_free(message);
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
      Log.errorln("sshd: no auth message");
      return nullptr;
    }

    Log.verboseln("sshd: [%d] trying %d:%d...", patience, ssh_message_type(message), ssh_message_subtype(message));
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
        out->IsSysop = isSysop;

        auto keyFp = XSSH::KeyFingerprint(auth_key);
        if (keyFp.has_error()) {
          out->KeyFingerprint = "N/A";
        } else {
          out->KeyFingerprint = keyFp.value();
        }

        Log.infoln("user '%s' was authenticated by key '%s'", out->User.c_str(), out->KeyFingerprint.c_str());
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

  Log.warningln("too much auth failures, aborting");
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
        Log.errorln("ignore ivalid key '%s': %d", rawKey.as<String>(), key.error());
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
      Log.infoln("unable to marshal authorized key: %d", authorizedKey.error());
    } else {
      jsonRootKeys.add(authorizedKey.value());
    }

    return true;
  });

  return {};
}
