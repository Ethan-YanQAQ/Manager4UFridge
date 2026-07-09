# WiFi 连接模块完整报告

> 生成日期: 2026-07-08
> 模块: ESP-01S (ESP8266) WiFi 驱动 — AT 指令透传
> 通信接口: USART1 (PA9/PA10), 115200 8N1

---

## 1. 硬件连接

| STM32H743 引脚 | 功能 | ESP-01S 引脚 | 说明 |
|:---|:---|:---|:---|
| **PA9** | USART1_TX (AF7) | **RXD** | STM32 → ESP-01S 数据发送 |
| **PA10** | USART1_RX (AF7) | **TXD** | ESP-01S → STM32 数据接收 |
| **PC1** | GPIO_Output (推挽+上拉) | **RST** | ESP-01S 硬件复位控制 |
| **3.3V** | 电源 | **VCC** | **必须 3.3V，不可接 5V！** |
| **GND** | 共地 | **GND** | 参考地 |

> 注: ESP-01S 的 CH_PD (EN) 引脚需接 3.3V 使能，否则模块不工作。

---

## 2. 文件清单

| 文件 | 说明 |
|:---|:---|
| `Core/Inc/wifi_esp01s.h` | WiFi 驱动头文件 — API 声明、配置宏、状态码枚举 |
| `Core/Src/wifi_esp01s.c` | WiFi 驱动实现 — AT 指令收发、连接管理、数据发送 |
| `Core/Inc/main.h` | 含 `ESP01_RST_Pin` / `ESP01_RST_GPIO_Port` 宏定义 (PC1) |
| `Core/Src/gpio.c` | ESP01_RST 引脚初始化 (推挽输出+上拉) |
| `Core/Src/usart.c` | USART1 初始化 (115200 8N1) + DMA 接收配置 |
| `CMakeLists.txt` | 第 50 行: `Core/Src/wifi_esp01s.c` 加入编译 |
| `addition/备份/main.c` | 完整 WiFi 集成版 main.c (备份) |

---

## 3. USART1 硬件配置

```c
// usart.c — MX_USART1_UART_Init()
huart1.Instance          = USART1;
huart1.Init.BaudRate     = 115200;      // 波特率
huart1.Init.WordLength   = UART_WORDLENGTH_8B;
huart1.Init.StopBits     = UART_STOPBITS_1;
huart1.Init.Parity       = UART_PARITY_NONE;
huart1.Init.Mode         = UART_MODE_TX_RX;
huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
huart1.Init.OverSampling = UART_OVERSAMPLING_16;
```

- GPIO: PA9/PA10, `GPIO_MODE_AF_PP`, `GPIO_AF7_USART1`
- DMA 接收: `DMA1_Stream0`, `DMA_REQUEST_USART1_RX`, CIRCULAR 模式 (当前未使用)
- USART1 中断: 优先级 0.0，已使能

---

## 4. 驱动架构 (`wifi_esp01s.h`)

### 4.1 配置宏

```c
#define WIFI_AT_CMD_TIMEOUT_MS      5000U   // 普通 AT 命令响应超时
#define WIFI_AT_LONG_TIMEOUT_MS    15000U   // 长操作超时 (WiFi连接、获取IP)
#define WIFI_AT_RX_BUF_SIZE          512U   // AT 响应接收缓冲区大小
#define WIFI_CHUNK_SIZE             2048U   // CIPSEND 单次最大 TCP 载荷 (字节)
```

### 4.2 状态码枚举

```c
typedef enum {
    WIFI_OK                =  0,   // 操作成功
    WIFI_ERR_TIMEOUT       = -1,   // AT 命令响应超时
    WIFI_ERR_AT_FAIL       = -2,   // AT 通信失败
    WIFI_ERR_WIFI_FAIL     = -3,   // WiFi 连接失败
    WIFI_ERR_TCP_FAIL      = -4,   // TCP 连接失败
    WIFI_ERR_SEND_FAIL     = -5,   // 数据发送失败
    WIFI_ERR_NOT_CONNECTED = -6,   // TCP 未连接
} WIFI_Status_t;
```

