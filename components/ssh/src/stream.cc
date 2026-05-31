#include <sdkconfig.h>
#include "ssh/stream.h"

#include <algorithm>
#include <cstring>

#include <freertos/FreeRTOS.h>

#include <esp_log.h>


using namespace SSH;

namespace
{
  static const char* TAG = "ssh::stream";
}

int Stream::read()
{
  if (readPos >= readSize) {
    readPos = 0;
    readSize = readBytes(reinterpret_cast<char *>(readBuf), sizeof(readBuf));
  }

  if (readPos >= readSize) {
    return -1;
  }

  return readBuf[readPos++];
}

size_t Stream::readBytes(char* buffer, size_t length)
{
  readTimedOut = false;
  readFailed = false;

  if (length == 0) {
    return 0;
  }

  if (readPos < readSize) {
    size_t buffered = std::min(length, readSize - readPos);
    std::copy(readBuf + readPos, readBuf + readPos + buffered, reinterpret_cast<uint8_t *>(buffer));
    readPos += buffered;
    return buffered;
  }

  if (ssh_channel_is_eof(chan)) {
    return 0;
  }

  int rc = ssh_channel_poll_timeout(chan, CONFIG_SSH_STREAM_POLL_TIMEOUT, 0);
  if (rc == SSH_ERROR) {
    readFailed = true;
    ESP_LOGE(TAG, "stream poll error");
    return 0;
  }
  if (rc == SSH_EOF) {
    return 0;
  }
  if (rc == 0) {
    readTimedOut = true;
    return 0;
  }

  rc = ssh_channel_read_timeout(chan, buffer, length, 0, CONFIG_SSH_STREAM_READ_TIMEOUT);
  if (rc == SSH_AGAIN) {
    readTimedOut = true;
    return 0;
  }
  if (rc < 0) {
    readFailed = true;
    ESP_LOGE(TAG, "stream read error: %d", rc);
    return 0;
  }

  return rc;
}

bool Stream::ReadTimedOut() const
{
  return readTimedOut;
}

bool Stream::ReadFailed() const
{
  return readFailed;
}

size_t Stream::write(uint8_t b)
{
  if (writeSize >= CONFIG_SSH_STREAM_WRITE_BUFFER_SIZE && !flush()) {
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

  size_t written = 0;
  while (written < length) {
    if (writeSize >= CONFIG_SSH_STREAM_WRITE_BUFFER_SIZE && !flush()) {
      return written;
    }

    size_t freeSpace = CONFIG_SSH_STREAM_WRITE_BUFFER_SIZE - writeSize;
    size_t chunk = std::min(freeSpace, length - written);
    std::memcpy(writeBuf + writeSize, buffer + written, chunk);
    writeSize += chunk;
    written += chunk;
  }

  return written;
}

bool Stream::flush()
{
  if (writeSize == 0) {
    return true;
  }

  if (!ssh_channel_is_open(chan)) {
    return false;
  }

  size_t written = 0;
  while (written < writeSize) {
    int rc = ssh_channel_write(chan, writeBuf + written, writeSize - written);
    if (rc <= 0) {
      ESP_LOGE(TAG, "stream write error: %d", rc);
      if (written > 0) {
        writeSize -= written;
        std::copy(writeBuf + written, writeBuf + written + writeSize, writeBuf);
      }
      return false;
    }

    written += rc;
  }

  writeSize = 0;
  return true;
}
