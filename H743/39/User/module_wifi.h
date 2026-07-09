#ifndef __MODULE_WIFI_H
#define __MODULE_WIFI_H

#include "./SYSTEM/sys/sys.h"

uint8_t wifi_init(void);
uint8_t wifi_send_at(const char *cmd, const char *expect, uint32_t timeout_ms);
uint8_t wifi_connect_ap(void);
uint8_t wifi_tcp_connect(void);
void    wifi_enter_transparent(void);
void    wifi_exit_transparent(void);
uint8_t wifi_self_test(void);

/* Called after entering transparent mode: all USART2 data goes to WiFi */
void    wifi_send_raw(const uint8_t *data, uint32_t len);

#endif
