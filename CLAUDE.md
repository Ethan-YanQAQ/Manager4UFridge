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

开发环境：STM32CubeMX（独立版）+ VS Code + arm-none-eabi-gcc + STM32 for VSCode 插件。

```bash
# CubeMX 打开 .ioc → 配引脚/QSPI → X-CUBE-AI 加载模型 → 生成代码
# VS Code 打开工程 → 写业务逻辑 → Build → Flash
```

QSPI 参考工程在 `H743_QSPI_REF/`，已通过代理克隆成功。

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
│  H743/H743VIT6_test/  （STM32 固件）              │
│  Core/Src/main.c    — 入口，ESP-01S WiFi 初始化   │
│  Core/Src/esp01s.c  — AT 指令驱动（UART 透传）    │
│  Core/Inc/esp01s.h  — ESP01S_HandleTypeDef 接口   │
│  计划加入：QSPI + DCMI + X-CUBE-AI 推理           │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  H743_QSPI_REF/  （QSPI Memory-Mapped 参考工程）   │
│  Memory Mapped Mode/H743_QSPI_XIP_1.ioc  — CubeMX │
│  Memory Mapped Mode/Core/Src/quadspi.c  — 驱动    │
│  Example1/Core/Src/w25qxx_qspi.c  — W25Qxx 驱动   │
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

### 模型部署方案

```
YOLO11n FP32 (student_best.pt, mAP50=0.935)
    → ONNX 导出
    → X-CUBE-AI INT8 量化（~2.48MB 权重）
    → QSPI Flash Memory-Mapped 存储 @ 0x90000000
    → Cube.AI 生成 C 推理代码
    → STM32H743 Cortex-M7 @ 480MHz 本地推理
```

### 关键约束

- STM32H743：**2MB Flash, 1MB SRAM，无 NPU**
- 外部晶振：**25MHz 无源晶振 (HSE)**
- YOLO11n INT8 权重 2.48MB > 内部 Flash → **必须 QSPI 外部 Flash**（W25Q256 32MB）
- QSPI Memory-Mapped @ 0x90000000，启用 D-Cache 后性能接近内部 Flash
- QSPI 引脚：PB2(CLK), PB10(NCS), PD11(IO0), PD12(IO1), PE2(IO2), PA1(IO3)
- W25Q256 DummyCycles=8, Fast Read=0xEB(1-4-4), FlashSize=24(32MB)
- 初始化顺序：`MPU_Config() → SystemClock_Config(Scale=0, 480MHz) → MX_QUADSPI_Init() → SCB_EnableICache/DCache()`
- DMA 与 D-Cache 一致性问题：`SCB_InvalidateDCache_by_Addr()` / `SCB_CleanDCache_by_Addr()` 必须 32 字节对齐
- 常见 HardFault：QSPI 区域没配 MPU Region / Cache 在 MPU 之前开了 / DummyCycles 填错

### 开发环境

| 需求 | 工具 |
|------|------|
| Python | conda env `fridge_ai`, Python 3.10, ultralytics 8.4.60 |
| 本地 GPU | RTX 4060 Laptop 8GB VRAM, CUDA 12.1 |
| 远程 GPU | RTX 3080 10G @ 223.109.239.36:10220（备用） |
| STM32 配置 | STM32CubeMX（独立版）+ X-CUBE-AI 插件 |
| STM32 编码 | VS Code + arm-none-eabi-gcc + STM32 for VSCode |
| 3D 建模 | Fusion 360（个人版免费）|
| 微信小程序 | HBuilderX + 微信开发者工具 |

## 关键文件索引

| 文件 | 内容 |
|------|------|
| `stm32h7notes.md` | STM32H7 开发笔记：MPU/Cache/QSPI/Cube.AI/HardFault 速查 |
| `task_plan.md` | 全项目分阶段计划（Phase 1-12）|
| `findings.md` | 研究记录：训练/数据集/ST YOLO/量化/部署预研 |
| `progress.md` | 开发会话日志 |
| `miniapp/STM32_to_Cloud.md` | STM32 → ESP8266 → 云函数对接指南 |
| `H743_QSPI_REF/Memory Mapped Mode/` | QSPI XIP 参考 .ioc + quadspi.c |

## 关键约束

- 模型权重（`*.pt`）、数据集（`datasets/`）、训练输出（`runs/`）均不入库，已在 `.gitignore` 排除
- `ssh_server.py`、`train_*.log`、`*.pt`、`*.zip`、`*.tar.gz` 已在 `.gitignore` 排除
- 推送前确保无 >100MB 文件（GitHub 硬限制）
- STM32CubeMX crdb.zip 下载失败需配代理 `Help → Updater Settings → Manual → http://127.0.0.1:33210`
- git clone 需要配代理 `export https_proxy=http://127.0.0.1:33210`