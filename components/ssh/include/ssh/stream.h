#pragma once

#include <sdkconfig.h>

#include <cstddef>
#include <stdint.h>

#include "libssh_esp.h"


namespace SSH
{
  class Stream
  {
  public:
    Stream(ssh_channel chan)
      : chan(chan)
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
    ssh_channel chan;
    size_t writeSize;
    uint8_t writeBuf[CONFIG_SSH_STREAM_BUFFER_SIZE];
  };
}
