#include "stream.h"
#include "libssh_esp.h"

namespace XSsh
{

  int ChanStream::available()
  {
    return 0;
  }

  int ChanStream::peek()
  {
    if (peekBuf != 0) {
      return peekBuf;
    }

    if (readBytes(&peekBuf, 1) == 1) {
      return peekBuf;
    }

    return -1;
  }

  int ChanStream::read()
  {
    int out = peek();
    peekBuf = 0;
    return out;
  }

  size_t ChanStream::readBytes(char* buffer, size_t length)
  {
    if (ssh_channel_is_eof(chan)) {
      return 0;
    }

    int rc = ssh_channel_poll_timeout(chan, pollTimeout, 0);
    if (rc <= 0) {
      // err or timeout or no data
      return 0;
    }

    do {
      rc = ssh_channel_read_timeout(chan, buffer, length, 0, readTimeout);
    } while (rc == SSH_AGAIN);
    return rc < 0 ? 0 : rc;
  }

  size_t ChanPrinter::write(uint8_t b)
  {
    return write(&b, 1);
  }

  size_t ChanPrinter::write(const uint8_t *buffer, size_t length)
  {
    if (!ssh_channel_is_open(chan)) {
      return 0;
    }

    int rc = 0;
    do {
      rc = ssh_channel_write(chan, buffer, length);
    } while (rc == SSH_AGAIN);
    return rc < 0 ? 0 : rc;
  }
}
