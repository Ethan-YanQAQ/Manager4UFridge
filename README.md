# Manager4UFridge —— 智能冰箱食材管理系统

基于 STM32H743 的多模态智能冰箱食材管理模块，结合计算机视觉与传感器技术，实现食材自动识别、存取追踪与腐坏预警。

## 功能规划

| 功能 | 说明 | 状态 |
|------|------|------|
| 食材录入与识别 | YOLO 视觉识别 + IoU 前后帧对比，自动判定存取操作 | 🚧 开发中 |
| 食材时效管理 | 记录存放时间，可视化展示，腐坏预警 | 🚧 开发中 |
| 线上提醒 | 微信小程序 + 智能体推送 | 📋 计划中 |
| 变质检测 | MQ135/MQ137 气体传感器多模态评估 | 📋 计划中 |

## 硬件方案

- **主控**：STM32H743VIT6（Cortex-M7, 480MHz）
- **WiFi**：ESP-01S（AT 指令集，UART 透传）
- **摄像头**：OV2640
- **传感器**：A3144 霍尔传感器（门磁）、MQ135/MQ137 气体传感器
- **交互**：TFT 电容触控屏
- **补光**：LED 补光灯
- **存储**：TF 卡

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
├── Phase_0/                     # PC 端算法验证（Python）
│   ├── src/
│   │   ├── main.py              # 主入口：MOCK/真实模式
│   │   ├── detector.py          # YOLO 检测器封装
│   │   ├── iou_matcher.py       # IoU 前后帧匹配，判定存取事件
│   │   └── inventory.py         # 库存数据库（SQLite）
│   ├── models/                  # YOLOv8 权重（不入库）
│   ├── config.yaml              # 配置文件
│   └── requirements.txt         # Python 依赖
│
├── YOLOv8forSTM/                # 模型训练
│   ├── merge_dataset.py         # 数据集合并脚本（Roboflow v1+v4 → fridge_30）
│   └── datasets/                # 训练数据集（不入库）
│
├── .gitignore                   # Git 忽略规则
└── README.md
```

## Phase_0 快速开始

### 环境

- Python ≥ 3.10
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

需要先将 YOLOv8 权重文件放入 `Phase_0/models/`。

## 算法思路

```
开门前拍照 → YOLOv8 检测 → 关门后拍照 → YOLOv8 检测
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

## 模型部署计划

1. 训练 YOLOv8 模型（30 类冰箱常见食材）
2. 量化压缩至 2MB 以内（INT8 量化 / 蒸馏 / 剪枝）
3. 部署到 STM32H743 本地推理

## Git 管理说明

本项目已配置 `.gitignore`，以下内容**不会**被提交到仓库：

- 编译产物（`Debug/`, `*.o`, `*.elf` …）
- IDE 配置（`.settings/`, `.cproject` …）
- 数据集（`datasets/`）
- 模型权重（`*.pt`）
- 数据库文件（`*.db`）

如需添加新的大文件类型，请编辑 `.gitignore`。

---

👤 **EthanYanQAQ**
