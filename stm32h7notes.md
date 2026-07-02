# STM32H7 开发笔记

面向 Manager4UFridge 项目的实战参考：STM32H743 + YOLO + QSPI Flash + Cube.AI。

## 目录

- [硬件规格](#硬件规格)
- [开发环境](#开发环境)
- [新建工程流程](#新建工程流程)
- [MPU + Cache 配置](#mpu--cache-配置)
- [QSPI 外部 Flash](#qspi-外部-flash)
- [X-CUBE-AI 模型部署](#x-cube-ai-模型部署)
- [DCMI 摄像头 + DMA](#dcmi-摄像头--dma)
- [常用代码片段](#常用代码片段)
- [HardFault 速查](#hardfault-速查)
- [参考资源](#参考资源)

---

## 硬件规格

### STM32H743VIT6

| 资源 | 数值 | 备注 |
|------|------|------|
| 内核 | Cortex-M7, 480MHz | 双精度 FPU |
| 内部 Flash | 2MB, Dual Bank | Bank1: 0x08000000, Bank2: 0x08100000 |
| 内部 RAM | ~1MB 总计 | DTCM(128KB) + AXI SRAM(512KB) + SRAM1-3(288KB) + SRAM4(64KB) |
| QSPI | 1 路, 支持 Memory-Mapped | 外部 Flash 映射到 0x90000000 |
| DCMI | 1 路, 8/10/12/14 bit | 摄像头接口，配合 DMA 双缓冲 |
| USART/UART | 多路 | ESP8266 用 1 路 |

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

---

## X-CUBE-AI 模型部署

### 安装

STM32CubeMX 中：`Help → Manage Embedded Software Packages → STMicroelectronics → X-CUBE-AI → Install`

### 加载模型

CubeMX 左侧：`Additional Software → X-CUBE-AI → Add Model`

```
Model File: student_best.pt 或 student_best.onnx
Input:      [1, 3, 640, 640]   (FP32)
Output:     [1, 84, 8400]      (YOLO 输出)
Quantization: INT8 (8-bit)
Validation: 随机输入测试 → 对比 PyTorch/ONNX 输出
Target:     STM32H743
```

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