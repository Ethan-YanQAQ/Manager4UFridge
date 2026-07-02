# Task Plan: 微信小程序（⚠️ 已废弃 — 实际采用方案 A）

> **注意**: 此文件为早期规划（方案 B：腾讯云 IoT + MQTT），实际开发采用了**方案 A：微信云开发 + HTTP**。当前小程序状态见 `task_plan.md` Phase 5-6。

## 架构

```
STM32 ──UART──▶ ESP-01S ──WiFi──▶ HTTP POST ──▶ 微信云函数 ──▶ 云数据库
  │                  │                                              │
  YOLO11n       AT 指令                                       微信小程序
  食材检测      HTTP 透传                                    直接读取展示
```

## 只需要一个平台

| 平台 | 用途 | 费用 |
|------|------|------|
| 微信小程序 + 云开发 | 用户端 + 后端 + 数据库 | 免费（云开发 5GB 数据库 + 云函数 3000 次/天）|

## Phases

### Phase 1: 平台注册
- [ ] 注册腾讯云 IoT Explorer，创建产品（物模型定义食材检测数据格式）
- [ ] 注册微信小程序 AppID（个人主体）
- [ ] ESP-01S 刷支持 MQTT AT 的固件
- **Status:** pending

### Phase 2: 硬件端 MQTT 接入
- [ ] STM32 通过 UART AT 指令驱动 ESP-01S 连接 WiFi
- [ ] ESP-01S 连接腾讯云 IoT MQTT broker（ProductID + DeviceName + DeviceSecret 认证）
- [ ] STM32 构造 JSON payload 上报检测结果到 Topic
- [ ] 数据格式: `{"timestamp":..., "detections":[{"class":"Apple","action":"ADDED"},...]}`
- **Status:** pending

### Phase 3: 小程序开发（uni-app + Vue3）
- [ ] HBuilderX 创建 uni-app 项目，配置微信小程序 AppID
- [ ] 集成腾讯云 IoT 小程序 SDK (mqtt.js + wx.connectSocket)
- [ ] 订阅设备 Topic，接收实时数据
- [ ] 页面：首页（概览）、库存列表（含新鲜度色标）、历史记录时间线
- **Status:** pending

### Phase 4: 云函数数据处理
- [ ] 腾讯云 IoT 规则引擎 → 转发数据到云函数
- [ ] 云函数比对前后帧（ADDED/REMOVED），更新库存状态
- [ ] 新鲜度计算：基于存放天数 → FRESH/WARNING/URGENT/EXPIRED
- **Status:** pending

### Phase 5: 联调测试
- [ ] MOCK 模式：小程序端预置数据测试 UI 流程
- [ ] 硬件联调：STM32 发送真实检测数据 → 小程序实时显示
- [ ] 体验版发布 + 真机测试
- **Status:** pending

## 页面设计

### 首页
```
┌─────────────────────────┐
│   我的冰箱               │
│   ┌─────┐ ┌─────┐ ┌───┐ │
│   │ 12  │ │  3  │ │ 2 │ │
│   │库存 │ │预警  │ │过期│ │
│   └─────┘ └─────┘ └───┘ │
│                          │
│  ⚠ 最近操作               │
│  + Apple    2分钟前       │
│  - Orange   1小时前       │
└─────────────────────────┘
```

### 库存页
```
┌─────────────────────────┐
│  库存  ▼ 全部类别        │
│  ┌─────────────────────┐ │
│  │ 🟢 Apple    3天     │ │
│  │ 🟡 Banana   7天     │ │
│  │ 🔴 Orange   12天    │ │
│  │ ⚫ Grape    15天    │ │
│  └─────────────────────┘ │
│  🟢新鲜  🟡预警  🔴紧急  ⚫过期 │
└─────────────────────────┘
```

## 关键参考项目

| 项目 | 链接 | 参考价值 |
|------|------|---------|
| SmartHomeDemo | github.com/YoM-lab/SmartHomeDemo | STM32+ESP8266+MQTT+小程序完整链路 |
| 智慧农业 STM32F103 | CSDN @DS小龙哥 | 腾讯云 IoT + ESP8266 + 小程序的 MQTT 对接 |
| WeChatMiniEsp8266 | github.com/xuhongv/WeChatMiniEsp8266 | 小程序 MQTT 客户端集成 |
