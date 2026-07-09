# Findings — 研究记录

## 1. 39/ 例程 main.c 工作流程分析 (2026-07-05)

### 文件结构（532 行，6 个函数 + 全局变量区）

| 行号 | 内容 | 说明 |
|------|------|------|
| 39-84 | 全局变量/缓冲区 | `g_ov_mode`, `g_dcmi_line_buf[2][4096]`, `g_jpeg_data_buf[1MB]`, `g_jpeg_data_len/ok`, JPEG 尺寸表 |
| 97-146 | `jpeg_data_process()` | 帧中断 ISR：处理 DMA 剩余数据 + 帧状态机 (0→1→2→0) |
| 155-180 | `jpeg_dcmi_rx_callback()` | JPEG DMA 行回调：双缓冲拷贝到 `g_jpeg_data_buf[]` |
| 187-205 | `rgblcd_dcmi_rx_callback()` | RGB DMA 行回调：DMA2D 逐行填充 LTDC → LCD |
| 213-327 | `jpeg_test()` | JPEG 模式主循环：拍照 → 找 FF D8/D9 → USART2 逐字节发给 PC |
| 336-456 | `rgb565_test()` | RGB565 模式主循环：实时预览，DMA2D 逐行填充 LCD |
| 458-532 | `main()` | 入口，~70 行：初始化 12 步 → 等待摄像头 → 按键选择 → 分发 |

### main() 四阶段执行流程

```
main()
 │
 ├── 第一阶段：系统初始化（行 460-475，12 步，顺序不可变）
 │   sys_cache_enable()                             // ① L1 I-Cache + D-Cache
 │   HAL_Init()                                     // ② HAL 库
 │   sys_stm32_clock_init(160, 5, 2, 4)             // ③ 400MHz (160×25/5÷2÷2)
 │   delay_init(400)                                // ④ 延时
 │   usart_init(115200)                             // ⑤ USART1 调试串口
 │   usart2_init(921600)                            // ⑥ USART2 JPEG 输出串口
 │   usmart_init(200)                               // ⑦ 串口命令调试
 │   mpu_memory_protection()                        // ⑧ MPU Cache 一致性
 │   led_init() / key_init()                        // ⑨ LED + 按键
 │   sdram_init()                                   // ⑩ 外部 SDRAM (0xC0000000, 32MB)
 │   lcd_init()                                     // ⑪ LCD (LTDC RGB 屏, 帧缓冲在 SDRAM)
 │   btim_timx_int_init(10000-1, 20000-1)           // ⑫ 定时器 10KHz, 帧率统计
 │
 ├── 第二阶段：等待摄像头就绪（行 481-490）
 │   while (ov5640_init() != 0)                     // 轮询直到成功
 │       显示 "OV5640 ERROR" + LED0 闪烁             // 摄像头未插/故障则卡死
 │   显示 "OV5640 OK"
 │
 ├── 第三阶段：用户选择模式（行 492-522）
 │   while(1) 闪烁显示 "KEY0:RGB565  KEY1:JPEG"
 │     KEY0 → g_ov_mode=0, break
 │     KEY1 → g_ov_mode=1, break
 │
 └── 第四阶段：分发（行 524-531）
     g_ov_mode==1 → jpeg_test()   // 无限循环
     g_ov_mode==0 → rgb565_test() // 无限循环
```

### 两个模式的本质区别

| | RGB565 模式 | JPEG 模式 |
|---|---|---|
| 数据格式 | 逐行 RGB565 像素 | 完整 JPEG 帧 |
| DMA 缓冲单位 | `lcddev.width/2` halfword | 4096 word (4KB) |
| 行回调 | `rgblcd_dcmi_rx_cb()` — DMA2D 填充 LTDC | `jpeg_dcmi_rx_cb()` — 拷贝到帧缓冲 |
| 帧完成信号 | `g_curline >= lcddev.height` | 帧中断 → `jpeg_data_process()` → `g_jpeg_data_ok=1` |
| 输出目标 | LCD 屏幕（实时） | USART2 → PC（逐字节发送） |
| 按键 | KEY0 对比度, KEY1 自动对焦, KEY2 特效, KEY_UP 缩放 | 同 + KEY_UP 改 JPEG 分辨率

### DCMI 双缓冲数据流（核心技术）

