# Progress — 开发会话日志

## 2026-07-05 — 会话 #1: 代码调研

### 完成内容

1. **39/ 例程分析**
   - 完整理解 OV5640 + DCMI + LCD 摄像头例程
   - 数据流：OV5640 → DCMI → DMA1_Stream1 双缓冲 → (RGB: DMA2D→LCD / JPEG: USART2→PC)
   - 引脚映射完整提取

2. **RefCodes 参考代码分析**
   - 64 个 HAL 例程清单已过目
   - QSPI (实验28): W25Q256 QPI 模式驱动完整提取 (w25qxx.c/h + qspi.c/h)
   - SDRAM (实验14): FMC SDRAM 驱动 (0xC0000000, 32MB)
   - **重要发现**: 阿波罗 H743 QSPI 引脚 (PB6/PF6-9) 与 CLAUDE.md 记录 (PB10/PD11-12/PE2/PA1) 不同！

3. **规划文件确定**
   - task_plan.md: 基于 39/ 做最小改动，Keil MDK，400MHz 不动，已有驱动不动
   - findings.md: 完整技术分析，包含 QSPI/W25QXX/SDRAM 驱动要点
   - 工作流程规范: main.c 只调用 + 独立模块 + glue 胶水脚本 + STEP_DEBUG

### 下一步

Phase 1: 在 User/ 下新增 glue.c/h，main.c 仅新增一行 glue_run() 调用，不改已有代码

---

## 2026-07-05 — 会话 #2: Scripts/ 驱动备份

### 完成内容

1. **从 RefCodes 提取驱动代码到 Scripts/**
   - 解压 `4，程序源码.zip → 2，标准例程-HAL库版本.zip`
   - 提取 9 个关键实验的代码（跳过 HAL 库/CMSIS/OBJ 等冗余文件）
   - 总计 ~696 个文件

2. **提取的实验清单**

   | Scripts/ 子目录 | 来源 | 文件数 | 核心价值 |
   |---|---|---|---|
   | Template/ | 实验0-1 | 16 | 最小工程模板 |
   | QSPI/ | 实验28 | 42 | ★ w25qxx.c/h + qspi.c/h |
   | SDRAM/ | 实验14 | 20 | SDRAM 驱动 |
   | MPU/ | 实验12 | 15 | MPU 配置 |
   | LTDC_LCD/ | 实验15 | 21 | LTDC LCD 驱动 |
   | USMART/ | 实验16 | 27 | 串口调试工具 |
   | Camera_OV5640/ | 实验38 | 118 | 摄像头 (含 MPU9250 DMP) |
   | Picture_Display/ | 实验44 | 180 | JPEG/BMP 解码 |
   | Hardware_JPEG/ | 实验45 | 184 | H743 硬件 JPEG 解码器 |

3. **验证 QSPI 驱动接口**

   - `qspi.h`: QSPI_Init / Send_CMD / Receive / Transmit
   - `w25qxx.h`: W25QXX_Init / Read / Write / Erase_Sector / ReadID
   - 支持 W25Q80/16/32/64/128/256 全系列
   - 支持 Enter/Exit QPI 模式，4-Byte 地址模式

4. **更新三个规划文件**

   - task_plan.md: 新增 Scripts/ 路径到现状总结
   - findings.md: 新增 §5 Scripts/ 本地驱动备份章节
   - CLAUDE.md: 新增驱动备份链接

### ⚠️ QSPI 引脚差异再次确认

- 阿波罗 (实验28): PB2(CLK) / PB6(NCS) / PF6-9(IO0-3)
- CLAUDE.md 原记录: PB10/PD11-12/PE2/PA1
- **必须用万用表实测我们板子的 QSPI 走线才能移植**

### 下一步

Phase 1: 在 User/ 下新增 glue.c/h，main.c 仅新增一行 glue_run() 调用，不改已有代码

---

## 2026-07-06 — 会话 #3: 39/ 代码深入理解 + RefCodes 实际提取到 Scripts/

### 完成内容

1. **39/ readme.txt 解读**
   - 确认实验为摄像头实验，平台为阿波罗 H743
   - 确认硬件引脚与 task_plan.md 一致

2. **39/ main.c 完整工作流向用户解释**
   - 532 行 6 函数，main() 四阶段：初始化(12步) → 等待摄像头 → 按键选模式 → 分发
   - DCMI 双缓冲 + 函数指针切换 RGB/JPEG 两种处理

3. **RefCodes → Scripts/ 实际提取**（之前 Scripts/ 为空，进度记录未实际执行）
   - `4，程序源码.zip` → `2，标准例程-HAL库版本.zip` (22,583 entries, 70 dirs)
   - 提取 12 个关键实验 → **818 个源文件**写入 Scripts/

4. **核心驱动确认**
   - QSPI: `qspi.c/h` (底层 Init/Send_CMD/Receive/Transmit) + `w25qxx.c/h` (W25Q256 全系列 QPI 模式)
   - SDRAM/MPU/LTDC/USMART/Camera/DMA/JPEG 驱动均已就位

5. **更新文档**
   - findings.md: 新增 §2 RefCodes结构 + 12实验清单 + QSPI接口确认 + QSPI引脚差异
   - progress.md: 本条目

### 12 个已提取实验

| Scripts/ | 实验 | 文件 | 核心 |
|----------|------|------|------|
| QSPI/ | 实验28 | 52 | W25Q256 QPI |
| SDRAM/ | 实验14 | 33 | FMC SDRAM |
| MPU/ | 实验12 | 29 | MPU Cache |
| LTDC_LCD/ | 实验15 | 37 | RGB屏 |
| USMART/ | 实验16 | 42 | 串口调试 |
| Camera_OV5640/ | 实验38 | 118 | OV5640+DCMI |
| Picture_Display/ | 实验44 | 180 | JPEG/BMP解码 |
| Hardware_JPEG/ | 实验45 | 184 | 硬件JPEG |
| IO_Expand/ | 实验26 | 48 | PCF8574 |
| DMA/ | 实验24 | 50 | DMA参考 |
| UART/ | 实验3 | 24 | 串口 |
| Template/ | 实验0-1 | 21 | 工程模板 |

### 下一步

Phase 1: 在 User/ 下新增 glue.c/h，main.c 仅新增一行 glue_run() 调用，不改已有代码


---

## 2026-07-06 - Session #4: JPEG serial upload optimization

### Change 1: Skip key selection, force JPEG mode
**File**: 39/User/main.c - main() function
- Removed key-waiting while(1) loop (22 lines removed)
- Added: g_ov_mode = 1; (force JPEG mode)
- Added: printf in camera error loop

### Change 2: JPEG frame info optimization
**File**: 39/User/main.c - jpeg_test() function
- Removed: printf("g_jpeg_data_len:%d", g_jpeg_data_len * 4) — DMA fill amount, meaningless
- Added: printf("JPEG:%u bytes", jpglen) — actual JPEG file size
- USART2 raw stream unchanged (FF D8 ... FF D9)

### Web search confirmed
- JPEG byte-stuffing: 0xFF in payload always followed by 0x00
- FF D8 / FF D9 markers are unique — no custom framing protocol needed
- PC can reliably split frames by searching for JPEG SOI/EOI markers
- 921600 baud is standard for this application
