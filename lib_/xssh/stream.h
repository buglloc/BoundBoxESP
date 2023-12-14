#ifndef XSSH_STREAM_H
#define XSSH_STREAM_H

#include <Arduino.h>

// fwd
typedef struct ssh_channel_struct* ssh_channel;

#define BUF_SIZE 512

namespace XSSH
{
  class ChanReader
  {
  public:
    explicit ChanReader(ssh_channel chan) : chan(chan) {};

    void setTimeouts(int pollMs, int readMs)
    {
      pollTimeout = pollMs;
      readTimeout = readMs;
    };

    int read();
    size_t readBytes(char* s, size_t length);

  private:
    ssh_channel chan;
    int pollTimeout = 100;
    int readTimeout = 5000;
  };

  class ChanWriter
  {
  public:
    explicit ChanWriter(ssh_channel chan) : chan(chan)
    {
      size = 0;
    };

    size_t write(uint8_t b);
    size_t write(const uint8_t* bytes, size_t length);
    bool flush();

    ~ChanWriter()
    {
      flush();
    }

  private:
    ssh_channel chan;
    uint8_t buffer[BUF_SIZE];
    size_t size;
  };
}

#endif