### 4.3 公开 API

| 函数 | 功能 | 返回值 |
|:---|:---|:---|
| `WIFI_Init()` | 初始化 ESP-01S (复位→AT测试→Station模式→单连接→普通传输模式) | `WIFI_OK` 或错误码 |
| `WIFI_ConnectAP(ssid, password)` | 连接 WiFi 热点 | `WIFI_OK` 或错误码 |
| `WIFI_GetLocalIP(ip_buf)` | 查询模块获取的局域网 IP | `WIFI_OK` 或错误码 |
| `WIFI_ConnectTCPServer(ip, port)` | 建立到 PC 服务器的 TCP 连接 | `WIFI_OK` 或错误码 |
| `WIFI_CloseTCP()` | 关闭 TCP 连接 | 无 |
| `WIFI_SendData(pData, len)` | 发送二进制数据 (自动分块 2048B/块) | `WIFI_OK` 或错误码 |
| `WIFI_SendFrame(pData, len)` | 发送 JPEG 帧 (单次 CIPSEND, 带 4 字节 LE 长度头) | `WIFI_OK` 或错误码 |
| `WIFI_SendSingle(pData, len)` | 发送整个缓冲区 (单次 CIPSEND, 无头部) | `WIFI_OK` 或错误码 |
| `WIFI_IsTCPConnected()` | 查询 TCP 连接状态 | 1=已连接, 0=未连接 |

---

## 5. AT 指令协议详解

### 5.1 底层 AT 收发机制 (`wifi_at_raw`)

```
wifi_at_raw(cmd, timeout):
  1. 清空接收缓冲 at_rx_buf[512]
  2. Flush USART1 RX FIFO (读走所有残留字节)
  3. HAL_UART_Transmit(&huart1, cmd, len, 2000ms) → 发送 AT 命令
  4. 逐字符轮询接收 (10ms 间隔):
     - 读到字符追加到 at_rx_buf
     - 提前退出条件: 收到 "OK\r\n" / "ERROR\r\n" / "FAIL\r\n" / "SEND OK\r\n"
     - 退出后额外读 20ms 收尾数据
  5. 超时未收到完整响应 → 返回 NULL
```

**特点**: 全部阻塞式 HAL_UART_Receive 轮询，不使用中断/DMA 接收 AT 响应。

### 5.2 初始化序列 (`WIFI_Init`)

```
步骤1: ESP-01S 硬件复位 (PC1 LOW→100ms→HIGH→等待 2500ms 启动)
步骤2: "+++" 逃生序列 (防止 ESP-01S 停留在透传模式)
        时序: 空闲 1.2s → 发送 "+++" → 等待 1.2s → 读响应
步骤3: AT 通信测试 (最多重试 5 次, 每次间隔 500ms)
        失败则 AT+RST 软件复位, 再重试 5 次
步骤4: ATE0       — 关闭回显
步骤5: AT+CWMODE=1  — 设为 Station 模式
步骤6: AT+CIPMUX=0  — 单连接模式
步骤7: AT+CIPMODE=0 — 普通传输模式 (非透传)
```

### 5.3 WiFi 连接 (`WIFI_ConnectAP`)

```
AT+CWJAP="<ssid>","<password>" → 超时 15s
  成功响应: "OK" 或 "WIFI GOT IP" → 额外等待 3s 确保 DHCP 完成
  失败响应: "FAIL" 或 "ERROR"  → 返回 WIFI_ERR_WIFI_FAIL
```

### 5.4 获取 IP (`WIFI_GetLocalIP`)

```
AT+CIFSR → 超时 3s
  解析: 查找 "STAIP,\"" 或 "+CIFSR:" 后双引号内的 IP 字符串
  返回: 最多 15 字符的 IP 地址 (如 "192.168.1.105")
```

### 5.5 TCP 连接 (`WIFI_ConnectTCPServer`)

```
AT+CIPCLOSE                    → 先关闭旧连接
AT+CIPSTART="TCP","<ip>",<port> → 超时 15s
  成功: "CONNECT" 或 "OK"
  已连接: "ALREADY CONNECTED" (同样视为成功)
  失败: 其他 → 返回 WIFI_ERR_TCP_FAIL
```

