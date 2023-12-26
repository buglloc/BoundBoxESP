#include "ssh/keyring.h"
#include "ssh/libssh_esp.h"

#include <algorithm>

#include <esp_log.h>


using namespace SSH;

void Keyring::Own(ssh_key key)
{
  keys.push_back(key);
}

void Keyring::Add(const ssh_key key)
{
  Own(ssh_key_dup(key));
}

size_t Keyring::Size() const
{
  return keys.size();
}

bool Keyring::Empty() const
{
  return keys.empty();
}

bool Keyring::Contains(const ssh_key targetKey) const
{
  for (const auto &key : keys) {
    if (ssh_key_cmp(targetKey, key, SSH_KEY_CMP_PUBLIC) != 0) {
      continue;
    }

    return true;
  }

  return false;
}

Keyring::~Keyring()
{
  std::vector<ssh_key>::iterator it = keys.begin();
  while (it != keys.end()) {
    ssh_key_free(*it);
    it = keys.erase(it);
  }
}
