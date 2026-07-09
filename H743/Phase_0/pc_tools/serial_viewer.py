#!/usr/bin/env python3
"""
serial_viewer.py — Receive JPEG frames from STM32H743 USART2 and display in real-time.

Protocol: Raw JPEG stream with FF D8 / FF D9 markers (byte-stuffed).
Default baud: 921600.

Usage:
    python serial_viewer.py COM3                    # Windows
    python serial_viewer.py /dev/ttyUSB0            # Linux
    python serial_viewer.py COM3 --save-dir ./cap   # Save frames to disk
    python serial_viewer.py --list                  # List all COM ports

Press 'q' to quit, 's' to save current frame.
"""

import sys
import os
import argparse

import serial
import serial.tools.list_ports
import cv2
import numpy as np

# ============================================================
# COM port listing
# ============================================================
def list_ports():
    """List all serial ports."""
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        print("No serial ports found.")
        return
    print(f"{'Port':10s} {'VID:PID':12s} Description")
    print("-" * 70)
    for p in ports:
        vidpid = ""
        if p.vid is not None:
            vidpid = f"{p.vid:04X}:{p.pid:04X}"
        print(f"{p.device:10s} {vidpid:12s} {p.description}")


# ============================================================
# Frame decoder: scan byte stream for FF D8 ... FF D9
# ============================================================
JPEG_SOI = bytes([0xFF, 0xD8])
JPEG_EOI = bytes([0xFF, 0xD9])
BUFFER_SIZE = 512 * 1024


class JPEGFrameDecoder:
    def __init__(self):
        self.buf = bytearray()
        self.frame_count = 0
        self.lost_frames = 0

    def feed(self, data: bytes):
        """Feed raw bytes, returns list of complete JPEG frames found."""
        self.buf.extend(data)
        frames = []

        if len(self.buf) > BUFFER_SIZE:
            self.buf = self.buf[len(self.buf) - BUFFER_SIZE + 256 * 1024:]

        while True:
            soi_idx = self.buf.find(JPEG_SOI)
            if soi_idx < 0:
                break

            eoi_idx = self.buf.find(JPEG_EOI, soi_idx + 2)
            if eoi_idx < 0:
                if soi_idx > 256 * 1024:
                    del self.buf[:soi_idx]
                break

            frame_len = eoi_idx - soi_idx + 2
            frame_data = bytes(self.buf[soi_idx:eoi_idx + 2])

            if frame_len > 100:
                frames.append(frame_data)

            del self.buf[:eoi_idx + 2]

        return frames


