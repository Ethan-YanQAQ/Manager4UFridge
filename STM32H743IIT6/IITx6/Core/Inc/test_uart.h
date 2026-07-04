#ifndef __TEST_UART_H__
#define __TEST_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Phase 1: 串口通信验证
 *   - 重定向 printf 到 USART1
 *   - 打印系统信息（MCU UID, 时钟频率）
 *   - 回环测试：接收字符 → 立即发回
 *   - LED 心跳（PB0 每 500ms 翻转）
 *
 * 使用方式：
 *   1. 在 main.c 顶部 #define TEST_PHASE_UART
 *   2. SystemClock_Config() 之后调用 test_uart_run()
 *   3. 用串口工具连接 USART1（115200/8/N/1），敲字符看回显
 */

void test_uart_run(void);

#ifdef __cplusplus
}
#endif

#endif /* __TEST_UART_H__ */