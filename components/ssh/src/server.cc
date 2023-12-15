#include "wolfssh_init.h"
#include "ssh/server.h"
#include "ssh_config.h"
#include "auth.h"

#include <freertos/FreeRTOS.h>

#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssh/ssh.h>

#include <lwip/netdb.h>
#include <lwip/sockets.h>

#include <defer.h>

#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh_server";

  enum class SelectResult {
    Fail,
    Timeout,
    RecvReady,
    ErrorReady,
  };

  inline int tcpSelect(SOCKET_T socketfd, int deadline)
  {
      WFD_SET_TYPE recvfds, errfds;
      int nfds = (int)socketfd + 1;
      struct timeval timeout = { (deadline > 0) ? deadline : 0, 0 };

      WFD_ZERO(&recvfds);
      WFD_SET(socketfd, &recvfds);
      WFD_ZERO(&errfds);
      WFD_SET(socketfd, &errfds);

      int ret = select(nfds, &recvfds, nullptr, &errfds, &timeout);
      if (ret == 0) {
        return SelectResult::Timeout;
      }

      if (ret > 0) {
        if (WFD_ISSET(socketfd, &recvfds)) {
          return SelectResult::RecvReady;
        }

        if (WFD_ISSET(socketfd, &errfds)) {
          return SelectResult::ErrorReady;
        }
      }

      return SelectResult::Fail;
  }

  int NonBlockSSHAccept(WOLFSSH* ssh)
  {
    int ret;
    int error;
    int sockfd;
    int select_ret = 0;
    int max_wait = 100;

    ret = wolfSSH_accept(ssh);
    error = wolfSSH_get_error(ssh);
    sockfd = (int)wolfSSH_get_fd(ssh);

    while (ret != WS_SUCCESS &&
            (error == WS_WANT_READ || error == WS_WANT_WRITE)) {

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
        if (select_ret == WS_SELECT_RECV_READY  ||
            select_ret == WS_SELECT_ERROR_READY ||
            error == WS_WANT_WRITE) {
            ret = wolfSSH_accept(ssh);
            error = wolfSSH_get_error(ssh);
        }
        else if (select_ret == WS_SELECT_TIMEOUT)
            error = WS_WANT_READ;
        else
            error = WS_FATAL_ERROR;
    }

    return ret;
  }
}

cpp::result<void, Error> Server::Initialize(const ServerConfig& cfg)
{
  ESP_LOGI(TAG, "setup wolfcrypt");
  int ret = wolfCrypt_Init();
  if (ret != 0) {
    ESP_LOGE(TAG,"unable to initialize wolfSSL: %d", ret);
    return cpp::fail(Error::ShitHappens);
  }

#ifdef DEBUG_WOLFSSL
  wolfSSL_Debugging_ON();
  ESP_LOGI(TAG,"WolfSSL debug ON");
#endif

#ifdef DEBUG_WOLFSSH
  wolfSSH_Debugging_ON();
  ESP_LOGI(TAG,"WolfSSH debug ON");
#endif

#ifndef WOLFSSL_TLS13
  ESP_LOGE(TAG,"requires #ifndef WOLFSSL_TLS13");
  return cpp::fail(Error::ShitHappens);
#endif

  ret = wolfSSH_Init();
  if (ret != WS_SUCCESS) {
    ESP_LOGE(TAG,"unable to initialize wolfSSH:: %d", ret);
    return cpp::fail(Error::ShitHappens);
  }

  ESP_LOGI(TAG, "setup auth logic");
  auto authRes = auth.Initialize(cfg);
  if (authRes.has_error()) {
    ESP_LOGE(TAG,"unable to initialize auth logic: %d", authRes.error());
    return cpp::fail(Error::ShitHappens);
  }

  return SetupWolfSSH(cfg);
}

