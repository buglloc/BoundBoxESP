#include "t_amoled/display.h"
#include "board_config.h"

#include <cstring>
#include <assert.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/spi_master.h>
#include <driver/gpio.h>

#include <esp_log.h>
#include <esp_check.h>
#include <esp_timer.h>


#define LOW         0x0
#define HIGH        0x1

#define SET_PIN_LEVEL(pin, level) do{gpio_set_level(pin, level);}while(0)

#define SET_TFT_SCK(level) SET_PIN_LEVEL(TFT_PIN_SCK, level)
#define SET_TFT_SDA(level) SET_PIN_LEVEL(TFT_PIN_SDA, level)
#define SET_TFT_RST(level) SET_PIN_LEVEL(TFT_PIN_RST, level)
#define SET_TFT_DC(level)  SET_PIN_LEVEL(TFT_PIN_DC, level)
#define SET_TFT_CS(level)  SET_PIN_LEVEL(TFT_PIN_CS, level)

using namespace Amoled;

namespace
{
  static const char* TAG = "amoled::display";

  const static LCDCommand kRM67162Init[] = {
    {0x11, {0x00}, 0x00}, // Sleep Out
    // {0x44, {0x01, 0x66}, 0x02}, //Set_Tear_Scanline
    // {0x35, {0x00}, 0x00}, //TE ON
    // {0x34, {0x00}, 0x00}, //TE OFF
    // {0x36, {0x00}, 0x01}, //Scan Direction Control
    {0x3A, {0x55}, 0x01}, // Interface Pixel Format 16bit/pixel
    // {0x3A, {0x66}, 0x01}, //Interface Pixel Format 18bit/pixel
    // {0x3A, {0x77}, 0x01}, //Interface Pixel Format 24bit/pixel
    {0x51, {0x00}, 0x01}, // Write Display Brightness MAX_VAL=0xFF
    {0x29, {0x00}, 0x00}, // Display on
    {0x51, {AMOLED_DEFAULT_BRIGHTNESS}, 0x01}, // Write Display Brightness   MAX_VAL=0xFF
    {0x36, {0x60}, 0x01}, // ??
  };
}

esp_err_t Display::Initialize()
{
  ESP_LOGD(TAG, "Initializing");
  gpio_set_direction(TFT_PIN_CS, GPIO_MODE_OUTPUT);
  gpio_set_direction(TFT_PIN_RST, GPIO_MODE_OUTPUT);
  gpio_set_direction(TFT_PIN_TE, GPIO_MODE_INPUT);

  gpio_set_direction(BACKLIGHT_PIN, GPIO_MODE_OUTPUT);
  gpio_set_level(BACKLIGHT_PIN, HIGH);

  // reset display
  SET_TFT_RST(HIGH);
  vTaskDelay(200 / portTICK_PERIOD_MS);
  SET_TFT_RST(LOW);
  vTaskDelay(300 / portTICK_PERIOD_MS);
  SET_TFT_RST(HIGH);
  vTaskDelay(200 / portTICK_PERIOD_MS);

  spi_bus_config_t buscfg = {
    .data0_io_num = TFT_QSPI_D0,
    .data1_io_num = TFT_QSPI_D1,
    .sclk_io_num = TFT_QSPI_SCK,
    .data2_io_num = TFT_QSPI_D2,
    .data3_io_num = TFT_QSPI_D3,
    .data4_io_num = TFT_PIN_NONE,
    .data5_io_num = TFT_PIN_NONE,
    .data6_io_num = TFT_PIN_NONE,
    .data7_io_num = TFT_PIN_NONE,
    .max_transfer_sz = (SEND_BUF_SIZE * 16) + 8,
    .flags = SPICOMMON_BUSFLAG_MASTER | SPICOMMON_BUSFLAG_GPIO_PINS | SPICOMMON_BUSFLAG_QUAD
  };

  spi_device_interface_config_t devcfg = {
    .command_bits = 8,
    .address_bits = 24,
    .mode = TFT_SPI_MODE,
    .clock_speed_hz = SPI_FREQUENCY,
    .spics_io_num = -1,
    .flags = SPI_DEVICE_HALFDUPLEX,
    .queue_size = 17,
  };

  ESP_RETURN_ON_ERROR(spi_bus_initialize(TFT_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO), TAG, "spi inialization");
  ESP_RETURN_ON_ERROR(spi_bus_add_device(TFT_SPI_HOST, &devcfg, &spi), TAG, "spi add device");

  // Initialize the screen multiple times to prevent initialization failure
  esp_err_t cmdRet;
  for (uint8_t i = 0; i < 3; ++i) {
    const LCDCommand* lcd_init = kRM67162Init;
    for (int i = 0; i < sizeof(kRM67162Init) / sizeof(LCDCommand); ++i) {
      cmdRet = WriteCommand(lcd_init[i]);
      if (cmdRet != ESP_OK) {
        ESP_LOGE(TAG, "initialization: write command %d failed", lcd_init[i].Addr);
        vTaskDelay(120 / portTICK_PERIOD_MS);
        continue;
      }

      if (lcd_init[i].Size == 0) {
        // ???
        vTaskDelay(120 / portTICK_PERIOD_MS);
      }
    }
  }

  lastBrightness = AMOLED_DEFAULT_BRIGHTNESS;
  return cmdRet;
}

