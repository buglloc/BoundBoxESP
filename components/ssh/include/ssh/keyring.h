#pragma once

#include <functional>
#include <vector>

#include <blob/bytes.h>

#include "common.h"


namespace SSH
{
  class Keyring
  {
  public:
    void Own(ssh_key key);
    void Add(const ssh_key key);

    size_t Size() const;
    bool Empty() const;

    bool Contains(const ssh_key targetKey) const;

    ~Keyring();

  private:
    std::vector<ssh_key> keys;
  };
}
