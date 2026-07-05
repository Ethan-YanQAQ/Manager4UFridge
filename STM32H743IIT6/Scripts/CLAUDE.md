# CLAUDE.md — 野火 OV5640 摄像头驱动移植

## 当前工作

**工作目录**: `E:\46\` (野火 H743 OV5640 Keil 工程)
**目标**: 最简移植——只改引脚和 I2C/SDRAM，跑通摄像头出图

## 硬件引脚 (实际板子)

```
摄像头:
  PA6  - PCLK (DCMI_PIXCLK)
  PA8  - XCLK (MCO1 → 25MHz)
  PB3  - SDA (软 SCCB, GPIO Output)
  PB4  - SCL (软 SCCB, GPIO Output)
  PB7  - VSYNC (DCMI_VSYNC)
  PH8  - HSYNC (DCMI_HSYNC)
  PC6  - D0
  PC7  - D1
  PC8  - D2
  PC9  - D3
  PC11 - D4
  PD3  - D5
  PB8  - D6
  PB9  - D7
  PA15 - RST (GPIO Output, 低有效)
  PD7  - PWDN (GPIO Output, 低有效)

FMC SDRAM (W9825G6KH 32MB, Bank 1 → 0xC0000000):
  PF0-5,PF12-15,PG0-2  - A0-A12
  PD14-15,PD0-1,PE7-15,PD8-10 - D0-D15
  PG4-5  - BA0-BA1
  PC2    - SDNE0 (CS)    ← 与野火(PH6)不同
  PC3    - SDCKE0         ← 与野火(PH7)不同
  PC0    - SDNWE
  PF11   - SDNRAS
  PG15   - SDNCAS
  PG8    - SDCLK
  PE0-1  - NBL0-NBL1

串口: PA9(TX) PA10(RX) CH340→USB, 115200bps
调试: PA13(SWDIO) PA14(SWCLK)
```

## 代码修改 (相对野火原版 @ E:\46\)

### bsp_ov5640.h — 引脚宏全替换

| 引脚 | 野火 → 我们 |
|------|-----------|
| VSYNC | PI5 → PB7 |
| HSYNC | PA4 → PH8 |
| PIXCLK | PA6 (不变) |
| PWDN | PG3 → PD7 |
| RST | PB5 → PA15 |
| SCL | PB6 → PB4 |
| SDA | PB7 → PB3 |
| D0-D7 | PH9-14,PI6-7 → PC6-9,PC11,PD3,PB8-9 |

### bsp_ov5640.c — 硬件I2C→软SCCB

- 删除 `#include "./i2c/bsp_i2c.h"` 和 `#include "./delay/core_delay.h"`
- 添加软 SCCB: `sccb_delay/start/stop/wb/rb`
- 添加 `OV5640_WriteReg(reg,val)` 和 `OV5640_ReadReg(reg)` (软 SCCB)
- 添加 `OV5640_WriteFW` 空桩 (AF 模块引用)
- `Delay()` → NOP 循环

### bsp_sdram.h — SDRAM Bank1 适配

| 宏 | 野火 | 我们 |
|------|------|------|
| FMC_CS (SDNE0) | PH6 | **PC2** |
| FMC_CKE (SDCKE0) | PH7 | **PC3** |
| FMC_BANK_SDRAM | Bank2 | **Bank1** |
| FMC_COMMAND_TARGET | BANK2 | **BANK1** |
| SDRAM_BANK_ADDR | 0xD0000000 | **0xC0000000** |

### bsp_sdram.c — SDBank 修正

- `hsdram1.Init.SDBank`: `FMC_SDRAM_BANK2` → `FMC_SDRAM_BANK1`

### bsp_lcd.h — 帧缓冲地址修正

- `LCD_FB_START_ADDRESS`: `0xD0000000` → `0xC0000000`

### main.c

- 注释 `I2CMaster_Init()` — 软 SCCB 不需要硬件 I2C
- 注释 `OV5640_AUTO_FOCUS()` — 摄像头模组无自动对焦

### bsp_i2c.c

- `OV5640_WriteReg/ReadReg` 用 `#if 0` 包裹 — 避免和 bsp_ov5640.c 重复

## 编译环境

Keil V5.06 (ARMCC V5), C89 标准
工程: `E:\46\Project\RVMDK（uv5）\Fire_H7.uvprojx`

## 当前状态

- 编译: **0 errors, 0 warnings**（Keil Prof 版）
- 下一步：烧录 → 串口查看 OV5640 初始化日志 → 确认 PID=0x5640