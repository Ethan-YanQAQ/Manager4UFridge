#!/usr/bin/env python3
"""
patch_main.py - Apply Phase 0-5 modifications to main.c.
Only: glue framework + QSPI + full-speed mode.
NO JPEG protocol changes (Phase 6).
"""
import shutil

CRLF = bytes([0x0D, 0x0A])
ESC  = bytes([0x5C, 0x72, 0x5C, 0x6E])

SRC = r'E:\H743\RefCodes\2，标准例程-HAL库版本\正点原子标准例程-HAL库版本\实验39 摄像头实验\User\main.c'
DST = r'E:\H743\39\User\main.c'

shutil.copy2(SRC, DST)
with open(DST, 'rb') as f:
    d = f.read()

# === 1. Add glue.h include ===
d = d.replace(
    b'#include "./BSP/MPU/mpu.h"\r\n',
    b'#include "./BSP/MPU/mpu.h"\r\n#include "../User/glue.h"\r\n',
    1)

# === 2. USART2 baud (keep 921600 original) ===
# NO CHANGE - keep original 921600

# === 3. OV5640 ERROR printf ===
d = d.replace(
    b'        lcd_show_string(30, 130, 240, 16, 16, "OV5640 ERROR", RED);\r\n',
    b'        lcd_show_string(30, 130, 240, 16, 16, "OV5640 ERROR", RED);\r\n'
    b'        printf("OV5640 ERROR, retrying...' + ESC + b'");\r\n',
    1)

# === 4. Force JPEG, skip key loop, add glue_run ===
idx = d.find(b'lcd_show_string(30, 130, 200, 16, 16, "OV5640 OK", RED);\r\n')
tail = d[idx:]
idx_if = tail.find(b'if (g_ov_mode == 1)')
d = d[:idx] + \
    b'lcd_show_string(30, 130, 200, 16, 16, "OV5640 OK", RED);\r\n' + \
    b'    printf("OV5640 OK, entering JPEG mode' + ESC + b'");\r\n' + \
    b'    glue_run();\r\n' + \
    b'    g_ov_mode = 1;\r\n\r\n' + \
    tail[idx_if:]

# === 5. Remove old g_jpeg_data_len printf ===
old5 = (b'            printf("g_jpeg_data_len:%d' + ESC + b'", g_jpeg_data_len * 4);'
        b'                      /* \xb4\xf2\xd3\xa1jpeg\xcd\xbc\xc6\xac\xb4\xf3\xd0\xa1 */\r\n')
if old5 in d:
    d = d.replace(old5, b'', 1)

# === 6. Add JPEG size printf ===
idx6 = d.rfind(b'p += jpgstart;')
if idx6 > 0:
    d = d[:idx6] + b'                printf("JPEG:%u bytes' + ESC + b'", jpglen);\r\n                ' + d[idx6:]

# === NO Phase 6 changes (no jpeg_send_raw, no delay, no AA55, no baud change) ===

with open(DST, 'wb') as f:
    f.write(d)

# Verify
checks = {
    'glue.h': b'#include "../User/glue.h"',
    '921600': b'usart2_init(921600);',
    'ERROR pf': b'OV5640 ERROR, retrying',
    'glue_run': b'glue_run();',
    'g_ov=1': b'g_ov_mode = 1;',
    'JPEG pf': b'JPEG:%u bytes',
    'NO jpeg_sender.h': b'module_jpeg_sender.h' not in d,
    'NO jpeg_send_raw': b'jpeg_send_raw' not in d,
    'NO delay 5000': b'delay_ms(5000)',
    'NO old pf': b'g_jpeg_data_len:%d' not in d,
    'raw USART2': b'USART2->TDR = p[i];',
    'single g_ok': d.count(b'g_jpeg_data_ok = 2;') == 1,
}
for name, ok in checks.items():
    print(f'[{"OK" if ok else "FAIL"}] {name}')

all_ok = all(checks.values())
print(f'\n{"SUCCESS" if all_ok else "FAILED"} ({len(d)} bytes)')