### 5.6 TCP 状态查询 (`WIFI_IsTCPConnected`)

```
AT+CIPSTATUS → 超时 2s
  STATUS:2 = 已连接
  STATUS:3 = 正在传输
  STATUS:4 = TCP 断开
  其他状态 = 未连接
```

---

## 6. 数据发送机制

### 6.1 分块发送 (`WIFI_SendData`)

用于连续流模式，将大数据拆分为 2048 字节的块:

```
while (remaining > 0) {
    chunk = min(remaining, 2048)

    1. AT+CIPSEND=<chunk>              → 发送 CIPSEND 命令
    2. 等待 '>' 提示符 (超时 5s)        → ESP-01S 准备好接收
    3. HAL_UART_Transmit(chunk_data)    → 发送二进制块 (超时 10s)
    4. 等待 "SEND OK" (超时 5s)         → TCP 发送确认

    remaining -= chunk
}
```

### 6.2 帧发送 (`WIFI_SendFrame`)

用于快照模式，单帧 JPEG + 4 字节长度头:

```
AT+CIPSEND=<len+4>                  → 含 4 字节头部
  ↓ 等待 '>' (3s)
  ↓ 发送 4 字节 LE uint32 长度头
  ↓ 发送 JPEG 数据 (5s)
  ↓ 等待 "SEND OK" (5s)
```

**协议格式 (PC 端解析)**:
```
Byte 0-3:  JPEG 数据长度 (LE uint32)
Byte 4-N:  JPEG 裸数据 (FF D8 ... FF D9)
```

### 6.3 单次发送 (`WIFI_SendSingle`)

不拆分、不带头部，一次 CIPSEND 发送全部数据:

```
AT+CIPSEND=<len>
  ↓ 等待 '>' (3s)
  ↓ HAL_UART_Transmit(all_data) (3s)
  ↓ 等待 "SEND OK" (5s)
```

### 6.4 发送超时设计原则

115200 波特率下，实际吞吐约 **11.2 KB/s**:

| JPEG 大小 | 纯传输时间 | 含 AT 握手 |
|:---|:---|:---|
| 4 KB | ~0.36s | ~0.5s |
| 8 KB | ~0.71s | ~0.9-1.2s |
| 15 KB | ~1.34s | ~1.7s |
| 25 KB | ~2.23s | ~2.5s |

> ⚠️ 超时值必须 ≥ 2-3 倍传输时间，推荐 3000-5000ms。过短会导致图片未发完就被强行截断。

---

## 7. 主程序集成流程 (备份版 main.c)

### 7.1 配置宏 (需在 main.h Private defines 中定义)

```c
#define WIFI_SSID        "YourWiFiSSID"       // WiFi 名称
#define WIFI_PASSWORD    "YourWiFiPassword"    // WiFi 密码
#define PC_SERVER_IP     "192.168.1.100"       // PC 局域网 IP
#define PC_SERVER_PORT   8888                  // TCP 端口
```

### 7.2 启动序列

```
1. SystemClock_Config()         → HSI 64MHz
2. MX_GPIO_Init()               → 含 ESP01_RST (PC1) 上拉
3. MX_USART1_UART_Init()        → 115200 8N1
4. MX_USART2_UART_Init()        → Debug 串口
5. MX_DCMI_Init()
6. OV2640_JPEG_Init()           → 摄像头初始化 (320x240 JPEG)
7. WIFI_Init()                  → ESP-01S 硬件复位+AT初始化
8. WIFI_ConnectAP(ssid, pwd)    → 连接 WiFi AP
9. WIFI_GetLocalIP(ip_buf)      → 打印模块 IP
10. WIFI_ConnectTCPServer(ip, port) → 连接 PC TCP 服务器 (最多 10 次重试, 间隔 2s)
11. OV2640_JPEG_Start_Capture() → 触发首次抓拍
```

### 7.3 主循环逻辑

