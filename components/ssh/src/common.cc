#include "ssh/common.h"

#include <wolfssl/wolfcrypt/sha256.h>
#include <base64.h>

namespace SSH
{
  std::expected<std::string, Error> KeyFingerprint(const Bytes& key)
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
    out += Base64::Encode(Bytes{digest, sizeof(digest)});
    return out;
  }
}
