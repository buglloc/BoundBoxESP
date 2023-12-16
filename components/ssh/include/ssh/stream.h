#pragma once

#include <cstddef>
#include <stdint.h>

#include "config.h"
#include "common.h"

#ifndef SSH_BUFFER_SIZE
    #define SSH_BUFFER_SIZE 512
#endif

// fwd
struct WOLFSSH;

namespace SSH
{
  class Stream
  {
  public:
    Stream(WOLFSSH* ssh, bool nonBlock = true)
      : ssh(ssh)
      , nonBlock(nonBlock)
      , writeSize(0)
    {};

    bool flush();

    ~Stream()
    {
      flush();
    }

    // ArduinoJson CustomReader: https://arduinojson.org/news/2019/11/01/version-6-13-0/#custom-reader
    // Reads one byte, or returns -1
    int read();
    // Reads several bytes, returns the number of bytes read.
    size_t readBytes(char* buffer, size_t length);

    // ArduinoJson CustomWriter: https://arduinojson.org/news/2019/11/01/version-6-13-0/#custom-writer
    // Writes one byte, returns the number of bytes written (0 or 1)
    size_t write(uint8_t c);
    // Writes several bytes, returns the number of bytes written
    size_t write(const uint8_t *buffer, size_t length);

  private:
    WOLFSSH* ssh = nullptr;
    bool nonBlock;
    size_t writeSize;
    uint8_t writeBuf[SSH_BUFFER_SIZE];
  };
}
