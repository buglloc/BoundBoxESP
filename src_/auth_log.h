#if 0
#ifndef AUTH_LOG_H
#define AUTH_LOG_H

#include <ArduinoLog.h>
#include <FS.h>

class TAuthLog
{
public:
  static TAuthLog &Instance();
  bool Begin();
  void Tick();
  Logging Logger();

  ~TAuthLog()
  {
#if USE_SD_LOGSTORE
  if (file) {
    file.flush();
    file.close();
  }
#endif
  }
private:
  TAuthLog() = default;

private:
  Logging log;
#if USE_SD_LOGSTORE
  File file;
#endif
};

#endif
#endif
