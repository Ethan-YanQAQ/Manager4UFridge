/**
 * bsp_ov5640.h - OV5640 摄像头驱动 (基于野火 H743 移植)
 *
 * 适配: STM32H743IIT6 核心板 + OV5640 DVP 8-bit
 * I2C: 软 SCCB (PB3=SDA, PB4=SCL) 替代硬件 I2C
 */

#ifndef __BSP_OV5640_H
#define __BSP_OV5640_H

#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

/* ── 图像尺寸 ── */
#define OV5640_WIDTH   320
#define OV5640_HEIGHT  240

/* ── DCMI 引脚 (我们的板子) ── */
/* VSYNC */
#define DCMI_VSYNC_PORT         GPIOB
#define DCMI_VSYNC_CLK()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define DCMI_VSYNC_PIN          GPIO_PIN_7
#define DCMI_VSYNC_AF           GPIO_AF13_DCMI
/* HSYNC */
#define DCMI_HSYNC_PORT         GPIOH
#define DCMI_HSYNC_CLK()        __HAL_RCC_GPIOH_CLK_ENABLE()
#define DCMI_HSYNC_PIN          GPIO_PIN_8
#define DCMI_HSYNC_AF           GPIO_AF13_DCMI
/* PIXCLK */
#define DCMI_PIXCLK_PORT        GPIOA
#define DCMI_PIXCLK_CLK()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define DCMI_PIXCLK_PIN         GPIO_PIN_6
#define DCMI_PIXCLK_AF          GPIO_AF13_DCMI
/* PWDN */
#define DCMI_PWDN_PORT          GPIOD
#define DCMI_PWDN_CLK()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define DCMI_PWDN_PIN           GPIO_PIN_7
/* RST */
#define DCMI_RST_PORT           GPIOA
#define DCMI_RST_CLK()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define DCMI_RST_PIN            GPIO_PIN_15

/* D0-D7 */
#define DCMI_D0_PORT            GPIOC
#define DCMI_D0_CLK()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define DCMI_D0_PIN             GPIO_PIN_6
#define DCMI_D0_AF              GPIO_AF13_DCMI

#define DCMI_D1_PORT            GPIOC
#define DCMI_D1_CLK()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define DCMI_D1_PIN             GPIO_PIN_7
#define DCMI_D1_AF              GPIO_AF13_DCMI

#define DCMI_D2_PORT            GPIOC
#define DCMI_D2_CLK()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define DCMI_D2_PIN             GPIO_PIN_8
#define DCMI_D2_AF              GPIO_AF13_DCMI

#define DCMI_D3_PORT            GPIOC
#define DCMI_D3_CLK()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define DCMI_D3_PIN             GPIO_PIN_9
#define DCMI_D3_AF              GPIO_AF13_DCMI

#define DCMI_D4_PORT            GPIOC
#define DCMI_D4_CLK()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define DCMI_D4_PIN             GPIO_PIN_11
#define DCMI_D4_AF              GPIO_AF13_DCMI

#define DCMI_D5_PORT            GPIOD
#define DCMI_D5_CLK()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define DCMI_D5_PIN             GPIO_PIN_3
#define DCMI_D5_AF              GPIO_AF13_DCMI

#define DCMI_D6_PORT            GPIOB
#define DCMI_D6_CLK()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define DCMI_D6_PIN             GPIO_PIN_8
#define DCMI_D6_AF              GPIO_AF13_DCMI

#define DCMI_D7_PORT            GPIOB
#define DCMI_D7_CLK()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define DCMI_D7_PIN             GPIO_PIN_9
#define DCMI_D7_AF              GPIO_AF13_DCMI

/* ── OV5640 设备地址 ── */
#define OV5640_ADDR_WRITE  0x78
#define OV5640_ADDR_READ   0x79
#define OV5640_PIDH        0x300A
#define OV5640_PIDL        0x300B

/* ── 类型定义 ── */
typedef struct {
    uint8_t PIDH;
    uint8_t PIDL;
} OV5640_IDTypeDef;

/* ── Debug 宏 ── */
#define CAMERA_DEBUG(fmt, arg...)  printf("<<-CAMERA->> " fmt "\r\n", ##arg)

/* ── API ── */
void OV5640_HW_Init(void);
void OV5640_Reset(void);
void OV5640_ReadID(OV5640_IDTypeDef *id);
void OV5640_RGB565Config(void);
void OV5640_Init(void);
void OV5640_DMA_Config(uint32_t buf_addr, uint32_t buf_size);

/* ── 外部变量 ── */
extern DCMI_HandleTypeDef  DCMI_Handle;
extern DMA_HandleTypeDef   DMA_Handle_dcmi;

#endif /* __BSP_OV5640_H */