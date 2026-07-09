#!/usr/bin/env python3
"""Quick test: read raw bytes from serial and verify 0x00-0xFF pattern."""
import serial, sys

port = sys.argv[1] if len(sys.argv) > 1 else "COM11"
baud = int(sys.argv[2]) if len(sys.argv) > 2 else 115200

ser = serial.Serial(port, baud, timeout=2)
print(f"Listening on {port} @ {baud}...")

while True:
    data = ser.read(256)  # read exactly 256 bytes
    if len(data) == 256:
        errors = sum(1 for i, b in enumerate(data) if b != i)
        print(f"Received 256 bytes, {errors} errors")
        if errors == 0:
            print("PERFECT! Serial link is clean. Problem is in JPEG source.")
        else:
            print(f"First 32 bytes: {data[:32].hex(' ')}")
            print(f"Expected:       {' '.join(f'{i:02x}' for i in range(32))}")
        break
    elif len(data) > 0:
        print(f"Got {len(data)} bytes (waiting for 256)...")
ser.close()