cpp::result<void, Error> SetupWolfSSH(const ServerConfig& cfg)
{
  wolfCtx = wolfSSH_CTX_new(WOLFSSH_ENDPOINT_SERVER, NULL);
  if (wolfCtx == nullptr) {
    ESP_LOGE(TAG,"couldn't allocate SSH CTX data.");
    return cpp::fail(Error::ShitHappens);
  }

  // set the login banner message
  if (!cfg.Banner.empty()) {
    wolfSSH_CTX_SetBanner(wolfCtx, cfg.Banner.c_str());
  } else {
    wolfSSH_CTX_SetBanner(wolfCtx, SSH_SERVER_BANNER);
  }

  wolfSSH_SetUserAuthTypes(wolfCtx, [](WOLFSSH* ssh, void* ctx) -> int {
    return WOLFSSH_USERAUTH_PUBLICKEY;
  });

  wolfSSH_SetUserAuth(wolfCtx, [](uint8_t authType, WS_UserAuthData* authData, void* ctx) -> int {
    if (authType != WOLFSSH_USERAUTH_PUBLICKEY) {
      return WOLFSSH_USERAUTH_INVALID_AUTHTYPE;
    }

    Auth* auth = reinterpret_cast<Auth *>(ctx);
  
    std::string userName(authData->username, authData->usernameSz);
    Bytes userKey(authData->sf.publicKey, authData->sf.publicKeySz);
    AuthInfo out;

    bool ok = auth->Authenticate(userName, userKey, out);
    if (ok) {
      ESP_LOGI(TAG, "user '%s' authenticated by key '%s'", out.User.c_str(), out.KeyFingerprint.c_str());
      return WOLFSSH_USERAUTH_SUCCESS;
    }

    return WOLFSSH_USERAUTH_INVALID_PUBLICKEY;
  });

  return {};
}

cpp::result<void, ListenError> Listen(const HandlerCallback& handler)
{
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family      = AF_INET;
  servAddr.sin_port        = htons(SSH_SERVER_PORT);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  // create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd <= 0) {
    ESP_LOGE(TAG, "failed to create a socket: %d", sockfd);
    return cpp::fail(ListenError::Sock);
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
    return cpp::fail(ListenError::Sock);
  }

  // bind the server socket to our port 
  ret = bind(
    sockfd,
    (struct sockaddr*)&servAddr,
    sizeof(servAddr)
  );
  if (ret != 0) {
    ESP_LOGE(TAG, "failed to bind to socket: %d", ret);
    return cpp::fail(ListenError::Bind);
  }

  // listen, finally
  ret = listen(sockfd, SSH_SERVER_BACKLOG);
  if (ret < 0) {
    ESP_LOGE(TAG, "failed to listen to socket: %d", ret);
    return cpp::fail(ListenError::Bind);
  }

  // accept && process loop
  for(;;) {
    WOLFSSH* ssh = wolfSSH_new(wolfCtx);
    if (ssh == NULL) {
      ESP_LOGE(TAG, "couldn't allocate SSH data");
      return cpp::fail(ListenError::ShitHappens);
    }

    wolfSSH_SetUserAuthCtx(ssh, &auth);
  #if SSH_HIGHWATER_MARK > 0
    wolfSSH_SetHighwaterCtx(ssh, (void*)ssh);
    wolfSSH_SetHighwater(ssh, SSH_HIGHWATER_MARK);
  #endif

    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientFd = accept(
      sockfd,
      (struct sockaddr*)&clientAddr,
      &clientAddrSz
    );
    if (clientFd == -1) {
      ESP_LOGI(TAG,"accept failed");
      exit(EXIT_FAILURE);
    }

    tcp_set_nonblocking(&clientFd);
    wolfSSH_set_fd(ssh, clientFd);

    auto connRes = AcceptConnection(ssh, clientFd, inet_ntoa(clientAddr));
    wolfSSH_stream_exit(ssh, 0);
    wolfSSH_free(ssh);
    if (clientFd != SOCKET_INVALID) {
      close(clientFd);
    }

    if (connRes.has_error()) {
      ESP_LOGE(TAG, "unable to process request: %d", connRes.error());
      return cpp::fail(connRes.errors());
    }
  }

  return {};
}

cpp::result<void, Error> Server::AcceptConnection(const WOLFSSH* ssh, std::string clientIP)
{
  int ret = NonBlockSSHAccept(ssh);
  if (ret != 0) {
    ESP_LOGE(TAG, "accept conn from %s failed: %d", clientIP.c_str(), ret);
    return cpp::fail(Error::Accept);
  }

  wolfSSH_GetUsername(ssh);

  uint8_t sessType = wolfSSH_GetSessionType(ssh);
  switch (sessType) {
  case WOLFSSH_SESSION_EXEC:
      if (ret == WS_SUCCESS) {
          ESP_LOGI(TAG,
              "[SSHD] Entering exec session [%s]",
                  wolfSSH_GetSessionCommand(ssh));
          // SHELL_Subsystem(conn, ssh, pPasswd, usrConf,
          //         wolfSSH_GetSessionCommand(ssh));
      }
      break;

  default:
    ESP_LOGI(TAG, "ignore unsopported session type: %d", sessType)
    return cpp::fail(Error::Unsupported);
  }

}

Server::~Server()
{
  wolfSSH_CTX_free(ctx);
}