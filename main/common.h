#pragma once

#include <esp_err.h>
#include <esp_log.h>

#include <hardware/manager.h>


#define ESP_SHUTDOWN_ON_ERROR(x, log_tag, format, ...) do {                             \
  esp_err_t err_rc_ = (x);                                                              \
  if (unlikely(err_rc_ != ESP_OK)) {                                                    \
    ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
    Hardware::Manager::Instance().Board().Shutdown();                                   \
  }                                                                                     \
} while(0)

#define TRUE_OR_SHUTDOWN(x, log_tag, format, ...) do {                                  \
  if (unlikely(!(x))) {                                                                 \
    ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
    Hardware::Manager::Instance().Board().Shutdown();                                   \
  }                                                                                     \
} while(0)
