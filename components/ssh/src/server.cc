#include <sdkconfig.h>
#include "wolfssh_init.h"
#include "ssh/server.h"
#include "ssh/common.h"
#include "ssh/keys.h"

#include <freertos/FreeRTOS.h>

#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssh/ssh.h>
#include <wolfssh/log.h>

#include <lwip/netdb.h>
#include <lwip/sockets.h>

#include <defer.h>

#include <esp_check.h>
#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::server";

  struct AuthContext
  {
    const AuthProvider& Provider;
    UserInfo& Out;
  };

  enum class SelectResult: uint8_t {
    Fail,
    Timeout,
    RecvReady,
    ErrorReady,
  };

  inline SelectResult tcpSelect(int socketfd, int deadline)
  {
      fd_set recvfds, errfds;
      int nfds = (int)socketfd + 1;
      struct timeval timeout = { (deadline > 0) ? deadline : 0, 0 };

      FD_ZERO(&recvfds);
      FD_SET(socketfd, &recvfds);
      FD_ZERO(&errfds);
      FD_SET(socketfd, &errfds);

      int ret = select(nfds, &recvfds, nullptr, &errfds, &timeout);
      if (ret == 0) {
        return SelectResult::Timeout;
      }

      if (ret > 0) {
        if (FD_ISSET(socketfd, &recvfds)) {
          return SelectResult::RecvReady;
        }

        if (FD_ISSET(socketfd, &errfds)) {
          return SelectResult::ErrorReady;
        }
      }

      return SelectResult::Fail;
  }

  inline void tcpSetNonblocking(int* sockfd)
  {
    int flags = fcntl(*sockfd, F_GETFL, 0);
    if (flags < 0) {
      ESP_LOGE(TAG, "tcpSetNonblocking: fcntl get failed");
      return;
    }

    flags = fcntl(*sockfd, F_SETFL, flags | O_NONBLOCK);
    if (flags < 0) {
      ESP_LOGE(TAG, "tcpSetNonblocking: fcntl set failed");
    }
  }

  int nonblockSSHAccept(WOLFSSH* ssh)
  {
    int ret;
    int error;
    int sockfd;
    SelectResult select_ret = SelectResult::Fail;
    int max_wait = 100;

    ret = wolfSSH_accept(ssh);
    error = wolfSSH_get_error(ssh);
    sockfd = (int)wolfSSH_get_fd(ssh);

    while (ret != WS_SUCCESS && (error == WS_WANT_READ || error == WS_WANT_WRITE)) {
      max_wait--;
      if (max_wait < 0) {
        error = WS_FATAL_ERROR;
      }
/*
      if (error == WS_WANT_READ)
        ESP_LOGE(TAG,"... client would read block\n");
      else if (error == WS_WANT_WRITE)
        ESP_LOGE(TAG,"... client would write block\n");
*/

      select_ret = tcpSelect(sockfd, 1);
      if (select_ret == SelectResult::RecvReady  || select_ret == SelectResult::ErrorReady || error == WS_WANT_WRITE) {
        ret = wolfSSH_accept(ssh);
        error = wolfSSH_get_error(ssh);
      }
      else if (select_ret == SelectResult::Timeout)
        error = WS_WANT_READ;
      else
        error = WS_FATAL_ERROR;
    }

    return ret;
  }

  const char* sessTypeName(WS_SessionType sessType)
  {
    switch (sessType)
    {
      case WOLFSSH_SESSION_SHELL: {
        static const char* name = "shell";
        return name;
      }

      case WOLFSSH_SESSION_EXEC: {
        static const char* name = "exec";
        return name;
      }

      case WOLFSSH_SESSION_SUBSYSTEM: {
        static const char* name = "subsystem";
        return name;
      }

      case WOLFSSH_SESSION_TERMINAL: {
        static const char* name = "terminal";
        return name;
      }

      default: {
        static const char* name = "unknown";
        return name;
      }
    }
  }

