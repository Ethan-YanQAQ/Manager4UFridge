# Manager4UFridge —— 智能冰箱食材管理系统

基于 STM32H743 的多模态智能冰箱食材管理模块，结合计算机视觉与传感器技术，实现食材自动识别、存取追踪与腐坏预警。

## 功能规划

| 功能 | 说明 | 状态 |
|------|------|------|
| 食材录入与识别 | YOLO 视觉识别 + IoU 前后帧对比，自动判定存取操作 | 🚧 开发中 |
| 食材时效管理 | 记录存放时间，可视化展示，腐坏预警 | 🚧 开发中 |
| 微信小程序 | 库存查看、新鲜度色标、存取历史、AI 对话助手 | ✅ 已完成 |
| AI 智能体 | DeepSeek API 接入，菜谱推荐 + 采购建议 | 🚧 CloudBase 配置中 |
| 模型部署 | YOLO11n INT8 量化 → QSPI Flash 存储 → STM32H743 推理 | 📋 部署中 |
| 3D 打印机壳 | 模拟冰箱外壳，摄像头 + LED 补光 + 传感器安装 | 📋 计划中 |
| 变质检测 | MQ135/MQ137 气体传感器多模态评估 | 📋 计划中 |

## 硬件方案

| 组件 | 型号 | 关键参数 | 接口 |
|------|------|---------|------|
| 主控 | STM32H743VIT6 | Cortex-M7, 480MHz, 2MB Flash, 1MB SRAM, LQFP100 | — |
| 晶振 | 无源 25MHz | HSE, 经 PLL 倍频至 480MHz | OSC_IN/OUT |
| 外部存储 | **W25Q256JV** | 32MB NOR Flash, 133MHz, Quad SPI | QSPI @ 0x90000000 |
| WiFi | ESP-01S | AT 指令集, TCP/HTTP 透传 | UART |
| 摄像头 | **OV2640** | 200万像素 UXGA, 15fps, SCCB 配置 | DCMI 8-bit |
| 门磁 | A3144 | 霍尔传感器, 开门检测 | GPIO 中断 |
| 气体传感器 | MQ135/MQ137 | 多模态变质评估（计划中） | ADC |

### QSPI 引脚分配

| 信号 | 引脚 | AF |
|------|------|-----|
| QSPI_CLK | PB2 | AF9 |
| QSPI_NCS | PB10 | AF9 |
| QSPI_IO0 | PD11 | AF9 |
| QSPI_IO1 | PD12 | AF9 |
| QSPI_IO2 | PE2 | AF9 |
| QSPI_IO3 | PA1 | AF9 |

### 时钟配置（CubeMX）

```
HSE: 25MHz 无源晶振
PLL1: /5 ×160 /2 = 480MHz SYSCLK
QSPI Kernel Clock: 240MHz (HCLK3), Prescaler=1 → 120MHz SCK
```

## 项目结构

```
Manager4UFridge/
├── H743/H743VIT6_test/          # STM32CubeIDE 固件工程
│   ├── Core/Inc/                # 用户头文件
│   ├── Core/Src/                # 用户源码（main.c, esp01s.c …）
│   ├── Core/Startup/            # 启动文件
│   ├── Drivers/STM32H7xx_HAL_Driver/  # HAL 库
│   └── H743VIT6_test.ioc        # CubeMX 工程配置
│
├── H743_QSPI_REF/               # STM32H743 QSPI Memory-Mapped 参考工程（GitHub）
│   ├── Memory Mapped Mode/      # ★ QSPI XIP 例程（含 .ioc + quadspi.c 驱动）
│   ├── Example1/                # W25Qxx 基础读写例程
│   └── CubeProgrammer ExtLoader/# 外部 Flash 烧录器 (.stldr)
│
├── Phase_0/                     # PC 端算法验证（Python）
│   ├── src/
│   │   ├── main.py              # 主入口：MOCK/真实模式
│   │   ├── detector.py          # YOLO 检测器封装
│   │   ├── iou_matcher.py       # IoU 前后帧匹配，判定存取事件
│   │   └── inventory.py         # 库存数据库（SQLite）
│   └── config.yaml              # 配置文件
│
├── YOLOv8forSTM/                # 模型训练
│   ├── train.py                 # 训练脚本（--stage teacher/student）
│   ├── build_v6.py              # 数据集构建（三源合并+去重+类合并）
│   ├── v6_results/              # 训练结果（student_best.pt, best.pt）
│   └── datasets/                # fridge_v6 数据集（28类, 13,018图）
│
├── miniapp/                     # 微信小程序（uni-app + Vue3 + 微信云开发）
│   ├── pages/                   # 5 页面：首页、库存、历史、预警、AI 对话
│   ├── cloudfunctions/          # 6 云函数：addDetection, getInventory, getHistory,
│   │                            #            api, aiAdvisor, chatAI
│   └── STM32_to_Cloud.md        # STM32 → 云函数对接指南
│
├── stm32h7notes.md              # ★ STM32H7 开发笔记（MPU/Cache/QSPI/Cube.AI/HardFault）
├── task_plan.md                 # 全项目计划与当前状态
├── findings.md                  # 研究记录与发现（训练/量化/部署）
├── progress.md                  # 开发会话日志
├── CLAUDE.md                    # Claude Code 项目指南
└── README.md
```

