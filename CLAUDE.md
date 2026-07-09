# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

Manager4UFridge — 基于 STM32H743 的智能冰箱食材管理系统。五个子系统：YOLO 模型训练、STM32 固件、PC 算法验证、微信小程序、3D 打印机壳。

## 常用命令

### Phase_0 算法验证（PC）

```bash
cd Phase_0/src
python main.py                         # MOCK 模式：预置合成数据，验证 IoU 存取判定
python main.py --real --image-before <前> --image-after <后>  # 真实推理（需 YOLO 权重）
```

### YOLO 模型训练

本地 RTX 4060 Laptop 8GB VRAM，conda 环境 `fridge_ai`（CUDA 12.1, Python 3.10, ultralytics 8.4.60）：

```bash
conda activate fridge_ai
cd YOLOv8forSTM
python train.py --stage teacher      # 训练 YOLO11l 教师模型（batch=14）
python train.py --stage student      # 训练 YOLO11n 学生模型（batch=32）
```

远程 RTX 3080 云服务器（223.109.239.36:10220）备用（已不用）：
```bash
python3 ssh_server.py "<remote command>"
```

数据集已解压到本地 `YOLOv8forSTM/datasets/fridge_v6/`，dataset.yaml path 已改为本地路径。

### STM32 固件

**开发环境**：Keil MDK (ARM Compiler 5/6)，基于正点原子 H743 例程模板。

**基础模板**：[39/](39/) — 正点原子 OV5640 + DCMI + LCD 摄像头例程，已编译通过。

**参考例程**：[RefCodes/【正点原子】阿波罗STM32H743开发板/](RefCodes/【正点原子】阿波罗STM32H743开发板/) — 完整 64 个 HAL 例程（包含 QSPI/SDRAM/MPU 等）。
**驱动备份**：[Scripts/](Scripts/) — 从 RefCodes 提取的关键实验驱动代码（QSPI/SDRAM/MPU/LTDC_LCD/USMART 等 9 个）。

#### 硬件确认

- 自制 H743 板卡与正点原子"阿波罗 H743 开发板"非常相似
- **SDRAM、串口、DCMI 引脚与正点原子一致** → 正点原子 BSP 驱动无需修改
- 系统时钟保持 400MHz（已验证可靠）

#### 工作流程铁律

1. **main.c 只做调用，不做定义** — 原有代码原封不动，仅新增 `glue_run()` 一行调用
2. **不修改已有驱动** — `Drivers/BSP/`、`Drivers/SYSTEM/`、`Middlewares/` 下的代码保持原样
3. **所有新功能写入独立模块** — `User/module_xxx.c/h`，include 已有驱动头文件即可
4. **胶水脚本实现分步调试** — `User/glue.c/h` 串联模块，`#define STEP_DEBUG` 宏控制分步/全速模式

#### 工程结构

```
39/
├── Drivers/BSP/              ← [不改] 正点原子驱动 (DCMI/LCD/SDRAM/OV5640/KEY/LED/MPU...)
├── Drivers/SYSTEM/           ← [不改] 系统组件 (delay/sys/usart)
├── Drivers/STM32H7xx_HAL_Driver/ ← [不改] HAL 库
├── Middlewares/USMART/       ← [不改] 串口调试工具
├── User/
│   ├── main.c               ← [最小改动] 只新增 glue_run() 调用
│   ├── glue.c/h             ← [新增] 胶水脚本，模块级联 + STEP_DEBUG
│   ├── module_qspi.c/h      ← [新增] QSPI/W25Q256 功能模块
│   ├── module_wifi.c/h      ← [新增] ESP-01S WiFi 功能模块
│   └── ...
└── Projects/                 ← [不改] Keil 工程文件
```

#### 39/ main.c 关键信息

| 项目 | 值 |
|------|-----|
| 系统时钟 | 400MHz (`sys_stm32_clock_init(160,5,2,4)`) |
| SDRAM 基址 | 0xC0000000, 32MB |
| LCD 帧缓冲 | SDRAM 低 1280×800×2 区域 |
| JPEG 帧缓冲 | 0xC01F4000 (1MB，在 LCD 帧缓冲之后) |
| 调试串口 | USART1 (PA9/PA10, 115200) |
| JPEG 输出串口 | USART2 (PA2/PA3, 921600) |
| DCMI DMA | DMA1_Stream1, 双缓冲循环模式 |
| 核心回调 | `dcmi_rx_callback` 函数指针 (运行时切换 RGB/JPEG)

### 代理配置

