#ifndef __WIFI_CONFIG_H
#define __WIFI_CONFIG_H

/* ============================================================
 * WiFi & Cloud Configuration — EDIT BEFORE COMPILING
 * ============================================================ */

#define WIFI_SSID       "ETHANYANDELL"
#define WIFI_PASSWORD   "1l1l1l1l"

#define CLOUD_HOST      "192.168.137.1"
#define CLOUD_PORT      8080

/* ESP-01S RST pin: PA1, active LOW */
#define ESP_RST_PORT    GPIOA
#define ESP_RST_PIN     GPIO_PIN_1

#endif
