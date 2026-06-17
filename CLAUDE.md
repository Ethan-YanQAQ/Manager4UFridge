# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

Manager4UFridge — 基于 STM32H743 的智能冰箱食材管理系统。三个子系统：STM32 固件、PC 端算法验证、YOLO 模型训练。

## 常用命令

### Phase_0 算法验证（PC）

```bash
cd Phase_0/src
python main.py                         # MOCK 模式：预置合成数据，验证 IoU 存取判定
python main.py --real --image-before <前> --image-after <后>  # 真实推理（需 YOLO 权重）
```

### YOLO 模型训练

训练在远程 RTX 3080 云服务器上运行，conda 环境 `fridge_ai`：

```bash
python train_kd.py --stage 1                              # Stage 1: 训练 YOLO11l 教师
python train_kd.py --stage 2 --teacher <best.pt路径>       # Stage 2: 蒸馏 → YOLO11n 学生
python train_kd.py --resume <last.pt路径>                  # 从 checkpoint 恢复训练
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
│  train_kd.py：                                   │
│    KDTrainer(DetectionTrainer)                   │
│    ├── Stage 1: 标准训练 YOLO11l 教师             │
│    └── Stage 2: 响应式 KD 蒸馏 → YOLO11n 学生     │
│         KD loss = KL(分类, T=3~4) + MSE(框回归)  │
│  rebuild_dataset.py：数据集重构（类合并+降采样）   │
└─────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────┐
│  H743/H743VIT6_test/  （STM32 固件）              │
│  Core/Src/main.c    — 入口，ESP-01S WiFi 初始化   │
│  Core/Src/esp01s.c  — AT 指令驱动（UART 透传）    │
│  Core/Inc/esp01s.h  — ESP01S_HandleTypeDef 接口   │
└─────────────────────────────────────────────────┘
```

### Phase_0 核心模块

| 模块 | 职责 |
|------|------|
| `detector.py` | YOLO 检测器封装。支持 real（ultralytics 权重）和 mock（预置 Detection 列表）两种模式 |
| `iou_matcher.py` | 贪心 IoU 匹配：同类物体内计算 IoU 矩阵 → 阈值过滤 → STILL/ADDED/REMOVED 判定 |
| `inventory.py` | SQLite 库存管理：入/出库记录、存放天数追踪、FRESH/WARNING/URGENT/EXPIRED 四级预警 |
| `config.yaml` | 模型配置（权重路径、阈值）、食材类别映射、腐坏天数阈值 |

### train_kd.py 关键实现细节

- **AMP 补丁**（模块加载时自动执行）：原版 ultralytics 的 `check_amp()` 会尝试下载 `yolo26n.pt`，国内网络超时导致无限重试。三处补丁（`checks.check_amp`、`torch_utils.check_amp`、`trainer.check_amp`）用当前模型直接验证 AMP，跳过下载。
- **KD 状态注入**：`KDTrainer.set_model_attributes()` 将教师模型、温度、权重等通过 `model._kd_*` 属性注入学生模型，替换 `model.loss` 为 `_kd_loss`。
- **Checkpoint 保存**：`save_model()` 保存前剥离 KD 状态（`_strip_kd`），保存后恢复（`_restore_kd`），避免 KD 属性污染 checkpoint。
- 环境变量 `ULTRALYTICS_OFFLINE=1` 禁止联网下载。

## 自定义 Skills

项目 `.claude/skills/` 下有两个 skill，`/init` 后可通过 `/git-manage` 和 `/smarter-debug` 调用：

- **git-manager**：自动化 Git 全流程 — 读 diff → 写 Conventional Commits → 更新 README → 检查 .gitignore → push
- **smarter-debug**：调试助手 — 优先追溯"最后已知正常"状态，查日志、对话上下文、Git 历史锁定变化窗口，再诊断修复

## 关键约束

- 模型权重（`*.pt`）、数据集（`datasets/`）、训练输出（`runs/`）均不入库，已在 `.gitignore` 排除
- 训练脚本通过 `--resume` 恢复时 `workers=4`（云服务器限制），正常训练 `workers=8`
- `ssh_server.py` 含敏感信息，已在 `.gitignore` 排除
- 推送前确保无 >100MB 文件（GitHub 硬限制）
