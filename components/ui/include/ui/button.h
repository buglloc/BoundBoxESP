#pragma once

#include <stdint.h>


namespace UI
{
  enum class ButtonState
  {
    None,
    Short,
    Long
  };

  class Button
  {
  public:
    bool UpdateState(bool pressed);
    ButtonState State() const;

  private:
    ButtonState calcState(bool pressed);

  private:
    ButtonState state = ButtonState::None;
    uint16_t pressedTicks = 0 ;
    bool seenPress = false;
    bool alreadyFired = false;
  };
}
