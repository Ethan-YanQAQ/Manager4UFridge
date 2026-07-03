/**
 * bsp_ai.c - Cube.AI YOLO11n 推理封装
 *
 * 使用 ai_network_create_and_init() 一键初始化
 * 激活值放 SDRAM, 权重从 QSPI Flash Memory-Mapped 读取
 */

#include "bsp_ai.h"
#include "network.h"
#include "network_data.h"

static ai_handle g_network = AI_HANDLE_NULL;

/* 激活值缓冲 (SDRAM) */
static AI_ALIGNED(4)
uint8_t g_activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE]
    __attribute__((section(".sdram_data")));

int bsp_ai_init(void)
{
    ai_error err;

    /* 权重 = QSPI Flash 0x90000000 (Memory-Mapped 直接读) */
    const ai_handle weights[] = { AI_NETWORK_DATA_WEIGHTS_GET() };
    const ai_handle activations[] = { g_activations };

    err = ai_network_create_and_init(&g_network, activations, weights);
    if (err.type != AI_ERROR_NONE) {
        return -1;
    }
    return 0;
}

int bsp_ai_run(float *input, float *output)
{
    ai_buffer ai_in[1];
    ai_buffer ai_out[1];
    ai_i32 nbatch;

    ai_in[0]  = AI_NETWORK_IN_1;
    ai_in[0].data  = AI_HANDLE_PTR(input);

    ai_out[0] = AI_NETWORK_OUT_1;
    ai_out[0].data = AI_HANDLE_PTR(output);

    nbatch = ai_network_run(g_network, &ai_in[0], &ai_out[0]);
    if (nbatch != 1) {
        return -1;
    }
    return 0;
}