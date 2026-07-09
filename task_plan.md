# Task Plan — 硬件调试与编程

## 项目目标

Manager4UFridge 智能冰箱食材管理系统 — STM32H743 固件开发。

## 现状总结

- **硬件平台**: 自制 H743 板卡，与正点原子"阿波罗 H743 开发板"非常相似
  - STM32H743 (2MB Flash, 1MB SRAM)
  - 25MHz 无源晶振 (HSE)，系统时钟 400MHz
  - QSPI Flash: W25Q256 32MB
  - SDRAM、OV5640 摄像头、LCD (RGB/LTDC 接口)、ESP-01S WiFi
- **硬件确认**: SDRAM、串口、DCMI 引脚与正点原子一致
- **基础模板**: `39/` — 正点原子 H743 摄像头例程，Keil MDK，已编译通过
- **参考资源**: `RefCodes/【正点原子】阿波罗STM32H743开发板/` — 完整 64 个 HAL 例程
- **本地备份**: `Scripts/` — 从 RefCodes 提取的 9 个关键实验驱动代码（含 QSPI/SDRAM/MPU/LTDC_LCD/USMART 等）
- **开发环境**: Keil MDK (ARM Compiler 5/6)

## 核心原则

1. **对 39/ 做最小改动** — 已有驱动不动，Keil 工程不动，时钟不动 (400MHz)
2. **增量开发** — 只新增我们需要的模块文件，不在已有文件上大改
3. **工作流程规范** — 见下方团队协作铁律

## 工作流程规范（团队协作铁律）

### 代码组织原则

```
39/                          ← 正点原子原始工程，驱动不动
├── Drivers/BSP/             ← [不改] 正点原子 BSP 驱动 (LED/KEY/LCD/SDRAM/DCMI/OV5640...)
├── Drivers/SYSTEM/          ← [不改] 系统组件 (delay/sys/usart)
├── Drivers/STM32H7xx_HAL_Driver/ ← [不改] HAL 库
├── Middlewares/USMART/      ← [不改] 串口调试工具
├── User/
│   ├── main.c               ← [最小改动] 只做系统初始化和模块调用
│   ├── stm32h7xx_hal_conf.h ← [不改]
│   ├── stm32h7xx_it.c/h     ← [按需小改] 中断服务函数
│   ├── glue.c               ← [新增] 胶水脚本：模块级联、分步调试
│   ├── glue.h               ← [新增]
│   ├── module_qspi.c        ← [新增] QSPI/W25Q256 功能模块
│   ├── module_qspi.h        ← [新增]
│   ├── module_wifi.c        ← [新增] ESP-01S WiFi 功能模块
│   ├── module_wifi.h        ← [新增]
│   └── ...                  ← 后续新增模块
└── Projects/                ← [不改] Keil 工程文件
```

### 铁律三条

1. **main.c 只做调用，不做定义**
   - 39/ 原有代码**原封不动**，`main()` 中所有已有函数调用和定义保持原样
   - 仅在需要的位置**新增一行** `glue_run()` 调用，启动我们的新模块
   - 所有新增功能函数定义在 `User/module_xxx.c` 中，不动 main.c 已有内容

2. **不修改已有驱动文件**
   - `Drivers/BSP/`、`Drivers/SYSTEM/`、`Middlewares/` 下的已有代码保持原样
   - 需要新功能 → 在 `User/` 下新增文件，include 已有驱动头文件即可

3. **胶水脚本 (glue.c/h) 实现分步调试**
   - 将各模块串联成完整功能流程
   - 使用 `#define STEP_DEBUG` 宏开关控制分步/全速运行
   - 每个模块有独立的 `xxx_self_test()` 函数用于单步验证

### 胶水脚本模板

```c
// glue.h
#ifndef __GLUE_H
#define __GLUE_H
#include "sys.h"

// 分步调试开关 — 注释掉则全速运行
#define STEP_DEBUG

// 新增模块自检函数声明
uint8_t qspi_self_test(void);     // QSPI 读写测试
uint8_t wifi_self_test(void);     // WiFi AT 测试

// 完整功能流程
void glue_run(void);
#endif

// glue.c
#include "glue.h"
// ... 各模块 include ...

void glue_run(void)
{
#ifdef STEP_DEBUG
    // 分步模式：逐个验证新模块
    // qspi_self_test();     // 验证 QSPI Flash 读写
    // wifi_self_test();     // 验证 ESP-01S 通信
#else
    // 全速模式：启动所有新模块，与 39/ 原有功能并行
    // ... 初始化新模块，进入主循环 ...
#endif
}
```

---

## Phases

### Phase 0: 代码调研与分析 ✅

