/**
  ******************************************************************************
  * @file    wifi_esp01s.c
  * @brief   ESP-01S WiFi module driver implementation
  *
  *          Communication flow:
  *            1. AT test → station mode → connect AP → get IP
  *            2. AT+CIPSTART → TCP connect to PC server
  *            3. AT+CIPSEND → send image chunks → wait "SEND OK"
  *
  *          Uses blocking HAL_UART_Receive for AT response parsing.
  *          Image data is sent via HAL_UART_Transmit after CIPSEND prompt.
  ******************************************************************************
  */
#include "wifi_esp01s.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Static Helpers — UART TX/RX for AT Commands                        */
/* ------------------------------------------------------------------ */

static char at_rx_buf[WIFI_AT_RX_BUF_SIZE];

/**
  * @brief  Send an AT command string and read the response.
  * @param  cmd       Full AT command (e.g. "AT\r\n")
  * @param  timeout   Max wait time in ms
  * @return Pointer to static RX buffer, or NULL on timeout.
  */
static char* wifi_at_raw(const char *cmd, uint32_t timeout)
{
    memset(at_rx_buf, 0, sizeof(at_rx_buf));

    /* Flush any stale RX data by reading with 1ms timeout */
    uint8_t dummy;
    while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) {}

    /* Send the AT command */
    size_t cmd_len = strlen(cmd);
    if (HAL_UART_Transmit(&huart1, (uint8_t *)cmd, cmd_len, 2000) != HAL_OK) {
        return NULL;
    }

    /* Read response character-by-character until idle gap */
    uint16_t idx = 0;
    uint32_t elapsed = 0;
    const uint32_t poll_interval = 10;  /* ms per read attempt */

    while (elapsed < timeout && idx < (sizeof(at_rx_buf) - 1)) {
        uint8_t ch;
        if (HAL_UART_Receive(&huart1, &ch, 1, poll_interval) == HAL_OK) {
            at_rx_buf[idx++] = (char)ch;
            at_rx_buf[idx]   = '\0';

            /* Early exit on terminal response lines */
            if (strstr(at_rx_buf, "OK\r\n") || strstr(at_rx_buf, "ERROR\r\n") ||
                strstr(at_rx_buf, "FAIL\r\n") || strstr(at_rx_buf, "SEND OK\r\n")) {
                /* Give a little extra time for trailing data */
                HAL_Delay(20);
                while (HAL_UART_Receive(&huart1, &ch, 1, 5) == HAL_OK) {
                    if (idx < sizeof(at_rx_buf) - 1) {
                        at_rx_buf[idx++] = (char)ch;
                        at_rx_buf[idx] = '\0';
                    }
                }
                break;
            }
        }
        elapsed += poll_interval;
    }

    return (idx > 0) ? at_rx_buf : NULL;
}

/**
  * @brief  Check if response contains the expected substring.
  */
static int wifi_contains(const char *response, const char *expected)
{
    if (response == NULL) return 0;
    return (strstr(response, expected) != NULL);
}

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

/**
  * @brief  Send "+++" escape sequence to pull ESP-01S out of
  *         transparent / data mode back into AT command mode.
  * @retval 1 if OK received, 0 otherwise.
  */
static int wifi_escape_from_data_mode(void)
{
    /* Flush RX */
    uint8_t dummy;
    while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) {}

    /*
     * ESP8266 "+++" escape protocol:
     *   1. Idle on TX for ≥ 1 second (guard time before)
     *   2. Send "+++" without any line ending
     *   3. Idle on TX for ≥ 1 second (guard time after)
     *   4. ESP responds with "OK\r\n" if successful
     */
    HAL_Delay(1200);                                 /* guard time before */
    HAL_UART_Transmit(&huart1, (uint8_t *)"+++", 3, 500);
    HAL_Delay(1200);                                 /* guard time after  */

    /* Try to read response */
    char buf[32] = {0};
    int  idx     = 0;
    uint32_t t0  = HAL_GetTick();
    while ((HAL_GetTick() - t0) < 1000 && idx < 30) {
        uint8_t ch;
        if (HAL_UART_Receive(&huart1, &ch, 1, 50) == HAL_OK) {
            buf[idx++] = (char)ch;
            buf[idx]   = '\0';
            if (strstr(buf, "OK") || strstr(buf, "ERROR")) break;
        }
    }

    return (strstr(buf, "OK") != NULL) ? 1 : 0;
}

/**
  * @brief  Basic AT communication test and station mode setup.
  *
  *         Robust against ESP-01S being left in transparent/data mode
  *         after an STM32 SWD re-flash (ESP-01S doesn't get reset).
  */
