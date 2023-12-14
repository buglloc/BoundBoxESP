#include "stream.h"
#include "libssh_esp.h"

namespace XSSH
{
  int ChanReader::read()
  {
    if (ssh_channel_is_eof(chan)) {
      return 0;
    }

    char buf;
    if (readBytes(&buf, 1) == 1) {
      return buf;
    }

    return -1;
  }

  size_t ChanReader::readBytes(char* buffer, size_t length)
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

  size_t ChanWriter::write(uint8_t b)
  {
    if (size + 1 >= BUF_SIZE && !flush()) {
      return 0;
    }

    buffer[size++] = b;
    return 1;
  }

  size_t ChanWriter::write(const uint8_t* bytes, size_t length)
  {
    if (!ssh_channel_is_open(chan)) {
      return 0;
    }

    for (size_t i = 0; i < length; i++) {
      if (write(bytes[i]) != 1) {
        return i;
      }
    }

    return length;
  }

  bool ChanWriter::flush() {
    if (size == 0) {
      return true;
    }

    if (!ssh_channel_is_open(chan)) {
      return false;
    }

    int rc = 0;
    do {
      rc = ssh_channel_write(chan, buffer, size);
    } while (rc == SSH_AGAIN);

    if (rc > 0) {
      size = 0;
      return true;
    }

    return false;
  }
}
