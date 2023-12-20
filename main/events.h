#pragma once

#include <esp_event.h>


ESP_EVENT_DECLARE_BASE(UI_EVENTS);

enum {
    TIMER_EVENT_STARTED,
    TIMER_EVENT_EXPIRY,
    TIMER_EVENT_STOPPED
};