uint8_t Display::Brightness() const
{
  return lastBrightness;
}

esp_err_t Display::SetBrightness(uint8_t level)
{
  lastBrightness = level;
  return WriteCommand({0x51, {level}, 0x01});
}

esp_err_t Display::PushColors(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t* data)
{
  esp_err_t ret = SetAddrWindow(x, y, x + w - 1, y + h - 1);
  if (ret != ESP_OK) {
    return ret;
  }

  return PushColors(data, w * h);
}

esp_err_t Display::PushColors(uint16_t* data, uint32_t size)
{
  bool started = false;
  esp_err_t ret = ESP_OK;
  uint16_t *p = data;
  assert(p);

  SET_TFT_CS(LOW);

  do {
      size_t chunk_size = size;
      spi_transaction_ext_t t = {0};
      memset(&t, 0, sizeof(t));

      if (!started) {
          t.base.flags = SPI_TRANS_MODE_QIO;
          t.base.cmd = 0x32 ;
          t.base.addr = 0x002C00;
          started = true;
      } else {
          t.base.flags = SPI_TRANS_MODE_QIO | SPI_TRANS_VARIABLE_CMD | SPI_TRANS_VARIABLE_ADDR | SPI_TRANS_VARIABLE_DUMMY;
          t.command_bits = 0;
          t.address_bits = 0;
          t.dummy_bits = 0;
      }

      if (chunk_size > SEND_BUF_SIZE) {
          chunk_size = SEND_BUF_SIZE;
      }

      t.base.tx_buffer = p;
      t.base.length = chunk_size * 16;
      ret = spi_device_polling_transmit(spi, reinterpret_cast<spi_transaction_t *>(&t));
      size -= chunk_size;
      p += chunk_size;
  } while (size > 0 && ret == ESP_OK);

  SET_TFT_CS(HIGH);
  return ret;
}

esp_err_t Display::Sleep()
{
  return WriteCommand({0x10, {0x00}, 0x00});
}

esp_err_t Display::Wakeup()
{
  return WriteCommand({0x11, {0x00}, 0x01});
}

esp_err_t Display::WriteCommand(const LCDCommand& cmd)
{
  SET_TFT_CS(LOW);

  spi_transaction_t t;
  memset(&t, 0, sizeof(t));
  t.flags = (SPI_TRANS_MULTILINE_CMD | SPI_TRANS_MULTILINE_ADDR);
  t.cmd = 0x02;
  t.addr = (uint32_t)cmd.Addr << 8;

  if (cmd.Size > 0) {
    t.tx_buffer = reinterpret_cast<const uint8_t *>(cmd.Data);
    t.length = 8 * cmd.Size;
  } else {
    t.tx_buffer = nullptr;
    t.length = 0;
  }
  esp_err_t ret = spi_device_polling_transmit(spi, &t);

  SET_TFT_CS(HIGH);
  return ret;
}

esp_err_t Display::SetAddrWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
  esp_err_t ret;
  ret = WriteCommand({
    0x2A, {
      (uint8_t)((xs >> 8) & 0xFF),
      (uint8_t)(xs & 0xFF),
      (uint8_t)((xe >> 8) & 0xFF),
      (uint8_t)(xe & 0xFF)
    },
    0x04
  });
  ESP_RETURN_ON_ERROR(ret, TAG, "set 0x2A addr");

  ret = WriteCommand({
    0x2B, {
      (uint8_t)((ys >> 8) & 0xFF),
      (uint8_t)(ys & 0xFF),
      (uint8_t)((ye >> 8) & 0xFF),
      (uint8_t)(ye & 0xFF)
    },
    0x04
  });
  ESP_RETURN_ON_ERROR(ret, TAG, "set 0x2B addr");

  ret = WriteCommand({
    0x2C,
    {0x00},
    0x00
  });
  ESP_RETURN_ON_ERROR(ret, TAG, "set 0x2C addr");

  return ESP_OK;
}
