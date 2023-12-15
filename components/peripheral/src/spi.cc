#include "peripheral/spi.h"
#include "peripheral_config.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_log.h>
#include <esp_check.h>


using namespace Peripheral;


esp_err_t Spi::Initialize()
{
  esp_err_t ret = ESP_OK;

  // Install GPIO ISR handler to be able to service SPI interrupts
  ret = gpio_install_isr_service(0);
  if (ret == ESP_ERR_INVALID_STATE) {
    ESP_LOGW(TAG, "GPIO ISR handler has been already installed");
    ret = ESP_OK; // ISR handler has been already installed so no issues
  }
  ESP_RETURN_ON_ERROR(ret, TAG, "GPIO ISR handler install failed");

  // Init SPI bus
  spi_bus_config_t buscfg = {
    .miso_io_num = PSPI_MISO_GPIO,
    .mosi_io_num = PSPI_MOSI_GPIO,
    .sclk_io_num = PSPI_SCLK_GPIO,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
  };

  ret = spi_bus_initialize(PSPI_HOST_ID, &buscfg, SPI_DMA_CH_AUTO);
  ESP_RETURN_ON_ERROR(ret, TAG, "SPI host #%d init failed", PSPI_HOST_ID);

  return ESP_OK;
}
