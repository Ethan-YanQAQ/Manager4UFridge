# STM32 → ESP8266 → 云函数 对接指南

## 架构

```
STM32 (YOLO11n 检测结果) → UART AT指令 → ESP-01S → WiFi → HTTP POST → 云函数 api
```

## ESP-01S AT 指令流程

### 1. 基础初始化
```
AT                          // 测试
AT+CWMODE=1                 // Station 模式
AT+CWJAP="WiFi名","WiFi密码"  // 连接 WiFi
```

### 2. HTTP POST 上报检测结果

```
AT+HTTPINIT
AT+HTTPPARA="URL","https://你的云环境ID.service.tcloudbase.com/api"
AT+HTTPPARA="CONTENT","application/json"
AT+HTTPDATA=512,5000        // 准备 512 字节数据，5秒内发送
>{"detections":[{"class":"Apple","action":"ADDED"},{"class":"Orange","action":"REMOVED"},{"class":"Banana","action":"STILL"}]}
AT+HTTPACTION=1             // POST 请求
AT+HTTPREAD                  // 读取响应
AT+HTTPTERM                  // 关闭 HTTP
```

## 数据格式

POST body:
```json
{
  "detections": [
    {"class": "Apple",   "action": "ADDED"},
    {"class": "Orange",  "action": "REMOVED"},
    {"class": "Banana",  "action": "STILL"}
  ]
}
```

action 取值: `ADDED` | `REMOVED` | `STILL`

## 部署步骤

1. 微信开发者工具 → 云开发控制台 → 云函数 → 部署 `api`
2. 云函数详情 → 触发器 → 添加 HTTP 触发器
3. 记下 HTTP 访问路径，填入 ESP-01S AT 指令