#ifdef DEBUG_WOLFSSH
  void wolfLog(enum wolfSSH_LogLevel logLevel, const char *const logMsg)
  {
    switch (logLevel) {
    case WS_LOG_ERROR:
      ESP_LOGE(TAG, "wolfssh: %s", logMsg);
      break;

    case WS_LOG_WARN:
      ESP_LOGW(TAG, "wolfssh: %s", logMsg);
      break;

    case WS_LOG_INFO:
      ESP_LOGI(TAG, "wolfssh: %s", logMsg);
      break;

    case WS_LOG_DEBUG:
      ESP_LOGD(TAG, "wolfssh: %s", logMsg);
      break;

    default:
      ESP_LOGI(TAG, "wolfssh: %s", logMsg);
      break;
    }
  }
#endif
}

Error Server::Initialize(const ServerConfig& cfg)
{
  ESP_LOGI(TAG, "setup wolfcrypt");
  int ret = wolfCrypt_Init();
  if (ret != 0) {
    ESP_LOGE(TAG,"unable to initialize wolfSSL: %d", ret);
    return Error::ShitHappens;
  }

#ifdef DEBUG_WOLFSSL
  wolfSSL_Debugging_ON();
  ESP_LOGI(TAG,"WolfSSL debug ON");
#endif

#ifdef DEBUG_WOLFSSH
  wolfSSH_Debugging_ON();
  wolfSSH_SetLoggingCb(wolfLog);
  ESP_LOGI(TAG, "WolfSSH debug ON");
#endif

#ifndef WOLFSSL_TLS13
  ESP_LOGE(TAG,"requires #ifndef WOLFSSL_TLS13");
  return Error::ShitHappens;
#endif

  ret = wolfSSH_Init();
  if (ret != WS_SUCCESS) {
    ESP_LOGE(TAG,"unable to initialize wolfSSH:: %d", ret);
    return Error::ShitHappens;
  }

  ESP_LOGI(TAG, "setup auth logic");
  Error err = auth.Initialize(cfg);
  if (err != Error::None) {
    ESP_LOGE(TAG,"unable to initialize auth logic: %d", (int)err);
    return Error::ShitHappens;
  }

  return SetupWolfSSH(cfg);
}

