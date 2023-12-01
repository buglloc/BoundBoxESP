#include "types.h"
#include "libssh_esp.h"
#include <libssh/misc.h>

namespace XSsh
{
  void keyFree(ssh_key key)
  {
    SSH_KEY_FREE(key);
  }

  Keyring::Keyring()
  : keys(ssh_list_new())
  {}

  void Keyring::Add(const ssh_key key)
  {
    ssh_list_append(keys, ssh_key_dup(key));
  }

  void Keyring::Visit(Keyring::VisitFn fn) const
  {
    ssh_key key_entry = nullptr;
    for (ssh_iterator* it = ssh_list_get_iterator(keys); it != nullptr ; it = it->next) {
      key_entry = ssh_iterator_value(ssh_key, it);
      if (key_entry == NULL) {
        continue;
      }

      if (!fn(key_entry)) {
        break;
      }
    }
  }

  size_t Keyring::Size() const
  {
    return ssh_list_count(keys);
  }

  bool Keyring::IsEmpty() const
  {
    return Size() != 0;
  }

  bool Keyring::Contains(const ssh_key targetKey) const
  {
    ssh_key key_entry = nullptr;
    for (ssh_iterator* it = ssh_list_get_iterator(keys); it != nullptr ; it = it->next) {
      key_entry = ssh_iterator_value(ssh_key, it);
      if (key_entry == NULL) {
        continue;
      }

      if (ssh_key_cmp(targetKey, key_entry, SSH_KEY_CMP_PUBLIC)) {
        continue;
      }

      return true;
    }

    return false;
  }

  Keyring::~Keyring()
  {
    Visit([](ssh_key key) -> bool {
      ssh_key_free(key);
      return true;
    });

    ssh_list_free(keys);
  }
}
