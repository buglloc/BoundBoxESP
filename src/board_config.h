#ifndef BB_BOARD_CONFIG_H
#define BB_BOARD_CONFIG_H

#include "defaults.h"

#define SERIAL_BAUD 115200
#define REQ_RSP_CAPACITY 16384

// SPI config
#define SPI_MOSI_PIN 11
#define SPI_SCK_PIN 12
#define SPI_MISO_PIN 13

#define BOOT_DELAY 1000

#ifdef LILYGO_TDISPLAY_AMOLED_SERIES

#define DISPLAY_BRIGHTNESS 100

// Network config
// #define NET_HAVE_ETHERNET 1
#define NET_ETHERNET_SS_PIN 10

#define NET_HAVE_WIFI 1
#define NET_WIFI_CONNECT_TIMEOUT 10
// End of network config

// Intrusion Detection System config
// #define HAVE_IDR 1
#define IDR_CASE_OPENED_PIN 45
#define IDR_CASE_OPENED_MODE INPUT_PULLUP
// End of intruder config

// Log store config
// #define HAVE_SD_CARD 1
#define SD_CARD_SS_PIN 14
// End of log store config
#else
// Network config
// #define NET_HAVE_ETHERNET 1
#define NET_ETHERNET_SS_PIN 10

#define NET_HAVE_WIFI 1
#define NET_WIFI_CONNECT_TIMEOUT 10
// End of network config

// Intrusion Detection System config
#define HAVE_IDR 1
#define IDR_CASE_OPENED_PIN 45
#define IDR_CASE_OPENED_MODE INPUT_PULLUP
// End of intruder config

// Log store config
// #define HAVE_SD_CARD 1
#define SD_CARD_SS_PIN 14
// End of log store config
#endif

#endif
