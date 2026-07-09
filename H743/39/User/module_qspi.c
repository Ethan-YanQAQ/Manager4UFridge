#include "./BSP/QSPI/qspi.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "module_qspi.h"

static const uint8_t test_pattern[] = {"QSPI Self-Test OK!"};
#define TEST_SIZE   sizeof(test_pattern)

uint8_t qspi_self_test(void)
{
    uint8_t buf[TEST_SIZE + 4];
    uint16_t id;
    uint32_t test_addr;

    printf("[QSPI] Initializing...\r\n");
    norflash_init();
    id = norflash_read_id();
    printf("[QSPI] Flash ID: 0x%04X\r\n", id);

    if (id != W25Q256 && id != BY25Q256)
    {
        printf("[QSPI] FAIL: Unknown Flash ID!\r\n");
        return 1;
    }
    printf("[QSPI] Flash detected: W25Q256/BY25Q256\r\n");

    test_addr = (32 * 1024 * 1024) - 4096;
    printf("[QSPI] Writing test pattern to 0x%08X...\r\n", test_addr);
    norflash_write((uint8_t *)test_pattern, test_addr, TEST_SIZE);

    printf("[QSPI] Reading back...\r\n");
    norflash_read(buf, test_addr, TEST_SIZE);
    buf[TEST_SIZE] = '\0';

    printf("[QSPI] Written: %s\r\n", test_pattern);
    printf("[QSPI] Read:    %s\r\n", buf);

    {
        uint8_t i, match = 1;
        for (i = 0; i < TEST_SIZE; i++)
            if (buf[i] != test_pattern[i]) { match = 0; break; }
        if (match)
        {
            printf("[QSPI] PASS: Read/Write verify OK!\r\n");
            return 0;
        }
        else
        {
            printf("[QSPI] FAIL: Data mismatch at byte %u\r\n", i);
            return 1;
        }
    }
}
