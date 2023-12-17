#include "ssh/common.h"

#include <string>

#include <wolfssl/wolfcrypt/sha256.h>

#include <blob/base64.h>


namespace SSH
{
  std::expected<std::string, Error> KeyFingerprint(const Blob::Bytes& key)
  {
    wc_Sha256 sha;
    if (wc_InitSha256(&sha) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    if (wc_Sha256Update(&sha, key.c_str(), key.size()) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    uint8_t digest[WC_SHA256_DIGEST_SIZE];
    if (wc_Sha256Final(&sha, digest) != 0) {
      return std::unexpected<Error>{Error::ShitHappens};
    }

    std::string out("SHA256:");
    out += Blob::Base64Encode({digest, sizeof(digest)});

    return out;
  }
}
