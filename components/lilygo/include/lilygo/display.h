#pragma once
#include <stdint.h>

#include <driver/spi_master.h>

#include <esp_err.h>


#define AMOLED_DEFAULT_BRIGHTNESS 50


namespace LilyGo
{
  struct LCDCommand
  {
    uint8_t Addr;
    uint8_t Data[20];
    uint32_t Size;
  };

  class Display
  {
  public:
    Display() = default;
    esp_err_t Initialize();
    uint8_t Brightness() const;
    esp_err_t SetBrightness(uint8_t level);
    esp_err_t PushColors(uint16_t x, uint16_t y, uint16_t width, uint16_t high, uint16_t* data);
    esp_err_t PushColors(uint16_t* data, uint32_t size);
    esp_err_t Sleep();
    esp_err_t Wakeup();

  private:
    esp_err_t WriteCommand(const LCDCommand& cmd);
    esp_err_t SetAddrWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);

  private:
    spi_device_handle_t spi;
    uint8_t lastBrightness;
  };
}
