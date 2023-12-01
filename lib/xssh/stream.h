#ifndef XSSH_STREAM_H
#define XSSH_STREAM_H

#include <Arduino.h>

typedef struct ssh_channel_struct* ssh_channel;

namespace XSsh
{
  class ChanStream: public Stream
  {
  public:
    explicit ChanStream(ssh_channel chan) : chan(chan) {};

    void setTimeouts(int pollMs, int readMs)
    {
      pollTimeout = pollMs;
      readTimeout = readMs;
    };

    virtual int available() override;
    virtual int read() override;
    virtual int peek() override;
    virtual size_t readBytes(char* buffer, size_t length) override;
    virtual size_t write(uint8_t b) override
    {
      return 0;
    }

  private:
    ssh_channel chan;
    char peekBuf;
    int pollTimeout = 100;
    int readTimeout = 5000;
  };

  class ChanPrinter: public Print
  {
  public:
    explicit ChanPrinter(ssh_channel chan) : chan(chan) {};

    virtual size_t write(uint8_t b) override;
    virtual size_t write(const uint8_t *buffer, size_t length) override;

    using Print::write; // pull in write(str) and write(buf, size) from Print
  private:
    ssh_channel chan;
  };
}

#endif
