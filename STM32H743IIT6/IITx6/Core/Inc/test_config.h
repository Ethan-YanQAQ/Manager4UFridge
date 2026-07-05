/**
 * test_config.h - 测试阶段开关
 *
 * 只开一个：
 *   TEST_PHASE_UART              → Phase 1:  USART1 回环 + printf
 *   TEST_PHASE_OV2640            → Phase 2:  OV5640 JPEG Snapshot → UART
 *   (都不开)                     → Phase 3:  FreeRTOS 三任务
 */

#ifndef __TEST_CONFIG_H
#define __TEST_CONFIG_H

/* ── 当前激活 ── */
#define TEST_PHASE_UART
//#define TEST_PHASE_OV2640
//#define TEST_PHASE_OV2640_SNAPSHOT

#endif /* __TEST_CONFIG_H */