```
OV5640 输出 8-bit 并行数据 @ PCLK
        │
        ▼
DCMI (硬件同步 HSYNC+VSYNC, PCLK上升沿)
        │
        ▼ DMA1_Stream1 (循环双缓冲模式)
        │
   ┌────┴────┐
   │ buf[0]  │  buf[1]   ← g_dcmi_line_buf[2][jpeg_line_size]
   │ (正在写入)│  (已满,等待读取)
   └────┬────┘
        │ DMA TC 中断 (传输完成中断)
        ▼
   dcmi_rx_callback() 函数指针
        │
   ┌────┴──────────────────┐
   │ RGB 模式              │ JPEG 模式
   │ rgblcd_dcmi_rx_cb()  │ jpeg_dcmi_rx_cb()
   │ ↓                    │ ↓
   │ DMA2D 逐行填充       │ 拷贝到 g_jpeg_data_buf[]
   │ LTDC → LCD           │ g_jpeg_data_len +=
   │ g_curline++          │
   │                      │ 帧中断 →
   │                      │ jpeg_data_process() →
   │                      │ g_jpeg_data_ok = 1 →
   │                      │ main 循环检测到 →
   │                      │ USART2 发送给 PC
   └──────────────────────┘
```

### 关键全局变量

| 变量 | 作用 |
|------|------|
| `g_ov_mode` | bit0: 0=RGB565, 1=JPEG |
| `g_dcmi_line_buf[2][4096]` | DMA 双缓冲 (每行 4KB) |
| `g_jpeg_data_buf[1MB]` | JPEG 帧缓冲 (SDRAM, 0xC01F4000) |
| `g_jpeg_data_len` | JPEG 有效数据长度 |
| `g_jpeg_data_ok` | 0=采集中, 1=可发送, 2=已发送 |
| `g_curline` / `g_yoffset` | LCD 当前行/垂直偏移 |
| `dcmi_rx_callback` | 函数指针，运行时切换 RGB/JPEG 回调 |

---

## 2. RefCodes 结构分析 & Scripts/ 驱动备份 (2026-07-06)

### RefCodes 目录结构

```
RefCodes/
├── 【正点原子】阿波罗STM32H743开发板资料 资料盘(A盘)/
│   ├── 01阿波罗STM32H743开发板光盘结构(必读).txt
│   ├── 4，程序源码.zip  ← 1.24GB，含全部例程
│   │   └── 2，标准例程-HAL库版本.zip  (22,583 entries, 70个目录)
│   │       ├── 实验0-1~0-3 Template工程模板
│   │       ├── 实验1~64 完整HAL例程
│   │       └── keilkilll.bat / 当前目录.c和.h文件批量替换.bat
│   ├── 5，SD卡根目录文件.rar
│   ├── 6，软件资料/ (MDK/图片编解码/字库/FATFS等)
│   └── STM32H7开发指南-HAL库版本_V1.0.pdf (58MB)
│
└── 【正点原子】手把手教你学FreeRTOS系列/
    └── FreeRTOS一期/二期视频资料
```

### 64+ HAL 例程完整清单

| 编号 | 实验 | ⭐ | 编号 | 实验 | ⭐ |
|------|------|---|---|------|---|--|
| 0-1~3 | Template工程模板 | | 33 | DS18B20温度传感器 | |
| 1 | 跑马灯 | | 34 | DHT11温湿度传感器 | |
| 2 | 蜂鸣器 | | 35 | MPU9250九轴传感器 | |
| **3** | **串口通信** | ⭐ | 36 | NRF24L01无线通信 | |
| 4 | 外部中断 | | 37 | FLASH模拟EEPROM | |
| 5 | 独立看门狗 | | **38** | **摄像头实验** | ⭐ |
| 7 | 定时器中断 | | 39 | 内存管理 | |
| 8 | PWM输出 | | 40 | SD卡 | |
| 10 | 电容触摸按键 | | 42 | FATFS | |
| 11 | OLED显示 | | 43 | 汉字显示 | |
| **12** | **MPU内存保护** | ⭐ | **44** | **图片显示** | ⭐ |
| 13 | TFTLCD(MCU屏) | | **45** | **硬件JPEG解码** | ⭐ |
| **14** | **SDRAM** | ⭐ | 46 | 网络实验(LAN8720) | |
| **15** | **LTDC LCD(RGB屏)** | ⭐ | 53 | 手写识别 | |
| **16** | **USMART调试** | ⭐ | 55 | 串口IAP | |
| 24 | **DMA** | ⭐ | 56-60 | USB各种模式 | |
| 25 | IIC | | 61 | 网络通信 | |
| **26** | **IO扩展(PCF8574)** | ⭐ | 62-64 | UCOSII | |
| **28** | **QSPI(W25Q256)** | ⭐ | | | |

⭐ = 已提取到 Scripts/

### 已提取到 Scripts/ 的 12 个实验

