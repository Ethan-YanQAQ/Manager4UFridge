/**
 * bsp_yolo_post.h - YOLO11n 输出后处理
 *
 * 输入:  f32[1×32×2100] YOLO 输出
 *        32 = 4 bbox + 28 class scores
 * 输出:  detection_t 数组
 */

#ifndef __BSP_YOLO_POST_H
#define __BSP_YOLO_POST_H

#include <stdint.h>

#define YOLO_NC         28          /* 类别数 */
#define YOLO_NOUT_CELLS 2100        /* 输出网格数 */
#define YOLO_NOUT_DIM   32          /* 每格输出维度 (4 bbox + 28 class) */
#define YOLO_CONF_THRESH 0.5f       /* 置信度阈值 */
#define YOLO_NMS_THRESH  0.45f      /* NMS IoU 阈值 */
#define YOLO_MAX_DET     20         /* 最大检出数 */

/* 检测结果 */
typedef struct {
    float  bbox[4];     /* [x1, y1, x2, y2] 归一化 0~1 */
    float  score;       /* 置信度 */
    uint8_t class_id;   /* 类别索引 0~27 */
} detection_t;

typedef struct {
    detection_t dets[YOLO_MAX_DET];
    int count;
} detection_list_t;

int bsp_yolo_post_process(
    const float *output,            /* YOLO 输出 [32*2100] */
    detection_list_t *result,       /* 结果 */
    int input_w, int input_h);      /* 输入分辨率 (320) */

#endif /* __BSP_YOLO_POST_H */