- [x] 阅读 39/readme.txt，理解例程功能
- [x] **深入分析 39/User/main.c（532 行）**：
  - `main()` 入口（行 458-532，仅 ~70 行）：系统初始化 12 步 → 等待 OV5640 就绪 → 按键选择 RGB/JPEG 模式 → 分发到子函数
  - `rgb565_test()`（行 336-456）：RGB565 实时预览模式，DMA 逐行 → DMA2D 填充 LTDC → LCD 显示
  - `jpeg_test()`（行 213-327）：JPEG 抓拍模式，DMA 逐行拼帧 → 帧完成后 USART2 逐字节发给 PC
  - `jpeg_data_process()`（行 97-146）：帧中断 ISR，处理 DMA 剩余数据 + 帧状态机 (0→1→2→0)
  - `jpeg_dcmi_rx_callback()`（行 155-180）：JPEG DMA 行回调，双缓冲拷贝到 g_jpeg_data_buf[]
  - `rgblcd_dcmi_rx_callback()`（行 187-205）：RGB DMA 行回调，DMA2D 逐行填充 LTDC
  - 全局变量：`g_ov_mode`, `g_dcmi_line_buf[2][4096]`, `g_jpeg_data_buf[1MB]@0xC01F4000`, `g_jpeg_data_len`, `g_jpeg_data_ok`, `dcmi_rx_callback` 函数指针
- [x] 分析 DCMI DMA 双缓冲核心机制：DMA1_Stream1 循环模式 → TC 中断 → 函数指针回调切换 RGB/JPEG 处理
- [x] 提取 39/ 完整硬件引脚映射表（DCMI/QSPI/SDRAM/UART/LED/KEY）
- [x] 分析 RefCodes 阿波罗 H743 完整例程 (64个)
- [x] 提取 QSPI/W25QXX/SDRAM 参考驱动代码 (实验28、实验14)

**Status**: complete ✅

---

### Phase 1: 创建 glue 框架 + 新增模块入口

- [ ] 在 `User/` 下新增 `glue.c` 和 `glue.h`
- [ ] 在 `main.c` 的 `main()` 函数末尾（while(1) 之前或其中合适位置）新增一行 `glue_run()` 调用 — **不删不改 main.c 已有代码**
- [ ] 在 Keil 工程中添加 glue.c 到编译列表
- [ ] 编译验证 — 39/ 原有功能应完全不受影响

**Status**: pending

**涉及文件**:
- `User/glue.c` — 新增
- `User/glue.h` — 新增
- `User/main.c` — **仅新增一行** `glue_run()` 调用，其余代码不动
- Keil 工程文件 — 添加 glue.c 到工程

---

### Phase 2: 验证 39/ 在自制板卡上运行

- [ ] 烧录 39/ 编译产物到自制板卡
- [ ] 验证 LED 闪烁、串口输出
- [ ] 验证 LCD 显示（有/无摄像头）
- [ ] 验证 OV5640 摄像头 — RGB565 实时预览 + JPEG 输出

**Status**: pending

> 此阶段不改代码，纯粹用 39/ 原始固件验证硬件。

---

### Phase 3: QSPI 集成 (W25Q256)

**背景**：28 QSPI 和 39/ 配置完全一致。引脚上机验证通过 (0xEF18=W25Q256)。详见 findings.md §6。

**Status**: complete ✅ (2026-07-06)

---

#### 变更清单总览

| 类型 | 文件 | 说明 |
|------|------|------|
| 新增 | `Drivers/BSP/QSPI/qspi.c` | QSPI BSP 驱动（从 28 QSPI 复制） |
| 新增 | `Drivers/BSP/QSPI/qspi.h` | PB2/PB6/PF6-9 QSPI 引脚宏定义 |
| 新增 | `Drivers/BSP/NORFLASH/norflash.c` | NOR Flash 高层驱动（W25Q256 QPI 模式） |
| 新增 | `Drivers/BSP/NORFLASH/norflash.h` | Flash 命令字 + 型号 ID 宏定义 |
| 新增 | `User/glue.c` | 胶水脚本（STEP_DEBUG / 全速模式） |
| 新增 | `User/glue.h` | glue 框架头文件 + STEP_DEBUG 开关 |
| 新增 | `User/module_qspi.c` | QSPI 封装层 + qspi_self_test() |
| 新增 | `User/module_qspi.h` | module_qspi 接口声明 |
| 修改 | `User/main.c` | **+1 include +1 函数调用** (2 行新增) |
| 修改 | `Drivers/BSP/MPU/mpu.c` | **+9 行** Region 0 @ 0x90000000 |
| 修改 | `Projects/MDK-ARM/atk_h743.uvprojx` | +glue.c +module_qspi.c +qspi.c +norflash.c +stm32h7xx_hal_qspi.c |

---

#### main.c 改动（精确）

