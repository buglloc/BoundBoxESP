#ifndef XSSH_TYPES_H
#define XSSH_TYPES_H

#include "libssh_esp.h"
#include <Arduino.h>
#include <result.h>

// fwd
struct ssh_list;

namespace XSSH
{
  enum class Error: uint8_t
  {
    None,
    ShitHappens,
  };

  enum class GenError: uint8_t
  {
    None,
    UnsupportedType,
    ShitHappens,
  };

  enum class ParseError: uint8_t
  {
    None,
    Malformed,
    UnsupportedType,
    ShitHappens,
  };

  enum class KeyType: uint8_t
  {
    None,
    Rsa,
    Ecdsa,
    Ed25519,
  };

  template <typename NativeDeleter, NativeDeleter deleter>
  struct sshDeleter {
    template <typename T>
    void operator()(T* ptr) {
      if (ptr != nullptr) {
        deleter(ptr);
      }
    }
  };

  using Key = std::unique_ptr<ssh_key_struct, sshDeleter<decltype(&ssh_key_free), &ssh_key_free>>;

  class Keyring
  {
  public:
    using VisitFn = std::function<bool(const ssh_key key)>;

  public:
    explicit Keyring();

    void Add(const ssh_key key);
    void Add(const Key& key)
    {
      Add(key.get());
    }

    void Visit(VisitFn fn) const;

    size_t Size() const;
    bool IsEmpty() const;
    bool Contains(const ssh_key targetKey) const;
    bool Contains(const Key& targetKey) const
    {
      return Contains(targetKey.get());
    }

    ~Keyring();
  private:
    ssh_list* keys = nullptr;
  };
}

#endif