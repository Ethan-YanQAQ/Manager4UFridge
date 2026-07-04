/**
 * bsp_yolo_post.c - YOLO11n 后处理实现
 *
 * 解码 + NMS 去重
 * output 布局: [2100, 32] 行优先 (YOLO11n 转置后)
 *   每行: [0..3] = bbox (x1,y1,x2,y2 归一化)
 *         [4..31] = class logits (需 sigmoid)
 */

#include "bsp_yolo_post.h"
#include <math.h>
#include <string.h>

/* --- helpers --- */
static inline float sigmoid(float x) { return 1.0f / (1.0f + expf(-x)); }

static inline float maxf(float a, float b) { return (a > b) ? a : b; }
static inline float minf(float a, float b) { return (a < b) ? a : b; }

static float box_iou(const float a[4], const float b[4])
{
    float x1 = maxf(a[0], b[0]);
    float y1 = maxf(a[1], b[1]);
    float x2 = minf(a[2], b[2]);
    float y2 = minf(a[3], b[3]);
    float iw = maxf(0, x2 - x1);
    float ih = maxf(0, y2 - y1);
    float inter = iw * ih;
    float area_a = (a[2] - a[0]) * (a[3] - a[1]);
    float area_b = (b[2] - b[0]) * (b[3] - b[1]);
    float uni = area_a + area_b - inter;
    return (uni > 1e-6f) ? inter / uni : 0;
}

static void nms_sort(detection_t *d, int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (d[j].score < d[j + 1].score) {
                detection_t t = d[j]; d[j] = d[j + 1]; d[j + 1] = t;
            }
        }
    }
}

int bsp_yolo_post_process(
    const float *output, detection_list_t *result,
    int input_w, int input_h)
{
    float thr = YOLO_CONF_THRESH;
    static detection_t raw[YOLO_NOUT_CELLS];   /* static: ~50KB, 避免栈溢出 */
    int raw_cnt = 0;

    /* --- 第1步: 解码每格 → 选高于阈值的候选 --- */
    for (int ci = 0; ci < YOLO_NOUT_CELLS; ci++) {
        const float *row = output + ci * YOLO_NOUT_DIM;

        /* bbox: [x1, y1, x2, y2] 归一化 0~1 */
        float bbox[4] = {
            row[0], row[1], row[2], row[3]
        };
        /* 边界裁剪 */
        bbox[0] = minf(maxf(bbox[0], 0), 1);
        bbox[1] = minf(maxf(bbox[1], 0), 1);
        bbox[2] = minf(maxf(bbox[2], 0), 1);
        bbox[3] = minf(maxf(bbox[3], 0), 1);

        /* 找最高分数的类别 */
        float max_score = 0;
        int best_cls = 0;
        for (int k = 0; k < YOLO_NC; k++) {
            float s = sigmoid(row[4 + k]);
            if (s > max_score) { max_score = s; best_cls = k; }
        }

        if (max_score < thr) continue;

        raw[raw_cnt].score = max_score;
        raw[raw_cnt].class_id = (uint8_t)best_cls;
        memcpy(raw[raw_cnt].bbox, bbox, 4 * sizeof(float));
        raw_cnt++;
    }

    /* --- 第2步: NMS 去重 --- */
    result->count = 0;
    if (raw_cnt == 0) return 0;

    nms_sort(raw, raw_cnt);

    static uint8_t kept[YOLO_NOUT_CELLS];       /* static: 2.1KB, 避免栈溢出 */
    memset(kept, 0, sizeof(kept));
    for (int i = 0; i < raw_cnt && result->count < YOLO_MAX_DET; i++) {
        if (kept[i]) continue;
        result->dets[result->count++] = raw[i];
        for (int j = i + 1; j < raw_cnt; j++) {
            if (kept[j]) continue;
            if (box_iou(raw[i].bbox, raw[j].bbox) > YOLO_NMS_THRESH) {
                kept[j] = 1;
            }
        }
    }

    return result->count;
}