## Phase_0 快速开始

### 环境

- Python ≥ 3.10
- 本地 conda 环境 `fridge_ai`（RTX 4060 Laptop 8GB VRAM, CUDA 12.1）
- 依赖安装：`pip install -r Phase_0/requirements.txt`

### 运行 MOCK 模式（无需模型权重）

```bash
cd Phase_0/src
python main.py
```

使用预置的合成检测数据，验证 IoU 存取判定算法的完整流程。

### 运行真实推理模式

```bash
python main.py --real --image-before <开门前图片> --image-after <关门后图片>
```

需要先将 YOLO 权重文件放入 `Phase_0/models/`。

## 算法思路

```
开门前拍照 → YOLO 检测 → 关门后拍照 → YOLO 检测
                                              ↓
                               IoU 前后帧匹配比对
                              ┌──────┼──────┐
                              │      │      │
                           STILL  ADDED  REMOVED
                              │      │      │
                              ▼      ▼      ▼
                           更新库存数据库（SQLite）
                              │
                              ▼
                    新鲜度计算 → 腐坏预警
```

## 模型部署方案

```
YOLO11n FP32 (student_best.pt, 2.6M参数, mAP50=0.935)
    → ONNX 导出
    → X-CUBE-AI INT8 量化（~2.48MB 权重）
    → QSPI Flash Memory-Mapped 存储 @ 0x90000000
    → Cube.AI 生成 C 推理代码
    → STM32H743 Cortex-M7 @ 480MHz 本地推理
```

### 关键约束

- STM32H743 内部 Flash 2MB，YOLO11n INT8 权重 2.48MB → **必须 QSPI 外部 Flash 存储**
- 内部 SRAM 1MB，INT8 激活值比 FP32 减半，需 Cube.AI 分析后确认
- Cortex-M7 无 NPU，推理预计 2-5 秒/帧（可接受）

### 训练结果（v6）

| 模型 | 参数 | mAP50 | mAP95 | 文件 |
|------|------|-------|-------|------|
| **YOLO11l Teacher** | 25M | **0.958** | 0.914 | `v6_results/best.pt` (49MB) |
| **YOLO11n Student** | 2.6M | **0.935** | 0.859 | `v6_results/student_best.pt` (5.2MB) |

数据集：28 类，13,018 张图（train=10,414, val=2,604），芋冰比 16.2x。

### STM32 部署工具链

| 工具 | 用途 |
|------|------|
| STM32CubeMX + X-CUBE-AI | 引脚/时钟/QSPI 配置 + 模型导入/量化/生成 C 代码 |
| VS Code + arm-none-eabi-gcc | 编辑/编译 |
| CubeProgrammer | 烧录内部 Flash + 外部 QSPI Flash (.stldr) |
| 参考工程 | `H743_QSPI_REF/` — QSPI Memory-Mapped 完整驱动 |

## 参考资源

| 资源 | 说明 |
|------|------|
| [stm32h7notes.md](stm32h7notes.md) | STM32H7 开发笔记（MPU/Cache/QSPI/Cube.AI/常见坑） |
| [task_plan.md](task_plan.md) | 全项目计划与分阶段任务 |
| [findings.md](findings.md) | 研究记录（训练/v6/量化/ST YOLO） |
| [progress.md](progress.md) | 开发会话日志 |
| `H743_QSPI_REF/Memory Mapped Mode/` | QSPI XIP 参考 .ioc + quadspi.c 驱动 |
| `miniapp/STM32_to_Cloud.md` | STM32 → 云函数对接指南 |

## Git 管理说明

本项目已配置 `.gitignore`，以下内容**不会**被提交到仓库：

- 编译产物（`Debug/`, `*.o`, `*.elf` …）
- IDE 配置（`.settings/`, `.cproject` …）
- 数据集（`datasets/`）
- 模型权重（`*.pt`）
- 数据库文件（`*.db`）

---

👤 **EthanYanQAQ**