# ============================================================
# Main
# ============================================================
def main():
    parser = argparse.ArgumentParser(description="STM32H743 JPEG Serial Viewer")
    parser.add_argument("port", nargs="?", default=None,
                        help="Serial port (e.g. COM3, /dev/ttyUSB0)")
    parser.add_argument("--baud", type=int, default=921600,
                        help="Baud rate (default: 921600)")
    parser.add_argument("--save-dir", default=None,
                        help="Directory to save captured frames")
    parser.add_argument("--max-saved", type=int, default=500,
                        help="Max frames to auto-save (default: 500)")
    parser.add_argument("--list", action="store_true",
                        help="List all COM ports and exit")
    parser.add_argument("--dump-raw", default=None,
                        help="Save ALL raw bytes to file (for debugging)")
    parser.add_argument("--save-lost", action="store_true",
                        help="Save corrupted/lost frames for inspection")
    args = parser.parse_args()

    if args.list:
        list_ports()
        return

    if not args.port:
        list_ports()
        print("\nUsage: python serial_viewer.py <PORT> [options]")
        return

    save_dir = args.save_dir
    if save_dir:
        os.makedirs(save_dir, exist_ok=True)
        print(f"[*] Saving frames to: {save_dir}")

    saved_count = 0
    lost_saved_count = 0
    paused = False
    raw_file = None
    lost_dir = None

    if args.dump_raw:
        raw_file = open(args.dump_raw, "wb")
        print(f"[*] Raw dump -> {args.dump_raw}")
    if args.save_lost:
        lost_dir = args.save_dir or "lost_frames"
        os.makedirs(lost_dir, exist_ok=True)
        print(f"[*] Corrupted frames -> {lost_dir}/")

    print(f"[*] Opening {args.port} @ {args.baud} baud...")
    try:
        ser = serial.Serial(
            port=args.port,
            baudrate=args.baud,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.5,
        )
    except serial.SerialException as e:
        print(f"[!] Cannot open {args.port}: {e}")
        print(f"[!] Close any serial terminal (PuTTY/SSCOM/etc.) and try again.")
        sys.exit(1)

    print(f"[*] Connected. Waiting for JPEG frames...")
    print(f"[*] Keys: 'q'=quit, 's'=save frame, 'p'=pause/resume, 'c'=clear\n")

    decoder = JPEGFrameDecoder()
    cv2.namedWindow("STM32 JPEG", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("STM32 JPEG", 640, 480)

    last_img = None

    try:
        while True:
            try:
                raw = ser.read(ser.in_waiting or 1)
            except serial.SerialException as e:
                print(f"\n[!] Serial error: {e}")
                break

            if raw:
                if raw_file:
                    raw_file.write(raw)

                frames = decoder.feed(raw)

                for frame_data in frames:
                    decoder.frame_count += 1
                    fn = decoder.frame_count

                    # Fix OV5640: FF A0 -> FF E0 (non-standard APP0 marker)
                    data_fixed = bytearray(frame_data)
                    for i in range(len(data_fixed) - 3):
                        if data_fixed[i] == 0xFF and data_fixed[i+1] == 0xA0:
                            data_fixed[i+1] = 0xE0
                    img_array = np.frombuffer(bytes(data_fixed), dtype=np.uint8).copy()
                    img = cv2.imdecode(img_array, cv2.IMREAD_COLOR)

                    if img is None:
                        decoder.lost_frames += 1
                        if decoder.lost_frames <= 3:
                            hex_str = frame_data[:32].hex(" ")
                            print(f"\n[!] Lost frame #{fn}: {len(frame_data)}B")
                            print(f"    First 32 bytes: {hex_str}")
                        # Save first lost frame as .jpg for debug
                        if decoder.lost_frames == 1:
                            with open("debug_lost.jpg", "wb") as lf:
                                lf.write(frame_data)
                            print("    Saved as debug_lost.jpg")
                        continue

                    last_img = img

                    sys.stdout.write(
                        f"\r[Frame #{fn:05d}] {len(frame_data):6d} bytes | "
                        f"{img.shape[1]}x{img.shape[0]} | "
                        f"lost: {decoder.lost_frames} | "
                        f"saved: {saved_count}  "
                    )
                    sys.stdout.flush()

                    if save_dir and not paused and saved_count < args.max_saved:
                        fname = os.path.join(save_dir, f"frame_{fn:05d}.jpg")
                        cv2.imwrite(fname, img)
                        saved_count += 1
                        if saved_count >= args.max_saved:
                            print(f"\n[*] Reached --max-saved ({args.max_saved}). Auto-save stopped.")

                    # Save first frame as both JPEG source and decoded PNG for comparison
                    if fn == 1:
                        with open("debug_source.jpg", "wb") as sf:
                            sf.write(frame_data)
                        cv2.imwrite("debug_decoded.png", img)
                        print("\n[*] Saved debug_source.jpg + debug_decoded.png for comparison")

                    if not paused:
                        info = f"Frame #{fn} | {len(frame_data)}B | {img.shape[1]}x{img.shape[0]}"
                        cv2.putText(img, info, (10, 25),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
                        cv2.imshow("STM32 JPEG", img)

            key = cv2.waitKey(1) & 0xFF
            if key == ord("q"):
                print("\n[*] Quit.")
                break
            elif key == ord("s"):
                if save_dir and last_img is not None:
                    fname = os.path.join(save_dir, f"manual_{decoder.frame_count:05d}.jpg")
                    cv2.imwrite(fname, last_img)
                    saved_count += 1
                    print(f"\n[*] Saved: {fname}")
                else:
                    print("\n[!] No frame or no --save-dir set.")
            elif key == ord("p"):
                paused = not paused
                print(f"\n[*] {'PAUSED' if paused else 'RESUMED'}")
            elif key == ord("c"):
                decoder.frame_count = 0
                decoder.lost_frames = 0
                saved_count = 0
                print("\n[*] Counters cleared.")

    except KeyboardInterrupt:
        print("\n[*] Interrupted.")
    finally:
        ser.close()
        cv2.destroyAllWindows()
        if raw_file:
            raw_file.close()
            print(f"[*] Raw dump saved: {args.dump_raw}")
        if lost_dir:
            print(f"[*] Corrupted frames saved: {lost_dir}/ ({lost_saved_count} files)")
        print(f"[*] Done. Received {decoder.frame_count} frames, {decoder.lost_frames} lost.")


if __name__ == "__main__":
    main()
