/**
 * test_config.h - 测试阶段开关
 *
 * 只开一个：
 *   TEST_PHASE_UART              → Phase 1:  USART1 回环 + printf + LED
 *   TEST_PHASE_OV2640            → Phase 2a: OV5640 连续采集帧大小统计
 *   TEST_PHASE_OV2640_SNAPSHOT   → Phase 2b: OV5640 快照 → 串口发 JPEG 给 PC
 *   (都不开)                     → Phase 3:  FreeRTOS 三任务
 */

#ifndef __TEST_CONFIG_H
#define __TEST_CONFIG_H

/* ── 当前激活的测试阶段（只开一个）── */
#define TEST_PHASE_UART
//#define TEST_PHASE_OV2640
//#define TEST_PHASE_OV2640_SNAPSHOT

#endif /* __TEST_CONFIG_H */