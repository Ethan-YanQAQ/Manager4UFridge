# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

Manager4UFridge — 基于 STM32H743 的智能冰箱食材管理系统。四个子系统：STM32 固件、PC 端算法验证、YOLO 模型训练、微信小程序。

## 常用命令

### Phase_0 算法验证（PC）

```bash
cd Phase_0/src
python main.py                         # MOCK 模式：预置合成数据，验证 IoU 存取判定
python main.py --real --image-before <前> --image-after <后>  # 真实推理（需 YOLO 权重）
```

### YOLO 模型训练

训练在远程 RTX 3080 云服务器（223.109.239.36:10220）上运行：

```bash
python train.py --stage teacher      # 训练 YOLO11l 教师模型（batch=14）
python train.py --stage student      # 训练 YOLO11n 学生模型（batch=32，直接训练不蒸馏）
```

数据集构建：
```bash
python build_v6.py                   # 从三个原始 zip 重建 fridge_v6（28 类）
```

SSH 登录（需要 paramiko，`ssh_server.py` 不入库）：
```bash
python3 ssh_server.py "<remote command>"
```

### STM32 固件

HAL 库基于 STM32CubeIDE 生成，在 IDE 中编译烧录。`main.c` 初始化后循环闪烁 LED。

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
│    └── --stage student: YOLO11n (batch=32, 直训) │
│  build_v6.py：数据集构建脚本                       │
│    └── 三源合并(Robofow v1+v4+Fruit) + MD5去重   │
│        + 去高密度堆叠 + 类合并(28类)               │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  H743/H743VIT6_test/  （STM32 固件）              │
│  Core/Src/main.c    — 入口，ESP-01S WiFi 初始化   │
│  Core/Src/esp01s.c  — AT 指令驱动（UART 透传）    │
│  Core/Inc/esp01s.h  — ESP01S_HandleTypeDef 接口   │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  miniapp/  （微信小程序 — 计划中）                 │
│  uni-app + Vue3 + 腾讯云 IoT + MQTT              │
│  ├── 库存查看（新鲜度色标）                        │
│  ├── 存取历史时间线                                │
│  └── 腐坏预警推送                                  │
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

数据集：28 类，13,018 张图（train=10,414），芋冰比 16.2x。权重文件在 `v6_results/`。

### 微信小程序架构（方案 A — 计划中）

```
STM32 ──UART──▶ ESP-01S ──WiFi──▶ MQTT ──▶ 腾讯云 IoT ──▶ 微信小程序
```
详细计划见 `task_plan_miniapp.md`。

## 自定义 Skills

- **git-manager**：自动化 Git 全流程 — 读 diff → 写 Conventional Commits → 更新 README → 检查 .gitignore → push
- **smarter-debug**：调试助手 — 优先追溯"最后已知正常"状态，查日志、对话上下文、Git 历史锁定变化窗口，再诊断修复
- **planning-with-files**：Manus 风格持久化规划 — task_plan.md / findings.md / progress.md

## 关键约束

- 模型权重（`*.pt`）、数据集（`datasets/`）、训练输出（`runs/`）均不入库，已在 `.gitignore` 排除
- `ssh_server.py`、`train_*.log`、`*.pt`、`*.zip`、`*.tar.gz` 已在 `.gitignore` 排除
- 推送前确保无 >100MB 文件（GitHub 硬限制）
- 训练服务器：RTX 3080 10G + Ubuntu 22.04, Python 3.11, PyTorch 2.2.2, ultralytics 8.4.60
