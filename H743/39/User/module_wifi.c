#include "module_wifi.h"
#include "wifi_config.h"
#include "./BSP/USART2/usart2.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include <string.h>
#include <stdio.h>

/* External USART2 handle from usart2.c */
extern UART_HandleTypeDef g_uart2_handle;

/* Current baud rate */
static uint32_t wifi_baud = 115200;

/* Debug: enable to see ESP-01S raw responses on USART1 */
#define WIFI_ECHO
#ifdef WIFI_ECHO
#define WIFI_LOG_RESP(buf) printf("[WiFi] << %s", buf)
#else
#define WIFI_LOG_RESP(buf) do{}while(0)
#endif

/* ================================================================
 * Hardware control
 * ================================================================ */

/**
 * @brief  Hardware reset ESP-01S via PA1
 *         PA1 = LOW (100ms) -> HIGH -> wait for module ready (~2s)
 */
static void wifi_hw_reset(void)
{
    GPIO_InitTypeDef gpio = {0};

    /* Configure PA1 as push-pull output */
    gpio.Pin = ESP_RST_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ESP_RST_PORT, &gpio);

    /* Pulse RST low */
    HAL_GPIO_WritePin(ESP_RST_PORT, ESP_RST_PIN, GPIO_PIN_RESET);
    delay_ms(100);
    HAL_GPIO_WritePin(ESP_RST_PORT, ESP_RST_PIN, GPIO_PIN_SET);

    /* Wait for module boot (ESP8266 boot time ~500ms + AT firmware init) */
    printf("[WiFi] HW reset done, waiting for module...\r\n");
    delay_ms(2000);
}

/* ================================================================
 * USART2 helpers
 * ================================================================ */
static void usart2_flush_rx(void);  /* forward decl, called by send_str */

/* USART ISR bit masks — CMSIS defines most, fill gaps */
#ifndef USART_ISR_TXE
#define USART_ISR_TXE   ((uint32_t)0x00000080)
#endif
#ifndef USART_ISR_RXNE
#define USART_ISR_RXNE  ((uint32_t)0x00000020)
#endif

/**
 * @brief  Send one byte via USART2 (direct register access, same style as main.c)
 */
static void usart2_putc(uint8_t ch)
{
    while ((USART2->ISR & USART_ISR_TXE) == 0);
    USART2->TDR = ch;
}

/**
 * @brief  Send raw bytes via USART2 (direct register access)
 */
static void usart2_send(const uint8_t *data, uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
        usart2_putc(data[i]);
}

/**
 * @brief  Send a null-terminated string via USART2
 */
static void usart2_send_str(const char *str)
{
    /* Clear ORE (Overrun Error) before transmission.
     * ORE blocks RXNE from being set, causing ESP-01S responses
     * to be lost on 2nd+ commands. Root cause: trailing bytes
     * from previous response arrive after we stop reading. */
    if (USART2->ISR & USART_ISR_ORE)
    {
        USART2->ICR = USART_ICR_ORECF;
    }
    /* Also clear any pending RX data */
    usart2_flush_rx();

    usart2_send((const uint8_t *)str, strlen(str));
    /* Wait for TX complete — last byte fully shifted out, line goes idle */
    while ((USART2->ISR & USART_ISR_TC) == 0);
}

/**
 * @brief  Flush any stale bytes from USART2 RX
 */
static void usart2_flush_rx(void)
{
    uint8_t dummy;
    while (USART2->ISR & USART_ISR_RXNE)
        dummy = (uint8_t)(USART2->RDR & 0xFF);
    (void)dummy;
}

/**
 * @brief  Read one byte from USART2, non-blocking
 * @retval 0:got byte, 1:nothing available
 */
static uint8_t usart2_getc_nb(uint8_t *ch)
{
    if (USART2->ISR & USART_ISR_RXNE)
    {
        *ch = (uint8_t)(USART2->RDR & 0xFF);
        return 0;
    }
    return 1;
}

/**
 * @brief  Read bytes from USART2 until expected string found or timeout.
 *         Direct register access — no HAL state machine interference.
 * @retval 0: found expected, 1: timeout, 2: got ERROR
 */
