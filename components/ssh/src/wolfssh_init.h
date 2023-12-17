#pragma once

#define WOLFSSL_TLS13
#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_ECC
#define HAVE_HKDF
#define HAVE_FFDHE_8192 /* or one of the other supported FFDHE sizes [2048, 3072, 4096, 6144, 8192] */
#define WC_RSA_PSS
#define WOLFSSH_TEST_THREADING

/*  note "file system": "load keys and certificate from files" vs NO_FILESYSTEM
 *  and "access an actual file system via SFTP/SCP" vs WOLFSSH_NO_FILESYSTEM
 *  we'll typically have neither on an embedded device:
 */
#define NO_FILESYSTEM
#define WOLFSSH_NO_FILESYSTEM
#ifndef WOLFSSL_USER_SETTINGS
  #define WOLFSSL_USER_SETTINGS
#endif

/* make sure this appears before any other wolfSSL headers */
#include <wolfssl/wolfcrypt/settings.h>
#include <user_settings.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/ssl.h>