Error Server::SetupWolfSSH(const ServerConfig& cfg)
{
  wolfCtx = wolfSSH_CTX_new(WOLFSSH_ENDPOINT_SERVER, NULL);
  if (wolfCtx == nullptr) {
    ESP_LOGE(TAG,"couldn't allocate SSH CTX data.");
    return Error::ShitHappens;
  }

  wolfSSH_SetUserAuthTypes(wolfCtx, [](WOLFSSH* ssh, void* ctx) -> int {
    return WOLFSSH_USERAUTH_PUBLICKEY;
  });

  wolfSSH_SetUserAuth(wolfCtx, [](uint8_t authType, WS_UserAuthData* authData, void* ctx) -> int {
    if (authType != WOLFSSH_USERAUTH_PUBLICKEY) {
      return WOLFSSH_USERAUTH_INVALID_AUTHTYPE;
    }

    AuthContext* authCtx = reinterpret_cast<AuthContext *>(ctx);

    std::string userName(reinterpret_cast<const char*>(authData->username), authData->usernameSz);
    Blob::Bytes userKey(authData->sf.publicKey.publicKey, authData->sf.publicKey.publicKeySz);
    bool ok = authCtx->Provider.Authenticate(userName, userKey);
    return ok ? WOLFSSH_USERAUTH_SUCCESS : WOLFSSH_USERAUTH_INVALID_PUBLICKEY;
  });

  wolfSSH_SetUserAuthResult(wolfCtx, [](byte result, WS_UserAuthData* authData, void* ctx) -> int {
    if (result != WOLFSSH_USERAUTH_SUCCESS) {
      ESP_LOGW(TAG, "auth failed");
      return WS_FATAL_ERROR;
    }

    AuthContext* authCtx = reinterpret_cast<AuthContext *>(ctx);
    authCtx->Out.Name = std::string(reinterpret_cast<const char*>(authData->username), authData->usernameSz);
    authCtx->Out.Role = authCtx->Provider.Role(authCtx->Out.Name);

    Blob::Bytes userKey(authData->sf.publicKey.publicKey, authData->sf.publicKey.publicKeySz);
    std::expected<std::string, Error> fpRet = KeyFingerprint(userKey);
    if (!fpRet) {
      ESP_LOGW(TAG, "unable to generate user key fingeprint: %d", (int)fpRet.error());
      return WS_ERROR;
    }
    authCtx->Out.KeyFingerprint = std::move(fpRet.value());

    ESP_LOGI(TAG,
      "user %s@%s was authenticated by key: %s",
      authCtx->Out.Name.c_str(), authCtx->Out.ClientIP.c_str(),
      authCtx->Out.KeyFingerprint.c_str()
    );
    return WS_SUCCESS;
  });

  /* ./keys/server-key-ecc.der, ECC */
  static const unsigned char ecc_key_der_256[] =
  {
      0x30, 0x77, 0x02, 0x01, 0x01, 0x04, 0x20, 0x61, 0x09, 0x99,
      0x0B, 0x79, 0xD2, 0x5F, 0x28, 0x5A, 0x0F, 0x5D, 0x15, 0xCC,
      0xA1, 0x56, 0x54, 0xF9, 0x2B, 0x39, 0x87, 0x21, 0x2D, 0xA7,
      0x7D, 0x85, 0x7B, 0xB8, 0x7F, 0x38, 0xC6, 0x6D, 0xD5, 0xA0,
      0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01,
      0x07, 0xA1, 0x44, 0x03, 0x42, 0x00, 0x04, 0x81, 0x13, 0xFF,
      0xA4, 0x2B, 0xB7, 0x9C, 0x45, 0x74, 0x7A, 0x83, 0x4C, 0x61,
      0xF3, 0x3F, 0xAD, 0x26, 0xCF, 0x22, 0xCD, 0xA9, 0xA3, 0xBC,
      0xA5, 0x61, 0xB4, 0x7C, 0xE6, 0x62, 0xD4, 0xC2, 0xF7, 0x55,
      0x43, 0x9A, 0x31, 0xFB, 0x80, 0x11, 0x20, 0xB5, 0x12, 0x4B,
      0x24, 0xF5, 0x78, 0xD7, 0xFD, 0x22, 0xEF, 0x46, 0x35, 0xF0,
      0x05, 0x58, 0x6B, 0x5F, 0x63, 0xC8, 0xDA, 0x1B, 0xC4, 0xF5,
      0x69
  };
static const int sizeof_ecc_key_der_256 = sizeof(ecc_key_der_256);

  int ret = wolfSSH_CTX_UsePrivateKey_buffer(wolfCtx,
    ecc_key_der_256, sizeof_ecc_key_der_256,
    WOLFSSH_FORMAT_ASN1
  );
  if (ret != WS_SUCCESS) {
    ESP_LOGE(TAG, "unable to set banner: %d", ret);
    return Error::ShitHappens;
  }

  return Error::None;
}

