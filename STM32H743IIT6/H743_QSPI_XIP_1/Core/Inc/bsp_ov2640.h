/**
 * bsp_ov2640.h - OV2640 摄像头驱动
 *
 * 接口: I2C1 (PB6=SCL, PB7=SDA) 用于 SCCB 配置
 *        DCMI 8-bit + DMA1_Stream2 双缓冲采集
 * 控制: PH6=PWDN (低有效), PH7=RST (低有效)
 * 输出: 320x240 RGB565
 */

#ifndef __BSP_OV2640_H
#define __BSP_OV2640_H

#include "main.h"
#include <stdint.h>

#define OV2640_WIDTH    320
#define OV2640_HEIGHT   240
#define OV2640_FRAME_SIZE  (OV2640_WIDTH * OV2640_HEIGHT * 2)  /* RGB565 = 153600 bytes */

/* API */
void     bsp_ov2640_init(void);
void     bsp_ov2640_start(void);
void     bsp_ov2640_stop(void);
uint8_t* bsp_ov2640_get_fb(void);            /* 获取当前帧缓冲指针 */
void     bsp_ov2640_set_frame_cb(void (*cb)(void));  /* 帧完成回调 */

#endif /* __BSP_OV2640_H */