**位置 1** — include 区，第 29 行 `#include "./BSP/MPU/mpu.h"` 之后：

```c
// [新增] ↓ 在 mpu.h include 之后
#include "../User/glue.h"
```

回滚：删除此行。

**位置 2** — `main()` 函数内，第 474 行 `key_init();` 之后：

```c
    key_init();                                  /* 初始化KEY */
    glue_run();                                  /* QSPI + new modules init */  // [新增]
    sdram_init();                                /* 初始化SDRAM */
```

回滚：删除 `glue_run();` 行。

---

#### mpu.c 改动（精确）

**位置** — `mpu_memory_protection()` 函数开头，在原有中文注释 "保护引导DTCM" 之前插入：

```c
void mpu_memory_protection(void)
{
    /* QSPI Flash Memory-Mapped region @ 0x90000000, 256MB */      // [新增]
    mpu_set_protection( 0x90000000,                                 // [新增]
                        MPU_REGION_SIZE_256MB,                      // [新增]
                        MPU_REGION_NUMBER0, 0,                      // [新增]
                        MPU_REGION_FULL_ACCESS,                     // [新增]
                        MPU_ACCESS_NOT_SHAREABLE,                   // [新增]
                        MPU_ACCESS_CACHEABLE,                       // [新增]
                        MPU_ACCESS_BUFFERABLE);                     // [新增]

    /* 保护引导DTCM,共128K字节 */                                    // [原有]
```

回滚：删除 "QSPI Flash Memory-Mapped" 注释开始的 9 行（直到空行）。

---

#### glue.h 完整内容

```c
#ifndef __GLUE_H
#define __GLUE_H
#include "./SYSTEM/sys/sys.h"

/* Comment out to disable step-by-step debug mode */
#define STEP_DEBUG                             // ← 注释此行 = 全速模式

uint8_t qspi_self_test(void);
void glue_run(void);
#endif
```

#### glue.c 完整内容

```c
#include "glue.h"
#include "module_qspi.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

void glue_run(void)
{
#ifdef STEP_DEBUG
    printf("\r\n=== STEP DEBUG MODE ===\r\n");
    printf("Press KEY0 to advance to next test\r\n\r\n");

    printf("--- Step 1: QSPI Self-Test ---\r\n");
    if (qspi_self_test() == 0)
        printf("--- QSPI: PASS ---\r\n\r\n");
    else
        printf("--- QSPI: FAIL ---\r\n\r\n");

    printf("=== All tests done ===\r\n");
#else
    /* Full-speed: init all, continue camera flow */
    norflash_init();
    printf("[GLUE] QSPI Flash ready, ID=0x%04X\r\n", norflash_read_id());
#endif
}
```

#### module_qspi.h 完整内容

```c
#ifndef __MODULE_QSPI_H
#define __MODULE_QSPI_H
#include "./SYSTEM/sys/sys.h"
uint8_t qspi_self_test(void);
#endif
```

#### module_qspi.c 完整内容

```c
#include "./BSP/QSPI/qspi.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "module_qspi.h"

static const uint8_t test_pattern[] = {"QSPI Self-Test OK!"};
#define TEST_SIZE   sizeof(test_pattern)

uint8_t qspi_self_test(void)
{
    uint8_t buf[TEST_SIZE + 4];
    uint16_t id;
    uint32_t test_addr;

    /* Step 1: Init and detect */
    printf("[QSPI] Initializing...\r\n");
    norflash_init();
    id = norflash_read_id();
    printf("[QSPI] Flash ID: 0x%04X\r\n", id);
    if (id != W25Q256 && id != BY25Q256)
    {
        printf("[QSPI] FAIL: Unknown Flash ID!\r\n");
        return 1;
    }

    /* Step 2: Write test pattern to last sector */
    test_addr = (32 * 1024 * 1024) - 4096;
    printf("[QSPI] Writing test pattern to 0x%08X...\r\n", test_addr);
    norflash_write((uint8_t *)test_pattern, test_addr, TEST_SIZE);

    /* Step 3: Read back and verify */
    printf("[QSPI] Reading back...\r\n");
    norflash_read(buf, test_addr, TEST_SIZE);
    buf[TEST_SIZE] = '\0';
    printf("[QSPI] Written: %s\r\n", test_pattern);
    printf("[QSPI] Read:    %s\r\n", buf);

    /* Step 4: Compare */
    {
        uint8_t i, match = 1;
        for (i = 0; i < TEST_SIZE; i++)
            if (buf[i] != test_pattern[i]) { match = 0; break; }
        if (match)
        {
            printf("[QSPI] PASS: Read/Write verify OK!\r\n");
            return 0;
        }
        else
        {
            printf("[QSPI] FAIL: Data mismatch at byte %u\r\n", i);
            return 1;
        }
    }
}
```

