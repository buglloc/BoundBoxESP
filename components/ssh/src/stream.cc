#include <sdkconfig.h>
#include "ssh/stream.h"

#include <freertos/FreeRTOS.h>

#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::stream";
}

int Stream::read()
{
  if (ssh_channel_is_eof(chan)) {
    return -1;
  }

  char buf;
  if (readBytes(&buf, 1) == 1) {
    return buf;
  }

  return -1;
}

size_t Stream::readBytes(char* buffer, size_t length)
{
  if (ssh_channel_is_eof(chan)) {
    return 0;
  }

  int rc = ssh_channel_poll_timeout(chan, CONFIG_SSH_STREAM_POLL_TIMEOUT, 0);
  if (rc <= 0) {
    // err or timeout or no data
    return 0;
  }

  do {
    rc = ssh_channel_read_timeout(chan, buffer, length, 0, CONFIG_SSH_STREAM_READ_TIMEOUT);
  } while (rc == SSH_AGAIN);
  return rc < 0 ? 0 : rc;
}

size_t Stream::write(uint8_t b)
{
  if (writeSize + 1 >= CONFIG_SSH_STREAM_BUFFER_SIZE && !flush()) {
    return 0;
  }

  writeBuf[writeSize++] = b;
  return 1;
}

size_t Stream::write(const uint8_t *buffer, size_t length)
{
  if (!ssh_channel_is_open(chan)) {
    return 0;
  }

  for (size_t i = 0; i < length; ++i) {
    if (write(buffer[i]) != 1) {
      return i;
    }
  }

  return length;
}

bool Stream::flush()
{
  if (writeSize == 0) {
    return true;
  }

  if (!ssh_channel_is_open(chan)) {
    return false;
  }

  int rc = ssh_channel_write(chan, writeBuf, writeSize);
  if (rc > 0) {
    writeSize = 0;
    return true;
  }

  ESP_LOGE(TAG, "stream write error: %d", rc);
  return false;
}
