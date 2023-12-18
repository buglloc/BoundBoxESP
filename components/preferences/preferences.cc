#include "preferences.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_system.h>
#include <esp_check.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <nvs.h>

#define RETURN_ON_ERROR(x, err, format, ...) do {                                  \
    esp_err_t err_rc_ = (x);                                                       \
    if (unlikely(err_rc_ != ESP_OK)) {                                             \
      ESP_LOGE(TAG, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);     \
      return err;                                                                  \
    }                                                                              \
  } while(0)

namespace
{
  static const char* TAG = "preferences";
}

Preferences::Error Preferences::Open(const std::string_view name)
{
  if (opened) {
    ESP_LOGW(TAG, "already opened");
    return Error::InvalidState;
  }

  const char* nvsName = name.empty() ? CONFIG_BB_PREF_NAMESPACE : name.cbegin();
  ESP_LOGI(TAG, "open NVS flash: %s", nvsName);

  esp_err_t err = nvs_flash_init();
  RETURN_ON_ERROR(err, Error::Internal, "nvs init failed");

  nvs = nvs::open_nvs_handle(nvsName, NVS_READWRITE, &err);
  RETURN_ON_ERROR(err, Error::Internal, "open nvs storage");

  opened = true;
  return Error::None;
}

Preferences::Error Preferences::Remove(const std::string_view name)
{
  if (!opened) {
    return Error::InvalidState;
  }

  if (name.empty()) {
    return Error::InvalidArg;
  }

  esp_err_t err = nvs->erase_item(name.cbegin());
  if (err == ESP_ERR_NVS_NOT_FOUND) {
    return Error::None;
  }
  RETURN_ON_ERROR(err, Error::Internal, "erase item");

  err = nvs->commit();
  RETURN_ON_ERROR(err, Error::Internal, "commit");

  return Error::None;
}

Preferences::Error Preferences::Erase()
{
  if (!opened) {
    return Error::InvalidState;
  }

  esp_err_t err = nvs->erase_all();
  RETURN_ON_ERROR(err, Error::Internal, "erase all");

  err = nvs->commit();
  RETURN_ON_ERROR(err, Error::Internal, "commit");

  return Error::None;
}

std::expected<Blob::Bytes, Preferences::Error> Preferences::GetBytes(const std::string_view key)
{
  if (!opened) {
    return std::unexpected<Error>{Error::InvalidState};
  }

  size_t size = 0;
  esp_err_t err = nvs->get_item_size(nvs::ItemType::BLOB, key.cbegin(), size);
  if (size == 0 || err == ESP_ERR_NVS_NOT_FOUND) {
    return std::unexpected<Error>{Error::NotExist};
  }

  Blob::Bytes out(size, '\xff');
  err = nvs->get_blob(key.cbegin(), out.data(), size);
  RETURN_ON_ERROR(err, std::unexpected<Error>{Error::Internal}, "get blob");

  return out;
}

Preferences::Error Preferences::StoreBytes(const std::string_view key, const Blob::Bytes& data)
{
  if (!opened) {
    return Error::InvalidState;
  }

  esp_err_t err = nvs->set_blob(key.cbegin(), (const void *)data.data(), data.size());
  RETURN_ON_ERROR(err, Error::Internal, "set blob");

  err = nvs->commit();
  RETURN_ON_ERROR(err, Error::Internal, "commit");

  return Error::None;
}

std::expected<std::string, Preferences::Error> Preferences::GetString(const std::string_view key)
{
  if (!opened) {
    return std::unexpected<Error>{Error::InvalidState};
  }

  size_t size = 0;
  esp_err_t err = nvs->get_item_size(nvs::ItemType::SZ, key.cbegin(), size);
  if (size == 0 || err == ESP_ERR_NVS_NOT_FOUND) {
    return std::unexpected<Error>{Error::NotExist};
  }

  std::string out(size, '\xff');
  err = nvs->get_string(key.cbegin(), out.data(), size);
  RETURN_ON_ERROR(err, std::unexpected<Error>{Error::Internal}, "get string");

  return out;
}

Preferences::Error Preferences::StoreString(const std::string_view key, const std::string_view data)
{
  if (!opened) {
    return Error::InvalidState;
  }

  esp_err_t err = nvs->set_string(key.cbegin(), data.cbegin());
  RETURN_ON_ERROR(err, Error::Internal, "set string");

  err = nvs->commit();
  RETURN_ON_ERROR(err, Error::Internal, "commit");

  return Error::None;
}

Preferences::~Preferences()
{
  if(!opened){
    return;
  }

  opened = false;
}
