# STM32H7 开发笔记

面向 Manager4UFridge 项目的实战参考：STM32H743 + YOLO + QSPI Flash + Cube.AI。

## 目录

- [硬件规格](#硬件规格)
- [CubeMX 配置完整清单](#cubemx-配置完整清单)
- [开发环境](#开发环境)
- [MPU + Cache 配置](#mpu--cache-配置)
- [QSPI 外部 Flash](#qspi-外部-flash)
- [FMC SDRAM](#fmc-sdram)
- [X-CUBE-AI 模型部署](#x-cube-ai-模型部署)
- [FreeRTOS 配置](#freertos-配置)
- [DCMI 摄像头 + DMA](#dcmi-摄像头--dma)
- [常用代码片段](#常用代码片段)
- [HardFault 速查](#hardfault-速查)
- [参考资源](#参考资源)

---

## 硬件规格

### 板级配置（已确认）

| 组件 | 型号 | 参数 |
|------|------|------|
| 主控 | STM32H743IIT6 | LQFP**176**, 480MHz |
| HSE 晶振 | 无源 **25MHz** | CubeMX HSE 填 25MHz |
| QSPI Flash | **W25Q256JV** | 32MB, 133MHz, DummyCycles=8 |
| 摄像头 | **OV5640** | 5MP, 2592×1944, DVP 8-bit, SCCB @ 0x78 |
| WiFi | ESP-01S | AT 指令, UART 透传 |

### 时钟树（CubeMX 配置）

```
HSE: 25MHz
PLL1: /5 ×160 /2 = 480MHz → SYSCLK
HCLK: /2 = 240MHz
QSPI Kernel: D1HCLK /2 = 120MHz (SCK when Prescaler=0)
```

### QSPI 引脚（已确认）

| 信号 | 引脚 | AF |
|------|------|-----|
| CLK | PB2 | AF9 |
| NCS | PB10 | AF9 |
| IO0 | PD11 | AF9 |
| IO1 | PD12 | AF9 |
| IO2 | PE2 | AF9 |
| IO3 | PA1 | AF9 |

### STM32H743VIT6

| 资源 | 数值 | 备注 |
|------|------|------|
| 内核 | Cortex-M7, 480MHz | 双精度 FPU |
| 内部 Flash | 2MB, Dual Bank | Bank1: 0x08000000, Bank2: 0x08100000 |
| 内部 RAM | ~1MB 总计 | DTCM(128KB) + AXI SRAM(512KB) + SRAM1-3(288KB) + SRAM4(64KB) |
| QSPI | 1 路, 支持 Memory-Mapped | 外部 Flash 映射到 0x90000000 |
| DCMI | 1 路, 8/10/12/14 bit | 摄像头接口，配合 DMA 双缓冲 |
| USART/UART | 多路 | ESP8266 用 1 路 |

### 外扩硬件

| 组件 | 型号 | 接口 | 容量 | 映射地址 |
|------|------|------|------|---------|
| QSPI Flash | W25Q256JV | QUADSPI | **32MB** | 0x90000000 |
| SDRAM | W9825G6KH | FMC Bank1 | **32MB** | 0xC0000000 |

---

## CubeMX 配置完整清单

> **模板来源**: `H743_QSPI_REF/Memory Mapped Mode/H743_QSPI_XIP_1.ioc`（H743 + W25Q64 + 266MHz）
> **目标硬件**: H743VIT6 + W25Q256 + W9825G6KH + 25MHz HSE + 480MHz

### 一、RCC 时钟

| 参数 | 模板值 | 需改成 | 说明 |
|------|--------|--------|------|
| HSE | **8 MHz** | **25 MHz** | 你的无源晶振 |
| HSE 模式 | Crystal/Ceramic | 不变 | — |
| SYSCLK | 266 MHz | **480 MHz** | H743 最高 |
| PLL1 Source | HSE | 不变 | — |
| DIVM1 | 自动 | **/5** | 25/5=5MHz VCO输入 |
| DIVN1 | 自动 | **×160** | 5×160=800MHz VCO |
| DIVP1 | 自动 | **/2** | 800/2=400? 用CubeMX自动解 |
| Power Scale | Scale 1/2 | **Scale 0** | 480MHz 必须 Scale 0 |
| HCLK | 自动 | **240 MHz** | D1CPRE /2 |
| APB1/APB2 | 120 MHz | 不变 | — |
| HCLK3（QSPI/FMC） | 133 MHz | **240 MHz** | 自动跟随 |
| QSPI Kernel | 133 MHz | **240 MHz** | Clock Prescaler=0 → 240MHz；但W25Q256上限133MHz → Prescaler至少为1（120MHz） |
| FMC SDRAM Clock | 无 | **HCLK3 / 2 = 120 MHz** | W9825G6KH 上限 166MHz |

> **操作**: 在 Clock Configuration 直接输入 SYSCLK=480 → 点 Resolve Clock Issues → CubeMX 自动求解放心用。

### 二、QUADSPI

| 参数 | 模板值 | 需改成 | 原因 |
|------|--------|--------|------|
| Flash Size | **22** (8MB) | **24** (32MB) | W25Q64→W25Q256, 2^(24+1)=32MB |
| Clock Prescaler | 1 | **1** | 240/2=120MHz ≤133MHz |
| FIFO Threshold | 4 | 不变 | — |
| Sample Shifting | HalfCycle | 不变 | — |
| CS High Time | 5 Cycle | 不变 | — |
| Clock Mode | Mode 0 | 不变 | — |

### 三、FMC SDRAM（模板没有，全部新增）

在 `Pinout → Connectivity → FMC → SDRAM1`：

**基础参数**：

| 参数 | 值 |
|------|-----|
| Clock & chip enable | **SDCKE0 + SDNE0** |
| Internal bank number | **4 banks** |
| Address | **13 bits** |
| Data | **16 bits** |
| Byte enable | **Enabled** |

**控制参数**：

| 参数 | 值 |
|------|-----|
| CAS Latency | **2** |
| Write protection | **Disabled** |
| SDRAM common clock | **HCLK / 2** |
| Burst read | **Enabled** |
| Read pipe delay | **0** |

**时序参数**（SDRAM 时钟 = 120MHz, Tck ≈ 8.33ns）：

| 参数 | 值 | 芯片要求 | 计算 |
|------|-----|---------|------|
| Row to column delay (tRCD) | **2** | ≥15ns | ceil(15/8.33) |
| Row precharge delay (tRP) | **2** | ≥15ns | ceil(15/8.33) |
| Row cycle delay (tRC) | **8** | ≥60ns | ceil(60/8.33) |
| Write recovery (tWR) | **2** | ≥2 tCK | — |
| Load mode to active (tMRD) | **2** | ≥2 tCK | — |
| Exit self-refresh (tXSR) | **9** | ≥72ns | ceil(72/8.33) |
| Self-refresh time (tRAS) | **6** | ≥42ns | ceil(42/8.33) |

### 四、MPU Region（必须全部配齐）

| Region | 地址 | 大小 | Cache | Buffer | Exec | 用途 |
|--------|------|------|:--:|:--:|:--:|------|
| 0 | 0x90000000 | **32MB** | ✅ | ✅ | ✅ | QSPI Flash（权重） |
| 1 | 0xC0000000 | 32MB | ✅ | ✅ | ❌ | SDRAM（激活值+帧缓冲） |
| 2 | 0x24000000 | 512KB | ✅ | ✅ | ❌ | AXI SRAM（内部） |
| 3 | 0x30000000 | 288KB | ❌ | ❌ | ❌ | SRAM1-3（DMA 缓冲） |

### 五、FreeRTOS

| 参数 | 值 | 说明 |
|------|-----|------|
| Interface | **CMSIS_V2** | V2 API |
| SYS Timebase | **TIM6** | 不用 SysTick（留给 FreeRTOS） |
| Memory scheme | **heap_4** | 支持碎片合并 |
| TOTAL_HEAP_SIZE | **30720** (30KB) | |
| MINIMAL_STACK_SIZE | 256 words | 1024 字节 |
| CHECK_FOR_STACK_OVERFLOW | **2** | 全面检测 |
| USE_NEWLIB_REENTRANT | **Enabled** | Cube.AI 需要 |
| USE_FPU | **Enabled** | H7 硬件浮点 |
| MAX_SYSCALL_INTERRUPT_PRIORITY | **5** | |
| TICK_RATE_HZ | **1000** | 1ms |

### 六、X-CUBE-AI

| 参数 | 值 |
|------|-----|
| Application | **ApplicationTemplate** |
| Model | `student_best_320.onnx` |
| Compression | **high**（INT8） |
| Optimization | **balanced** |
| External Flash | QSPI @ 0x90000000（权重.bin） |
| External RAM | SDRAM @ 0xC0000000（激活值） |

> **注意**: CubeMX GUI 会因 Flash 超 2MB 拒绝生成网络代码。用 CLI 绕过：
> ```bash
> stedgeai generate --target stm32h7 --name network -m student_best_320.onnx --compression high --optimization balanced --split-weights --output <工程>/X-CUBE-AI/App/
> ```
> 生成后手动复制 7 个 network_* 文件到工程。

### 七、SYS 与调试

| 参数 | 值 |
|------|-----|
| Debug | **Serial Wire** |
| Timebase Source | **TIM6** |

### 八、YOLO11n 内存规划

```
┌─────────────────────────────────────────────────┐
│  内部 Flash (0x08000000, 2MB)                    │
│  ├── 启动文件 + HAL 库 + FreeRTOS                │
│  ├── 推理代码 (network.c, ~645KB)                │
│  └── 用户代码 (main.c, 驱动)                     │
├─────────────────────────────────────────────────┤
│  QSPI Flash (0x90000000, 32MB)                  │
│  └── 权重 (network_data_params, INT8 ~2.5MB)     │
├─────────────────────────────────────────────────┤
│  SDRAM (0xC0000000, 32MB)                       │
│  ├── .sdram_data (激活值 ~1.5MB)                  │
│  ├── fb[0] @ 0xC0100000 (153KB)                 │
│  ├── fb[1] @ 0xC0140000 (153KB)                 │
│  ├── g_ai_input @ 0xC0200000 (1.2MB)            │
│  ├── g_ai_output @ 0xC0400000 (263KB)           │
│  └── (剩余 ~27MB 空闲)                           │
├─────────────────────────────────────────────────┤
│  内部 SRAM (DTCM+AXI+SRAM1-3, ~1MB)             │
│  ├── FreeRTOS 堆 + 任务栈                        │
│  ├── DMA 缓冲区                                  │
│  └── Cube.AI runtime library                    │
└─────────────────────────────────────────────────┘
```

### RAM 区域用途建议

| 区域 | 地址 | 大小 | 用途 |
|------|------|------|------|
| DTCM | 0x20000000 | 128KB | 关键数据、中断栈（零等待） |
| AXI SRAM | 0x24000000 | 512KB | 大缓冲区、帧缓冲 |
| SRAM1-3 | 0x30000000 | 288KB | 通用、DMA 缓冲区 |
| SRAM4 | 0x38000000 | 64KB | 低功耗保留数据 |

### 为什么必须外挂 QSPI Flash

- YOLO11n FP32 权重 = 9.9MB > 2MB 内部 Flash
- YOLO11n INT8 权重 = 2.48MB > 2MB 内部 Flash
- 外挂 W25Q256 (32MB) 或 W25Q128 (16MB) QSPI Flash → 存权重绰绰有余
- Memory-Mapped 模式：CPU 直接按地址读权重（0x90000000），零拷贝

---

## 开发环境

### 方案 A：STM32CubeIDE（一站式，~1GB）

```
下载: https://www.st.com/en/development-tools/stm32cubeide.html
包含: CubeMX + 编辑器 + GCC + ST-Link 调试器
插件: 内置 X-CUBE-AI（Help → Manage Embedded Software）
```

### 方案 B：CubeMX 独立版 + VS Code（轻量，~500MB）

| 工具 | 下载 |
|------|------|
| STM32CubeMX | https://www.st.com/en/development-tools/stm32cubemx.html |
| arm-none-eabi-gcc | https://developer.arm.com/downloads/-/gnu-rm |
| VS Code 插件 | STM32 for VSCode + Cortex-Debug |

### 工作流

```
CubeMX 打开 .ioc → 配引脚/时钟/QSPI → X-CUBE-AI 加载模型 → 生成代码
     ↓
VS Code 打开工程 → 写 main.c 业务逻辑
     ↓
Ctrl+Shift+P → Build → Flash → 跑起来
```

---

## 新建工程流程

### 1. 芯片选型

CubeMX → 搜索 `STM32H743VIT6` → 双击

### 2. 电源等级（关键！）

```
System Core → RCC → Power Regulator Voltage Scale → Scale 0
```

默认是 Scale 3（低功耗），不改到不了 480MHz。

### 3. 时钟配置

```
Pinout → RCC:
  HSE: Crystal/Ceramic Resonator
  LSE: Crystal/Ceramic Resonator (可选)

Clock Configuration:
  HSE 输入值 → 填板子实际晶振（通常是 8MHz 或 25MHz）
  SYSCLK → 直接输入 480 → 点 OK 自动求解
  最终: SYSCLK=480MHz, HCLK=240MHz, APB4=120MHz
```

### 4. 调试口

```
System Core → SYS → Debug → Serial Wire
```

**不要**把 SWD 引脚复用作 GPIO——烧了就锁死芯片。

### 5. 内存保护

```
System Core → CORTEX_M7:
  CPU ICache:  ✅ 启用
  CPU DCache:  ✅ 启用
  MPU:         手动配置（见下节）
```

### 6. 外设配置

按项目需求依次配：QUADSPI → DCMI → USART → GPIO

### 7. 代码生成

```
Project Manager:
  Toolchain: Makefile (VS Code) 或 MDK-ARM
  Copy only necessary library files: ✅
  Generate peripheral init as .c/.h pairs: ✅
```

---

## 🔴 生成代码后必须修改

> CubeMX Generate Code 之后，必须手动改以下内容。**每次都改**，因为 CubeMX 的 USER CODE 段保留但配置相关代码会被覆盖。

### 一、CubeMX 里改（Generate Code 前）

| # | 位置 | 改什么 | 不改后果 |
|---|------|--------|---------|
| 1 | Pinout → RCC → HSE | `BYPASS Clock Source` → **`Crystal/Ceramic Resonator`** | 无源晶振不起振 |
| 2 | Connectivity → FMC → SDRAM1 | Column bits 如果可编辑就改 **9**，不可编辑则代码里改 | SDRAM 访问地址错位 |
| 3 | CORTEX_M7 → MPU | 弹窗直接点 **Yes**（默认配置），不在 CubeMX UI 手动加 Region | — |

### 二、main.c 修改

#### 2.1 修正 HSE 模式（CubeMX 改过 Crystal 后可跳过）

文件: `Core/Src/main.c`

```c
// 找 SystemClock_Config 函数里的这行
// 如果 CubeMX 忘改，手动改：
RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;  // 旧: 有源晶振
RCC_OscInitStruct.HSEState = RCC_HSE_ON;       // 新: 无源晶振
```

#### 2.2 删掉旧模板的 XIP 跳转代码

文件: `Core/Src/main.c` → `/* USER CODE BEGIN 0 */` 区域

```c
/* USER CODE BEGIN 0 */
// ❌ 删掉以下全部（模板遗留的 XIP 测试代码）：
u8 writebuf[]={"Hello world from QSPI Memory Mapped Mode !"};
u8 readbuf[100];
typedef void(*pFunction)(void);
pFunction JumpToApplication;
#define APPLICATION_ADDRESS 0X90000000
/* USER CODE END 0 */
```

```c
/* USER CODE BEGIN 2 */
// ❌ 删掉 JumpToApplication 相关代码：
if (CSP_QSPI_EnableMemoryMappedMode() != HAL_OK) { Error_Handler(); }
SCB_DisableDCache();
SCB_DisableICache();
SysTick->CTRL=0;
JumpToApplication=(pFunction) (*(__IO u32*) (APPLICATION_ADDRESS+4));
__set_MSP(*(__IO u32*) APPLICATION_ADDRESS);
JumpToApplication();
/* USER CODE END 2 */
```

#### 2.3 添加 MPU_Config() 并修正初始化顺序

文件: `Core/Src/main.c` → `/* USER CODE BEGIN 4 */`

```c
/* USER CODE BEGIN 4 */
static void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct = {0};
    HAL_MPU_Disable();

    // Region 0: QSPI Flash @ 0x90000000, 32MB
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0x90000000;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;  // W25Q256 = 32MB
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    // Region 1: SDRAM @ 0xC0000000, 32MB
    MPU_InitStruct.BaseAddress      = 0xC0000000;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER1;
    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
/* USER CODE END 4 */
```

文件: `Core/Src/main.c` → `main()` 函数

```c
int main(void)
{
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    // ❌ 删掉 CubeMX 生成在这里的 SCB_EnableICache/DCache
    // （CubeMX 默认放在 HAL_Init 前面，这是错的）

    HAL_Init();
    /* USER CODE BEGIN Init */
    MPU_Config();           // ← 加在 HAL_Init 之后
    /* USER CODE END Init */

    SystemClock_Config();
    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    // 外设初始化（CubeMX 自动生成）
    MX_GPIO_Init();
    MX_FMC_Init();
    MX_QUADSPI_Init();
    MX_USART_Init();        // 等加了 USART 后

    /* USER CODE BEGIN 2 */
    // ★ 开 Cache 移到这里（外设初始化之后）
    SCB_EnableICache();
    SCB_EnableDCache();

    // SDRAM 初始化序列
    SDRAM_InitSequence();   // ← 加在 MX_FMC_Init 之后

    // QSPI 初始化 + 进入 MemoryMapped
    CSP_QUADSPI_Init();
    CSP_QSPI_EnableMemoryMappedMode();

    // Cube.AI 初始化
    MX_X_CUBE_AI_Init();
    /* USER CODE END 2 */

    // FreeRTOS
    osKernelInitialize();
    MX_FREERTOS_Init();
    osKernelStart();
    while(1) {}
}
```

### 三、fmc.c 修改

文件: `Core/Src/fmc.c`

#### 3.1 修正列地址位宽

```c
// 第 48 行附近
hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;   // ❌ 旧
hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;   // ✅ W9825G6KH 是 9 位列地址
```

#### 3.2 添加 SDRAM 初始化序列

文件: `Core/Src/fmc.c` → `/* USER CODE BEGIN 0 */`

```c
/* USER CODE BEGIN 0 */
#define SDRAM_MODEREG_BURST_LENGTH_1            ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     ((uint16_t)0x0000)
#define SDRAM_MODEREG_CAS_LATENCY_2             ((uint16_t)0x0020)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD   ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE    ((uint16_t)0x0200)

void SDRAM_InitSequence(void)
{
    FMC_SDRAM_CommandTypeDef cmd = {0};
    uint32_t temp = 0;
    cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;

    // 1. 时钟使能
    cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    cmd.AutoRefreshNumber = 1;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);
    HAL_Delay(1);

    // 2. 预充电所有 Bank
    cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    // 3. 8次自动刷新
    cmd.CommandMode       = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    cmd.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    // 4. 加载模式寄存器 (CL=2, Burst=1, Sequential)
    temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1
         | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL
         | SDRAM_MODEREG_CAS_LATENCY_2
         | SDRAM_MODEREG_OPERATING_MODE_STANDARD
         | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    cmd.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    cmd.ModeRegisterDefinition = temp;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    // 5. 设置刷新率 (120MHz: 64ms×120MHz/8192 ≈ 937)
    HAL_SDRAM_ProgramRefreshRate(&hsdram1, 937);
}
/* USER CODE END 0 */
```

然后在 `MX_FMC_Init()` 末尾调用：

```
/* USER CODE BEGIN FMC_Init 2 */
SDRAM_InitSequence();   // ← 加这行
/* USER CODE END FMC_Init 2 */
```

### 四、quadspi.c 修改

文件: `Core/Src/quadspi.c`

```c
// CSP_QSPI_Read 函数中, 第 665 行附近
// W25Q256 的 0xEB Fast Read Quad I/O 需要 8 个 dummy cycles
s_command.DummyCycles = 6U;   // ❌ 旧 (W25Q64 的值)
s_command.DummyCycles = 8U;   // ✅ W25Q256
```

### 五、FreRTOS 配置（后续）

Generate Code 后，在 `freertos.c` 中按需添加 Cube.AI 推理任务（栈至少 2048 words）。当前默认 `defaultTask` 栈 128 words 不满足推理需求。

### 六、检查清单

每次 `Generate Code` 后检查:

- [ ] HSE = Crystal（CubeMX）或 `RCC_HSE_ON`（代码）
- [ ] ColumnBits = 9
- [ ] main.c 无 XIP 跳转代码残留
- [ ] main.c 无 `SCB_EnableCache` 在 `HAL_Init` 之前
- [ ] main.c 加了 `MPU_Config()`（含 QSPI + SDRAM 两个 Region）
- [ ] main.c 加了 `SDRAM_InitSequence()` 调用
- [ ] quadspi.c `CSP_QSPI_Read` DummyCycles = 8
- [ ] QSPI FlashSize = 24, Prescaler = 1
- [ ] **FLASH.ld 加了 SDRAM MEMORY 区域 + `.sdram_data` 段**
- [ ] `g_ai_output` 地址无重叠 (≥0xC0400000，距 `g_ai_input` +1MB 不够)

---

## 🐛 常见代码陷阱 (2026-07-04 代码审查发现)

### 1. 栈溢出 — 大数组不能用局部变量

YOLO 后处理中 `detection_t raw[2100]` (~50KB) + `int kept[2100]` (~8KB) 如果在栈上分配，远超 FreeRTOS 任务的 16KB 栈 → HardFault。

**修复**: 改为 `static` 声明，或放 SDRAM。

```c
// ❌ 栈上分配（必崩）
detection_t raw[YOLO_NOUT_CELLS];   // ~50KB
int kept[YOLO_NOUT_CELLS];          // ~8KB

// ✅ static 分配（.bss 段，不占栈）
static detection_t raw[YOLO_NOUT_CELLS];
static uint8_t kept[YOLO_NOUT_CELLS];
```

### 2. DCMI 双缓冲 — DMA 不会自动乒乓

`HAL_DCMI_Start_DMA` 在 `CONTINUOUS` 模式下只写入一个缓冲区，循环覆盖。交换 `fb_idx` 不会改变 DMA 的目标地址。

**修复**: 在 `FrameEventCallback` 中 Stop → 切换缓冲 → Start：

```c
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
    SCB_InvalidateDCache_by_Addr((uint32_t *)fb[fb_idx], OV2640_FRAME_SIZE);
    fb_idx = 1 - fb_idx;    // 切换到另一个缓冲
    HAL_DCMI_Stop(hdcmi);   // 停止当前 DMA
    HAL_DCMI_Start_DMA(hdcmi, DCMI_MODE_CONTINUOUS,
                       (uint32_t)fb[fb_idx], OV2640_FRAME_SIZE / 4);
}
```

### 3. I2C 地址二次左移

`HAL_I2C_Mem_Read` 的 `DevAddress` 需要 `(7-bit addr << 1)`。如果已经左移过的值再 `<< 1`，地址错误。

```c
// ❌ 二次左移：0x60 << 1 = 0xC0 → 7-bit addr = 0x60（错误！）
#define OV2640_ADDR 0x60
HAL_I2C_Mem_Read(&hi2c1, OV2640_ADDR << 1, ...);

// ✅ 直接传入已左移的值
HAL_I2C_Mem_Read(&hi2c1, OV2640_ADDR, ...);
```

### 4. DCMI DMA 计数器单位

`__HAL_DCMI_GET_COUNTER` 返回 DMA 传输的 **32-bit word 数**，不是字节数。DCMI 每 4 个像素打包为 1 个 word。需要 ×4 得到字节数。

```c
// ❌ 直接当字节数用
g_snap_len = __HAL_DCMI_GET_COUNTER(hdcmi);

// ✅ 转为字节数
g_snap_len = __HAL_DCMI_GET_COUNTER(hdcmi) * 4;
```

### 5. HAL_DCMI_FrameEventCallback 重复定义

多个 .c 文件同时定义 `HAL_DCMI_FrameEventCallback`（非 weak）→ 链接器报错。

**修复**: 用 `#ifdef` 条件编译，或一方用 `__weak`：

```c
// bsp_ov2640.c — FreeRTOS 阶段
#if !defined(TEST_PHASE_OV2640) && !defined(TEST_PHASE_OV2640_SNAPSHOT)
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) { ... }
#endif

// test_ov2640.c — 测试阶段
#if defined(TEST_PHASE_OV2640) || defined(TEST_PHASE_OV2640_SNAPSHOT)
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) { ... }
#endif
```

通过 `test_config.h` 统一管理测试阶段宏。

### 6. MPU QSPI Region 大小不匹配

W25Q256 容量 32MB，MPU Region 若设 16MB，访问 16-32MB 区间无缓存保护。

```c
// ❌ 16MB < W25Q256 的 32MB
M.Size = MPU_REGION_SIZE_16MB;

// ✅
M.Size = MPU_REGION_SIZE_32MB;
```

---

## MPU + Cache 配置

### 初始化顺序（必须严格遵守）

```c
HAL_Init();
MPU_Config();            // 1. MPU 必须在 Cache 之前
SystemClock_Config();    // 2. 时钟（Scale 0, 480MHz）
MX_QUADSPI_Init();       // 3. QSPI（含 MemoryMapped 配置）
MX_DCMI_Init();          // 4. 摄像头
MX_USART_Init();         // 5. 串口
// ... 其他外设 ...
SCB_EnableICache();      // 6. Cache 最后开
SCB_EnableDCache();
MX_X_CUBE_AI_Init();     // 7. AI 模型加载
```

### 必加 MPU Region

| Region | 地址 | 大小 | Cache | 说明 |
|--------|------|------|-------|------|
| QSPI Flash | 0x90000000 | **32MB** | ✅ | 权重存储 |
| DTCM | 0x20000000 | 128KB | ❌ | 关键数据 |
| AXI SRAM | 0x24000000 | 512KB | ✅ | 帧缓冲 |
| SRAM1-3 | 0x30000000 | 288KB | ✅ | 通用/DMA |

### QSPI Region 示例代码

```c
MPU_Region_InitTypeDef MPU_InitStruct = {0};
HAL_MPU_Disable();

// QSPI Flash 区域（权重存储）
MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
MPU_InitStruct.BaseAddress      = 0x90000000;
MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
MPU_InitStruct.SubRegionDisable = 0x00;
MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
HAL_MPU_ConfigRegion(&MPU_InitStruct);

HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
```

### Cache 维护函数（DMA 场景必用）

```c
// CPU 写数据到 DMA 发送缓冲区后
SCB_CleanDCache_by_Addr((uint32_t*)buf, size);

// DMA 接收数据写入缓冲区后，CPU 要读
SCB_InvalidateDCache_by_Addr((uint32_t*)buf, size);

// 注意：地址和 size 必须 32 字节对齐（Cache Line = 32B）
```

---

## QSPI 外部 Flash

### 常用 Flash 芯片

| 型号 | 容量 | 速度 | 常见板子 |
|------|------|------|---------|
| W25Q128 | 16MB | 104MHz | 正点原子、野火 |
| W25Q256 | 32MB | 104MHz | 正点原子 H743 |
| MX25LM51245G | 64MB | 133MHz | ST 官方 EVAL 板 |

### 引脚连接

QSPI 用 6 根线：

```
BK1_NCS  → Flash CS
BK1_CLK  → Flash CLK
BK1_IO0  → Flash IO0 (SI / SO)
BK1_IO1  → Flash IO1
BK1_IO2  → Flash IO2
BK1_IO3  → Flash IO3
```

### CubeMX 配置要点

```
QUADSPI Mode: Memory Mapped
Flash Size:    2^(FSIZE+1) = 写出 Index 值（如 32MB = 2^25 → Index=24）
Clock Prescaler: 根据 SYSCLK 和 Flash 最大速率算
Chip Select High Time: 2-3 cycles
Dual Flash: Disable
```

### Memory-Mapped 模式读写

```c
// 读权重数据 — 直接指针访问
const uint8_t *weights = (const uint8_t *)0x90000000;
// weights[offset] 就是 Flash 上第 offset 字节

// 写 Flash — 必须先退出映射
HAL_QSPI_Abort(&hqspi);
QSPI_EraseSector(addr);
QSPI_WritePage(addr, data, len);
// 重新映射
QSPI_CommandTypeDef sCommand = { /* ... */ };
HAL_QSPI_MemoryMapped(&hqspi, &sCommand);

// 写完后失效 D-Cache
SCB_InvalidateDCache_by_Addr((uint32_t*)base, len);
```

### 写权重到 QSPI Flash 的流程

```
1. HAL_QSPI_Abort(&hqspi)           // 退出映射
2. QSPI_Erase 权重存放区域          // 先擦除
3. QSPI_Write 权重 .bin 文件内容     // 逐页写入
4. HAL_QSPI_MemoryMapped(&hqspi)    // 恢复映射
5. 读回校验（CRC/MD5）              // 确认无误
```

## FMC SDRAM

### W9825G6KH 参数

| 参数 | 数值 |
|------|------|
| 容量 | 32MB（256Mbit） |
| 位宽 | 16 bit |
| Bank数 | 4 |
| 行地址 | 13 bit (A0-A12) |
| 列地址 | 9 bit (A0-A8) |
| 最高时钟 | 166MHz@CL3, 133MHz@CL2 |
| 映射地址 | FMC Bank1: **0xC0000000** |

### CubeMX 配置

见上方 [CubeMX 配置完整清单 → 三、FMC SDRAM](#三fmc-sdram模板没有全部新增)。

### 初始化代码（MX_FMC_Init 之后手动调用）

```c
void SDRAM_InitSequence(void)
{
    FMC_SDRAM_CommandTypeDef cmd = {0};
    cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;

    // 1. 时钟使能
    cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    cmd.AutoRefreshNumber = 1;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0x1000);
    HAL_Delay(1);

    // 2. 预充电所有Bank
    cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0x1000);

    // 3. 8次自动刷新
    cmd.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    cmd.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0x1000);

    // 4. 加载模式寄存器 (CL=2, Burst=1, Sequential)
    cmd.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    cmd.ModeRegisterDefinition = 0x0020;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0x1000);

    // 5. 设置刷新率 (120MHz: 64ms×120MHz/8192 ≈ 937)
    HAL_SDRAM_ProgramRefreshRate(&hsdram1, 937);
}

// 读写测试
uint32_t *p = (uint32_t *)0xC0000000;
*p = 0xA5A5A5A5;
if (*p == 0xA5A5A5A5) { /* SDRAM OK */ }
```

### 初始化顺序

```c
HAL_Init();
MPU_Config();              // 先配 MPU(含 0xC0000000)
SystemClock_Config();      // 480MHz
MX_FMC_Init();             // FMC 外设
SDRAM_InitSequence();      // ★ 发送 SDRAM 初始化序列
MX_QUADSPI_Init();         // QSPI
SCB_EnableICache();
SCB_EnableDCache();
MX_X_CUBE_AI_Init();       // Cube.AI（激活值在 SDRAM）
```

### 常见问题

- **MemManage HardFault 访问 0xC0000000** → MPU 没配这个 Region
- **SDRAM 读回全 0** → 没调 `SDRAM_InitSequence()`
- **数据随机出错** → D-Cache 没 Invalidate，或时序参数偏紧

---

## 链接脚本 (Linker Script)

### 为什么需要修改

CubeMX 生成的链接脚本（`STM32H743VITX_FLASH.ld`）只定义了内部 RAM 区域（DTCM, RAM_D1, RAM_D2, RAM_D3, ITCMRAM），**不包含外部 SDRAM**。如果代码中有数据要放在 SDRAM（如 Cube.AI 激活值、帧缓冲），必须：

1. 在 `MEMORY` 块添加 SDRAM 区域
2. 在 `SECTIONS` 块添加 `.sdram_data` 输出段

### 必须添加的内容

#### 1. MEMORY 块 — 添加 SDRAM

```ld
MEMORY
{
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 2048K
  DTCMRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
  RAM_D1 (xrw)   : ORIGIN = 0x24000000, LENGTH = 512K
  RAM_D2 (xrw)   : ORIGIN = 0x30000000, LENGTH = 288K
  RAM_D3 (xrw)   : ORIGIN = 0x38000000, LENGTH = 64K
  ITCMRAM (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K
  SDRAM (xrw)    : ORIGIN = 0xC0000000, LENGTH = 32M   /* ← 新增 */
}
```

#### 2. SECTIONS 块 — 添加 .sdram_data 段

```ld
  /* External SDRAM section (AI activations, frame buffers — not loaded, not zeroed) */
  .sdram_data (NOLOAD) :
  {
    . = ALIGN(4);
    *(.sdram_data)
    *(.sdram_data*)
    . = ALIGN(4);
  } >SDRAM
```

插入位置：`.bss` 段之后、`._user_heap_stack` 之前。

> **NOLOAD** 是关键：SDRAM 的内容不需要在 Flash 中存储初始值，也不需要在启动时清零（SDRAM 初始化序列已经完成硬件初始化）。

### C 代码中使用

```c
// 方式1: 通过 section attribute
static AI_ALIGNED(4)
uint8_t g_activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE]
    __attribute__((section(".sdram_data")));

// 方式2: 直接使用绝对地址（需要自己管理不发生重叠）
static float *g_ai_input  = (float *)0xC0200000;   // 1.2MB
static float *g_ai_output = (float *)0xC0400000;   // 无重叠
```

### SDRAM 地址规划（32MB @ 0xC0000000）

```
0xC0000000 ┌─────────────────────┐
           │ .sdram_data 段       │  ← 链接器管理（AI 激活值 ~1.5MB）
0xC0100000 ├─────────────────────┤
           │ fb[0] (153KB)        │  ← 摄像头帧缓冲 0
0xC0140000 ├─────────────────────┤
           │ fb[1] (153KB)        │  ← 摄像头帧缓冲 1
0xC0200000 ├─────────────────────┤
           │ g_ai_input (1.2MB)   │  ← AI 输入 tensor (320×320×3 float)
0xC0400000 ├─────────────────────┤
           │ g_ai_output (263KB)  │  ← AI 输出 tensor (32×2100 float)
0xC0500000 ├─────────────────────┤
           │ (剩余 ~27MB 空闲)     │
0xC1FFFFFF └─────────────────────┘
```

> **注意**: `g_ai_input` 和 `g_ai_output` 使用绝对地址，必须确保与 `.sdram_data` 段不重叠。

### 检查清单

- [ ] `MEMORY` 块有 `SDRAM (xrw) : ORIGIN = 0xC0000000, LENGTH = 32M`
- [ ] `SECTIONS` 块有 `.sdram_data (NOLOAD) : { ... } >SDRAM`
- [ ] `bsp_ai.c` 的 `g_activations` 有 `__attribute__((section(".sdram_data")))`
- [ ] `main.c` 初始化顺序: `MPU_Config → MX_FMC_Init → SDRAM_InitSequence → EnableCache`

---

## X-CUBE-AI 模型部署

### 安装

STM32CubeMX 中：`Help → Manage Embedded Software Packages → STMicroelectronics → X-CUBE-AI → Install`

### 加载模型

CubeMX 左侧 `Additional Software → X-CUBE-AI → 勾选 Core → Application = ApplicationTemplate → Add Model`：

```
Model File: YOLOv8forSTM/v6_results/student_best_320.onnx
Input:      [1, 3, 224, 224]   (FP32)
Output:     [1, 32, 2100]      (YOLO 输出)
Compression: high (INT8 8-bit)
Optimization: balanced
Validation: 不勾选
Target:     STM32H743
```

### 绕过 CubeMX FLash 限制

CubeMX GUI 会因为模型权重 > 2MB 内部 Flash 而拒绝生成网络代码。用 CLI 绕过：

```bash
"STM32Cube/Repository/.../stedgeai.exe" generate \
  --target stm32h7 --name network \
  -m student_best_320.onnx \
  --compression high --optimization balanced \
  --allocate-inputs --allocate-outputs --split-weights \
  --output <工程>/X-CUBE-AI/App/
```

生成后手动复制 `network*.c/h` 到工程。`--split-weights` 确保权重 .bin 文件单独生成，可烧入 QSPI Flash。

### 模型规格（最终采用）

| 参数 | 数值 |
|------|------|
| 模型 | YOLO11n 320×320 INT8 |
| 权重 | FP32 9.9MB → INT8 编译后 ~2.5MB（QSPI Flash） |
| 激活 | FP32 5.86MB → INT8 ~1.5MB（SDRAM） |
| MACC | 1,132,046,565（11.3亿次） |
| 输出 | f32(1×32×2100) YOLO 检测头 |

### 分析

点 `Analyze` → 查看报告：

```
Flash: 推理代码 + 权重 = xxx KB
RAM:   激活值 + 中间张量 = xxx KB
Inference Time: xxx ms @ 480MHz
```

### 常见 Cube.AI 错误

| 错误 | 原因 | 解决 |
|------|------|------|
| E200 (ValidationError) | ONNX opset 不兼容 | 导出时指定 opset=17 |
| E801 (HwIOError) | 模型太大超出 Flash | QSPI Flash 外存，改链接脚本 |
| AI buffer overflow | ATON_BUF 超 SRAM 限制 | 调整 buffer 大小或放 AXI SRAM |
| "redefinition of xxx" | 生成代码变量冲突 | 手动修，去掉重复定义 |

### 生成的代码结构

```
X-CUBE-AI/App/
├── app_x-cube-ai.c       ← 初始化 + 推理入口
├── app_x-cube-ai.h
├── ai_model_data.c       ← 权重数组（巨大）
├── ai_model_config.h
└── network.c / network.h ← 推理引擎

调用: aiRun(model_handle, input, output);
```

---

## FreeRTOS 配置

### CubeMX 关键参数

见上方 [CubeMX 配置完整清单 → 五、FreeRTOS](#五freertos)。

### 任务规划建议

| 任务 | 优先级 | 栈大小 | 说明 |
|------|--------|--------|------|
| YOLO 推理 | Normal | **2048 words (8KB)** | Cube.AI 调用链深 |
| 摄像头采集 | High | 512 words | DCMI DMA 双缓冲 |
| WiFi 上报 | Low | 512 words | ESP8266 AT 指令 |
| UI/状态监控 | Low | 256 words | LED + 门磁 |

### 注意事项

- `HAL_Delay()` 禁止在任务中使用 → 用 `vTaskDelay()`
- SYS Timebase → **TIM6**（SysTick 留给 FreeRTOS）
- `SysTick_Handler` 里**不能删** `xPortSysTickHandler()`
- Cube.AI 推理任务用 `osThreadNew()` 创建，推理阻塞不影响其他任务

---

## DCMI 摄像头 + DMA

### OV5640 接法

```
DCMI_D0-D7   → OV5640 Y0-Y7     (8 位数据)
DCMI_PIXCLK  → OV5640 PCLK      (像素时钟)
DCMI_HSYNC   → OV5640 HREF      (行同步)
DCMI_VSYNC   → OV5640 VSYNC      (帧同步)
I2C SCL/SDA  → OV5640 SCCB       (寄存器配置, 地址 0x78)
```

> **OV5640 vs OV2640 关键差异**:
> | 参数 | OV5640 | OV2640 |
> |------|--------|--------|
> | SCCB 地址 | **0x78** (7-bit=0x3C) | 0x60 (7-bit=0x30) |
> | 寄存器地址 | **16-bit** | 8-bit |
> | PID | **0x56 0x40** (reg 0x300A/B) | 0x7F 0xA2 (reg 0x1C/D) |
> | 最大分辨率 | 2592×1944 (5MP) | 1600×1200 (2MP) |
> | SCCB 写 | `[regH, regL, val]` 3字节 | `[reg, val]` 2字节 |
| DVP 位宽 | **10-bit** D[9:0] | 8-bit D[7:0] |
| 8-bit 接法 | D[9:2]→DCMI_D0~7 | D[7:0]→DCMI_D0~7 |

### ST 官方 OV5640 驱动参考

**来源**: `github.com/STMicroelectronics/stm32-ov5640`

ST 官方驱动采用四文件架构，初始化流程为：
```
OV5640_Common[141] → SetResolution(4 reg) → SetPixelFormat(2 reg) → SetPolarities → EnableDVPMode
```

**关键寄存器 (ST 官方值, 2026-07-04 通过 curl 下载验证)**:

| 寄存器 | ST 值 | 说明 |
|--------|-------|------|
| `0x300E` (MIPI_CTRL) | `0x58`→**0x18** | 先关 MIPI PHY(0x58), 流开启时写 0x18 使能 DVP |
| `0x4300` (FORMAT_CTRL00) | **0x6F** | RGB565 格式 (非 0x61) |
| `0x501F` (FORMAT_MUX) | **0x01** | ISP→RGB MUX (非 0x00) |
| `0x4740` (POLARITY) | 0x22→**0x23** | PCLK=high, HREF=high, VSYNC=high |
| `0x3017` | **0x7F** | DVP 焊盘: VSYNC+HREF+PCLK+D[9:6] |
| `0x3018` | **0xFC** | DVP 焊盘: D[5:0] |
| `0x503D` | **0x00** | 关 color bar (调试: 0x80 开 8 色彩条) |

**OV5640_POLARITY_CTRL (0x4740) 位定义**:
| Bit | 信号 | 0 | 1 |
|-----|------|---|---|
| [5] | PCLK | Active Low | Active High |
| [1] | HREF | Active Low | Active High |
| [0] | VSYNC | Active High | Active Low |

### 双缓冲 DMA

```c
uint8_t frame_buf[2][FRAME_SIZE] __attribute__((section(".sram_axi")));

// DMA 半传输中断 → buf[0] 就绪，处理
// DMA 传输完成中断 → buf[1] 就绪，处理
// 处理前必须 Invalidate D-Cache

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
    SCB_InvalidateDCache_by_Addr((uint32_t*)current_buf, FRAME_SIZE);
    // 送给 YOLO 推理
    aiRun(model, current_buf, output);
}
```

### 图像预处理

YOLO11n 需要 640×640 RGB 输入：

```
OV2640 输出(JPG/RGB) → 缩放到 640×640 → Normalize(mean/std) → 模型输入
```

---

## 常用代码片段

### 栈 + 堆配置

在链接脚本 `.ld` 中：

```
_estack     = 0x20020000;    /* DTCM 顶, 128KB 栈 */
_Min_Heap_Size = 0x8000;     /* 32KB 堆 */
_Min_Stack_Size = 0x4000;    /* 16KB 栈 */
```

### HAL 时间基准

如果用了 FreeRTOS，HAL 时间基准不能用 SysTick：

```
System Core → SYS → Timebase Source → TIM6
```

裸机默认用 SysTick，不用改。

### 调试打印（串口重定向）

```c
int _write(int fd, char *ptr, int len) {
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 100);
    return len;
}
// printf 即可输出到串口
```

### 读 Flash 唯一 ID

```c
// 读芯片 UID (96bit)
uint32_t uid[3];
uid[0] = *((uint32_t*)0x1FF1E800);
uid[1] = *((uint32_t*)0x1FF1E804);
uid[2] = *((uint32_t*)0x1FF1E808);
```

---

## HardFault 速查

| 症状 | 常见原因 | 解决 |
|------|---------|------|
| 一上电就 HardFault | MPU 配了不放行的区域 | 补 QSPI Flash Region |
| | Cache 在 MPU 之前开启 | 调换初始化顺序 |
| | SDRAM 全局变量带初值 | `= {0}` 改为不初始化 |
| | 栈溢出（大数组在栈上） | 大数组改 `static` 或放 SDRAM |
| DMA 后数据错乱 | D-Cache 没 Invalidate | `SCB_InvalidateDCache_by_Addr()` |
| | 缓冲区地址未 32B 对齐 | `__attribute__((aligned(32)))` |
| 访问 0x90000000 崩 | QSPI 没配 MPU Region | 加 QSPI Region（见上节） |
| | QSPI 还没 init 就访问 | 确保 `MX_QUADSPI_Init()` 在前 |
| Cube.AI 推理崩 | 输入尺寸不匹配 | 检查 input tensor shape |
| | 权重校验失败 | 重写 QSPI Flash，校验 CRC |
| 串口乱码 | HSE 频率配错 | 查板子晶振实际值 |
| 烧录后无法连接 | SWD 脚被复用作 GPIO | BOOT0 拉高救砖，改代码 |

### 调试 HardFault 命令

GDB 中：
```
info registers       # 看 PC/LR 在哪崩的
x/10x $sp           # 看栈上的异常帧
p/x *((uint32_t*)0xE000ED2C)  # 读 CFSR 异常原因寄存器
```

---

## 正点原子 F767/H743 IGT6 核心板参考代码 (2026-07-04 阅读)

> 来源: `Refcode/STM32F767,H743-IGT6/` — 正点原子 Apollo 开发板配套例程
> 包含: 原理图、数据手册、65 个 HAL 库实验例程
> 缺失: BSP 驱动库（仅包含 User 层 main.c, 驱动封装在付费 BSP 包中）

### 标准初始化顺序（所有实验一致）

```c
sys_cache_enable();                    // 1. 开 L1-Cache (最先)
HAL_Init();                            // 2. HAL 库初始化
sys_stm32_clock_init(432,25,2,9);      // 3. 时钟: PLL/25MHz/2分频/9倍频 → 216MHz(F767)
delay_init(216);                       // 4. 延时函数 (需要时钟频率参数)
usart_init(115200);                    // 5. 串口 (调试输出)
led_init();                            // 6. LED (心跳指示)
mpu_memory_protection();               // 7. MPU 内存保护 (SDRAM 初始化之后再设)
sdram_init();                          // 8. SDRAM 初始化
lcd_init();                            // 9. LCD (需要 SDRAM 做帧缓冲)
key_init();                            // 10. 按键输入
// 然后初始化具体外设 (QSPI/I2C/DMA/摄像头等)
```

> **注意**: 正点原子把 MPU 放在 SDRAM 之后，与我们的做法（MPU 在 SDRAM 之前）不同。两种都可以：
> - MPU 在前：Region 配置好了，外设初始化后立即生效 → 更安全
> - SDRAM 在前：SDRAM 初始化序列发送完再配 MPU → 初始化期间无 MPU 限制
> - 我们采用 MPU 在前的方式（见 [MPU + Cache 配置](#mpu--cache-配置)）

### 变量放置在绝对地址

正点原子用 ARM 编译器的 `__at` 属性，直接将变量放在 SDRAM 物理地址：

```c
// AC5 编译器 (ARM Compiler 5)
uint16_t testsdram[250000] __attribute__((at(0xC0000000)));

// AC6 编译器 (ARM Compiler 6)
uint16_t testsdram[250000] __attribute__((section(".bss.ARM.__at_0xC0000000")));
```

比我们自己定义 `.sdram_data` 段更直接，但缺点：
- 不同编译器语法不同（AC5 vs AC6）
- 不支持多个分散的变量（需手动管理地址不重叠）
- Cube.AI 自动生成的 `AI_ALIGNED` + `.sdram_data` section 方式更健壮

### SDRAM 测试方法

```c
#define BANK5_SDRAM_ADDR  0xC0000000

// 写入: 每 16KB 写一个递增的 uint32_t 值，共 2048 个采样点覆盖 32MB
for (i = 0; i < 32 * 1024 * 1024; i += 16 * 1024) {
    *(__IO uint32_t*)(BANK5_SDRAM_ADDR + i) = temp++;
}

// 读出: 读回并校验单调递增（比写固定值+比较更可靠，能发现地址线短路）
for (i = 0; i < 32 * 1024 * 1024; i += 16 * 1024) {
    temp = *(__IO uint32_t*)(BANK5_SDRAM_ADDR + i);
    if (i > 0 && temp <= sval) break;  // 单调性校验失败
}
```

> **启示**: 我们的 `SDRAM_InitSequence()` 之后应加类似的读写测试确认硬件正常。

### QSPI Flash 使用模式

```c
// 1. 初始化
norflash_init();                    // BSP 层封装: QSPI GPIO + HAL_QSPI_Init + MemoryMapped

// 2. 读 ID 确认芯片在位
id = norflash_read_id();
while (id == 0 || id == 0xFFFF) {   // 0 或全 1 = 芯片不在位
    LED0_TOGGLE();                   // LED 闪烁提示
    delay_ms(500);
}

// 3. Flash 大小硬编码（W25Q256 = 32MB）
flashsize = 32 * 1024 * 1024;

// 4. 读写操作（从末尾 200 字节处开始）
#define FLASH_ADDR  (flashsize - 200)
norflash_write(buf, FLASH_ADDR, len);   // 写
norflash_read(buf, FLASH_ADDR, len);    // 读
```

> **关键**: 初始化后必须读 ID 验证芯片在位，0x0000 或 0xFFFF 表示通信失败。正点原子用 `norflash_write/read` 封装了 HAL_QSPI 的 MemoryMapped 进出操作，这样写 Flash 时自动退出映射、写完后恢复映射。

### DMA 使用模式

```c
dma_init(DMA2_Stream7, DMA_CHANNEL_4);          // 初始化 DMA 外设

HAL_UART_Transmit_DMA(&huart, buf, len);        // 启动 DMA 传输

// 等待 DMA 传输完成（轮询方式，FreeRTOS 下应改用信号量）
while (!__HAL_DMA_GET_FLAG(&hdma, DMA_FLAG_TCIF3_7)) {
    // 查询进度: __HAL_DMA_GET_COUNTER(&hdma) 返回剩余数据项数
    pro = 1 - (__HAL_DMA_GET_COUNTER(&hdma) / total_len);
}
__HAL_DMA_CLEAR_FLAG(&hdma, DMA_FLAG_TCIF3_7);
HAL_UART_DMAStop(&huart);                       // 停止 DMA
```

> **注意**: `__HAL_DMA_GET_COUNTER()` 返回**剩余**数据项数（不是已传输的），且单位是数据宽度（word/halfword/byte）。DCMI 场景需 ×4 转字节数。

### MPU 保护设置

正点原子分两层：
1. `mpu_memory_protection()` — 设置板级默认 MPU region（SDRAM/QSPI/LCD 等）
2. `mpu_set_protection(addr, size, rgn, ap, priv, share, cache, buffer)` — 设置单个 region

典型调用：
```c
mpu_set_protection(
    0x20002000,                    // 基地址
    MPU_REGION_SIZE_128B,          // 大小
    MPU_REGION_NUMBER0,            // Region 编号
    MPU_REGION_FULL_ACCESS,        // 访问权限
    MPU_REGION_PRIV_RO_URO,        // 特权/用户权限
    MPU_ACCESS_NOT_SHAREABLE,      // 不共享
    MPU_ACCESS_NOT_CACHEABLE,      // 不缓存
    MPU_ACCESS_BUFFERABLE          // 可缓冲
);
```

### 摄像头和照相机实验（实验 39、47）

**该参考包中这两个实验的源代码缺失**，仅含 readme.txt 和 keilkill.bat。

正点原子 OV5640 摄像头驱动通常在单独的 "增值资料" 包中，包含：
- `BSP/OV5640/ov5640.c` — 完整的 OV5640 寄存器初始化表（200+ 寄存器）
- `BSP/DCMI/dcmi.c` — DCMI + DMA 双缓冲配置
- `BSP/SCCB/sccb.c` — SCCB 协议封装（16-bit 寄存器地址）

> 我们参考 ArduCAM 和 ESP32-CAM 的 OV5640 初始化序列自行编写了驱动（见 bsp_ov2640.c）

### 正点原子实验 vs 本项目对照

| 正点原子实验 | 本项目对应 | 状态 |
|------------|-----------|------|
| 实验12 MPU | `main.c → MPU_Config()` | ✅ 已实现 |
| 实验14 SDRAM | `fmc.c → SDRAM_InitSequence()` | ✅ 已实现 |
| 实验28 QSPI | `quadspi.c → CSP_QSPI_Init()` | ✅ 已实现 |
| 实验39 摄像头 | `bsp_ov2640.c` (OV5640) | ✅ 已实现 |
| 实验20 DMA | DCMI DMA + USART DMA | ✅ 已实现 |
| 实验25 IIC | OV5640 SCCB I2C | ✅ 已实现 |
| 实验47 照相机 | `test_ov2640.c` snapshot | ✅ 已实现 |
| 实验40 内存管理 | 链接脚本 .sdram_data 段 | ✅ 已实现 |

### 原理图参考

> 原理图路径: `Refcode/STM32F767,H743-IGT6/1，原理图/`

正点原子核心板关键引脚（IGT6 LQFP176 封装）：

| 功能 | 正点原子核心板 | 本项目 | 差异 |
|------|--------------|--------|------|
| QSPI | PB2(CLK), PB6(NCS), PD11-12, PE2, PA1 | PB2(CLK), **PB10**(NCS), PD11-12, PE2, PA1 | NCS 不同 |
| SDRAM | FMC Bank1 标准引脚 | 同 | — |
| DCMI | 标准 OV5640 8-bit 映射 | 同 | — |
| USART1 | PA9(TX), PA10(RX) | **PB14**(TX), **PB15**(RX) | 不同 |
| I2C1 | PB6(SCL), PB7(SDA) | 同 | — |
| LED | PB0, PF7 等 | PB0 | 相同 |

> **警告**: USART1 和 QSPI NCS 引脚与正点原子核心板不同，烧录正点原子例程前须修改引脚配置。

| 资源 | 链接 |
|------|------|
| RM0433 参考手册 | STM32H743/753 Reference Manual |
| AN4839 | STM32H7 L1 Cache 管理 |
| PM0253 | Cortex-M7 编程手册 |
| X-CUBE-AI 文档 | ST Edge AI 开发者云 |
| STM32 AI Model Zoo | github.com/STMicroelectronics/stm32ai-modelzoo |
| 安富莱(硬汉)论坛 | forum.anfulai.cn — H7 实战帖多 |
| 本项目 Cube.AI 指南 | `miniapp/STM32_to_Cloud.md` |

---

## 🐞 硬件调试过程 (2026-07-04)

> 工程: `STM32H743IIT6/IITx6/`
> 板子: STM32H743IIT6 + W25Q256 + W9825G6KH + OV5640 + ESP-01S
> 策略: 每步一个独立验证点, 通过后进入下一步, 避免多变量同时调试

### STEP 0 — 工程编译通过

**目标**: CubeMX 生成 + 自定义代码, 编译 0 错误 0 警告

- [ ] CubeMX 界面配好 HSE(25MHz Crystal) + PLL(480MHz) + HCLK(240MHz)
- [ ] 所有外设引脚确认与硬件一致
- [ ] 自定义文件加入工程 (bsp_*, app_tasks, test_*)
- [ ] `arm-none-eabi-gcc` 编译通过
- [ ] 链接脚本含 SDRAM + `.sdram_data`

### STEP 1 — FreeRTOS 启动 + 串口 printf

**目标**: 确认 MCU 跑起来, 时钟正确, 调度器正常运行

- [ ] 烧录后串口有 `printf` 输出 (115200/8/N/1)
- [ ] 打印 SYSCLK=480MHz, HCLK=240MHz (确认时钟配置)
- [ ] LED PB0 每 500ms 翻转一次 (确认调度器在跑)
- [ ] 串口回环正常 (敲键盘有回应)

**激活**: `test_config.h` → `#define TEST_PHASE_UART`

**验证点**:
```
╔══════════════════════════╗
║  Manager4UFridge  UART  ║
╚══════════════════════════╝
MCU:   STM32H743IIT6
UID:   XXXXXXXX-XXXXXXXX-XXXXXXXX
SYSCLK: 480 MHz
USART1: 115200 bps
[ECHO] ...
```

### STEP 2 — 门磁 EXTI 中断

**目标**: 确认 PG9 门磁 GPIO EXTI 工作

- [ ] 开门 → 串口出 `[DOOR] OPEN`
- [ ] 关门 → 串口出 `[DOOR] CLOSE`
- [ ] 回调函数被正确调用

**激活**: FreeRTOS 模式下 `vTaskMonitor` 任务体的 `#if 1`
**文件**: `app_tasks.c` → `vTaskMonitor()`

### STEP 3 — OV5640 I2C 通信 (软 I2C)

**目标**: 确认软 I2C 能读到 OV5640 PID

- [ ] `sccb_read(0x300A)` 返回 0x56
- [ ] `sccb_read(0x300B)` 返回 0x40
- [ ] PID 校验通过, 不进入死循环

**调试技巧**: 如果死循环(LED快闪), 用逻辑分析仪/示波器看 PB3/PB4 波形:
- SCL 是否有 100kHz 方波
- SDA 是否有数据变化
- 检查 PB3/PB4 是否被 CubeMX 配置为其他功能

**文件**: `bsp_ov5640.c` → `bsp_ov5640_init()`

### STEP 4 — OV5640 出图 (DCMI + DMA)

**目标**: 确认 DCMI DMA 能采集到有效帧数据

- [ ] DCMI DMA 双缓冲无溢出
- [ ] 帧大小 = 153600 bytes (320×240×2 RGB565)
- [ ] JPEG 头验证通过 (0xFF 0xD8) 如果启用 JPEG
- [ ] 或: 测试图案模式 (0x503D=0x80) 看到 8 色彩条

**调试技巧**:
- 先写 0x503D=0x80 开 color bar, 跳过镜头对准问题
- 如果 DCMI_D0-D7 接了 OV5640 D[9:2], 确认高 8 位对齐

**文件**: `bsp_ov5640.c` → `bsp_ov5640_start()`, `app_tasks.c` → `vTaskCamera()`

### STEP 5 — SDRAM 读写测试

**目标**: 确认外部 SDRAM 正常

- [ ] 写入 0xC0000000 递增模式
- [ ] 读出校验通过 (单调递增检查)
- [ ] 全 32MB 无坏点

**测试代码** (在 `main.c` → `USER CODE 2` 中插入):
```c
uint32_t temp = 0;
for (uint32_t i = 0; i < 32*1024*1024; i += 16*1024) {
    *(__IO uint32_t*)(0xC0000000 + i) = temp++;
}
temp = 0;
for (uint32_t i = 0; i < 32*1024*1024; i += 16*1024) {
    uint32_t v = *(__IO uint32_t*)(0xC0000000 + i);
    if (i > 0 && v <= *(volatile uint32_t*)(0xC0000000 + i - 16*1024)) {
        printf("[FAIL] SDRAM at 0x%08X\r\n", (unsigned)(0xC0000000 + i));
        break;
    }
}
printf("[OK] SDRAM 32MB passed\r\n");
```

### STEP 6 — QSPI Flash 读写测试

**目标**: 确认 W25Q256 正常工作

- [ ] `norflash_read_id()` 返回有效 ID (非 0x0000 或 0xFFFF)
- [ ] Memory-Mapped 模式: 读 0x90000000 不 HardFault
- [ ] 写→读校验通过

### STEP 7 — Cube.AI 推理单次

**目标**: 确认 YOLO11n 能成功加载并推理一次

- [ ] `bsp_ai_init()` 返回 0 (网络创建成功)
- [ ] 用随机/固定输入数据调用 `bsp_ai_run()`, 返回 1 (batch=1)
- [ ] 输出 tensor 非全零

**文件**: `bsp_ai.c` → `bsp_ai_init()` / `bsp_ai_run()`

### STEP 8 — 全链路: 门→拍照→推理→输出

**目标**: 端到端验证

- [ ] 开门触发 → DCMI 拍照 → 预处理 → AI 推理 → NMS → 串口出 `[DET]`
- [ ] 检测结果可读 (class_id + score + bbox)

**激活**: FreeRTOS 模式, 三个任务全部 `#if 1`
**文件**: `app_tasks.c` → 全部任务

---

### 当前状态

| STEP | 状态 | 备注 |
|------|:----:|------|
| 0 编译 | 🔧 | Post-gen 修复完成, 待编译验证 |
| 1 串口 | 📋 | TEST_PHASE_UART 已激活 |
| 2 门磁 | 📋 | |
| 3 I2C | 📋 | 软 I2C PB3/PB4 |
| 4 摄像头 | 📋 | |
| 5 SDRAM | 📋 | |
| 6 QSPI | 📋 | 引脚待确认 |
| 7 AI | 📋 | network.c 未生成 |
| 8 全链路 | 📋 | |

### STEP 0 已完成的 Post-Gen 修复

| 文件 | 修改 |
|------|------|
| `main.c` | HCLK DIV4→DIV2, FLASH_LATENCY 1→4 |
| `main.c` | 初始化顺序: HAL→Clock→外设→MPU→Cache→SDRAM |
| `main.c` | MPU: 默认→QSPI(32MB,exec) + SDRAM(32MB,no-exec) |
| `main.c` | 添加 SDRAM_InitSequence() + printf 重定向 |
| `main.c` | QSPI/AI init 注释掉 (STEP 6/7 再启用) |
| `main.c` | 添加 test phase 分支 (UART / OV5640 / FreeRTOS) |
| `fmc.c` | ColumnBits 8→9 |
| `quadspi.c` | GPIO Speed LOW→VERY_HIGH |
| `FLASH.ld` | SDRAM 32M + `.sdram_data (NOLOAD)` 段 |
| 本项目模型训练 | `YOLOv8forSTM/` 及 `v6_results/` |