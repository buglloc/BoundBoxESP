#include "lilygo/touch.h"
#include "board_config.h"

#include <functional>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <driver/i2c.h>

#include <esp_lcd_touch_cst816s.h>
#include <esp_system.h>
#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>
#include <esp_timer.h>


using namespace LilyGo;

namespace
{
  static const char* TAG = "lilygo::touch";
  static SemaphoreHandle_t xTouchMu;
}

esp_err_t TouchSensor::Initialize()
{
  esp_err_t ret;

  xTouchMu = xSemaphoreCreateBinary();
  if (xTouchMu == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "no mutex allocated");
  }

  ESP_LOGD(TAG, "Initializing");
  i2c_config_t i2c_conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = TOUCH_PIN_SDA,
    .scl_io_num = TOUCH_PIN_SCL,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master = {
      .clk_speed = 400000,
    },
  };

  ret = i2c_param_config(TOUCH_I2C_NUM, &i2c_conf);
  ESP_RETURN_ON_ERROR(ret, TAG, "configure i2c");

  ret = i2c_driver_install(TOUCH_I2C_NUM, i2c_conf.mode, 0, 0, 0);
  ESP_RETURN_ON_ERROR(ret, TAG, "install i2c driver");

  esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG();
  ret = esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)TOUCH_I2C_NUM, &tp_io_config, &tpIO);
  ESP_RETURN_ON_ERROR(ret, TAG, "create panel tp io");

  esp_lcd_touch_config_t tp_cfg = {
    .x_max = TFT_WIDTH,
    .y_max = TFT_HEIGHT,
    .rst_gpio_num = TOUCH_PIN_RST,
    .int_gpio_num = TOUCH_PIN_IRQ,
    .levels = {
      .reset = 0,
      .interrupt = 0,
    },
    .flags = {
      .swap_xy = 0,
      .mirror_x = 0,
      .mirror_y = 0,
    },
    .interrupt_callback = [](esp_lcd_touch_handle_t tp) -> void {
      BaseType_t xHigherPriorityTaskWoken = pdFALSE;
      xSemaphoreGiveFromISR(xTouchMu, &xHigherPriorityTaskWoken);
      if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
      }
    }
  };

  ret = esp_lcd_touch_new_i2c_cst816s(tpIO, &tp_cfg, &tp);
  ESP_RETURN_ON_ERROR(ret, TAG, "create panel tp");

  return ESP_OK;
}

bool TouchSensor::GetPoint(uint16_t& x, uint16_t& y)
{
  uint16_t xArray[1] = {0};
  uint16_t yArray[1] = {0};
  uint8_t cnts = 0;

  // Read data from touch controller into memory
  if (xSemaphoreTake(xTouchMu, 0) == pdTRUE) {
      esp_lcd_touch_read_data(tp);
  }

  // Get coordinates
  bool pressed = esp_lcd_touch_get_coordinates(tp, xArray, yArray, nullptr, &cnts, 1);
  pressed = pressed && cnts > 0;
  x = xArray[0];
  y = yArray[0];

  // TODO(buglloc): ???
  homePressed = pressed && x == HOME_BUTTON_X && y == HOME_BUTTON_Y;

  if (x > TFT_WIDTH) {
    x = 0;
  }

  if (y > TFT_HEIGHT) {
    y = 0;
  }

  return pressed && x && y;
}

bool TouchSensor::HomePressed() const
{
  return homePressed;
}
