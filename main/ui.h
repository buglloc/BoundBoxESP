#pragma once

#include <hardware/manager.h>

class UI
{
public:
  Error Initialize(Hardware::Manager& hw);

private:
  Hardware::Manager& hw;
}