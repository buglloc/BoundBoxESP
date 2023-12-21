#include <sdkconfig.h>
#include "ui/button.h"
#include "config.h"


using namespace UI;

bool Button::UpdateState(bool pressed)
{
  ButtonState newState = calcState(pressed);
  if (newState == state) {
    return false;
  }

  state = newState;
  return newState != ButtonState::None;
}

ButtonState Button::State() const
{
  return state;
}

ButtonState Button::calcState(bool pressed)
{
  const uint32_t longPressTicks = (CONFIG_UI_LONG_PRESS_TIME_MS /CONFIG_UI_PERIOD_TIME_MS);

  if (pressed) {
    if (!seenPress) {
      // new press
      pressedTicks = 0;
      seenPress = true;
      return ButtonState::None;
    }

    pressedTicks++;
    if (!alreadyFired && pressedTicks >= longPressTicks) {
      // fire event by long tap
      alreadyFired = true;
      return ButtonState::Long;
    }

    return ButtonState::None;
  }

  if (seenPress) {
    // release button
    seenPress = false;

    if (alreadyFired) {
      alreadyFired = false;
      return ButtonState::None;
    }

    ButtonState state = pressedTicks < longPressTicks ? ButtonState::Short : ButtonState::Long;
    alreadyFired = false;
    pressedTicks = 0;
    return state;
  }

  return ButtonState::None;
}
