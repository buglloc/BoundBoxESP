#include "peripheral/spi.h"
#include "peripheral_config.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <esp_log.h>
#include <esp_check.h>


using namespace Peripheral;


esp_err_t Spi::Initialize()
{
  // Init SPI bus
  spi_bus_config_t buscfg = {
    .miso_io_num = PSPI_MISO_GPIO,
    .mosi_io_num = PSPI_MOSI_GPIO,
    .sclk_io_num = PSPI_SCLK_GPIO,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
  };

  esp_err_t ret = spi_bus_initialize(PSPI_HOST_ID, &buscfg, SPI_DMA_CH_AUTO);
  ESP_RETURN_ON_ERROR(ret, TAG, "SPI host #%d init failed", PSPI_HOST_ID);

  return ESP_OK;
}
