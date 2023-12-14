#include "t_amoled/board.h"
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

#include <lvgl.h>


using namespace Amoled;

namespace
{
  static const char* TAG = "amoled_board";
  static const char* LV_TAG = "amoled_lvgl";

  static SemaphoreHandle_t xGuiMu;
  static bool initialized = false;
  static lv_disp_draw_buf_t dispBuf; // Internal graphic buffer(s) called draw buffer(s)
  static lv_disp_drv_t dispDrv;      // Display driver (LCD)
  static lv_indev_drv_t inDevDrv;    // Input device driver (Touch)

  static void lvGuiTask(void *arg)
  {
    ESP_LOGI(LV_TAG, "Starting LVGL task");
    uint32_t taskDelayMS = 0;
    while (1)
    {
      taskDelayMS = 0;
      if (xSemaphoreTake(xGuiMu, portMAX_DELAY) == pdTRUE) {
        taskDelayMS = lv_task_handler();
        xSemaphoreGive(xGuiMu);
      }

      if (taskDelayMS > 500) {
        taskDelayMS = 500;
      } else if (taskDelayMS < 10) {
        taskDelayMS = 10;
      }

      vTaskDelay(pdMS_TO_TICKS(taskDelayMS));
    }
  }
}

esp_err_t Board::Initialize()
{
  if (initialized) {
    return ESP_OK;
  }

  ESP_RETURN_ON_ERROR(display.Initialize(), "amoled_board", "could't initialize display");
  ESP_RETURN_ON_ERROR(ts.Initialize(), "amoled_board", "could't initialize touch sensor");
  initialized = true;
  return ESP_OK;
}

esp_err_t Board::InitializeLVGL()
{
  esp_err_t ret;
  ret = Initialize();
  ESP_RETURN_ON_ERROR(ret, TAG, "board initialize");

  xGuiMu = xSemaphoreCreateMutex();
  if (xGuiMu == nullptr) {
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
  lv_color_t* buf = reinterpret_cast<lv_color_t *>(heap_caps_malloc(LV_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA));
  assert(buf);
  lv_disp_draw_buf_init(&dispBuf, buf, nullptr, LV_LCD_BUF_SIZE);

  lv_disp_drv_init(&dispDrv);
  dispDrv.hor_res = TFT_WIDTH;
  dispDrv.ver_res = TFT_HEIGHT;
  dispDrv.full_refresh = 1;
  dispDrv.draw_buf = &dispBuf;

  dispDrv.user_data = &display;
  dispDrv.flush_cb = [](lv_disp_drv_t* dispDrv, const lv_area_t* area, lv_color_t* colorP) -> void {
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
    static_cast<Display *>(dispDrv->user_data)->PushColors(area->x1, area->y1, w, h, reinterpret_cast<uint16_t *>(colorP));
    lv_disp_flush_ready(dispDrv);
  };

  lv_disp_t* lvDisplay = lv_disp_drv_register(&dispDrv);
  if (lvDisplay == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "register lvgl driver");
  }

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

  lv_indev_drv_init(&inDevDrv);
  inDevDrv.type = LV_INDEV_TYPE_POINTER;
  inDevDrv.disp = lvDisplay;
  inDevDrv.user_data = &ts;
  inDevDrv.read_cb = [](lv_indev_drv_t *drv, lv_indev_data_t *data) -> void {
    uint16_t x, y = 0;
    bool pressed = static_cast<TouchSensor *>(drv->user_data)->GetPoint(x, y);

    data->point.x = x;
    data->point.y = y;
    data->state = pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  };

  lv_indev_t* inDevTouchpad = lv_indev_drv_register(&inDevDrv);
  if (inDevTouchpad == nullptr) {
    ret = ESP_ERR_NO_MEM;
    ESP_RETURN_ON_ERROR(ret, TAG, "register lvgl indev driver");
  }

  xTaskCreatePinnedToCore(lvGuiTask, "lvgl gui task", LV_TASK_STACK_DEPTH, nullptr, LV_TASK_PRIO, nullptr, LV_TASK_CORE);
  return ESP_OK;
}
