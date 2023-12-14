#ifndef BB_BOARD_MANAGER_H
#define BB_BOARD_MANAGER_H

#include "config.h"
#include "board_config.h"
#include "net_manager.h"

class TBoardManager
{
public:
  enum class BoardState
  {
    None,
    Boot,
    WaitNet,
    WaitCredential,
    Process,
    Idle,
  };

  struct BoardInfo
  {
    BoardState State;
    IPAddress LocalIP;
    uint32_t BattVoltage;
    float CoreTemp;

    bool operator==(const BoardInfo& info) const
    {
      return (
        State == info.State &&
        LocalIP == info.LocalIP &&
      #if HAVE_BATTERY
        abs((int)BattVoltage - (int)info.BattVoltage) < 50 &&
      #endif
      #if HAVE_TEMP_SENSOR
        fabs(CoreTemp - info.CoreTemp) < 0.1 &&
      #endif
        true
      );
    }
  };

public:
  static TBoardManager &Instance();
  bool Begin();
  void Tick();
  void ToState(BoardState targetState);
  bool ScheduleRestart(int sec);
  bool ResetConfig();
  bool StoreConfig(std::unique_ptr<TConfig> cfg);
  TNetManager& Net() const;
  const TConfig& RuntimeConfig() const;
  uint32_t Uptime() const;
  uint32_t FreeHeap() const;
  uint32_t BattVoltage() const;
  float CoreTemp() const;

private:
  TBoardManager() = default;
  void tickIntruder();
  void tickRestart();
  void tickBoardInfo();

private:
  uint32_t startTime;
  uint32_t uptime;
  uint32_t restartAt;
  uint32_t infoUpdatedAt;
  BoardInfo boardInfo;
  std::unique_ptr<TConfig> runtimeConfig;
};

#endif