| Scripts/ 子目录 | 来源 | 文件数 | 核心驱动文件 |
|---|---|---|---|
| **QSPI/** | 实验28 | 52 | `qspi.c/h` + `w25qxx.c/h` — W25Q256 QPI模式 |
| **SDRAM/** | 实验14 | 33 | `sdram.c/h` — FMC SDRAM |
| **MPU/** | 实验12 | 29 | `mpu.c/h` — MPU Cache配置 |
| **LTDC_LCD/** | 实验15 | 37 | `ltdc.c/h` + `lcd.c/h` — RGB屏驱动 |
| **USMART/** | 实验16 | 42 | `usmart.c/h` — 串口调试组件 |
| **Camera_OV5640/** | 实验38 | 118 | `ov5640.c/h` + `dcmi.c/h` — 39/的原始模板 |
| **Picture_Display/** | 实验44 | 180 | JPEG/BMP解码 + 图片显示 |
| **Hardware_JPEG/** | 实验45 | 184 | H743硬件JPEG解码器 |
| **IO_Expand/** | 实验26 | 48 | `pcf8574.c/h` — I2C IO扩展 |
| **DMA/** | 实验24 | 50 | `dma.c/h` — DMA通用参考 |
| **UART/** | 实验3 | 24 | `usart.c/h` — 基础串口 |
| **Template/** | 实验0-1 | 21 | 最小工程模板 |
| **总计** | | **818** | |

### QSPI 驱动接口确认

```c
// qspi.h — QSPI 底层
u8 QSPI_Init(void);
void QSPI_Send_CMD(u32 instr, u32 addr, u32 dummy, u32 imode, u32 amode, u32 asize, u32 dmode);
u8 QSPI_Receive(u8* buf, u32 datalen);
u8 QSPI_Transmit(u8* buf, u32 datalen);

// w25qxx.h — W25Q256 芯片操作
u16 W25QXX_ReadID(void);  // 读取ID → 识别型号
void W25QXX_Init(void);
void W25QXX_Qspi_Enable(void);  // 进入QPI 4线模式
void W25QXX_Read(u8* buf, u32 Addr, u16 Len);
void W25QXX_Write(u8* buf, u32 Addr, u16 Len);
void W25QXX_Erase_Sector(u32 Dst_Addr);  // 4KB擦除
void W25QXX_Erase_Chip(void);
// 支持: W25Q80/16/32/64/128/256 (ID: 0xEF13~0xEF18)
```

### QSPI 引脚差异 ⚠️ → 已解决 ✅ (2026-07-06)

| 信号 | 阿波罗 H743 (实验28) | CLAUDE.md 原记录 |
|------|---------------------|-----------------|
| CLK | **PB2** | PB2 |
| NCS | **PB6** | **PB10** |
| IO0 | **PF6** | **PD11** |
| IO1 | **PF7** | **PD12** |
| IO2 | **PF8** | **PE2** |
| IO3 | **PF9** | **PA1** |

> ~~**两套引脚除CLK外完全不同！必须万用表实测我们板子QSPI走线。**~~

**✅ 2026-07-06 上机验证**：直接烧录正点原子「实验28 QSPI」到自制 IIT6 板卡，串口输出 `QSPI FLASH Ready!`，W25Q256 检测成功。**确认自制板 QSPI 引脚与正点原子阿波罗 H743 完全一致**：
- PB2(AF9)=CLK, PB6(AF10)=NCS, PF6(AF9)=IO0, PF7(AF9)=IO1, PF8(AF10)=IO2, PF9(AF10)=IO3
- 正点原子 qspi.c/h + norflash.c/h 可直接套用，无需改引脚

### 提取策略

- **保留**: .c / .h / .s / .uvprojx / .uvoptx / .txt / .bat / .scvd
- **跳过**: .o / .axf / .hex / .bin / .lst / .dbg 等编译产物
- **跳过**: CORE/ / HALLIB/ / CMSIS/ 等公共目录 (39/ 已有)
- **保留**: HARDWARE/ (BSP) / SYSTEM/ / USER/ / USMART/ / readme.txt

---

## 3. LTDC LCD 调试方案 (2026-07-06)

### 故障现象

运行实验15 LTDC LCD(RGB屏) 例程，LCD 屏幕不显示。

### LCD 初始化关键路径

```
main()
├── mpu_memory_protection()    ← MPU 保护 SDRAM/LCD 区域
├── led_init()                 ← LED0=PB1
├── sdram_init()               ← FMC SDRAM 0xC0000000, 32MB
│   └── HAL_SDRAM_MspInit()   ← GPIO: PC0/2/3, PD0/1/8/9/10/14/15,
│                                PE0/1/7-15, PF0-5/11-15, PG0/1/2/4/5/8/15
│   └── sdram_initialization_sequence()
└── lcd_init()
    └── ltdc_panelid_read()    ← 读取 M0(PG6)/M1(PI2)/M2(PI7) 硬件引脚
        ├── id!=0 → ltdc_init()
        │   ├── 按 id 选面板参数 (pwidth/pheight/hsw/vsw/hbp/vbp/hfp/vfp)
        │   ├── ltdc_clk_set() — PLL3 时钟
        │   ├── HAL_LTDC_Init() → HAL_LTDC_MspInit()
        │   │   └── LTDC GPIO: BL(PB5), DE(PF10), VSYNC(PI9), HSYNC(PI10), CLK(PG7)
        │   │   └── R[3:7]/G[2:7]/B[3:7] 数据线 (16-bit RGB565)
        │   ├── ltdc_layer_parameter_config() — 帧缓冲在 SDRAM
        │   ├── LTDC_BL(1) — 打开背光
        │   └── ltdc_clear(0xFFFFFFFF) — 清屏白色
        └── id==0 → FMC MCU屏检测
```

### 可能的故障点（按概率排序）

1. **SDRAM 未初始化成功** — 帧缓冲在 SDRAM，SDRAM 坏了 LCD 必然不亮
2. **面板 ID 读取为 0** — M0/M1/M2 引脚焊接错误或上拉/下拉电阻不对
3. **背光电源不足** — 7寸屏需 12V 1A 外部供电，USB 供电不够
4. **FPC 排线接触不良** — 40P FPC 座子虚焊/插反
5. **LTDC 引脚不匹配** — 自制板 LTDC 数据线走线可能不同
6. **MPU Cache 配置问题** — SDRAM 区域未正确设为 write-through

### 调试版 main.c 输出内容

已修改 `E:\15 LTDC LCDRGB\User\main.c`，通过串口 USART1 (PA9/PA10, 115200) 输出：

| 检查项 | 输出内容 | 判断 |
|--------|---------|------|
| 程序是否启动 | "LTDC LCD RGB Debug Start" | 有=串口OK |
| LED 状态 | LED0 ON/OFF | 程序跑到哪一步 |
| SDRAM 单地址 RW | 写入 0xA5 / 读回比较 | 通过=芯片OK |
| SDRAM 多地址 RW | 5 个不同地址写读 | 通过=地址线OK |
| LCD 面板 ID | lcddev.id 十六进制值 | 0=未检测到面板 |
| 面板类型 | 中文描述 | 确认识别正确 |
| LTDC 分辨率 | pwidth x pheight | 0=LTDC未初始化 |
| M0/M1/M2 引脚 | PG6/PI2/PI7 原始电平 | 确定硬件 strapping |

### 控制开关

```c
#define LCD_DEBUG   // 注释掉恢复原始最小代码
```

### M0/M1/M2 面板 ID 对应表

| M[2:0] | ID | 面板 | 分辨率 |
|--------|-----|------|--------|
| 000 | 0x4342 | 4.3寸 | 480×272 |
| 001 | 0x7084 | 7寸 | 800×480 |
| 010 | 0x7016 | 7寸 | 1024×600 |
| 011 | 0x7018 | 7寸 | 1280×800 |
| 100 | 0x4384 | 4.3寸 | 800×480 |
| 101 | 0x1018 | 10.1寸 | 1280×800 |

---

## 4. ARM Compiler 5 中文编码问题 (2026-07-06) ⚠️

### 问题

在 ARM Compiler 5 (armcc V5.06) 环境下，`.c` 文件中出现中文字符（UTF-8 编码）会导致两个严重问题：

1. **编译警告 `#870-D: invalid multibyte character sequence`**
   - UTF-8 中文字节序列被 armcc 按系统 locale (GBK/CP936) 解析，识别为非法多字节序列

2. **相邻字符被"吃掉"**
   - 最危险的情况：中文注释/字符串后面的 ASCII 字符可能被多字节序列吞掉
   - 实测案例：`DBG_PRINTF("SDRAM 部分地址读写失败，可能: ***\r\n")` 
     → 编译后变成 `BG_PRINTF(...)`（`D` 被 UTF-8 序列吞掉）
   - 导致编译错误 `#20: identifier "BG_PRINTF" is undefined` 或产生奇怪的符号错误

### 根本原因

- ARM Compiler 5 是 Windows-native 编译器，默认使用系统 ANSI 代码页（中文 Windows = GBK/CP936）
- 现代编辑器（VS Code 等）默认保存为 UTF-8
- UTF-8 中一个中文字符占 3 字节，GBK 占 2 字节 → 解析错位

### 铁律

**给 ARM Compiler 5 写的任何 `.c/.h` 源文件，只能用纯 ASCII 字符。**

- 注释用英文写
- printf 字符串用英文
- 如果必须保留中文注释，文件编码必须设为 **GB2312/GBK**（Keil 默认编码）
- ARM Compiler 6 (armclang) 默认 UTF-8，无此问题

### 影响范围

- `39/` 工程模板的原始文件全部是 **GBK 编码**（正点原子用 Keil 编辑器写的）
- 我们用 VS Code 或其他编辑器新增的文件需要注意编码
- **编译时如遇奇怪的符号未定义/语法错误，先检查是否有中文字符**

### Python 编辑 GBK 编码 C 文件的铁律 (2026-07-06) 🔴

用 Python 脚本修改正点原子 `.c/.h` 文件时，三个坑反复踩，必须死记：

#### 坑 1：中文注释导致 Edit 工具/字符串匹配失败

正点原子文件都是 **GBK 编码**，中文字符在 GBK 和 UTF-8 下是不同的字节序列。Edit 工具和 `data.replace()` 匹配包含中文注释的字符串时，会因为编码不一致失败。

**铁律**：匹配字符串**只用纯 ASCII 子串**。例如：
- ❌ 匹配 `lcd_fill(0, 150, 239, 319, WHITE);  /* 精显白色 */`
- ✅ 匹配 `lcd_fill(0, 150, 239, 319, WHITE);` 然后 Python 里跳过注释部分

**方法**：用 `data.find(b'ASCII-only-substring')` 定位，用 `data.replace(old_ascii, new_ascii)` 替换，**永远不要在匹配模式里包含中文字节**。

#### 坑 2：Python bytes 字面量中 `\r\n` 被转成真换行

Python bytes 字面量里，`\r\n` 是真正的 CR+LF 字节 (0x0D 0x0A)。如果需要在 C 源码中写 `printf("...\r\n")`（4 个可打印字符 `\` `r` `\` `n`），必须用**显式字节构造**：

```python
# ❌ 错误：\r\n 被转成真正的 0x0D 0x0A，printf 字符串断开
new = b'printf("hello\\r\\n");'  # 在 bytes 字面量中 \\r\\n 也是 4 个字符
# 但注意：b'\\r\\n' 在 Python 里是 4 字节：\ r \ n（对的）
# 而 b'\r\n' 是 2 字节：CR LF（错的！）