```bash
export https_proxy=http://127.0.0.1:33210
export http_proxy=http://127.0.0.1:33210
export all_proxy=socks5://127.0.0.1:33210
```

CubeMX 需单独在 UI 中配代理：`Help → Updater Settings → Connection Parameters → Manual → http://127.0.0.1:33210`

## 架构

```
┌─────────────────────────────────────────────────┐
│  Phase_0/src/  （Python 算法验证）                 │
│  main.py → detector.py → iou_matcher.py          │
│                  ↓                                │
│            inventory.py（SQLite）                 │
│                                                   │
│  数据流：开门前图 → YOLO检测 → IoU贪心匹配        │
│        → 关门后图 → YOLO检测 → STILL/ADDED/REMOVED│
│        → 更新库存 + 腐坏预警                       │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  YOLOv8forSTM/  （模型训练）                      │
│  train.py：统一训练脚本                            │
│    ├── --stage teacher: YOLO11l (batch=14)       │
│    └── --stage student: YOLO11n (batch=32)       │
│  build_v6.py：数据集构建脚本                       │
│    └── 三源合并(Roboflow v1+v4+Fruit) + MD5去重   │
│        + 去高密度堆叠 + 类合并(28类)               │
│  v6_results/: student_best.pt, best.pt            │
│  datasets/fridge_v6/: 28类, 13,018图(已解压本地)   │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  39/  （STM32 固件 — 基于正点原子模板）             │
│  User/main.c        — 入口，仅新增 glue_run()      │
│  User/glue.c/h      — 胶水脚本 + STEP_DEBUG       │
│  User/module_qspi.c/h  — QSPI/W25Q256            │
│  User/module_wifi.c/h  — ESP-01S WiFi AT 驱动     │
│  Drivers/BSP/       — [不改] 正点原子 BSP 驱动     │
│  RefCodes/          — 完整 64 个 HAL 参考例程       │
│  计划加入：X-CUBE-AI 推理 (YOLO11n INT8)           │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  miniapp/  （微信小程序）                          │
│  uni-app + Vue3 + 微信云开发                      │
│  ├── 5 页面：首页、库存、历史、预警、AI对话        │
│  ├── 6 云函数：addDetection, getInventory,         │
│  │            getHistory, api, aiAdvisor, chatAI  │
│  └── STM32_to_Cloud.md — 硬件对接指南             │
└─────────────────────────────────────────────────┘
```

### Phase_0 核心模块

| 模块 | 职责 |
|------|------|
| `detector.py` | YOLO 检测器封装。支持 real（ultralytics 权重）和 mock（预置 Detection 列表）两种模式 |
| `iou_matcher.py` | 贪心 IoU 匹配：同类物体内计算 IoU 矩阵 → 阈值过滤 → STILL/ADDED/REMOVED 判定 |
| `inventory.py` | SQLite 库存管理：入/出库记录、存放天数追踪、FRESH/WARNING/URGENT/EXPIRED 四级预警 |
| `config.yaml` | 模型配置（权重路径、阈值）、食材类别映射、腐坏天数阈值 |

### 训练结果（v6）

| | 模型 | 参数 | mAP50 | 推理速度 |
|------|------|------|-------|---------|
| Teacher | YOLO11l | 25M | **0.958** | 8.1ms |
| Student | YOLO11n | 2.6M | **0.935** | 1.7ms |


### 关键约束

- STM32H743：**2MB Flash, 1MB SRAM，无 NPU**
- 外部晶振：**25MHz 无源晶振 (HSE)**
- YOLO11n INT8 权重 2.48MB > 内部 Flash → **必须 QSPI 外部 Flash**（W25Q256 32MB）
- QSPI Memory-Mapped @ 0x90000000，启用 D-Cache 后性能接近内部 Flash

## 关键约束

- 模型权重（`*.pt`）、数据集（`datasets/`）、训练输出（`runs/`）均不入库，已在 `.gitignore` 排除
- `ssh_server.py`、`train_*.log`、`*.pt`、`*.zip`、`*.tar.gz` 已在 `.gitignore` 排除
- 推送前确保无 >100MB 文件（GitHub 硬限制）
- STM32CubeMX crdb.zip 下载失败需配代理 `Help → Updater Settings → Manual → http://127.0.0.1:33210`
- git clone 需要配代理 `export https_proxy=http://127.0.0.1:33210`
- ⚠️ **QSPI 引脚待确认**：阿波罗 H743 用 PB6/PF6-9，但我们板子实际走线需实地测量