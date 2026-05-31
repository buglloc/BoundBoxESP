#include "lilygo/touch.h"
#include "board_config.h"

#include <functional>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <driver/i2c_master.h>

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
  // signalled from the touch IRQ to notify GetPoint() that new data is available
  static SemaphoreHandle_t touchIrqSem;
}

esp_err_t TouchSensor::Initialize()
{
  esp_err_t ret;

  touchIrqSem = xSemaphoreCreateBinary();
  if (touchIrqSem == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "no IRQ semaphore allocated");
  }

  ESP_LOGD(TAG, "initializing");
  i2c_master_bus_config_t i2c_conf = {
    .i2c_port = TOUCH_I2C_NUM,
    .sda_io_num = TOUCH_PIN_SDA,
    .scl_io_num = TOUCH_PIN_SCL,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
    .trans_queue_depth = 0,
    .flags = {
      .enable_internal_pullup = 1,
    },
  };

  ret = i2c_new_master_bus(&i2c_conf, &i2cBus);
  ESP_RETURN_ON_ERROR(ret, TAG, "configure i2c");

  esp_lcd_panel_io_i2c_config_t tp_io_config = {};
  tp_io_config.dev_addr = ESP_LCD_TOUCH_IO_I2C_CST816S_ADDRESS;
  tp_io_config.control_phase_bytes = 1;
  tp_io_config.dc_bit_offset = 0;
  tp_io_config.lcd_cmd_bits = 8;
  tp_io_config.lcd_param_bits = 0;
  tp_io_config.flags.disable_control_phase = 1;
  tp_io_config.scl_speed_hz = 400000;
  ret = esp_lcd_new_panel_io_i2c(i2cBus, &tp_io_config, &tpIO);
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
      xSemaphoreGiveFromISR(touchIrqSem, &xHigherPriorityTaskWoken);
      if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
      }
    }
  };

  ret = esp_lcd_touch_new_i2c_cst816s(tpIO, &tp_cfg, &tp);
  ESP_RETURN_ON_ERROR(ret, TAG, "create panel tp");

  return ESP_OK;
}

TouchSensor::~TouchSensor()
{
  if (tp != nullptr) {
    esp_lcd_touch_del(tp);
    tp = nullptr;
  }

  if (tpIO != nullptr) {
    esp_lcd_panel_io_del(tpIO);
    tpIO = nullptr;
  }

  if (i2cBus != nullptr) {
    i2c_del_master_bus(i2cBus);
    i2cBus = nullptr;
  }
}

bool TouchSensor::GetPoint(uint16_t& x, uint16_t& y)
{
  esp_lcd_touch_point_data_t points[1] = {};
  uint8_t cnts = 0;

  // Read data from touch controller into memory
  if (xSemaphoreTake(touchIrqSem, 0) == pdTRUE) {
      esp_lcd_touch_read_data(tp);
  }

  // Get coordinates
  esp_err_t err = esp_lcd_touch_get_data(tp, points, &cnts, 1);
  bool pressed = err == ESP_OK && cnts > 0;
  x = points[0].x;
  y = points[0].y;

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
