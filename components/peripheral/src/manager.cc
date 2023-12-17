#include <sdkconfig.h>
#include "peripheral/manager.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_event.h>
#include <esp_check.h>
#include <esp_log.h>
#include <nvs_flash.h>


#define ESP_INTR_FLAG_DEFAULT 0
#define BBP_SPI_HOSTID NeedTooChooseSpiHost
#ifdef CONFIG_BBP_USE_SPI2_HOST
  #undef BBP_SPI_HOSTID
  #define BBP_SPI_HOSTID SPI3_HOST
#endif
#ifdef CONFIG_BBP_USE_SPI3_HOST
  #undef BBP_SPI_HOSTID
  #define BBP_SPI_HOSTID SPI3_HOST
#endif

using namespace Peripheral;

namespace
{
  static const char* TAG = "peripheral";

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
      .mosi_io_num = CONFIG_BBP_SPI_MOSI_GPIO,
      .miso_io_num = CONFIG_BBP_SPI_MISO_GPIO,
      .sclk_io_num = CONFIG_BBP_SPI_SCLK_GPIO,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(BBP_SPI_HOSTID, &buscfg, SPI_DMA_CH_AUTO);
    ESP_RETURN_ON_ERROR(ret, TAG, "SPI host #%d init failed", BBP_SPI_HOSTID);

    return ESP_OK;
  }
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
