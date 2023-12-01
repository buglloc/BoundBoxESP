#ifndef BB_BOARD_MANAGER_H
#define BB_BOARD_MANAGER_H

#include "config.h"
#include "net_manager.h"

class TBoardManager
{
public:
  static TBoardManager &Instance();
  bool Begin();
  void Tick();
  long Uptime();
  TNetManager& Net();
  TConfig& RuntimeConfig();

private:
  TBoardManager() = default;
  void tickIntruder();

private:
  unsigned long startTime;
  TConfig runtimeConfig;
};

#endif
