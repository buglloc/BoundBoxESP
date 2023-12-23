#pragma once

#include <esp_err.h>
#include <esp_types.h>
#include <esp_lcd_types.h>

#include <stdatomic.h>


// fwd
struct esp_lcd_touch_s;
typedef esp_lcd_touch_s* esp_lcd_touch_handle_t;
struct esp_lcd_panel_io_t;
typedef esp_lcd_panel_io_t* esp_lcd_panel_io_handle_t;

namespace Amoled
{
  class TouchSensor
  {
  public:
    TouchSensor() = default;
    esp_err_t Initialize();
    bool GetPoint(uint16_t& x, uint16_t& y);
    bool HomePressed() const;

  private:
    atomic_bool homePressed;
    esp_lcd_touch_handle_t tp = nullptr;
    esp_lcd_panel_io_handle_t tpIO = nullptr;
  };
}
