"""
PC 端接收脚本：从串口接收 OV2640 JPEG 快照并保存为 .jpg 文件

用法: python recv_jpeg.py COM3 [output.jpg]

协议:
  STM32 发送 [0xAA 0xBB][4字节长度 big-endian][JPEG 数据]
"""
import serial
import sys
import struct
import time


def recv_jpeg(port: str, baud: int = 115200, timeout: float = 30.0):
    ser = serial.Serial(port, baud, timeout=1.0)
    ser.reset_input_buffer()
    print(f"[RECV] Listening on {port} @ {baud} bps...")

    deadline = time.time() + timeout
    buf = b""

    while time.time() < deadline:
        # 等待 sync word 0xAA 0xBB
        if len(buf) < 2:
            chunk = ser.read(ser.in_waiting or 1)
            if chunk:
                buf += chunk
            else:
                continue

        # 找 sync word
        idx = buf.find(b"\xAA\xBB")
        if idx < 0:
            # 只保留最后 1 字节（防止 sync 跨缓冲区）
            buf = buf[-1:]
            continue

        # 等待帧头完整（sync + 4 字节长度 = 6 字节）
        if len(buf) - idx < 6:
            chunk = ser.read(ser.in_waiting or 1)
            if chunk:
                buf += chunk
            continue

        # 解析长度
        header = buf[idx:idx + 6]
        total_len = struct.unpack(">I", header[2:6])[0]
        print(f"[RECV] Frame detected, length={total_len} bytes")

        # 丢弃 header 前的内容
        buf = buf[idx + 6:]

        # 收 JPEG 数据
        while len(buf) < total_len and time.time() < deadline:
            remaining = total_len - len(buf)
            chunk = ser.read(max(remaining, ser.in_waiting or 1024))
            if chunk:
                buf += chunk
                if len(buf) % 32768 == 0 or len(buf) == total_len:
                    pct = 100.0 * len(buf) / total_len
                    print(f"  recv {len(buf)}/{total_len} ({pct:.0f}%)")

        if len(buf) >= total_len:
            jpeg_data = buf[:total_len]

            # 验证 JPEG header
            if jpeg_data[:2] == b"\xFF\xD8":
                output = sys.argv[2] if len(sys.argv) > 2 else "snapshot.jpg"
                with open(output, "wb") as f:
                    f.write(jpeg_data)
                print(f"[OK] Saved to {output} ({len(jpeg_data)} bytes)")
                return output
            else:
                print(f"[WARN] Not a valid JPEG (header={jpeg_data[:4].hex()})")
                buf = buf[total_len:]  # 跳过, 继续找下一个
                continue
        else:
            print("[FAIL] Timeout waiting for JPEG data")
            return None

    print("[FAIL] No frame detected within timeout")
    return None


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: python {sys.argv[0]} <COMx> [output.jpg]")
        sys.exit(1)

    result = recv_jpeg(sys.argv[1])
    if result is None:
        sys.exit(1)