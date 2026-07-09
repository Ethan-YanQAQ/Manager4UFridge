/**
  ******************************************************************************
  * @file    wifi_esp01s.h
  * @brief   ESP-01S WiFi module driver — AT command interface over USART1
  *
  *          Hardware:
  *            ESP-01S TX  ← PA10 (USART1_RX)
  *            ESP-01S RXD ← PA9  (USART1_TX)
  *            Baud: 115200 8N1
  *
  *          Protocol:
  *            Standard Espressif AT firmware v2.x
  ******************************************************************************
  */
#ifndef __WIFI_ESP01S_H__
#define __WIFI_ESP01S_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Configuration                                                       */
/* ------------------------------------------------------------------ */
#define WIFI_AT_CMD_TIMEOUT_MS      5000U   /* AT command response timeout   */
#define WIFI_AT_LONG_TIMEOUT_MS    15000U   /* Long op timeout (connect, IP) */
#define WIFI_AT_RX_BUF_SIZE          512U   /* UART RX buffer for AT resp    */
#define WIFI_CHUNK_SIZE             2048U   /* Max TCP payload per CIPSEND   */

/* ------------------------------------------------------------------ */
/* Status Codes                                                        */
/* ------------------------------------------------------------------ */
typedef enum {
    WIFI_OK = 0,
    WIFI_ERR_TIMEOUT      = -1,
    WIFI_ERR_AT_FAIL      = -2,
    WIFI_ERR_WIFI_FAIL    = -3,
    WIFI_ERR_TCP_FAIL     = -4,
    WIFI_ERR_SEND_FAIL    = -5,
    WIFI_ERR_NOT_CONNECTED = -6,
} WIFI_Status_t;

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

/**
  * @brief  Initialize ESP-01S communication.
  *         Tests basic AT command, configures station mode.
  * @retval WIFI_OK or error code.
  */
int WIFI_Init(void);

/**
  * @brief  Connect to a Wi-Fi access point.
  * @param  ssid      AP SSID (null-terminated)
  * @param  password  AP password (null-terminated)
  * @retval WIFI_OK or error code.
  */
int WIFI_ConnectAP(const char *ssid, const char *password);

/**
  * @brief  Get the module's local IP address string.
  * @param  ip_buf  Output buffer (min 16 bytes).
  * @retval WIFI_OK or error code.
  */
int WIFI_GetLocalIP(char *ip_buf);

/**
  * @brief  Establish a TCP connection to the PC server.
  * @param  server_ip   Server IPv4 address (e.g. "192.168.1.100")
  * @param  server_port Server TCP port (e.g. 8888)
  * @retval WIFI_OK or error code.
  */
int WIFI_ConnectTCPServer(const char *server_ip, uint16_t server_port);

/**
  * @brief  Close active TCP connection.
  */
void WIFI_CloseTCP(void);

/**
  * @brief  Send binary data to the connected TCP server.
  *         Automatically splits large payloads into CIPSEND-friendly chunks.
  *         Blocks until all data is sent or error occurs.
  * @param  pData  Pointer to data buffer.
  * @param  len    Number of bytes to send.
  * @retval WIFI_OK or error code.
  */
int WIFI_SendData(const uint8_t *pData, uint32_t len);

/**
  * @brief  Send JPEG frame with 4-byte length header.
  *         Protocol: AT+CIPSEND=<len+4> → wait '>' →
  *                   send 4-byte LE uint32 length → send JPEG data →
  *                   wait "SEND OK".
  *         Single CIPSEND for the entire frame + header.
  * @param  pData  Pointer to JPEG data buffer.
  * @param  len    JPEG data length in bytes.
  * @retval WIFI_OK or error code.
  */
int WIFI_SendFrame(const uint8_t *pData, uint32_t len);

/**
  * @brief  Send entire frame in one CIPSEND (no chunking).
  *         For snapshot mode — buffer is frozen, no risk of overwrite.
  * @param  pData  Pointer to data buffer.
  * @param  len    Total bytes to send.
  * @retval WIFI_OK or error code.
  */
int WIFI_SendSingle(const uint8_t *pData, uint32_t len);

/**
  * @brief  Check if ESP-01S has an active TCP connection.
  * @retval 1 = connected, 0 = not connected.
  */
int WIFI_IsTCPConnected(void);

#ifdef __cplusplus
}
#endif

#endif /* __WIFI_ESP01S_H__ */
