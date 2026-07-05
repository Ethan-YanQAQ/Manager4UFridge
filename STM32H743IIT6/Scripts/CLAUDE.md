# CLAUDE.md — 野火 OV5640 摄像头驱动移植

## 当前工作

**工作目录**: `E:\46\` (野火 H743 OV5640 Keil 工程)
**目标**: 最简移植——只改引脚和 I2C，跑通摄像头出图

## 原始代码

**野火原版 (未修改)**: `E:\VScodeProjects\QS\Refcode\wildfire\`
**CubeMX 自建工程 (之前)**: `E:\VScodeProjects\QS\STM32H743IIT6\IITx6\`

## 硬件引脚

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

串口: PA9(TX) PA10(RX) CH340→USB, 115200bps
调试: PA13(SWDIO) PA14(SWCLK)

FMC SDRAM (W9825G6KH 32MB, Bank 1, 基址 0xC0000000):
  PF0    - FMC_A0
  PF1    - FMC_A1
  PF2    - FMC_A2
  PF3    - FMC_A3
  PF4    - FMC_A4
  PF5    - FMC_A5
  PF12   - FMC_A6
  PF13   - FMC_A7
  PF14   - FMC_A8
  PF15   - FMC_A9
  PG0    - FMC_A10
  PG1    - FMC_A11
  PG2    - FMC_A12
  PD14   - FMC_D0
  PD15   - FMC_D1
  PD0    - FMC_D2
  PD1    - FMC_D3
  PE7    - FMC_D4
  PE8    - FMC_D5
  PE9    - FMC_D6
  PE10   - FMC_D7
  PE11   - FMC_D8
  PE12   - FMC_D9
  PE13   - FMC_D10
  PE14   - FMC_D11
  PE15   - FMC_D12
  PD8    - FMC_D13
  PD9    - FMC_D14
  PD10   - FMC_D15
  PG4    - FMC_BA0
  PG5    - FMC_BA1
  PC0    - FMC_SDNWE
  PC2    - FMC_SDNE0 (CS)
  PC3    - FMC_SDCKE0
  PF11   - FMC_SDNRAS
  PG15   - FMC_SDNCAS
  PG8    - FMC_SDCLK
  PE0    - FMC_NBL0 (LDQM)
  PE1    - FMC_NBL1 (UDQM)
```

## 代码修改 (相对野火原版)

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
| D0-D7 | PH9-14,PD3,PI6-7 → PC6-9,PC11,PD3,PB8-9 |

### bsp_ov5640.c — 硬件I2C→软SCCB

- 删除 `#include "./i2c/bsp_i2c.h"` 和 `#include "./delay/core_delay.h"`
- 添加软 SCCB: `sccb_delay/start/stop/wb/rb`
- 添加 `OV5640_WriteReg(reg,val)` 和 `OV5640_ReadReg(reg)` (软 SCCB 实现)
- 添加 `OV5640_WriteFW` 空桩 (AF 模块需要引用)
- `Delay()` → NOP 循环 (SCCB ~100kHz, 无需精确定时)

### main.c

- 注释 `I2CMaster_Init()` — 软 SCCB 不需要硬件 I2C 初始化
- 注释 `OV5640_AUTO_FOCUS()` — 摄像头模组无自动对焦

### bsp_i2c.c

- `OV5640_WriteReg/ReadReg` 用 `#if 0` 包裹 — 避免和 bsp_ov5640.c 重复

## 编译环境

Keil V5.06 (ARMCC V5), C89 标准
工程: `E:\46\Project\RVMDK（uv5）\Fire_H7.uvprojx`

## 当前状态

- 编译: **0 errors, 0 warnings**（Keil 已注册 Prof 版，无 32KB 限制）
- include path 完整（`..\..\Libraries\STM32H7xx_HAL_Driver\Inc` 在 uvprojx 第 339 行）
- 下一步：烧录 → 串口查看 OV5640 初始化日志 → 确认 PID=0x5640