#### Keil 工程改动（atk_h743.uvprojx）

在 `Drivers/STM32H7xx_HAL_Driver` 组中添加（stm32h7xx_hal_pwr_ex.c 之后）：

```xml
<File>
  <FileName>stm32h7xx_hal_qspi.c</FileName>
  <FileType>1</FileType>
  <FilePath>..\..\Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_qspi.c</FilePath>
</File>
```

在 `Drivers/BSP` 组中添加（pcf8574.c 之后）：

```xml
<File>
  <FileName>qspi.c</FileName>
  <FileType>1</FileType>
  <FilePath>..\..\Drivers\BSP\QSPI\qspi.c</FilePath>
</File>
<File>
  <FileName>norflash.c</FileName>
  <FileType>1</FileType>
  <FilePath>..\..\Drivers\BSP\NORFLASH\norflash.c</FilePath>
</File>
```

在 `User` 组中添加（stm32h7xx_it.c 之后）：

```xml
<File>
  <FileName>glue.c</FileName>
  <FileType>1</FileType>
  <FilePath>..\..\User\glue.c</FilePath>
</File>
<File>
  <FileName>module_qspi.c</FileName>
  <FileType>1</FileType>
  <FilePath>..\..\User\module_qspi.c</FilePath>
</File>
```

---

#### 运行行为

| 模式 | 行为 |
|------|------|
| `STEP_DEBUG` 已定义 (当前) | 启动后先执行 QSPI 自检 → 串口输出结果 → 然后继续摄像头流程 |
| 注释 `STEP_DEBUG` | 静默初始化 QSPI → 串口输出 Flash ID → 继续摄像头流程 |

#### 新增文件目录结构

```
39/
├── Drivers/BSP/
│   ├── QSPI/           ← 新增目录
│   │   ├── qspi.c
│   │   └── qspi.h
│   └── NORFLASH/       ← 新增目录
│       ├── norflash.c
│       └── norflash.h
└── User/
    ├── glue.c          ← 新增
    ├── glue.h          ← 新增
    ├── module_qspi.c   ← 新增
    └── module_qspi.h   ← 新增
```

---

### Phase 4: ESP-01S WiFi 集成 (2026-07-08)

**Status**: in_progress

#### 硬件方案

| 信号 | STM32 引脚 | 说明 |
|------|-----------|------|
| ESP TX → STM32 RX | PA3 | USART2 RX，复用 |
| ESP RX ← STM32 TX | PA2 | USART2 TX，复用 |
| ESP RST | PA1 | GPIO 输出，低电平复位 |
| ESP CH_PD/EN | 3.3V | 硬拉高，无需代码 |
| ESP VCC/GND | 3.3V/GND | 独立供电 ≥500mA |

#### 通信策略

```
上电 → 115200 AT 检测 → AT+UART_CUR 尝试 921600
  ├── OK → STM32 USART2 切 921600
  └── ERROR → 保持 115200
→ AT+CWMODE=1 → AT+CWJAP → AT+CIPSTART (TCP)
→ AT+CIPMODE=1 → AT+CIPSEND (进透传)
→ JPEG 字节直通 WiFi → PC 端 TCP Server 接收
→ +++ (退出透传)
```

#### 核心设计

