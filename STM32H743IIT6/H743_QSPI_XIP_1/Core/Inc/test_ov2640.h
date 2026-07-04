#ifndef __TEST_OV2640_H__
#define __TEST_OV2640_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Phase 2: OV2640 摄像头验证（裸机，不依赖 FreeRTOS）
 *
 * 测试流程：
 *   1. I2C SCCB 读取 OV2640 寄存器 PID/VER（确认摄像头在线）
 *   2. DCMI + DMA 双缓冲连续采集 JPEG 帧
 *   3. 每收到一帧打印帧大小和首字节
 *   4. LED PB0 每 2 帧翻转一次
 *
 * 使用方式：
 *   1. 注释 main.c 中的 #define TEST_PHASE_UART
 *   2. 在 main.c 中 #define TEST_PHASE_OV2640
 *   3. I2C PB6(SCL) PB7(SDA) 必须连接 OV2640 SCCB
 */

void test_ov2640_run(void);

#ifdef __cplusplus
}
#endif

#endif /* __TEST_OV2640_H__ */