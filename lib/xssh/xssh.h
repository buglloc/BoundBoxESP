#ifndef XSSH_XSSH_H
#define XSSH_XSSH_H

#include "types.h"
#include "stream.h"
#include <Arduino.h>
#include <Result.h>

namespace XSSH
{
  void Begin();
  cpp::result<Key, GenError> GenKey(KeyType keyType, int bits);
  cpp::result<Key, ParseError> ParsePublicKey(const String& in);
  cpp::result<Key, ParseError> ParsePrivateKey(const String& in, const String& passphrase = String());

  cpp::result<String, Error> KeyFingerprint(const Key& key);
  cpp::result<String, Error> KeyFingerprint(const ssh_key key);

  cpp::result<String, Error> MarshalPrivateKey(const Key& key, const String& passphrase = String());
  cpp::result<String, Error> MarshalPrivateKey(const ssh_key key, const String& passphrase = String());

  cpp::result<String, Error> MarshalAuthorizedKey(const Key& key);
  cpp::result<String, Error> MarshalAuthorizedKey(const ssh_key key);
}

#endif