ListenError Server::Listen(const HandlerCallback& handler)
{
  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family      = AF_INET;
  servAddr.sin_port        = htons(CONFIG_SSH_SERVER_PORT);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  // create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd <= 0) {
    ESP_LOGE(TAG, "failed to create a socket: %d", sockfd);
    return ListenError::Sock;
  }
  REF_DEFER(if (sockfd != SOCKET_INVALID) {close(sockfd); sockfd = SOCKET_INVALID;});

  // make sure server is setup for reuse addr
  int on = 1;
  int ret = setsockopt(
    sockfd,
    SOL_SOCKET,
    SO_REUSEADDR,
    (char*)&on,
    (socklen_t)sizeof(on)
  );
  if (ret != 0) {
    ESP_LOGE(TAG, "failed to setsockopt addr on socket: %d", ret);
    return ListenError::Sock;
  }

  // bind the server socket to our port
  ret = bind(
    sockfd,
    (struct sockaddr*)&servAddr,
    sizeof(servAddr)
  );
  if (ret != 0) {
    ESP_LOGE(TAG, "failed to bind to socket: %d", ret);
    return ListenError::Bind;
  }

  // listen, finally
  ret = listen(sockfd, CONFIG_SSH_SERVER_BACKLOG);
  if (ret < 0) {
    ESP_LOGE(TAG, "failed to listen to socket: %d", ret);
    return ListenError::Bind;
  }

  // accept && process loop
  for(;;) {
    WOLFSSH* ssh = wolfSSH_new(wolfCtx);
    if (ssh == NULL) {
      ESP_LOGE(TAG, "couldn't allocate SSH data");
      return ListenError::ShitHappens;
    }

  #if CONFIG_SSH_HIGHWATER_MARK > 0
    wolfSSH_SetHighwaterCtx(ssh, (void*)ssh);
    wolfSSH_SetHighwater(ssh, CONFIG_SSH_HIGHWATER_MARK);
  #endif

    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientFd = accept(
      sockfd,
      (struct sockaddr*)&clientAddr,
      &clientAddrSize
    );
    if (clientFd == -1) {
      ESP_LOGI(TAG, "accept failed");
      return ListenError::Accept;
    }

    UserInfo userInfo;
    userInfo.ClientIP = std::string(INET_ADDRSTRLEN, '\xff');
    inet_ntop(AF_INET, &clientAddr.sin_addr, userInfo.ClientIP.data(), INET_ADDRSTRLEN);

    AuthContext authCtx = {
      .Provider = auth,
      .Out = userInfo
    };
    wolfSSH_SetUserAuthCtx(ssh, &authCtx);
    wolfSSH_SetUserAuthResultCtx(ssh, &authCtx);

    tcpSetNonblocking(&clientFd);
    wolfSSH_set_fd(ssh, clientFd);

    ListenError processErr = AcceptConnection(ssh, userInfo, handler);

    int error = wolfSSH_stream_exit(ssh, 0);
    int ret = wolfSSH_get_error(ssh);
    if (error != WS_SOCKET_ERROR_E && error != WS_FATAL_ERROR) {
      ret = wolfSSH_shutdown(ssh);
      // peer hung up, stop shutdown
      if (ret == WS_SOCKET_ERROR_E) {
        ret = 0;
      }

      error = wolfSSH_get_error(ssh);
      if (error != WS_SOCKET_ERROR_E && (error == WS_WANT_READ || error == WS_WANT_WRITE)) {
        int maxAttempt = 10; // make 10 attempts max before giving up
        int attempt;

        for (attempt = 0; attempt < maxAttempt; attempt++) {
            ret = wolfSSH_worker(ssh, NULL);
            error = wolfSSH_get_error(ssh);

            // peer succesfully closed down gracefully
            if (ret == WS_CHANNEL_CLOSED) {
              break;
            }

            // peer hung up, stop shutdown
            if (ret == WS_SOCKET_ERROR_E) {
              break;
            }

            if (error != WS_WANT_READ && error != WS_WANT_WRITE) {
              break;
            }
        }

        if (attempt == maxAttempt) {
          ESP_LOGW(TAG, "gave up on gracefull shutdown, closing client %s socket", userInfo.ClientIP.c_str());
        }
      }
    }

    wolfSSH_free(ssh);
    if (clientFd != SOCKET_INVALID) {
      close(clientFd);
    }

    ESP_LOGI(TAG, "stack HighWaterMark: %u", uxTaskGetStackHighWaterMark(nullptr));
    if (processErr != ListenError::None) {
      ESP_LOGE(TAG, "unable to process request: %d", (int)processErr);
      return processErr;
    }
  }

  return ListenError::None;
}

ListenError Server::AcceptConnection(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler)
{
  int ret = nonblockSSHAccept(ssh);
  if (ret != 0) {
    ESP_LOGE(TAG, "accept conn from %s failed: %d", userInfo.ClientIP.c_str(), ret);
    return ListenError::Accept;
  }

  WS_SessionType sessType = wolfSSH_GetSessionType(ssh);
  switch (sessType) {
  case WOLFSSH_SESSION_EXEC:
    return ProcessSessionCommand(ssh, userInfo, handler);

  default:
    ESP_LOGW(TAG, "unsupported session from %s: %s", userInfo.ClientIP.c_str(), sessTypeName(sessType));
    return ListenError::Unsupported;
  }
}

ListenError Server::ProcessSessionCommand(WOLFSSH* ssh, const UserInfo& userInfo, const HandlerCallback& handler)
{
  std::string cmd = wolfSSH_GetSessionCommand(ssh);
  Stream stream(ssh, true);
  if (!handler(userInfo, cmd, stream)) {
    ESP_LOGE(TAG, "handler fail");
  }

  return ListenError::None;
}

Server::~Server()
{
  wolfSSH_CTX_free(wolfCtx);
}
