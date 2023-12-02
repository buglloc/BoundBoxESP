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
  long Uptime() const;
  const TNetManager& Net() const;
  const TConfig& RuntimeConfig() const;

private:
  TBoardManager() = default;
  void tickIntruder();

private:
  unsigned long startTime;
  std::unique_ptr<TConfig> runtimeConfig;
};

#endif
