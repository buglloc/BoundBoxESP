#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <result.h>

class TUIManager
{
public:
  enum class Error: uint8_t
  {
    None,
    Internal
  };

public:
  static TUIManager &Instance();
  bool Begin();
  void Tick();

private:
  TUIManager() = default;

};

#endif