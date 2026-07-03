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
| 摄像头 | OV2640 | UXGA 1600×1200, SCCB, DCMI 8-bit |
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
| 0 | 0x90000000 | 16MB | ✅ | ✅ | ✅ | QSPI Flash（权重） |
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
│  ├── 激活值 (~3MB)                               │
│  ├── 输入 tensor (320×320×3 = 1200KB)             │
│  └── 帧缓冲 (DCMI)                               │
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

    // Region 0: QSPI Flash @ 0x90000000, 16MB
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0x90000000;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_16MB;
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
| QSPI Flash | 0x90000000 | 16MB | ✅ | 权重存储 |
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
MPU_InitStruct.Size             = MPU_REGION_SIZE_16MB;
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

### OV2640 接法

```
DCMI_D0-D7   → OV2640 Y0-Y7     (8 位数据)
DCMI_PIXCLK  → OV2640 PCLK      (像素时钟)
DCMI_HSYNC   → OV2640 HREF      (行同步)
DCMI_VSYNC   → OV2640 VSYNC      (帧同步)
I2C SCL/SDA  → OV2640 SCCB       (寄存器配置)
```

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

## 参考资源

| 资源 | 链接 |
|------|------|
| RM0433 参考手册 | STM32H743/753 Reference Manual |
| AN4839 | STM32H7 L1 Cache 管理 |
| PM0253 | Cortex-M7 编程手册 |
| X-CUBE-AI 文档 | ST Edge AI 开发者云 |
| STM32 AI Model Zoo | github.com/STMicroelectronics/stm32ai-modelzoo |
| 安富莱(硬汉)论坛 | forum.anfulai.cn — H7 实战帖多 |
| 本项目 Cube.AI 指南 | `miniapp/STM32_to_Cloud.md` |
| 本项目模型训练 | `YOLOv8forSTM/` 及 `v6_results/` |