int WIFI_Init(void)
{
    char *resp;

    /*
     * 1. Hardware reset ESP-01S via RST pin (PC1).
     *    This guarantees a clean cold-boot regardless of what state
     *    it was left in (transparent mode, TCP open, etc.).
     */
    HAL_GPIO_WritePin(ESP01_RST_GPIO_Port, ESP01_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(ESP01_RST_GPIO_Port, ESP01_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(2500);  /* wait for ESP-01S full boot */

    /*
     * 2. Backup: if HW reset line isn't wired yet, try "+++" escape
     *    to pull ESP-01S out of transparent/data mode.
     */
    wifi_escape_from_data_mode();

    /* 3. Test AT communication (try up to 5 times) */
    int at_ok = 0;
    for (int attempt = 0; attempt < 5; attempt++) {
        resp = wifi_at_raw("AT\r\n", 2000);
        if (wifi_contains(resp, "OK")) { at_ok = 1; break; }
        HAL_Delay(500);
    }

    if (!at_ok) {
        /* Last resort: software-reset the ESP-01S and wait for reboot */
        wifi_at_raw("AT+RST\r\n", 3000);
        HAL_Delay(3000);  /* ESP-01S reboot time */

        /* Flush boot messages from RX buffer */
        uint8_t dummy;
        while (HAL_UART_Receive(&huart1, &dummy, 1, 10) == HAL_OK) {}

        /* Retry AT after reset */
        for (int attempt = 0; attempt < 5; attempt++) {
            resp = wifi_at_raw("AT\r\n", 2000);
            if (wifi_contains(resp, "OK")) { at_ok = 1; break; }
            HAL_Delay(500);
        }

        if (!at_ok) return WIFI_ERR_AT_FAIL;
    }

    /* 3. Disable echo */
    wifi_at_raw("ATE0\r\n", 1000);

    /* 4. Set station mode */
    resp = wifi_at_raw("AT+CWMODE=1\r\n", 2000);
    if (!wifi_contains(resp, "OK")) return WIFI_ERR_AT_FAIL;

    /* 5. Single connection mode (needed for CIPSTART) */
    resp = wifi_at_raw("AT+CIPMUX=0\r\n", 2000);
    if (!wifi_contains(resp, "OK")) return WIFI_ERR_AT_FAIL;

    /* 6. Set TCP send mode to normal (not transparent) */
    resp = wifi_at_raw("AT+CIPMODE=0\r\n", 2000);
    if (!wifi_contains(resp, "OK")) return WIFI_ERR_AT_FAIL;

    return WIFI_OK;
}

/**
  * @brief  Connect to a Wi-Fi access point.
  */
int WIFI_ConnectAP(const char *ssid, const char *password)
{
    char cmd[128];
    int len = snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    if (len < 0 || len >= (int)sizeof(cmd)) return WIFI_ERR_AT_FAIL;

    char *resp = wifi_at_raw(cmd, WIFI_AT_LONG_TIMEOUT_MS);

    /* Possible responses: "OK", "WIFI CONNECTED", "WIFI GOT IP" */
    if (wifi_contains(resp, "OK") || wifi_contains(resp, "WIFI GOT IP")) {
        /* Wait for IP assignment */
        HAL_Delay(3000);
        return WIFI_OK;
    }

    /* Check for common failure reasons */
    if (wifi_contains(resp, "FAIL") || wifi_contains(resp, "ERROR")) {
        return WIFI_ERR_WIFI_FAIL;
    }

    return WIFI_ERR_TIMEOUT;
}

/**
  * @brief  Query the module's assigned IP address.
  */
int WIFI_GetLocalIP(char *ip_buf)
{
    char *resp = wifi_at_raw("AT+CIFSR\r\n", 3000);
    if (resp == NULL) return WIFI_ERR_AT_FAIL;

    /* Response format: +CIFSR:STAIP,"192.168.x.x" */
    char *start = strstr(resp, "STAIP,\"");
    if (start == NULL) {
        start = strstr(resp, "+CIFSR:");
        if (start == NULL) return WIFI_ERR_AT_FAIL;
        /* Skip prefix */
        start = strchr(start, '"');
        if (start == NULL) return WIFI_ERR_AT_FAIL;
        start++;
    } else {
        start += 7; /* strlen("STAIP,\"") */
    }

    char *end = strchr(start, '"');
    if (end == NULL) return WIFI_ERR_AT_FAIL;

    size_t len = (size_t)(end - start);
    if (len > 15) len = 15;
    memcpy(ip_buf, start, len);
    ip_buf[len] = '\0';

    return WIFI_OK;
}

/**
  * @brief  Connect to a TCP server on the PC.
  */
int WIFI_ConnectTCPServer(const char *server_ip, uint16_t server_port)
{
    /* Close any existing connection first */
    wifi_at_raw("AT+CIPCLOSE\r\n", 2000);
    HAL_Delay(500);

    char cmd[96];
    int len = snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%u\r\n",
                       server_ip, server_port);
    if (len < 0 || len >= (int)sizeof(cmd)) return WIFI_ERR_AT_FAIL;

    char *resp = wifi_at_raw(cmd, WIFI_AT_LONG_TIMEOUT_MS);

    /* ESP may respond with "CONNECT" or "OK" depending on firmware */
    if (wifi_contains(resp, "CONNECT") || wifi_contains(resp, "OK")) {
        HAL_Delay(500);
        return WIFI_OK;
    }

    if (wifi_contains(resp, "ALREADY CONNECTED")) {
        return WIFI_OK;  /* Already connected — fine */
    }

    return WIFI_ERR_TCP_FAIL;
}

/**
  * @brief  Close the TCP connection.
  */
void WIFI_CloseTCP(void)
{
    wifi_at_raw("AT+CIPCLOSE\r\n", 3000);
}

/**
  * @brief  Send binary data over TCP with chunking.
  *         Each chunk: AT+CIPSEND=<len> → wait ">" → send data → wait "SEND OK"
  */
int WIFI_SendData(const uint8_t *pData, uint32_t len)
{
    uint32_t remaining = len;
    uint32_t offset    = 0;
    char     cmd[32];

    while (remaining > 0) {
        uint32_t chunk = (remaining > WIFI_CHUNK_SIZE) ? WIFI_CHUNK_SIZE : remaining;

        /* 1. Issue CIPSEND command */
        int cmd_len = snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%lu\r\n", (unsigned long)chunk);
        if (cmd_len < 0 || cmd_len >= (int)sizeof(cmd)) return WIFI_ERR_SEND_FAIL;

        /* Flush & send CIPSEND */
        {
            uint8_t dummy;
            while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) {}
        }
        HAL_UART_Transmit(&huart1, (uint8_t *)cmd, (uint16_t)cmd_len, 2000);

        /* 2. Wait for ">" prompt */
        {
            uint32_t wait_start = HAL_GetTick();
            int got_prompt = 0;
            while ((HAL_GetTick() - wait_start) < 5000) {
                uint8_t ch;
                if (HAL_UART_Receive(&huart1, &ch, 1, 100) == HAL_OK) {
                    if (ch == '>') { got_prompt = 1; break; }
                }
            }
            if (!got_prompt) return WIFI_ERR_SEND_FAIL;
        }

        /* 3. Send binary chunk */
        if (HAL_UART_Transmit(&huart1, (uint8_t *)(pData + offset),
                              (uint16_t)chunk, 10000) != HAL_OK) {
            return WIFI_ERR_SEND_FAIL;
        }

        /* 4. Wait for "SEND OK" */
        {
            char confirm[64] = {0};
            uint32_t wait_start = HAL_GetTick();
            int idx = 0;
            while ((HAL_GetTick() - wait_start) < 5000) {
                uint8_t ch;
                if (HAL_UART_Receive(&huart1, &ch, 1, 50) == HAL_OK) {
                    if (idx < 60) confirm[idx++] = (char)ch;
                    confirm[idx] = '\0';
                    if (strstr(confirm, "SEND OK")) break;
                }
            }
            if (!strstr(confirm, "SEND OK")) return WIFI_ERR_SEND_FAIL;
        }

        offset    += chunk;
        remaining -= chunk;
    }

    return WIFI_OK;
}

