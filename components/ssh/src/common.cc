#include "common.h"

#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/coding.h>


namespace SSH
{
  cpp::result<std::string, Error> KeyFingerprint(const Bytes& key)
  {
    byte digest[WC_SHA256_DIGEST_SIZE];
    char fp[48] = { 0 };
    word32 fpSz = sizeof(fp);
    int ret;

    wc_Sha256 sha;
    ret = wc_InitSha256(&sha);
    if (ret == 0)
      ret = wc_Sha256Update(&sha, key.c_str(), key.size());
    if (ret == 0)
      ret = wc_Sha256Final(&sha, digest);
    if (ret == 0)
      ret = Base64_Encode_NoNl(digest, sizeof(digest), (byte*)fp, &fpSz);

    if (ret == 0) {
      if (fp[fpSz] == '=') {
        fp[fpSz] = 0;
      }

      std::string out;
      out.reserve(7+fpSz);
      out.append("SHA256:");
      out.append(fp);
      return std::move(out);
    }

    return cpp::fail(Error::ShitHappens);
  }
}