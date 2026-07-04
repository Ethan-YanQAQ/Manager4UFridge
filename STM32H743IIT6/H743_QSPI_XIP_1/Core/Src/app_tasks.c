/**
 * app_tasks.c - 应用任务实现
 *
 * 主流程: door→camera→preprocess→infer→postprocess→uart output
 * 每个阶段用 #if 1/0 控制，调试时逐步激活
 */

#include "app_tasks.h"
#include "main.h"
#include "bsp_door.h"
#include "bsp_ov2640.h"
#include "bsp_ai.h"
#include "bsp_yolo_post.h"
#include <stdio.h>
#include <string.h>

/* 帧队列 */
QueueHandle_t g_frame_queue = NULL;

/* AI 输入输出缓冲 (SDRAM) */
static float *g_ai_input  = (float *)0xC0200000;   /* 320*320*3*4 = 1.2MB */
static float *g_ai_output = (float *)0xC0400000;   /* input之后留足余量, 避免重叠 */

/* 检测结果 */
static detection_list_t g_det_result;

/* 门磁回调 (ISR 上下文, 只设置标志) */
static volatile uint8_t g_door_triggered = 0;
static void door_cb(uint8_t state)
{
    if (state == DOOR_OPEN) g_door_triggered = 1;
}

/* --- 图像预处理: RGB565(320×240) → float RGB(320×320×3) normalize --- */
static void preprocess_rgb565(const uint8_t *src, float *dst)
{
    /* 简单最近邻上采样 240→320 (纵向重复部分行) + 横向直接拷贝 */
    for (int y = 0; y < 320; y++) {
        int sy = (y * 240) / 320;  /* 最近邻映射回 240 */
        const uint16_t *row = (const uint16_t *)(src + sy * 320 * 2);
        for (int x = 0; x < 320; x++) {
            uint16_t px = row[x];
            float r = (float)((px >> 11) & 0x1F) / 31.0f;
            float g = (float)((px >> 5)  & 0x3F) / 63.0f;
            float b = (float)( px        & 0x1F) / 31.0f;
            /* NHWC 布局: [H][W][C] = [320][320][3] */
            int idx = (y * 320 + x) * 3;
            dst[idx + 0] = r;
            dst[idx + 1] = g;
            dst[idx + 2] = b;
        }
    }
}

/* === 任务1: 门磁监控 === */
void vTaskMonitor(void *arg)
{
    bsp_door_init();
    bsp_door_set_callback(door_cb);

#if 1 /* STEP2: 门磁测试 */
    uint8_t last_state = DOOR_CLOSED;
    for (;;) {
        uint8_t st = bsp_door_get_state();
        if (st != last_state) {
            last_state = st;
            char buf[32];
            int len = snprintf(buf, sizeof(buf),
                               "[DOOR] %s\r\n", st ? "OPEN" : "CLOSE");
            HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 100);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
#else
    for (;;) { vTaskDelay(pdMS_TO_TICKS(1000)); }
#endif
}

/* === 任务2: 摄像头采集 === */
void vTaskCamera(void *arg)
{
    bsp_ov2640_init();
    bsp_ov2640_start();

    for (;;) {
#if 1 /* STEP3: 摄像头测试 */
        if (g_door_triggered) {
            g_door_triggered = 0;
            uint8_t *fb = bsp_ov2640_get_fb();
            /* 送帧指针到推理队列 (阻塞等 AI 任务取) */
            xQueueSend(g_frame_queue, &fb, pdMS_TO_TICKS(5000));
        }
#endif
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* === 任务3: AI 推理 === */
void vTaskAI(void *arg)
{
    bsp_ai_init();

    for (;;) {
#if 1 /* STEP4~6: 推理 */
        uint8_t *fb = NULL;
        if (xQueueReceive(g_frame_queue, &fb, pdMS_TO_TICKS(1000)) == pdTRUE && fb) {
            /* 1. 预处理 */
            preprocess_rgb565(fb, g_ai_input);

            /* 2. 推理 */
            if (bsp_ai_run(g_ai_input, g_ai_output) == 0) {
                /* 3. 后处理 */
                int n = bsp_yolo_post_process(g_ai_output, &g_det_result, 320, 320);

                /* 4. 串口输出结果 */
                char buf[256];
                int len = 0;
                for (int i = 0; i < n; i++) {
                    detection_t *d = &g_det_result.dets[i];
                    len += snprintf(buf + len, sizeof(buf) - len,
                        "[DET %d] cls=%d score=%.2f bbox=[%.2f %.2f %.2f %.2f]\r\n",
                        i, d->class_id, d->score,
                        d->bbox[0], d->bbox[1], d->bbox[2], d->bbox[3]);
                }
                if (n == 0) {
                    len = snprintf(buf, sizeof(buf), "[DET] nothing\r\n");
                }
                HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 100);
            }
        }
#else
        vTaskDelay(pdMS_TO_TICKS(1000));
#endif
    }
}