/**
  * @brief  Send JPEG frame with 4-byte little-endian length header.
  *
  *         Protocol: the PC receiver expects a 4-byte LE uint32 length
  *         prefix before the raw JPEG data.  This prevents TCP framing
  *         issues and lets the receiver know exactly how many bytes to
  *         read for the current frame.
  *
  *         AT+CIPSEND payload = 4 header bytes + JPEG bytes.
  *
  * @param  pData  Pointer to JPEG data buffer.
  * @param  len    JPEG data length in bytes.
  * @retval WIFI_OK or error code.
  */
int WIFI_SendFrame(const uint8_t *pData, uint32_t len)
{
    char cmd[32];
    uint32_t total_len = len + 4;  /* 4-byte header + JPEG payload */

    /* 1. Issue CIPSEND for header + JPEG */
    int cmd_len = snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%lu\r\n",
                           (unsigned long)total_len);
    if (cmd_len < 0 || cmd_len >= (int)sizeof(cmd)) return WIFI_ERR_SEND_FAIL;

    /* Flush stale RX */
    {
        uint8_t dummy;
        while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) {}
    }

    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, (uint16_t)cmd_len, 2000);

    /* 2. Wait for ">" prompt */
    {
        uint32_t wait_start = HAL_GetTick();
        int got_prompt = 0;
        while ((HAL_GetTick() - wait_start) < 3000) {
            uint8_t ch;
            if (HAL_UART_Receive(&huart1, &ch, 1, 200) == HAL_OK) {
                if (ch == '>') { got_prompt = 1; break; }
            }
        }
        if (!got_prompt) return WIFI_ERR_SEND_FAIL;
    }

    /* 3. Send 4-byte little-endian length header */
    uint8_t header[4];
    header[0] = (uint8_t)(len & 0xFF);
    header[1] = (uint8_t)((len >> 8) & 0xFF);
    header[2] = (uint8_t)((len >> 16) & 0xFF);
    header[3] = (uint8_t)((len >> 24) & 0xFF);

    if (HAL_UART_Transmit(&huart1, header, 4, 1000) != HAL_OK) {
        return WIFI_ERR_SEND_FAIL;
    }

    /* 4. Send JPEG data */
    if (HAL_UART_Transmit(&huart1, (uint8_t *)pData, (uint16_t)len,
                          5000) != HAL_OK) {
        return WIFI_ERR_SEND_FAIL;
    }

    /* 5. Wait for "SEND OK" */
    {
        char confirm[64] = {0};
        uint32_t wait_start = HAL_GetTick();
        int idx = 0;
        while ((HAL_GetTick() - wait_start) < 5000) {
            uint8_t ch;
            if (HAL_UART_Receive(&huart1, &ch, 1, 50) == HAL_OK) {
                if (idx < 60) confirm[idx++] = (char)ch;
                confirm[idx] = '\0';
                if (strstr(confirm, "SEND OK")) break;
            }
        }
        if (!strstr(confirm, "SEND OK")) return WIFI_ERR_SEND_FAIL;
    }

    return WIFI_OK;
}

