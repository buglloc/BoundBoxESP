#pragma once

#define SPI_FREQUENCY         75000000
#define TFT_SPI_MODE          (0)
#define TFT_SPI_HOST          SPI2_HOST

#define TFT_WIDTH             536
#define TFT_HEIGHT            240
#define SEND_BUF_SIZE         (TFT_WIDTH * TFT_HEIGHT + 8) / 10

#define TFT_PIN_TE            GPIO_NUM_9
#define TFT_PIN_SDO           GPIO_NUM_8

#define TFT_PIN_DC            GPIO_NUM_7
#define TFT_PIN_RST           GPIO_NUM_17
#define TFT_PIN_CS            GPIO_NUM_6
#define TFT_PIN_MOSI          GPIO_NUM_18
#define TFT_PIN_SCK           GPIO_NUM_47

#define TFT_QSPI_CS           GPIO_NUM_6
#define TFT_QSPI_SCK          GPIO_NUM_47
#define TFT_QSPI_D0           GPIO_NUM_18
#define TFT_QSPI_D1           GPIO_NUM_7
#define TFT_QSPI_D2           GPIO_NUM_48
#define TFT_QSPI_D3           GPIO_NUM_5
#define TFT_QSPI_RST          GPIO_NUM_17

#define TFT_PIN_NONE          GPIO_NUM_NC

#define BACKLIGHT_PIN         GPIO_NUM_38

#define PIN_BUTTON_1          GPIO_NUM_0
#define PIN_BUTTON_2          GPIO_NUM_21

#define TOUCH_PIN_SDA         GPIO_NUM_3
#define TOUCH_PIN_SCL         GPIO_NUM_2
#define TOUCH_PIN_IRQ         GPIO_NUM_21
#define TOUCH_PIN_RST         GPIO_NUM_NC
#define TOUCH_I2C_NUM         I2C_NUM_0

#define LV_LCD_BUF_SIZE        (TFT_WIDTH * TFT_HEIGHT)
#define LV_TICK_PERIOD_MS      1
#define LV_TASK_STACK_DEPTH    4096*2
#define LV_TASK_PRIO           1
#define LV_TASK_CORE           1

#define HOME_BUTTON_X         600
#define HOME_BUTTON_Y         120

#define BATT_ADC_UNIT         ADC_UNIT_1
#define BATT_ADC_CHANNEL      ADC_CHANNEL_4
#define BATT_ADC_ATTEN        ADC_ATTEN_DB_11
#define BATT_ADC_WIDTH_BIT    ADC_BITWIDTH_12
#define BATT_ADC_DEF_VREF     1100
