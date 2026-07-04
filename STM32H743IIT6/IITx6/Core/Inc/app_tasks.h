/**
 * app_tasks.h - 应用任务胶水层
 *
 * 3 个任务 + 帧队列将摄像头→推理→输出串联
 * 每个任务体用 #if 0/1 控制激活，支持分块调试
 */

#ifndef __APP_TASKS_H
#define __APP_TASKS_H

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "queue.h"
#include "bsp_yolo_post.h"

/* 帧队列 (传递帧缓冲指针) */
extern QueueHandle_t g_frame_queue;

/* 任务入口 (给 freertos.c 引用) */
void vTaskCamera(void *arg);
void vTaskAI(void *arg);
void vTaskMonitor(void *arg);

#endif /* __APP_TASKS_H */