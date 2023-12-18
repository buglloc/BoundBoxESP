#include "config.h"
#include "hardware/manager.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_event.h>
#include <esp_check.h>
#include <esp_log.h>
#include <nvs_flash.h>


using namespace Hardware;

namespace
{
  static const char* TAG = "hardware";

  esp_err_t initISR()
  {
    return gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  }

  esp_err_t initNVS()
  {
    // Initialize NVS partition
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_LOGW(TAG, "NVS partition was truncated and needs to be erased");
      ESP_RETURN_ON_ERROR(nvs_flash_erase(), TAG, "nvs flash erase");
      ret = nvs_flash_init();
    }

    return ret;
  }

  esp_err_t initSPI()
  {
    // Init SPI bus
    spi_bus_config_t buscfg = {
      .mosi_io_num = CONFIG_BBHW_SPI_MOSI_GPIO,
      .miso_io_num = CONFIG_BBHW_SPI_MISO_GPIO,
      .sclk_io_num = CONFIG_BBHW_SPI_SCLK_GPIO,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(BBHW_SPI_HOSTID, &buscfg, SPI_DMA_CH_AUTO);
    ESP_RETURN_ON_ERROR(ret, TAG, "SPI host #%d init failed", BBHW_SPI_HOSTID);

    return ESP_OK;
  }
}

Manager& Manager::Instance()
{
  static Manager instance;
  return instance;
}

esp_err_t Manager::Initialize()
{
  if (initialized) {
    ESP_LOGW(TAG, "already initialized");
    return ESP_OK;
  }

  // required for gpio, spi interrupts and so on
  ESP_LOGI(TAG, "setup ISR service");
  ESP_RETURN_ON_ERROR(initISR(), TAG, "failed to initialize ISR");

  ESP_LOGI(TAG, "setup NVS");
  ESP_RETURN_ON_ERROR(initNVS(), TAG, "failed to initialize NVS");

  ESP_LOGI(TAG, "create event loop");
  ESP_RETURN_ON_ERROR(esp_event_loop_create_default(), TAG, "failed to initialize default event loop");

  ESP_LOGI(TAG, "setup board");
  // ESP_RETURN_ON_ERROR(board.Initialize(), TAG, "failed to initialize T-Amoled board");

  ESP_LOGI(TAG, "setup SPI");
  ESP_RETURN_ON_ERROR(initSPI(), TAG, "failed to initialize SPI");

  ESP_LOGI(TAG, "setup network");
  ESP_RETURN_ON_ERROR(net.Initialize(), TAG, "failed to initialize Network");

  initialized = true;
  return ESP_OK;
}
