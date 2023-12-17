#include "ssh/stream.h"

#include <freertos/FreeRTOS.h>

#include <wolfssh/ssh.h>
#include <lwip/sockets.h>

#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::stream";
}

int Stream::read()
{
  char b;
  return readBytes(&b, 1);
}

size_t Stream::readBytes(char* buffer, size_t length)
{
  int rc;
  int sshFd = wolfSSH_get_fd(ssh);
  do {
    int error = 0;
    socklen_t len = sizeof(error);
    rc = getsockopt(sshFd, SOL_SOCKET, SO_ERROR, &error, &len);
    if (rc != 0) {
        // if we can't even call getsockopt, give up
        ESP_LOGE(TAG, "unable to query socket fd: %d", rc);
        return 0;
    }

    if (error != 0) {
        // socket has a non zero error status
        ESP_LOGE(TAG, "getsockopt returned error: %d", rc);
        return 0;
    }

    rc = wolfSSH_stream_read(ssh, (uint8_t *)buffer, length);
    if (rc <= 0) {
      rc = wolfSSH_get_error(ssh);
      if (rc != WS_WANT_READ && rc != WS_WANT_WRITE) {
        ESP_LOGE(TAG, "stream read error: %d", rc);
        return 0;
      }

      // no data, just wait
      taskYIELD();
    }
  } while (nonBlock);

  return static_cast<size_t>(rc);
}

size_t Stream::write(uint8_t b)
{
  if (writeSize + 1 >= SSH_BUFFER_SIZE && !flush()) {
    return 0;
  }

  writeBuf[writeSize++] = b;
  return 1;
}

size_t Stream::write(const uint8_t *buffer, size_t length)
{
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

  int rc = wolfSSH_stream_send(ssh, writeBuf, writeSize);
  if (rc > 0) {
    writeSize = 0;
    return true;
  }

  ESP_LOGE(TAG, "stream write error: %d", rc);
  return false;
}
