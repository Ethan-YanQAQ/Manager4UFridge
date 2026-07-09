#include "glue.h"
#include "module_qspi.h"
#include "module_wifi.h"
#include "wifi_config.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

void glue_run(void)
{
#ifdef STEP_DEBUG
    printf("\r\n=== STEP DEBUG MODE ===\r\n");

    printf("--- Step 1: QSPI Self-Test ---\r\n");
    if (qspi_self_test() == 0)
        printf("--- QSPI: PASS ---\r\n\r\n");
    else
        printf("--- QSPI: FAIL ---\r\n\r\n");

    printf("--- Step 2: WiFi Self-Test ---\r\n");
    if (wifi_self_test() == 0)
        printf("--- WiFi: PASS ---\r\n\r\n");
    else
        printf("--- WiFi: FAIL ---\r\n\r\n");

    printf("=== All tests done ===\r\n");
#else
    norflash_init();
    printf("[GLUE] QSPI Flash ready, ID=0x%04X\r\n", norflash_read_id());

    /* WiFi: step-by-step with error check */
    if (wifi_init() != 0)
    {
        printf("[GLUE] WiFi init FAIL, stopping WiFi setup\r\n");
        return;
    }
    if (wifi_connect_ap() != 0)
    {
        printf("[GLUE] WiFi AP connect FAIL, stopping WiFi setup\r\n");
        return;
    }
    if (wifi_tcp_connect() != 0)
    {
        printf("[GLUE] TCP connect FAIL, stopping WiFi setup\r\n");
        return;
    }
    wifi_enter_transparent();
    printf("[GLUE] WiFi pipeline ready, USART2 = TCP to %s:%d\r\n", CLOUD_HOST, CLOUD_PORT);
#endif
}
