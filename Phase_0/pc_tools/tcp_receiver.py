#!/usr/bin/env python3
"""
tcp_receiver.py — Receive JPEG frames from ESP-01S via WiFi TCP.

ESP-01S transparent mode sends raw JPEG bytes (FF D8 ... FF D9).
This server receives them, decodes, displays, and saves.

Usage:
    python tcp_receiver.py                        # listen on 0.0.0.0:8080
    python tcp_receiver.py --port 9000            # custom port
    python tcp_receiver.py --save-dir ./frames    # save all frames
    python tcp_receiver.py --display              # show frames in window

Press 'q' in display window to quit, Ctrl+C in terminal otherwise.
"""

import socket
import sys
import os
import argparse
import time
from collections import deque
import cv2
import numpy as np
import warnings
warnings.filterwarnings("ignore")  # suppress libjpeg "premature end" etc.


def find_jpeg_boundaries(data):
    """Find (start, end) of complete JPEG frames in byte buffer.
    Returns list of (start_offset, end_offset_exclusive) tuples.
    """
    frames = []
    i = 0
    while i < len(data) - 1:
        if data[i] == 0xFF and data[i + 1] == 0xD8:  # SOI
            j = i + 2
            while j < len(data) - 1:
                if data[j] == 0xFF and data[j + 1] == 0xD9:  # EOI
                    frames.append((i, j + 2))
                    i = j + 2
                    break
                j += 1
            else:
                break  # no EOI found yet
        else:
            i += 1
    return frames


def main():
    parser = argparse.ArgumentParser(description="TCP JPEG receiver for ESP-01S")
    parser.add_argument("--host", default="0.0.0.0", help="Listen address (default: 0.0.0.0)")
    parser.add_argument("--port", type=int, default=8080, help="Listen port (default: 8080)")
    parser.add_argument("--save-dir", default=None, help="Directory to save received JPEGs")
    parser.add_argument("--display", action="store_true", help="Display frames in OpenCV window")
    args = parser.parse_args()

    if args.save_dir:
        os.makedirs(args.save_dir, exist_ok=True)
        print(f"Saving frames to: {args.save_dir}")

    # Create TCP server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((args.host, args.port))
    server.listen(1)

    print(f"TCP server listening on {args.host}:{args.port}")
    print(f"Your PC IP addresses:")
    import subprocess
    try:
        result = subprocess.run(["ipconfig"], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'IPv4' in line or 'IP Address' in line:
                ip = line.split(':')[-1].strip()
                if ip and not ip.startswith('127.'):
                    print(f"  {ip}")
    except:
        pass
    print(f"Waiting for ESP-01S to connect...")
    print(f"(Make sure wifi_config.h has CLOUD_HOST set to your PC's IP)")
    print()

    server.settimeout(0.5)   # quick poll so Ctrl+C works on Windows

    conn = None
    buf = bytearray()
    frame_count = 0
    good_count = 0
    bad_count = 0

    try:
        while True:
            # Accept connection
            if conn is None:
                try:
                    conn, addr = server.accept()
                    print(f"Connected: {addr}")
                    buf.clear()
                    conn.settimeout(0.5)
                except socket.timeout:
                    continue  # back to top of loop, check Ctrl+C

            # Read data
            try:
                chunk = conn.recv(65536)
                if not chunk:
                    print("Connection closed by client")
                    conn.close()
                    conn = None
                    continue
                buf.extend(chunk)
            except socket.timeout:
                continue  # quick poll, no data is normal
            except ConnectionResetError:
                print("Connection reset")
                conn.close()
                conn = None
                continue

            # Extract complete JPEG frames
            frames = find_jpeg_boundaries(buf)
            for start, end in frames:
                jpeg_data = bytes(buf[start:end])
                size = len(jpeg_data)

                # Decode
                img = None
                try:
                    nparr = np.frombuffer(jpeg_data, np.uint8)
                    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                except:
                    pass

                if img is None:
                    # Bad frame: skip, just count
                    bad_count += 1
                else:
                    # Good frame
                    good_count += 1
                    print(f"Frame {frame_count}: {size}b ({img.shape[1]}x{img.shape[0]}) "
                          f"[good:{good_count} bad:{bad_count}]", end="\r")

                    if args.save_dir:
                        fname = os.path.join(args.save_dir, f"frame_{frame_count:04d}.jpg")
                        with open(fname, 'wb') as f:
                            f.write(jpeg_data)

                    if args.display:
                        cv2.imshow("ESP-01S JPEG Stream", img)
                        key = cv2.waitKey(1) & 0xFF
                        if key == ord('q'):
                            print("\nQuit requested")
                            raise KeyboardInterrupt
                        elif key == ord('s'):
                            cv2.imwrite(f"screenshot_{time.strftime('%H%M%S')}.jpg", img)

                frame_count += 1

            # Remove processed frames from buffer
            if frames:
                last_end = frames[-1][1]
                buf = buf[last_end:]

            # Prevent buffer from growing unbounded
            if len(buf) > 10 * 1024 * 1024:  # 10MB max
                print("Buffer too large, resetting")
                buf.clear()

    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        if conn:
            conn.close()
        server.close()
        if args.display:
            cv2.destroyAllWindows()
        print(f"\nDone. {frame_count} frames: {good_count} good, {bad_count} bad")


if __name__ == "__main__":
    main()