static uint8_t usart2_expect(const char *expect, uint32_t timeout_ms)
{
    char buf[256];
    uint16_t pos = 0;
    uint32_t start = HAL_GetTick();
    uint8_t ch;

    memset(buf, 0, sizeof(buf));

    while (1)
    {
        if (usart2_getc_nb(&ch) == 0)
        {
            if (pos < sizeof(buf) - 1)
                buf[pos++] = (char)ch;

            if (strstr(buf, expect) != NULL)
            {
                WIFI_LOG_RESP(buf);
                return 0;
            }
            if (strstr(buf, "ERROR") != NULL)
            {
                WIFI_LOG_RESP(buf);
                return 2;
            }
        }

        if ((HAL_GetTick() - start) > timeout_ms)
        {
            if (pos > 0)
                printf("[WiFi] TIMEOUT (%lums), got: %s\r\n", timeout_ms, buf);
            else
                printf("[WiFi] TIMEOUT (%lums, no response)\r\n", timeout_ms);
            return 1;
        }
    }
}

/* ================================================================
 * AT command interface
 * ================================================================ */

/**
 * @brief  Send AT command and wait for expected response
 * @param  cmd: AT command string (e.g. "AT\r\n")
 * @param  expect: expected response substring (e.g. "OK")
 * @param  timeout_ms: max wait time
 * @retval 0:OK, 1:timeout, 2:ERROR
 */
uint8_t wifi_send_at(const char *cmd, const char *expect, uint32_t timeout_ms)
{
    printf("[WiFi] >> %s", cmd);
    usart2_send_str(cmd);    /* send_str now clears ORE + flushes RX before TX */
    return usart2_expect(expect, timeout_ms);
}

/* ================================================================
 * High-level WiFi operations
 * ================================================================ */

/**
 * @brief  Initialize ESP-01S: reset + AT test + baud rate negotiation
 * @retval 0:OK, 1:FAIL
 */
uint8_t wifi_init(void)
{
    uint8_t ret;

    printf("[WiFi] === Init Start ===\r\n");

    /* Step 1: GPIO + USART2 init at default 115200 */
    wifi_hw_reset();

    /* Re-init USART2 for TX_RX (original usart2_init sets TX only) */
    usart2_init(115200);
    g_uart2_handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&g_uart2_handle);
    wifi_baud = 115200;
    printf("[WiFi] USART2 ready @ %lu baud\r\n", wifi_baud);

    /* Step 2: Disable echo first — prevents UART confusion */
    ret = wifi_send_at("ATE0\r\n", "OK", 3000);
    if (ret != 0)
    {
        printf("[WiFi] WARN: ATE0 failed, continuing...\r\n");
    }
    else
    {
        printf("[WiFi] Echo disabled\r\n");
    }

    /* Step 3: AT test */
    ret = wifi_send_at("AT\r\n", "OK", 3000);
    if (ret != 0)
    {
        printf("[WiFi] FAIL: AT error (code=%d)\r\n", ret);
        return 1;
    }
    printf("[WiFi] AT test OK\r\n");

    /* Step 4: Firmware version */
    wifi_send_at("AT+GMR\r\n", "OK", 3000);

    /* Step 4: Switch to 460800 — ESP-01S reliably tested at this speed */
    ret = wifi_send_at("AT+UART_CUR=460800,8,1,0,0\r\n", "OK", 2000);
    if (ret == 0)
    {
        HAL_UART_DeInit(&g_uart2_handle);
        usart2_init(460800);
        g_uart2_handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&g_uart2_handle);
        wifi_baud = 460800;
        printf("[WiFi] Switched to %lu baud\r\n", wifi_baud);
    }
    else
    {
        printf("[WiFi] Baud switch not supported, staying at 115200\r\n");
    }

    printf("[WiFi] === Init OK @ %lu baud ===\r\n", wifi_baud);
    return 0;
}

/**
 * @brief  Connect to WiFi AP using credentials from wifi_config.h
 * @retval 0:OK, 1:FAIL
 */
uint8_t wifi_connect_ap(void)
{
    uint8_t ret;
    char cmd[128];

    /* Set Station mode */
    ret = wifi_send_at("AT+CWMODE=1\r\n", "OK", 3000);
    if (ret != 0)
    {
        printf("[WiFi] FAIL: CWMODE error\r\n");
        return 1;
    }

    /* Connect to AP */
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);
    printf("[WiFi] Connecting to %s...\r\n", WIFI_SSID);
    ret = wifi_send_at(cmd, "OK", 15000);  /* WiFi connection takes 5-15s */

    if (ret != 0)
    {
        printf("[WiFi] FAIL: Cannot connect to AP (code=%d)\r\n", ret);
        printf("[WiFi] Check SSID and password in wifi_config.h\r\n");
        return 1;
    }
    printf("[WiFi] Connected to %s\r\n", WIFI_SSID);
    return 0;
}

