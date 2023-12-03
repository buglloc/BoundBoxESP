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
  bool ScheduleRestart(int sec);
  bool StoreConfig(std::unique_ptr<TConfig> cfg);
  uint32_t Uptime() const;
  uint32_t FreeHeap() const;
  const TNetManager& Net() const;
  const TConfig& RuntimeConfig() const;

private:
  TBoardManager() = default;
  void tickIntruder();
  void tickRestart();

private:
  uint32_t startTime;
  uint32_t restartAt;
  std::unique_ptr<TConfig> runtimeConfig;
};

#endif
