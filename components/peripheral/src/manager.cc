#include <sdkconfig.h>
#include "peripheral/manger.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_event.h>
#include <esp_check.h>
#include <esp_log.h>


#define ESP_INTR_FLAG_DEFAULT 0
// SPI1 used by touch screen
#define PSPI_HOST_ID SPI2_HOST

using namespace Peripheral;

namespace
{
  static const char* TAG = "peripheral";

  esp_err_t gpioInit()
  {
    return gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  }

  esp_err_t spiInit()
  {
    // Init SPI bus
    spi_bus_config_t buscfg = {
      .mosi_io_num = CONFIG_BBP_SPI_MOSI_GPIO,
      .miso_io_num = CONFIG_BBP_SPI_MISO_GPIO,
      .sclk_io_num = CONFIG_BBP_SPI_SCLK_GPIO,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(PSPI_HOST_ID, &buscfg, SPI_DMA_CH_AUTO);
    ESP_RETURN_ON_ERROR(ret, TAG, "SPI host #%d init failed", PSPI_HOST_ID);

    return ESP_OK;
  }
}

esp_err_t Manager::Initialize()
{
  if (initialized) {
    ESP_LOGW(TAG, "already initialized");
    return ESP_OK;
  }

  ESP_LOGI(TAG, "create event loop");
  ESP_RETURN_ON_ERROR(esp_event_loop_create_default(), TAG, "failed to initialize default event loop");

  // required for gpio, spi interrupts and so on
  ESP_LOGI(TAG, "setup ISR service");
  ESP_RETURN_ON_ERROR(gpioInit(), TAG, "failed to initialize default event loop");

  ESP_LOGI(TAG, "setup board");
  // ESP_RETURN_ON_ERROR(board.Initialize(), TAG, "failed to initialize T-Amoled board");

  ESP_LOGI(TAG, "setup SPI");
  ESP_RETURN_ON_ERROR(spiInit(), TAG, "failed to initialize SPI");

  ESP_LOGI(TAG, "setup network");
  NetConfig netCfg;
  ESP_RETURN_ON_ERROR(net.Initialize(netCfg), TAG, "failed to initialize Network");

  initialized = true;
  return ESP_OK;
}