```c
while (1) {
    if (g_jpeg_frame_ready) {
        // 用 WIFI_SendFrame 发送 (带 4 字节长度头)
        if (WIFI_SendFrame(jpeg_frame_buf, g_jpeg_frame_len) == WIFI_OK) {
            LED 快闪 (25ms) → 成功
        } else {
            // 发送失败 → 关闭 TCP → 重连 → 日志
            WIFI_CloseTCP();
            HAL_Delay(1000);
            WIFI_ConnectTCPServer(PC_SERVER_IP, PC_SERVER_PORT);
        }
        HAL_Delay(50);
        OV2640_JPEG_Start_Capture();  // 触发下一帧
    }
}
```

---

## 8. 数据流全链路

```
OV2640 Sensor
  │ D[7:0] + HSYNC + VSYNC + PCLK
  ▼
DCMI (Snapshot Mode) + DMA2 (Normal Mode)
  │ 捕获一帧 JPEG → FRAME 中断 → g_jpeg_frame_ready = 1
  ▼
jpeg_frame_buf[60KB] @ AXI SRAM 0x24000000
  │ CPU 读取
  ▼
wifi_esp01s.c → AT+CIPSEND 协议封装
  │
  ▼
USART1 (PA9/PA10, 115200 8N1)
  │ 串口 TTL 电平
  ▼
ESP-01S (ESP8266)
  │ 802.11 b/g/n WiFi → TCP/IP 协议栈
  ▼
WiFi AP (路由器)
  │ 局域网
  ▼
PC TCP Server (Python: receive_image.py)
  │ 解析 4 字节 LE 长度头 → 读取 N 字节 JPEG
  ▼
OpenCV / Pillow 解码 → GUI 显示 + 可选存盘
```

### 8.1 波特率瓶颈分析

| 环节 | 带宽 | 状态 |
|:---|:---|:---|
| DCMI PCLK | ~4 MHz (CLKRC=0x03) | 远大于下游 |
| DMA (AHB) | 64 MHz HCLK | 足够 |
| USART1 | 115200 bps ≈ 11.2 KB/s | **最大瓶颈** |
| ESP-01S WiFi | 802.11n 理论 72 Mbps | 实际 > 1 MB/s，不是瓶颈 |
| PC TCP | 局域网 100 Mbps+ | 不是瓶颈 |

---

## 9. 容错机制

### 9.1 ESP-01S 状态恢复

ESP-01S 在 STM32 SWD 复位后不会自动复位，可能卡在透传模式或 TCP 已打开状态。`WIFI_Init()` 的三层防护:

1. **硬件复位** (PC1): LOW 100ms → HIGH → 等 2500ms 冷启动
2. **"+++" 逃生**: 1.2s 空闲 → "+++" → 1.2s 空闲 → 读 "OK"
3. **AT+RST 软件复位**: 如果 AT 无响应，软复位+等 3000ms+重新测试

### 9.2 TCP 断线重连

主循环发送失败时自动:
1. `WIFI_CloseTCP()` — 关闭旧连接
2. 等待 1s
3. `WIFI_ConnectTCPServer()` — 重新连接

### 9.3 发送超时保护

- 等待 `>` 提示: 3-5 秒超时
- UART 发送: 3-10 秒超时 (取决于数据量)
- 等待 "SEND OK": 5 秒超时

---

## 10. 两种传输方案对比

项目中存在两套独立的 main.c 方案:

| 特性 | **WiFi 方案** (备份 main.c) | **串口直连方案** (当前 main.c) |
|:---|:---|:---|
| 传输接口 | USART1 → ESP-01S → WiFi → TCP | USART2 → USB-TTL → COM 口 |
| 数据通道 | 独立 (USART1 仅传图, USART2 仅 debug) | 共用 (USART2 同时传输 debug + 图像) |
| 帧协议 | 4 字节 LE 长度头 (无 sync 标记) | `0x5A 0xA5` + 4 字节 LE 长度 + JPEG |
| 发送函数 | `WIFI_SendFrame()` | 直接 `HAL_UART_Transmit(&huart2, ...)` |
| PC 接收 | `receive_image.py` (TCP Server) | `serial_receiver.py` (串口状态机) |
| 优点 | 无线传输，远距离 | 无 WiFi 依赖，调试方便 |
| 缺点 | 需要 WiFi AP 和 PC 在同一网络 | 仅 1 个 USB-TTL，带宽受限 |
| 帧率 (8KB JPEG) | ~1 fps | ~1 fps |

