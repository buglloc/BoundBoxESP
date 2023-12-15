/* WOLFSSL_USER_SETTINGS is defined here only for the syntax highlighter
 * see CMakeLists.txt
#define WOLFSSL_USER_SETTINGS
 */

#include "sdkconfig.h"
#include "ssh_server_config.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_netif.h>
#include <esp_event.h>

#define WOLFSSL_ESPIDF
#define WOLFSSL_ESPWROOM32

#define WOLFSSL_TLS13
#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_ECC
#define HAVE_HKDF
#define HAVE_FFDHE_8192 /* or one of the other supported FFDHE sizes [2048, 3072, 4096, 6144, 8192] */
#define WC_RSA_PSS
#define WOLFSSH_TEST_THREADING

/*  note "file system": "load keys and certificate from files" vs NO_FILESYSTEM
 *  and "access an actual file system via SFTP/SCP" vs WOLFSSH_NO_FILESYSTEM
 *  we'll typically have neither on an embedded device:
 */
#define NO_FILESYSTEM
#define WOLFSSH_NO_FILESYSTEM

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/include/user_settings.h>

#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/ssl.h>

#include "ssh_server.h"

/* logging
 *
 * see
 *   https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/log.html
 *   https://github.com/wolfSSL/wolfssl/blob/master/wolfssl/wolfcrypt/logging.h
 */
#ifdef LOG_LOCAL_LEVEL
    #undef LOG_LOCAL_LEVEL
#endif
#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

static const char *TAG = "SSH Server main";

/* 10 seconds, used for heartbeat message in thread */
static TickType_t DelayTicks = (10000 / portTICK_PERIOD_MS);


/*
 * main initialization for UART, optional ethernet, time, etc.
 */
void init()
{
    TickType_t EthernetWaitDelayTicks = (1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "Begin main init.");




    while (NoEthernet()) {
        ESP_LOGI(TAG,"Waiting for ethernet...");
        vTaskDelay(EthernetWaitDelayTicks ? EthernetWaitDelayTicks : 1);
    }

    wolfSSH_Init();
}

void server_session(void* args)
{
    while (1) {
        server_test(args);
        vTaskDelay(DelayTicks ? DelayTicks : 1); /* Minimum delay = 1 tick */
    }
}

void app_main(void)
{
    init();

    xTaskCreate(server_session, "server_session", 6024 * 4, NULL,
                tskIDLE_PRIORITY, NULL);

    for (;;) {
        /* we're not actually doing anything here, other than a heartbeat message */
        ESP_LOGI(TAG,"wolfSSH Server main loop heartbeat!");

        taskYIELD();
        vTaskDelay(DelayTicks ? DelayTicks : 1); /* Minimum delay = 1 tick */
    }

    /* TODO this is unreachable with RTOS threads, do we ever want to shut down? */
    wolfSSH_Cleanup();
}
