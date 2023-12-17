#include "blob/bytes.h"

namespace
{
  size_t encodeBase64Length(size_t inLen)
  {
    return (inLen + 2) / 3 * 4;
  }

  unsigned char binaryToBase64(unsigned char v) {
    // Capital letters - 'A' is ascii 65 and base64 0
    if(v < 26) return v + 'A';

    // Lowercase letters - 'a' is ascii 97 and base64 26
    if(v < 52) return v + 71;

    // Digits - '0' is ascii 48 and base64 52
    if(v < 62) return v - 4;

    // '+' is ascii 43 and base64 62
    if(v == 62) return '+';

    // '/' is ascii 47 and base64 63
    if(v == 63) return '/';

    return 255;
  }

  unsigned char base64ToBinary(unsigned char c) {
    // Capital letters - 'A' is ascii 65 and base64 0
    if('A' <= c && c <= 'Z') return c - 'A';

    // Lowercase letters - 'a' is ascii 97 and base64 26
    if('a' <= c && c <= 'z') return c - 71;

    // Digits - '0' is ascii 48 and base64 52
    if('0' <= c && c <= '9') return c + 4;

    // '+' is ascii 43 and base64 62
    if(c == '+') return 62;

    // '/' is ascii 47 and base64 63
    if(c == '/') return 63;

    return 255;
  }

  size_t decodeBase64Length(const std::string& input) {
    size_t b64chars = 0;
    for (auto&& ch: input) {
      if (base64ToBinary(ch) >= 64) {
        break;
      }
      b64chars++;
    }

    return b64chars/4*3 + (b64chars % 4 ? b64chars % 4 - 1 : 0);
  }
}

namespace Blob
{
  std::string Base64Encode(const Bytes& bytes)
  {
    size_t fullSets = bytes.size()/3;
    std::string out("\xff", encodeBase64Length(bytes.size()));

    const uint8_t* inPtr = bytes.data();
    char* outPtr = &out[0];
    for(size_t i = 0; i < fullSets; ++i) {
      outPtr[0] = binaryToBase64(                         inPtr[0] >> 2);
      outPtr[1] = binaryToBase64((inPtr[0] & 0x03) << 4 | inPtr[1] >> 4);
      outPtr[2] = binaryToBase64((inPtr[1] & 0x0F) << 2 | inPtr[2] >> 6);
      outPtr[3] = binaryToBase64( inPtr[2] & 0x3F);

      inPtr += 3;
      outPtr += 4;
    }

    switch(bytes.length() % 3) {
      // case 0:
      //   outPtr[0] = '\0';
      //   break;
      case 1:
        outPtr[0] = binaryToBase64(                         inPtr[0] >> 2);
        outPtr[1] = binaryToBase64((inPtr[0] & 0x03) << 4);
        outPtr[2] = '=';
        outPtr[3] = '=';
        // outPtr[4] = '\0';
        break;
      case 2:
        outPtr[0] = binaryToBase64(                         inPtr[0] >> 2);
        outPtr[1] = binaryToBase64((inPtr[0] & 0x03) << 4 | inPtr[1] >> 4);
        outPtr[2] = binaryToBase64((inPtr[1] & 0x0F) << 2);
        outPtr[3] = '=';
        // outPtr[4] = '\0';
        break;
    }

    return out;
  }

  Bytes Base64Decode(const std::string& in)
  {
    size_t outLen = decodeBase64Length(in);
    Bytes out(outLen, '\xff');

    const char* inPtr = in.c_str();
    uint8_t* outPtr = &out[0];
    // While there are still full sets of 24 bits...
    for(unsigned int i = 2; i < outLen; i += 3) {
      outPtr[0] = base64ToBinary(inPtr[0]) << 2 | base64ToBinary(inPtr[1]) >> 4;
      outPtr[1] = base64ToBinary(inPtr[1]) << 4 | base64ToBinary(inPtr[2]) >> 2;
      outPtr[2] = base64ToBinary(inPtr[2]) << 6 | base64ToBinary(inPtr[3]);

      inPtr += 4;
      outPtr += 3;
    }

    switch(outLen % 3) {
      case 1:
        outPtr[0] = base64ToBinary(inPtr[0]) << 2 | base64ToBinary(inPtr[1]) >> 4;
        break;
      case 2:
        outPtr[0] = base64ToBinary(inPtr[0]) << 2 | base64ToBinary(inPtr[1]) >> 4;
        outPtr[1] = base64ToBinary(inPtr[1]) << 4 | base64ToBinary(inPtr[2]) >> 2;
        break;
    }

    return out;
  }
}