---

## 11. 编译与构建

`wifi_esp01s.c` 已在 CMakeLists.txt 中注册:

```cmake
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Core/Src/ov2640_sccb.c
    Core/Src/ov2640_jpeg.c
    Core/Src/wifi_esp01s.c       # ← WiFi 驱动
)
```

构建命令:
```bash
cmake --preset Debug
cmake --build build/Debug
```

> 注意: 当前 main.c 不调用 WiFi 函数 (已切换为串口直连方案)，但 `wifi_esp01s.c` 仍在编译中，切换到 WiFi 方案时只需替换 main.c 并添加 `#include "wifi_esp01s.h"` + 配置宏。

---

## 12. 切换到 WiFi 方案的步骤

1. **修改 `Core/Inc/main.h`**，在 `Private defines` 中添加:
   ```c
   #define WIFI_SSID        "你的WiFi名"
   #define WIFI_PASSWORD    "你的WiFi密码"
   #define PC_SERVER_IP     "你的PC局域网IP"
   #define PC_SERVER_PORT   8888
   ```

2. **替换 `Core/Src/main.c`** 为 `addition/备份/main.c` 的内容

3. **启动 PC TCP Server**:
   ```bash
   pip install pillow opencv-python
   python addition/claude_results/receive_image.py --port 8888
   ```

4. **编译+烧录**

---

## 13. 已知问题

| 问题 | 现象 | 解决/备注 |
|:---|:---|:---|
| 重新烧录后 TCP 连接不上 | 烧录后需要重启 PC 端 Python 脚本 | 见 `addition/问题记录.md` — STM32 SWD 复位不影响 ESP-01S，需重启 PC server |
| ESP-01S 卡在透传模式 | AT 命令无响应 | WIFI_Init 中已加入 "+++" 逃生 + 硬件复位 |
| 115200 波特率瓶颈 | 帧率 ~1 fps (8KB) | 可考虑升级到 921600 波特率，或换用 ESP32 (SPI/SDIO) |
| WiFi 凭据硬编码 | 需要重新编译才能换 WiFi | 后续可加 AT 指令动态配置 |
| ESP-01S 需 3.3V 供电 | 5V 会烧毁模块 | 使用板载 3.3V 或外接 LDO |

---

## 14. 参考文档索引

| 文档 | 路径 | 内容 |
|:---|:---|:---|
| 完美闭环指南 | `addition/stm32h7_wifi_image_perfect_guide.md` | DCMI+DMA+WiFi 完整联调思路 |
| 上下文交接报告 | `addition/上下文交接报告.md` | 引脚映射、驱动移植记录 |
| 模块实现报告 | `addition/claude_results/模块实现报告.md` | 全模块架构 + 帧协议详解 |
| 直接传输方案 | `addition/直接传输方案.md` | 无 WiFi 的串口直连替代方案 |
| Snapshot 方案 | `addition/snapshot方案.md` | DCMI Snapshot 模式原理 |
| 引脚关系图 | `addition/引脚关系图.md` | 全板硬件引脚映射 |
| 问题记录 | `addition/问题记录.md` | 已知缺陷/排查记录 |
| 备份 main.c | `addition/备份/main.c` | 完整 WiFi 集成版主程序 |
| PC 接收脚本 | `addition/claude_results/receive_image.py` | TCP Server JPEG 接收+显示 |
| PC 串口脚本 | `addition/claude_results/serial_receiver.py` | 串口双模 (debug+图像) 接收 |



注意：这个wifi连接方案是从别人的项目里面弄过来的，但是已经跑通了，请你不要用这里面的引脚，引脚做本地化适配，波特率也是本地化适配961200bps，只需要参考他的wifi连接方案，检查我们为什么连接失败
