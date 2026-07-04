/**
 * bsp_ov5640.h - OV5640 摄像头驱动
 *
 * 接口: 软 I2C (PB3=SDA, PB4=SCL) 用于 SCCB 配置
 *       DCMI 8-bit + DMA 双缓冲采集
 * 控制: PH6=PWDN (低有效), PH7=RST (低有效)
 *
 * SCCB 地址 0x78, 16-bit 寄存器地址, 软 I2C ~100kHz
 * 输出: 320x240 RGB565
 */

#ifndef __BSP_OV5640_H
#define __BSP_OV5640_H

#include "main.h"
#include <stdint.h>

#define OV5640_WIDTH    320
#define OV5640_HEIGHT   240
#define OV5640_FRAME_SIZE  (OV5640_WIDTH * OV5640_HEIGHT * 2)  /* RGB565 = 153600 bytes */

void     bsp_ov5640_init(void);
void     bsp_ov5640_start(void);
void     bsp_ov5640_stop(void);
uint8_t* bsp_ov5640_get_fb(void);
void     bsp_ov5640_set_frame_cb(void (*cb)(void));

#endif /* __BSP_OV5640_H */