/**
  * @brief  Send entire JPEG frame in ONE CIPSEND (no chunking).
  *
  *         Snapshot mode: the buffer is "frozen" after a single-frame
  *         DCMI capture.  We send it whole via a single AT+CIPSEND=<len>
  *         command at 115200 baud.
  *
  *         At 115200: ~11.2 KB/s → an 8 KB JPEG takes ~0.7 s.
  *         Timeouts are generous (2–3 s) to tolerate TCP retransmission.
  *
  * @param  pData  Pointer to data buffer.
  * @param  len    Total bytes to send (typically 5–15 KB).
  * @retval WIFI_OK or error code.
  */
int WIFI_SendSingle(const uint8_t *pData, uint32_t len)
{
    char cmd[32];

    /* 1. Issue CIPSEND for the ENTIRE frame */
    int cmd_len = snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%lu\r\n",
                           (unsigned long)len);
    if (cmd_len < 0 || cmd_len >= (int)sizeof(cmd)) return WIFI_ERR_SEND_FAIL;

    /* Flush any stale RX data */
    {
        uint8_t dummy;
        while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) {}
    }

    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, (uint16_t)cmd_len, 2000);

    /* 2. Wait for ">" prompt (ESP-01S ready for raw data) */
    {
        uint32_t wait_start = HAL_GetTick();
        int got_prompt = 0;
        while ((HAL_GetTick() - wait_start) < 3000) {
            uint8_t ch;
            if (HAL_UART_Receive(&huart1, &ch, 1, 200) == HAL_OK) {
                if (ch == '>') { got_prompt = 1; break; }
            }
        }
        if (!got_prompt) return WIFI_ERR_SEND_FAIL;
    }

    /* 3. Send the entire JPEG buffer in one continuous UART burst.
     *    Timeout = 3000 ms to allow slow 115200 transmission of
     *    up to ~15 KB frames (~1.3 s physical time). */
    if (HAL_UART_Transmit(&huart1, (uint8_t *)pData, (uint16_t)len,
                          3000) != HAL_OK) {
        return WIFI_ERR_SEND_FAIL;
    }

    /* 4. Wait for "SEND OK" (ESP-01S TCP send confirmation) */
    {
        char confirm[64] = {0};
        uint32_t wait_start = HAL_GetTick();
        int idx = 0;
        while ((HAL_GetTick() - wait_start) < 5000) {
            uint8_t ch;
            if (HAL_UART_Receive(&huart1, &ch, 1, 50) == HAL_OK) {
                if (idx < 60) confirm[idx++] = (char)ch;
                confirm[idx] = '\0';
                if (strstr(confirm, "SEND OK")) break;
            }
        }
        if (!strstr(confirm, "SEND OK")) return WIFI_ERR_SEND_FAIL;
    }

    return WIFI_OK;
}

/**
  * @brief  Check TCP connection status.
  */
int WIFI_IsTCPConnected(void)
{
    char *resp = wifi_at_raw("AT+CIPSTATUS\r\n", 2000);
    if (resp == NULL) return 0;
    /* STATUS:2 = connected, STATUS:3 = transmitting, STATUS:4 = TCP disconnect */
    return (strstr(resp, "STATUS:2") || strstr(resp, "STATUS:3")) ? 1 : 0;
}
