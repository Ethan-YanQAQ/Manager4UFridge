#!/usr/bin/env python3
"""
serial_yolo_viewer.py — YOLO detection viewer over wired serial (USART1).

Receives JPEG frames from STM32H743 via USB-UART (CH340),
runs YOLO inference, draws bounding boxes with class labels, live display.

Usage:
    conda activate fridge_ai
    python serial_yolo_viewer.py COM11                     # Windows
    python serial_yolo_viewer.py COM11 --teacher --imgsz 640
    python serial_yolo_viewer.py COM11 --conf 0.5
    python serial_yolo_viewer.py --list                    # list COM ports

Press 'q' to quit, 's' to screenshot.
"""

import sys
import os
import argparse
import time
import warnings
import numpy as np
import serial
import serial.tools.list_ports

warnings.filterwarnings("ignore")

PROJECT_ROOT = r"E:\VScodeProjects\QS"
TEACHER_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "best.pt")
STUDENT_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "student_best.pt")

# OS-level fd redirect for libjpeg C-level warnings
_devnull = os.open(os.devnull, os.O_WRONLY)
_old_stderr = os.dup(2)


def _quiet_decode(buf):
    os.dup2(_devnull, 2)
    img = __import__("cv2").imdecode(buf, __import__("cv2").IMREAD_COLOR)
    os.dup2(_old_stderr, 2)
    return img


def find_jpeg_boundaries(data):
    frames = []
    i = 0
    while i < len(data) - 1:
        if data[i] == 0xFF and data[i + 1] == 0xD8:
            j = i + 2
            while j < len(data) - 1:
                if data[j] == 0xFF and data[j + 1] == 0xD9:
                    frames.append((i, j + 2))
                    i = j + 2
                    break
                j += 1
            else:
                break
        else:
            i += 1
    return frames


def draw_boxes(img, detections, class_names):
    import cv2
    colors = {}
    for det in detections:
        cls_id = det["class_id"]
        if cls_id not in colors:
            np.random.seed(cls_id)
            colors[cls_id] = tuple(int(c) for c in np.random.randint(80, 255, 3))
        color = colors[cls_id]
        x1, y1, x2, y2 = det["bbox_abs"]
        label = f"{det['class_name']} {det['confidence']:.2f}"
        cv2.rectangle(img, (x1, y1), (x2, y2), color, 2)
        (tw, th), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
        cv2.rectangle(img, (x1, y1 - th - 4), (x1 + tw, y1), color, -1)
        cv2.putText(img, label, (x1, y1 - 2), cv2.FONT_HERSHEY_SIMPLEX, 0.5,
                    (255, 255, 255), 1, cv2.LINE_AA)
    return img


def list_ports():
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        print("No serial ports found.")
        return
    for p in ports:
        print(f"  {p.device} — {p.description}")


def main():
    parser = argparse.ArgumentParser(description="Serial YOLO viewer for STM32H743 USART1")
    parser.add_argument("port", nargs="?", help="COM port (e.g. COM11)")
    parser.add_argument("--baud", type=int, default=921600)
    parser.add_argument("--model", default=STUDENT_MODEL)
    parser.add_argument("--teacher", action="store_true")
    parser.add_argument("--conf", type=float, default=0.15)
    parser.add_argument("--imgsz", type=int, default=320)
    parser.add_argument("--list", action="store_true", help="List COM ports")
    parser.add_argument("--save-dir", default=None, help="Save frames to directory")
    args = parser.parse_args()

    if args.list:
        list_ports()
        return

    if not args.port:
        print("No COM port specified. Use --list to see available ports.")
        print("Usage: python serial_yolo_viewer.py COM11")
        sys.exit(1)

    model_path = TEACHER_MODEL if args.teacher else args.model
    if not os.path.exists(model_path):
        print(f"Model not found: {model_path}")
        sys.exit(1)

    from ultralytics import YOLO
    print(f"Loading: {model_path}")
    model = YOLO(model_path)
    print(f"Model: {len(model.names)} classes")

    if args.save_dir:
        os.makedirs(args.save_dir, exist_ok=True)

    import cv2
    cv2.namedWindow("YOLO Serial - Fridge", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("YOLO Serial - Fridge", 960, 720)

    ser = None
    buf = bytearray()
    frame_count = 0
    det_count = 0
    fps_t0 = time.time()
    fps_frames = 0

    try:
        ser = serial.Serial(args.port, args.baud, timeout=0.1)

        while True:
            chunk = ser.read(65536)
            if chunk:
                buf.extend(chunk)
            else:
                chunk = b""

            frames = find_jpeg_boundaries(buf)
            for start, end in frames:
                jpeg_data = bytes(buf[start:end])
                frame_count += 1
                fps_frames += 1

                nparr = np.frombuffer(jpeg_data, np.uint8)
                import cv2 as _cv2
                img = _quiet_decode(nparr)
                if img is None:
                    continue

                results = model(img, imgsz=args.imgsz, conf=args.conf, verbose=False)
                detections = []
                if results and results[0].boxes is not None:
                    h, w = img.shape[:2]
                    for box in results[0].boxes:
                        cls_id = int(box.cls[0].item())
                        xyxy = box.xyxy[0].cpu().numpy()
                        detections.append({
                            "class_id": cls_id,
                            "class_name": model.names.get(cls_id, f"cls_{cls_id}"),
                            "confidence": float(box.conf[0].item()),
                            "bbox_abs": [int(xyxy[0]), int(xyxy[1]),
                                         int(xyxy[2]), int(xyxy[3])],
                        })
                    det_count += len(detections)

                img_out = draw_boxes(img.copy(), detections, class_names=model.names) if detections else img
                cv2.imshow("YOLO Serial - Fridge", img_out)

                elapsed = time.time() - fps_t0
                if elapsed > 2.0 and fps_frames > 0:
                    fps = fps_frames / elapsed
                    print(f"\r{fps:.1f} FPS | Frame:{frame_count} Det:{det_count}    ", end="")
                    fps_t0 = time.time()
                    fps_frames = 0

                if args.save_dir:
                    fname = os.path.join(args.save_dir, f"frame_{frame_count:04d}.jpg")
                    with open(fname, "wb") as f:
                        f.write(jpeg_data)

                key = cv2.waitKey(1) & 0xFF
                if key == ord("q"):
                    raise KeyboardInterrupt
                elif key == ord("s"):
                    _cv2.imwrite(f"snap_{time.strftime('%H%M%S')}.jpg", img_out)

            if frames:
                buf = buf[frames[-1][1]:]
            if len(buf) > 10 * 1024 * 1024:
                buf.clear()

    except KeyboardInterrupt:
        print(f"\nDone. {frame_count} frames, {det_count} detections.")
    finally:
        if ser:
            ser.close()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