# ✅ 正确：显式构造，永不踩坑
CRLF = bytes([0x0D, 0x0A])       # C 语句间的真正换行
ESC  = bytes([0x5C, 0x72, 0x5C, 0x6E])  # C 源码中的字面量 \r\n (4 字节)

new = b'printf("hello"' + ESC + b'");' + CRLF
```

**铁律**：给 C 文件加 printf 时，代码换行用 `CRLF` 变量，格式字符串里的 `\r\n` 用 `ESC` 变量。**绝不裸写 `\r\n` 或 `\\r\n` 在 bytes 字面量里**。

#### 标准模板

```python
CRLF = bytes([0x0D, 0x0A])
ESC  = bytes([0x5C, 0x72, 0x5C, 0x6E])

with open('main.c', 'rb') as f:
    data = f.read()

# 匹配只用 ASCII 子串
old = b'sprintf((char *)datatemp, \"%s%d\", (char *)g_text_buf, i);'
new = b'printf(\">> KEY1: Write addr=0x%08X' + ESC + b'\", flashsize-200);' + CRLF + b'            ' + old
data = data.replace(old, new, 1)

with open('main.c', 'wb') as f:
    f.write(data)
```

#### 坑 3：Python 普通字符串中 `\n` 被吃成真换行 (2026-07-06) 🔴

用 `in` 或 `find()` 搜索含 Windows 路径的字符串（如 `NORFLASH\norflash.c`）时，Python 普通字符串 `'...'` 里的 `\n` 是真换行 (0x0A)，不是反斜杠+n。

```python
# ❌ 错误：Python 普通字符串中 \n = 真换行 (0x0A)
# 'NORFLASH\\norflash.c' → 'NORFLASH' + 0x5C + 'n' + 'orflash.c'
# 看起来对，但容易在多层转义中搞混