/**
 * @brief  Connect to TCP server using host/port from wifi_config.h
 * @retval 0:OK, 1:FAIL
 */
uint8_t wifi_tcp_connect(void)
{
    uint8_t ret;
    char cmd[128];

    /* Single connection mode */
    ret = wifi_send_at("AT+CIPMUX=0\r\n", "OK", 2000);
    if (ret != 0)
    {
        printf("[WiFi] FAIL: CIPMUX error\r\n");
        return 1;
    }

    /* Connect to TCP server */
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", CLOUD_HOST, CLOUD_PORT);
    printf("[WiFi] Connecting to %s:%d...\r\n", CLOUD_HOST, CLOUD_PORT);
    ret = wifi_send_at(cmd, "OK", 10000);
    if (ret != 0)
    {
        printf("[WiFi] FAIL: TCP connect error (code=%d)\r\n", ret);
        printf("[WiFi] Check server is running: %s:%d\r\n", CLOUD_HOST, CLOUD_PORT);
        return 1;
    }
    printf("[WiFi] TCP connected to %s:%d\r\n", CLOUD_HOST, CLOUD_PORT);
    return 0;
}

/**
 * @brief  Enter transparent (passthrough) mode
 *         After this, all USART2 data goes straight to TCP server.
 */
void wifi_enter_transparent(void)
{
    uint8_t ret;

    ret = wifi_send_at("AT+CIPMODE=1\r\n", "OK", 2000);
    if (ret != 0)
        printf("[WiFi] WARN: CIPMODE error\r\n");

    /* AT+CIPSEND with no arguments enters transparent mode */
    ret = wifi_send_at("AT+CIPSEND\r\n", ">", 3000);
    if (ret == 0)
        printf("[WiFi] Transparent mode ON - USART2 is now TCP pipe\r\n");
    else
        printf("[WiFi] WARN: Enter transparent mode failed\r\n");
}

/**
 * @brief  Exit transparent mode
 *         +++ with 1s silence before and after, no CR/LF
 */
void wifi_exit_transparent(void)
{
    printf("[WiFi] Exiting transparent mode...\r\n");
    delay_ms(1000);                                    /* >=1s silence */
    usart2_send((const uint8_t *)"+++", 3);            /* no \r\n! */
    delay_ms(500);                                     /* wait for OK */
    usart2_expect("OK", 1000);                         /* consume OK */

    /* Disable transparent mode */
    wifi_send_at("AT+CIPMODE=0\r\n", "OK", 2000);
    printf("[WiFi] Transparent mode OFF\r\n");
}

/**
 * @brief  Send raw data via USART2 (transparent mode or AT mode)
 *         In transparent mode, this goes directly to TCP server.
 */
void wifi_send_raw(const uint8_t *data, uint32_t len)
{
    usart2_send(data, (uint16_t)len);
}

/* ================================================================
 * Self-test (for STEP_DEBUG mode)
 * ================================================================ */

uint8_t wifi_self_test(void)
{
    uint8_t ret;

    printf("\r\n[WiFi] === Self-Test Start ===\r\n");

    /* 2.1-2.4: Init + AT test + firmware version */
    ret = wifi_init();
    if (ret != 0)
    {
        printf("[WiFi] === Self-Test FAIL at init ===\r\n");
        return 1;
    }

    /* 2.5: Connect to WiFi AP */
    ret = wifi_connect_ap();
    if (ret != 0)
    {
        printf("[WiFi] === Self-Test FAIL at WiFi connect ===\r\n");
        return 1;
    }

    /* 2.6: Connect to TCP server */
    ret = wifi_tcp_connect();
    if (ret != 0)
    {
        printf("[WiFi] === Self-Test FAIL at TCP connect ===\r\n");
        printf("[WiFi] Continuing anyway (server may not be running)\r\n");
    }

    /* 2.7: Test transparent mode entry/exit */
    wifi_enter_transparent();
    delay_ms(500);

    /* Send a test message via transparent mode */
    wifi_send_raw((const uint8_t *)"Hello from STM32!\r\n", 20);
    delay_ms(500);

    wifi_exit_transparent();

    printf("[WiFi] === Self-Test PASS ===\r\n");
    return 0;
}
