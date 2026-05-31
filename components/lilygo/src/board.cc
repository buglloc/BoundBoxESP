#include "lilygo/board.h"
#include "board_config.h"

#include <functional>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>
#include <esp_heap_caps.h>
#include <esp_timer.h>
#include <esp_sleep.h>

#include <lvgl.h>


using namespace LilyGo;

namespace
{
  static const char* TAG = "lilygo::board";
  static const char* LV_TAG = "lilygo::lvgl";

  static bool initialized = false;

  void lvGuiTask(void *arg)
  {
    ESP_LOGI(LV_TAG, "starting LVGL task");
    uint32_t taskDelayMS = 0;
    Board* board = reinterpret_cast<Board *>(arg);
    for (;;)
    {
      taskDelayMS = 0;
      if (board->GuiLock()) {
        taskDelayMS = lv_timer_handler();
        board->GuiUnlock();
      }

      if (taskDelayMS > 500) {
        taskDelayMS = 500;
      } else if (taskDelayMS < 5) {
        taskDelayMS = 5;
      }

      vTaskDelay(pdMS_TO_TICKS(taskDelayMS));
    }
  }
}

esp_err_t Board::Initialize()
{
  if (initialized) {
    ESP_LOGW(TAG, "already initialized");
    return ESP_OK;
  }

  ESP_LOGI(TAG, "setup display");
  ESP_RETURN_ON_ERROR(display.Initialize(), TAG, "could't initialize display");

  ESP_LOGI(TAG, "setup touch sensor");
  ESP_RETURN_ON_ERROR(touchSensor.Initialize(), TAG, "could't initialize touch sensor");

  ESP_LOGI(TAG, "setup temp sensor");
  ESP_RETURN_ON_ERROR(tempSensor.Initialize(), TAG, "could't initialize temp sensor");

  ESP_LOGI(TAG, "setup baterry controller");
  ESP_RETURN_ON_ERROR(batteryController.Initialize(), TAG, "could't initialize baterry controller");

  initialized = true;
  return ESP_OK;
}

bool Board::GuiLock()
{
  return xSemaphoreTake(guiMu, portMAX_DELAY) == pdTRUE;
}

void Board::GuiUnlock()
{
  xSemaphoreGive(guiMu);
}


esp_err_t Board::InitializeLVGL()
{
  esp_err_t ret;
  guiMu = xSemaphoreCreateMutex();
  if (guiMu == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "no mutex allocated");
  }

  lv_init();

  #if LV_USE_LOG
    lv_log_register_print_cb([](const char* buf) -> void {
      ESP_LOGI(LV_TAG, "%s", buf);
    });
  #endif

  // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
  lv_color_t* buf1 = reinterpret_cast<lv_color_t *>(heap_caps_malloc(LV_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
  assert(buf1);
  lv_color_t* buf2 = reinterpret_cast<lv_color_t *>(heap_caps_malloc(LV_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
  assert(buf2);
  lv_display_t* lvDisplay = lv_display_create(TFT_WIDTH, TFT_HEIGHT);
  if (lvDisplay == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "create lvgl display");
  }

  lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565_SWAPPED);
  lv_display_set_buffers(lvDisplay, buf1, buf2, LV_LCD_BUF_SIZE * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_user_data(lvDisplay, &display);
  lv_display_set_flush_cb(lvDisplay, [](lv_display_t* disp, const lv_area_t* area, uint8_t* pxMap) -> void {
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
    static_cast<LilyGo::Display *>(lv_display_get_user_data(disp))->PushColors(area->x1, area->y1, w, h, reinterpret_cast<uint16_t *>(pxMap));
    lv_display_flush_ready(disp);
  });

  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
    .callback = [](void *arg) -> void {
      (void) arg;
      lv_tick_inc(LV_TICK_PERIOD_MS);
    },
    .name = "lvgl_tick",
  };
  esp_timer_handle_t periodic_timer;
  ret = esp_timer_create(&periodic_timer_args, &periodic_timer);
  ESP_RETURN_ON_ERROR(ret, TAG, "create lvgl_tick timer");

  ret = esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000);
  ESP_RETURN_ON_ERROR(ret, TAG, "start lvgl_tick timer");

  lv_indev_t* inDevTouchpad = lv_indev_create();
  if (inDevTouchpad == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "create lvgl indev");
  }

  lv_indev_set_type(inDevTouchpad, LV_INDEV_TYPE_POINTER);
  lv_indev_set_display(inDevTouchpad, lvDisplay);
  lv_indev_set_user_data(inDevTouchpad, &touchSensor);
  lv_indev_set_read_cb(inDevTouchpad, [](lv_indev_t *indev, lv_indev_data_t *data) -> void {
    uint16_t x = 0;
    uint16_t y = 0;
    bool pressed = static_cast<LilyGo::TouchSensor *>(lv_indev_get_user_data(indev))->GetPoint(x, y);

    data->point.x = x;
    data->point.y = y;
    data->state = pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  });

  xTaskCreatePinnedToCore(lvGuiTask, "lvgl gui task", LV_TASK_STACK_DEPTH, this, LV_TASK_PRIO, nullptr, LV_TASK_CORE);
  return ESP_OK;
}

void Board::Restart()
{
  esp_restart();
}

void Board::Shutdown()
{
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
  esp_deep_sleep_start();
}