# ❌ 更糟：忘了用双反斜杠
# 'NORFLASH\norflash.c' → 'NORFLASH' + 0x0A + 'orflash.c'  ← 真换行！

# ✅ 正确：bytes 搜索用显式字节构造，永不踩坑
BS = bytes([0x5C])  # 单个反斜杠
pattern = b'NORFLASH' + BS + b'norflash.c'
found = pattern in data

# ✅ 也可以用 raw bytes：b'NORFLASH\\norflash.c' 中 \\n 永远=反斜杠+n
# 但容易跟坑2混淆，建议统一用显式字节
```

**铁律**：搜索含 Windows 路径分隔符 `\` 的字符串时，**bytes 搜索用 `BS = bytes([0x5C])` 显式拼接**。绝不用普通字符串 `'...\n...'` 做路径匹配。

**三坑汇总**：

| 坑 | 触发条件 | 后果 | 解法 |
|----|---------|------|------|
| 1 中文匹配 | Edit/`replace()` 含 GBK 中文 | 匹配失败 | 只用 ASCII 子串 |
| 2 `\r\n` 字节 | bytes 字面量裸写 `\r\n` | printf 字符串断开 | `ESC = bytes([0x5C,0x72,0x5C,0x6E])` |
| 3 `\n` 搜索 | 普通字符串含 Windows 路径 `\n` | `in`/`find` 匹配失败 | `BS = bytes([0x5C])` + 拼接 |

### 反客 4.3寸 RGB 面板参数 (2026-07-06)

从 `FK429M1` 示例代码 `lcd_rgb.h` 中提取：

```c
// 反客 RGB043M1 4.3寸 480x272 RGB 面板 LTDC 时序
#define HBP   43    // 水平后沿
#define VBP   12    // 垂直后沿
#define HSW   1     // 水平同步宽度
#define VSW   1     // 垂直同步宽度
#define HFP   8     // 水平前沿
#define VFP   8     // 垂直前沿
#define LCD_Width   480
#define LCD_Height  272
#define LCD_CLK     10  // 10MHz 像素时钟
```

与正点原子 4.3寸 参数差异：

| 参数 | 正点原子 | 反客 |
|------|---------|------|
| HBP | 40 | **43** |
| VBP | 8 | **12** |
| HFP | 5 | **8** |
| VFP | 8 | 8 |
| CLK | 9MHz | **10MHz** |

- 反客面板无 M0/M1/M2 识别引脚，`ltdc_panelid_read()` 需强制返回面板 ID
- `ltdc_clk_set(300, 25, 30)` 产生 10MHz = 25MHz × 300/25 / 30

---

## 5. 自制板硬件资料分析 (2026-07-06)

### 板卡型号

`STM32F767-H743-IGT6` 核心板 — 双 MCU 兼容（F767/H743），用户使用 H743。

### 资料来源

`E:\H743\HWparameters\STM32F767,H743-IGT6\`：
- `1，原理图/` — CORE (MCU) + POWER&LCD&MEMORY 原理图 PDF
- `3，PCB定位图/` — Altium PcbDoc
- `4，程序源码/` — 65个实验例程 (F767 版本，BSP 驱动未包含)
- `5，硬件资料/` — 触摸屏 IC (GT系列) + 背光驱动 MP3302

### LTDC 引脚映射确认

通过 PyMuPDF 提取原理图文本 + 网标分析：**H743 的 LTDC 引脚与正点原子阿波罗 H743 完全一致。**

STM32H743 LTDC (AF14) → 40P FPC 连接器：

| LCD 信号 | H743 引脚 | 说明 |
|----------|----------|------|
| LCD_R3 | PH9 | |
| LCD_R4 | PH10 | |
| LCD_R5 | PH11 | |
| LCD_R6 | PH12 | |
| LCD_R7 | PG6 | 同时也是 M0 识别脚 |
| LCD_G2 | PH2 | |
| LCD_G3 | PH3 | |
| LCD_G4 | PH4 | |
| LCD_G5 | PH5 | |
| LCD_G6 | PH6 | |
| LCD_G7 | PH7 | 同时也是 M1 识别脚 |
| LCD_B3 | PE4 | |
| LCD_B4 | PE5 | |
| LCD_B5 | PE6 | |
| LCD_B6 | PE10 | |
| LCD_B7 | PE11 | 同时也是 M2 识别脚 |
| LCD_CLK | PG7 | |
| LCD_HSYNC | PI10 | |
| LCD_VSYNC | PI9 | |
| LCD_DE | PF10 | |
| LCD_BL | PB5 | 背光控制 |

### 背光电路

背光驱动芯片：**MP3302** (升压 LED 驱动)，使能脚连 PB5。
- `LTDC_BL(1)` → PB5 HIGH → MP3302 使能 → 背光亮
- 4.3寸屏也需要背光供电

### 其他确认

- DCMI 引脚：与正点原子一致（原理图已确认）
- SDRAM (W9825G6KH)：FMC BANK5 @ 0xC0000000，32MB
- QSPI (W25Q256)：PcbDoc 中确认引脚 PF8/PF9/PF7/PB6/PB2
- 串口1：PA9/PA10（CH340 USB转串口）

### 屏幕不亮排查结论

软件层面全部正常：
- SDRAM 读写测试 PASS ✓
- LTDC 初始化完成 (id=0x4342) ✓
- 反客面板时序正确 (HBP=43/VBP=12/CLK=10MHz) ✓
- 帧缓冲测试图案已写入 ✓
- LTDC 引脚映射与 Alientek 一致 ✓

剩余可能原因：
1. **背光供电不足** — 4.3寸屏需外部 12V 1A

---

## 6. QSPI 移植分析：28 QSPI → 39/ (2026-07-06)

### 配置对比结果

| 配置项 | 28 QSPI | 39/ | 差异 |
|--------|---------|-----|------|
| 系统时钟 | `sys_stm32_clock_init(160,5,2,4)` 400MHz | 相同 | 无 |
| Cache | I+D Cache, D-Cache Force Write-through | 相同 | 无 |
| HSI48 | 使能 (QSPI 需要 48MHz) | 相同 | 无 |
| HAL_QSPI_MODULE_ENABLED | ✓ | ✓ | 无 |
| 编译器宏定义 | `USE_HAL_DRIVER,STM32H743xx` | 相同 | 无 |
| 头文件路径 | `..\..\Drivers` (含所有 BSP) | 相同 | 无 |
| MPU 区域 | 7 个区域 (1-7), Region 0 空闲 | 相同 | 无 |

### 源文件差异

| 文件 | 28 QSPI | 39/ | 动作 |
|------|---------|-----|------|
| `Drivers/BSP/QSPI/qspi.c/h` | ✓ | ✗ | **复制到 39/** |
| `Drivers/BSP/NORFLASH/norflash.c/h` | ✓ | ✗ | **复制到 39/** |
| `stm32h7xx_hal_qspi.c` (Keil 工程) | ✓ | ✗ | **添加到 39/ Keil 工程** |
| `Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c` | ✓ | ✓ (HAL 库已有) | 只需加工程引用 |

### QSPI 关键配置参数（来自 28 QSPI qspi.c）

```c
g_qspi_handle.Init.ClockPrescaler = 1;        // QSPI_CLK = 200/(1+1) = 100MHz
g_qspi_handle.Init.FifoThreshold = 4;          // FIFO 阈值 4 字节
g_qspi_handle.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
g_qspi_handle.Init.FlashSize = POSITION_VAL(0X2000000)-1;  // 32MB (2^25)
g_qspi_handle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_3_CYCLE;
g_qspi_handle.Init.ClockMode = QSPI_CLOCK_MODE_3;         // CPOL=1, CPHA=1
g_qspi_handle.Init.FlashID = QSPI_FLASH_ID_1;
g_qspi_handle.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
```

### QSPI 引脚映射（已验证）

| STM32 引脚 | QSPI 信号 | W25Q256 引脚 | AF |
|-----------|----------|-------------|-----|
| PB2 | QSPI_CLK | Pin 6 (CLK) | AF9 |
| PB6 | QSPI_NCS | Pin 1 (/CS) | AF10 |
| PF6 | QSPI_IO0 | Pin 5 (SI/IO0) | AF9 |
| PF7 | QSPI_IO1 | Pin 2 (SO/IO1) | AF9 |
| PF8 | QSPI_IO2 | Pin 3 (/WP/IO2) | AF10 |
| PF9 | QSPI_IO3 | Pin 7 (/HOLD/IO3) | AF10 |

### MPU 考虑

- 当前 39/ 使用 Region 1-7, **Region 0 空闲**
- QSPI Memory-Mapped 模式在 0x90000000, 无需 MPU 配置也能工作（默认背景区域允许访问）
- **可选优化**：添加 Region 0 @ 0x90000000, 256MB, Cacheable+Bufferable → 提升 QSPI 内存映射读速度

### 移植清单

1. 复制 `qspi.c/h` → `39/Drivers/BSP/QSPI/`
2. 复制 `norflash.c/h` → `39/Drivers/BSP/NORFLASH/`
3. Keil 工程添加源文件：`qspi.c`, `norflash.c`, `stm32h7xx_hal_qspi.c`（HAL 库）
4. 可选：`mpu.c` 添加 Region 0 @ 0x90000000（Cacheable+Bufferable）
5. 新增 `User/module_qspi.c/h` — 封装 norflash_read/write/erase 为高层接口

---

## 7. SD 卡 (SDMMC) 驱动分析 (2026-07-07)

### 来源

正点原子「实验41 SD卡实验」— RefCodes 中的 HAL 例程。

### 用户实测结果

- 卡类型: SDHC, 容量 ~119 GB, 块大小 512 字节
- Sector 0 含 MBR 分区表 (55 AA 签名)

### 系统配置对比（实验41 vs 39/）

全部一致：

| 配置 | 值 |
|------|-----|
| 时钟 | `sys_stm32_clock_init(160,5,2,4)` → 400MHz |
| Cache | I+D Cache, D-Cache Force Write-through |
| HAL_SD_MODULE_ENABLED | 39/ 已默认使能 |
| SDMMC 时钟 | INIT: 240MHz/(250×2)=480KHz, NSPEED: 240MHz/(4×2)=30MHz |

### SDMMC 引脚（阿波罗 H743）

| 信号 | 引脚 | AF |
|------|------|-----|
| SD1_D0 | PC8 | AF12 |
| SD1_D1 | PC9 | AF12 |
| SD1_D2 | PC10 | AF12 |
| SD1_D3 | PC11 | AF12 |
| SD1_CLK | PC12 | AF12 |
| SD1_CMD | PD2 | AF12 |

### 引脚冲突

PC8/PC9/PC11 与 DCMI (OV5640 摄像头) 共享：
- DCMI 用 AF13，SDMMC 用 AF12 — 不同 AF，硬件不冲突
- 但 GPIO 引脚物理共享，**不能同时使用**摄像头和 SD 卡
- 实际场景：先拍照存 JPEG 到 SDRAM → 再写 SD 卡 → 分时复用，可行

### 驱动架构

```
User/module_sdcard.c/h     ← 高层封装（本项目新增）
        │