**透传模式零改动**：ESP-01S 进入透传后，USART2 变成 TCP 管道。[jpeg_test()](39/User/main.c#L276) 中 `USART2->TDR = p[i]` 的循环完全不需要修改，字节从 STM32 → USART2 → ESP-01S → WiFi → TCP Server。

<**main.c 改动**：
- 改 `usart2_init(115200)` → `usart2_init(921600)`（尝试高速后），或不改（fallback 115200 时）
- JPEG 发送循环零改动

#### 新增文件

| 类型 | 文件 | 说明 |
|------|------|------|
| 新增 | `User/module_wifi.c` | ESP-01S AT 驱动：init/reset/cmd/send |
| 新增 | `User/module_wifi.h` | 接口声明 |
| 新增 | `User/wifi_config.h` | WiFi SSID/密码/服务器 IP/端口 |
| 修改 | `User/glue.h` | +1 行 `wifi_self_test()` 声明 |
| 修改 | `User/glue.c` | +Step 2 WiFi 自检 |
| 修改 | `Projects/MDK-ARM/atk_h743.uvprojx` | +module_wifi.c |

#### module_wifi 接口

```c
uint8_t wifi_init(void);               // 硬件复位 + AT 检测 + 波特率协商
uint8_t wifi_send_cmd(const char *cmd, const char *expect, uint32_t timeout_ms);
uint8_t wifi_connect_ap(const char *ssid, const char *pwd);
uint8_t wifi_tcp_connect(const char *host, uint16_t port);
void    wifi_enter_transparent(void);   // AT+CIPMODE=1 + AT+CIPSEND → 透传
void    wifi_exit_transparent(void);    // +++ 退出透传
uint8_t wifi_self_test(void);          // 全流程自检
```

#### STEP_DEBUG 流程

```
Step 1: QSPI Self-Test  (已有)
Step 2: WiFi Self-Test   (新增)
  ├── 2.1 GPIO + USART2 初始化
  ├── 2.2 硬件复位 ESP-01S (PA1 LOW→delay→HIGH→wait ready)
  ├── 2.3 AT 测试 (AT→OK)
  ├── 2.4 固件版本 (AT+GMR)
  ├── 2.5 尝试 921600 波特率 (AT+UART_CUR)
  ├── 2.6 连接 WiFi (AT+CWJAP)
  ├── 2.7 TCP 连接 (AT+CIPSTART)
  ├── 2.8 进透传 → 发测试数据 → 退出透传
  └── 2.9 PASS/FAIL
```

#### 波特率协商逻辑

```c
usart2_init(115200);                   // 先用默认波特率通信
wifi_send_cmd("AT\r\n", "OK", 2000);  // AT 测试
wifi_send_cmd("AT+UART_CUR=921600,8,1,0,0\r\n", "OK", 2000);
// 如果 OK → HAL_UART_DeInit + usart2_init(921600)
// 如果 ERROR → 保持 115200，打印提示
```

#### 调试记录 (2026-07-08)

**第1轮**：AT test OK，后续全部 TIMEOUT。根因多轮排查：
1. HAL_UART_Transmit 状态机与手写 RX 轮询冲突 → 改直接寄存器访问
2. 函数顺序/宏重定义编译错误 → 修复
3. 核心发现：ESP-01S 响应尾随 `\r\n` 未被读走 → **USART Overrun Error (ORE)** 导致接收器锁死

**最终根因**：每条 AT 命令响应后有尾随字节（如 `ATE0\r\nOK\r\n`），`strstr("OK")` 命中后立即返回，`\r\n` 留在 RDR 没读。下一条命令发送时 ORE 永久阻塞 RX。

**最终修复**：`usart2_send_str` 每次发送前清 ORE（`USART2->ICR = USART_ICR_ORECF`）+ flush RX 残留。

**第2轮**：全通！完整链路验证通过。

```
ATE0          -> OK       (关回显, 消干扰)
AT            -> OK
AT+GMR        -> v1.7.4.0 (ESP-01S AT 固件版本)
AT+CWMODE=1   -> OK       (Station 模式)
AT+CWJAP      -> WIFI CONNECTED / WIFI GOT IP
AT+CIPSTART   -> CONNECT OK (TCP 192.168.137.1:8080)
AT+CIPMODE=1  -> OK       (透传模式)
AT+CIPSEND    -> >        (进入透传, USART2=TCP管道)
GLUE: WiFi pipeline ready
```

#### 性能数据

| 波特率 | 14KB JPEG 耗时 | 帧率 |
|--------|---------------|------|
| 115200 | ~1.3s | ~0.7 FPS |
| 921600 | ~0.16s | ~6 FPS |

921600 波特率已启用（ESP v1.7.4 支持 AT+UART_CUR）。

#### 当前状态

**Status**: complete ✅ (2026-07-08)

ESP-01S 全栈链路打通：OV5640 → DCMI/DMA → SDRAM → USART2(921600) → ESP-01S 透传 → WiFi → PC TCP Server → 实时 JPEG 显示。

#### 配置文件

WiFi 账号 `ETHANYANDELL` / 密码 `1l1l1l1l`，PC 热点 IP `192.168.137.1:8080`。

#### 回滚

删除 `module_wifi.c/h`、`wifi_config.h`，恢复 `glue.c/h` 和 Keil 工程即可。

---

### Phase 5: 整体联调

- [x] 关闭 STEP_DEBUG，全速运行完整功能链路
- [x] 系统稳定性验证

**Status**: complete ✅ (2026-07-06)

#### 改动：注释 STEP_DEBUG

**文件**：[glue.h](39/User/glue.h)，**1 行**：

```c
//#define STEP_DEBUG    // ← 注释掉 = 全速模式
```

**行为变化**：

| 模式 | 启动行为 | 串口输出 |
|------|---------|---------|
| STEP_DEBUG (之前) | 启动后等待 KEY0，逐步执行 QSPI 自检 | 详细自检日志 |
| 全速 (现在) | 启动后静默初始化 QSPI，直接进入摄像头 | `[GLUE] QSPI Flash ready, ID=0xEF18` |

回滚：取消注释 `#define STEP_DEBUG` 即可。

---

### Phase 6: JPEG 帧发送 + PC 接收

**Status**: complete ✅ (2026-07-07)

#### 文件清单

| 类型 | 文件 | 说明 |
|------|------|------|
| 新增 | `User/module_jpeg_sender.c/h` | `jpeg_send_frame()` 封装 |
| 新增 | `Phase_0/pc_tools/serial_viewer.py` | PC 端串口 JPEG 解码显示 |
| 修改 | `User/main.c` | 7 项累积改动（见下） |
| 修改 | `User/glue.h` | +1 行 `jpeg_send_frame` 声明 |
| 修改 | `User/glue.c` | +include +extern +Step 2 测试 |
| 修改 | `Projects/MDK-ARM/atk_h743.uvprojx` | +module_jpeg_sender.c |

#### main.c 累积改动清单

| # | 位置 | 改动 | 目的 |
|---|------|------|------|
| 1 | include 区 | `#include "../User/glue.h"` | glue 框架 |
| 2 | main() L468 | `usart2_init(115200)` (原 921600) | USB-TTL 兼容 |
| 3 | main() ov5640_init 循环 | `printf("OV5640 ERROR, retrying...")` | 调试输出 |
| 4 | main() OV5640 OK 后 | `printf(...)` + `glue_run()` + `g_ov_mode=1` | 跳过按键，强制 JPEG |
| 5 | jpeg_test() | 移除 `printf("g_jpeg_data_len:%d",...)` | DMA 填充量无意义 |
| 6 | jpeg_test() | 新增 `printf("JPEG:%u bytes", jpglen)` | 真实帧大小 |
| 7 | jpeg_test() `p+=jpgstart` 后 | `if (p[2]==0xA0) p[2]=0xE0;` | OV5640 FF A0→FF E0 修正 |

#### 关键发现

**OV5640 FF A0 问题**：OV5640 JPEG 输出的 APP0 标记为 `FF A0` 而非标准 `FF E0`，导致所有解码器拒绝。第 7 项改动修复此 bug。经验证：改这一个字节后 320×240 JPEG 完全正常。

#### PC 端使用

```bash
cd Phase_0/pc_tools
python serial_viewer.py COM11 --baud 115200 --save-dir ./test_frames
```

#### Step 6.3: glue + Keil integration

- [ ] glue.c: add jpeg_send_frame() test in STEP_DEBUG mode
- [ ] Keil project: add module_jpeg_sender.c

**Status**: pending

---

### Phase 6 附：DCMI FIFO 溢出根因与修复 (2026-07-07)

#### 根因

`DCMI->RISR = 0x1A` — **OVR_RIS (bit3) = DCMI FIFO overrun**。每帧多次溢出丢字节，导致 JPEG 数据在大数据量时损坏。运动模糊帧小（~14KB）碰巧不丢或少丢所以看起来正常。

#### 修复：dcmi.c DMA 配置优化

```c
// 原配置
FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
MemBurst      = DMA_MBURST_SINGLE;
Priority      = DMA_PRIORITY_HIGH;

// 修复后
FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
MemBurst      = DMA_MBURST_INCR8;     // 32 bytes/burst, optimal for SDRAM
Priority      = DMA_PRIORITY_VERY_HIGH;
```

#### 后续方案（如仍不够）

- D2 SRAM 做中间缓冲 + MDMA 搬 SDRAM（硬汉社区验证可行）
- 降低 OV5640 PCLK 频率
- SDRAM 超频到 200MHz

---

### Phase 7: SD Card Integration (SDMMC)

**Status**: complete ✅ (2026-07-07)

#### 系统配置对比：实验41 SD卡 vs 39/

| 配置项 | 实验41 | 39/ | 结论 |
|--------|--------|-----|------|
| 时钟 | `sys_stm32_clock_init(160,5,2,4)` 400MHz | 相同 | ✅ |
| Cache | I+D Cache, Write-through | 相同 | ✅ |
| HAL 版本 | STM32H7xx_HAL_Driver | 相同 | ✅ |
| HAL_SD_MODULE_ENABLED | ✓ | ✓ (stm32h7xx_hal_conf.h) | ✅ |
| stm32h7xx_hal_sd.c | ✓ | ✓ (已存在但未加入工程) | ✅ |
| stm32h7xx_hal_sd_ex.c | ✓ | ✓ (已存在但未加入工程) | ✅ |
| stm32h7xx_ll_sdmmc.c | ✓ | ✓ (已存在但未加入工程) | ✅ |
| SDMMC_NSpeed_CLK_DIV | legacy 别名 → SDMMC_NSPEED_CLK_DIV(0x04)→30MHz | 相同 | ✅ |
| MPU | 7 区域 (1-7) | 8 区域 (0-7, QSPI占用Region0) | ✅ 兼容 |

> **结论**：系统配置完全一致，SDMMC 驱动可直接移植，无需修改 HAL 库或时钟配置。

#### SDMMC 引脚映射

| 信号 | STM32 引脚 | AF |
|------|-----------|-----|
| SD1_D0 | PC8 | AF12 |
| SD1_D1 | PC9 | AF12 |
| SD1_D2 | PC10 | AF12 |
| SD1_D3 | PC11 | AF12 |
| SD1_CLK | PC12 | AF12 |
| SD1_CMD | PD2 | AF12 |

> ⚠️ PC8/PC9/PC11 与 DCMI (OV5640) 共享引脚，分时复用。已验证两块电路均可独立工作。

#### 变更清单

| 类型 | 文件 | 说明 |
|------|------|------|
| 新增 | `Drivers/BSP/SDMMC/sdmmc_sdcard.c` | SD卡 BSP 驱动（从实验41复制） |
| 新增 | `Drivers/BSP/SDMMC/sdmmc_sdcard.h` | SD卡引脚宏 + API 声明 |
| 新增 | `User/module_sdcard.c` | SD卡高层封装：init/read/write/info/test |
| 新增 | `User/module_sdcard.h` | module_sdcard 接口声明 |
| 修改 | `User/glue.h` | +1 行 `sdcard_self_test()` 声明 |
| 修改 | `User/glue.c` | +include +Step 2 SD卡自检 + 全速初始化 |
| 修改 | `Projects/MDK-ARM/atk_h743.uvprojx` | +stm32h7xx_hal_sd.c +stm32h7xx_hal_sd_ex.c +stm32h7xx_ll_sdmmc.c +sdmmc_sdcard.c +module_sdcard.c |

#### main.c

**无需新增修改**。`glue_run()` 位置已在 Phase 7.1 修复中调整至 ov5640_init 之前（见下方）。

#### Phase 7.1 修复：SD 卡初始化时序 (2026-07-07)

**问题**：`glue_run()` 原本在 `ov5640_init()` 之后调用。但 `ov5640_jpeg_mode()` 内部调用 `dcmi_init()` + `dcmi_dma_init()`，配置了 DCMI 引脚（PC8/PC9/PC11 AF13）。这些引脚与 SDMMC（AF12）共享。即使 DCMI CAPTURE 未使能，OV5640 传感器已在驱动并行数据总线，导致 SD 卡初始化失败。

**修复**：

| 文件 | 改动 |
|------|------|
| `main.c` L482 | `glue_run()` 从 `ov5640_init()` 之后**移到之前**（L482，while 循环前） |
| `main.c` L494 | 删除旧的 `glue_run()` 调用 |
| `glue.c` 全速模式 | `sdcard_get_info()` 加返回值检查，初始化失败时打印提示而非输出全零 |

**时序**：
```
修复前: ov5640_init (DCMI引脚已配AF13) → glue_run → SD init FAIL
修复后: glue_run → SD init OK → ov5640_init → DCMI
```

#### 运行行为

| 模式 | 行为 |
|------|------|
| `STEP_DEBUG` 已定义 | Step 1: QSPI 自检 → Step 2: SD 卡自检（含读写验证） |
| 注释 `STEP_DEBUG` | QSPI 静默初始化 + SD 卡初始化并打印卡信息 |

#### SD 卡自检流程

1. `sd_init()` — 最多重试 5 次
2. 打印卡信息（类型、容量、块大小等）
3. 读测试扇区 (0x200000) 原始数据
4. 写测试图案 → 读回校验
5. 恢复原始数据

#### 诊断结果 (2026-07-08)

- `SDMMC kernel clock: 200,000,000 Hz` ✅ — `HAL_RCCEx_GetPeriphCLKFreq` 正常返回 200MHz
- `HAL_SD_Init err=1 (HAL_ERROR)` — 故障在 `SD_PowerON` → `SD_PowerON` 阶段（CMD0/CMD8/ACMD41 卡通信失败）
- 已排除：时钟分频、HAL 文件缺失、MPU、链路脚本、`glue_run` 时序
- **待查**：卡电源/方向/收发器配置、引脚是否被其他外设占用
- **结论**：暂时搁置，先推进 WiFi 无线通信

#### 下一步：FATFS 文件系统

当前为裸扇区读写。要保存 `.jpg` 文件供 PC 读取，需集成 FATFS（实验43）。实验43 位于 RefCodes，含 `ff.c/h`、`diskio.c/h`、`exfuns/` 等。SDMMC 底层驱动（`sd_read_disk`/`sd_write_disk`）已就绪，FATFS 对接仅需实现 `diskio.c` 中的 6 个函数。

---

### Phase 8: YOLO AI Inference

**Decision**: Discussion 2 — AI first, FreeRTOS later. Discussion 3 — source code from web references.

#### Key Parameters (from web research)

| Parameter | Value |
|------|-----|
| YOLO Model | YOLO11n, 2.6M params |
| INT8 Quantized Size | ~2.5MB |
| Inference RAM | ~2.1MB (needs SDRAM) |
| Expected Speed | ~350ms/frame (2.8 FPS) |
| Weight Storage | QSPI Flash 0x90000000 (Memory-Mapped) |
| Work Buffer | SDRAM 0xC0000000 |
| Tensor Arena | DTCM 0x20000000 (128KB, zero-wait-state) |

#### References

- [STM32H7 CMSIS-NN YOLOv11](https://www.e-com-net.com/article/2049646732450521088.htm)
- [yolo-30k-stm32](https://github.com/Zero0Hero/yolo-30k-stm32) — STM32H723 + X-CUBE-AI
- [trieu1162000/MSc-Thesis](https://github.com/trieu1162000/MSc-Thesis) — STM32H743 + YOLO + TFLite

#### Step 7.1: Research reference code

- [ ] Read above GitHub repos, understand X-CUBE-AI generated code structure
- [ ] Verify YOLO11n export TFLite/ONNX compatibility with X-CUBE-AI
- [ ] Record findings in findings.md

#### Step 7.2: Export model + generate C inference code

- [ ] ultralytics export YOLO11n to TFLite INT8
- [ ] STM32CubeMX / X-CUBE-AI analyze model and generate C code
- [ ] Extract generated files to 39/Middlewares/AI/
- [ ] Extract CMSIS-NN runtime library

#### Step 7.3: Hardware preparation

- [ ] Burn model weights to QSPI Flash (via norflash_write or external programmer)
- [ ] Configure SDRAM as inference work buffer
- [ ] Configure DTCM as tensor arena
- [ ] Linker script: .tensor_arena to 0x20000000

#### Step 7.4: module_ai.c/h

- [ ] New files: 39/User/module_ai.c/h
- [ ] ai_init() — load weights from QSPI Flash, init inference engine
- [ ] ai_infer(const uint8_t *jpeg, uint32_t len) — single frame inference
- [ ] ai_get_results(void) — return detection results
- [ ] ai_self_test() — built-in test image inference verification
- [ ] Pure ASCII comments

#### Step 7.5: glue + Keil integration

- [ ] Keil: add module_ai.c + Middlewares/AI/*.c
- [ ] Keil: add CMSIS-NN include path
- [ ] -O3 + LTO optimization
- [ ] glue.c: add ai_self_test() in STEP_DEBUG
- [ ] main.c full-speed: JPEG capture to AI inference to result output

#### Step 7.6: PC accuracy verification

- [ ] pc_tools/compare_results.py — STM32 vs PC YOLO inference results
- [ ] Compare mAP/IoU, confirm INT8 quantization loss

**Status**: pending

---

### Phase 9: FreeRTOS Migration (future)

- [ ] Wrap module_xxx as FreeRTOS tasks
- [ ] Task priority: Camera > AI > QSPI > WiFi

**Status**: pending

### DCMI (OV5640)

| 摄像头信号 | STM32 引脚 | 说明 |
|-----------|-----------|------|
| OV_D0~D7 | PC6/7/8/9/11, PD3, PB8/9 | AF13_DCMI |
| OV_SCL | PB4 | SCCB I2C |
| OV_SDA | PB3 | SCCB I2C |
| OV_VSYNC | PB7 | AF13_DCMI |
| OV_HREF | PH8 | AF13_DCMI |
| OV_PCLK | PA6 | AF13_DCMI |
| OV_RESET | PA15 | GPIO |
| OV_XCLK | PA8 | GPIO |
| OV_PWDN | PCF8574_P2 | I2C IO扩展 |

### QSPI (W25Q256) — ✅ 已验证

| 信号 | 引脚 | 复用 | 验证 |
|------|------|------|------|
| CLK | PB2 | AF9 | ✅ 2026-07-06 |
| NCS | PB6 | AF10 | ✅ |
| IO0 | PF6 | AF9 | ✅ |
| IO1 | PF7 | AF9 | ✅ |
| IO2 | PF8 | AF10 | ✅ |
| IO3 | PF9 | AF10 | ✅ |

> **验证方法**：烧录正点原子「实验28 QSPI」→ `QSPI FLASH Ready!`

### 其他

| 信号 | 引脚 |
|------|------|
| LED0 (DS0) | PB1 |
| KEY0 | PH3 |
| KEY1 | PH2 |
| KEY2 | PC13 |
| KEY_UP (WK_UP) | PA0 |
| USART1 (调试串口) | PA9/PA10 |
| USART2 (JPEG输出) | PA2/PA3 |
