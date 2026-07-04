/**
 * bsp_ai.h - Cube.AI YOLO11n 推理封装
 *
 * 输入:  float[1][3][320][320]  (NHWC, 307200 floats = 1.2MB in SDRAM)
 * 输出:  float[1][32][2100]     (67200 floats = 263KB in SDRAM)
 * 权重:  INT8 ~2.5MB @ QSPI Flash 0x90000000 (Memory-Mapped)
 * 激活:  运行时 ~1.5MB @ SDRAM
 */

#ifndef __BSP_AI_H
#define __BSP_AI_H

#include <stdint.h>

#define AI_INPUT_SIZE    307200   /* 320*320*3 floats */
#define AI_OUTPUT_SIZE   67200    /* 32*2100 floats */

int  bsp_ai_init(void);
int  bsp_ai_run(float *input, float *output);

#endif /* __BSP_AI_H */