Drivers/BSP/SDMMC/
  sdmmc_sdcard.c/h         ← BSP 驱动（从实验41复制）
        │
HAL: stm32h7xx_hal_sd.c   ← HAL SD 驱动
     stm32h7xx_hal_sd_ex.c
     stm32h7xx_ll_sdmmc.c
```

### API 接口

```c
uint8_t sdcard_init(void);                                          // 初始化（最多重试5次）
uint8_t sdcard_read_sectors(uint8_t *buf, uint32_t sector, uint32_t count);
uint8_t sdcard_write_sectors(uint8_t *buf, uint32_t sector, uint32_t count);
void    sdcard_get_info(void);                                      // 串口打印卡信息
uint8_t sdcard_self_test(void);                                     // 读写验证自检
```

### 自检流程

1. Init SD 卡（最多 5 次重试）
2. 打印卡信息（类型/容量/块大小）
3. 读测试扇区 0x200000 原始数据备份
4. 写 "SDCARD Self-Test OK!" 测试图案
5. 读回并 memcmp 验证
6. 恢复原始数据

### FATFS 准备

裸扇区读写已就绪。FATFS（实验43）对接仅需实现 `diskio.c` 中的 `disk_read`/`disk_write` 等函数，底层调用 `sdcard_read_sectors`/`sdcard_write_sectors`。

### MPU 影响

无影响。39/ 的 8 个 MPU 区域全部占用（新增 QSPI Region 0），SDMMC 外设寄存器在 0x52000000，由默认背景区域覆盖，无需额外 MPU 配置。
3. **MP3302 背光驱动** — 可能需要特定配置

---

## 8. ESP-01S (ESP8266) WiFi 驱动研究 (2026-07-08)

### 资料来源

- ESP8266 模块官方指导文件.zip → AT 指令集 v0.18 (2014) + IoT SDK 手册
- Web 搜索：csdn、cnblogs、programmersought 上的 STM32+ESP8266 透传实现

### ESP-01S 硬件参数

| 参数 | 值 |
|------|-----|
| 工作电压 | 3.0-3.6V（建议 3.3V） |
| 峰值电流 | ≥300mA（TCP 握手时） |
| SPI Flash | 1MB |
| 天线 | PCB 天线，增益 3DBi |
| 默认波特率 | 115200 |
| AT 指令行尾 | `\r\n` |

### 透传模式 AT 指令序列

```
AT                  -> OK              (模块检测)
AT+CWMODE=1         -> OK              (Station 模式)
AT+CWJAP="ssid","pwd" -> WIFI GOT IP  (连 WiFi, 需 5-15s)
AT+CIPMUX=0         -> OK              (单连接)
AT+CIPSTART="TCP","host",port -> OK    (TCP 连接)
AT+CIPMODE=1        -> OK              (启用透传)
AT+CIPSEND          -> >               (进入透传)
[所有 USART 数据直通 TCP]
+++                 -> OK              (退出透传, 需要 1s 静默)
```

### 退出透传的关键细节

`+++` 不加 `\r\n`，需要前后各 >=1 秒无数据发送。否则 `+++` 被当普通数据发送。

```c
HAL_Delay(1000);                        // >=1s silence
HAL_UART_Transmit(..., "+++", 3, 100); // no \r\n
HAL_Delay(100);                         // wait for response
```

### 电源注意事项

ESP-01S 在 TCP 握手时峰值电流可达 300mA+。VCC 脚旁边必须并 100uF 钽电容 + 0.1uF 陶瓷电容（距引脚 <2cm），否则电压跌落导致模块掉电重启。

### 引脚注意事项

ESP-01S 丝印 "TX" = 模块的 RX（接 MCU TX），"RX" = 模块的 TX（接 MCU RX）。

### 本项目的引脚方案

| ESP-01S | STM32 | 说明 |
|---------|-------|------|
| TX | PA3 (USART2 RX) | 模块发 -> STM32 收 |
| RX | PA2 (USART2 TX) | 模块收 <- STM32 发 |
| RST | PA1 (GPIO) | 低复位 |
| CH_PD/EN | 3.3V | 硬拉高 |
| VCC | 3.3V | >=500mA |
| GND | GND | 共地 |
