#!/usr/bin/env python3
"""
live_yolo_viewer.py — Real-time YOLO detection viewer over WiFi TCP.

Receives JPEG frames from STM32H743 via ESP-01S WiFi transparent tunnel,
runs YOLO inference, draws bounding boxes with class labels, displays live.

Usage:
    conda activate fridge_ai
    python live_yolo_viewer.py                              # default: 0.0.0.0:8080
    python live_yolo_viewer.py --port 9000                  # custom port
    python live_yolo_viewer.py --model best.pt              # custom model
    python live_yolo_viewer.py --conf 0.5                   # confidence threshold

Press 'q' to quit, 's' to screenshot, 'p' to pause/resume.
"""

import sys
import os
import argparse
import socket
import time
import warnings
import numpy as np
import cv2
warnings.filterwarnings("ignore")

# OS-level fd redirect to suppress libjpeg C-library warnings
_devnull = os.open(os.devnull, os.O_WRONLY)
_old_stderr = os.dup(2)

def _quiet_decode(buf):
    os.dup2(_devnull, 2)
    img = cv2.imdecode(buf, cv2.IMREAD_COLOR)
    os.dup2(_old_stderr, 2)
    return img

# ─── Paths ───
PROJECT_ROOT = r"E:\VScodeProjects\QS"
DEFAULT_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "best.pt")
STUDENT_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "student_best.pt")


def find_jpeg_boundaries(data):
    """Find complete JPEG frames (FF D8 ... FF D9) in byte buffer."""
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
    """Draw YOLO detection boxes on image."""
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


def main():
    parser = argparse.ArgumentParser(description="Live YOLO viewer over WiFi TCP")
    parser.add_argument("--host", default="0.0.0.0")
    parser.add_argument("--port", type=int, default=8080)
    parser.add_argument("--model", default=STUDENT_MODEL, help="YOLO model path")
    parser.add_argument("--conf", type=float, default=0.15, help="Confidence threshold")
    parser.add_argument("--imgsz", type=int, default=320)
    parser.add_argument("--teacher", action="store_true", help="Use teacher (YOLO11l) model")
    args = parser.parse_args()

    model_path = DEFAULT_MODEL if args.teacher else args.model
    if not os.path.exists(model_path):
        print(f"Model not found: {model_path}")
        print("Available models:")
        for p in [DEFAULT_MODEL, STUDENT_MODEL]:
            print(f"  {p} {'(exists)' if os.path.exists(p) else '(MISSING)'}")
        sys.exit(1)

    # ─── Load YOLO model ───
    print(f"Loading YOLO model: {model_path}")
    from ultralytics import YOLO
    model = YOLO(model_path)
    class_names = model.names
    print(f"Model loaded: {len(class_names)} classes")

    # ─── TCP server ───
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((args.host, args.port))
    server.listen(1)
    server.settimeout(0.5)
    print(f"Listening on {args.host}:{args.port}, waiting for STM32...")

    conn = None
    buf = bytearray()
    paused = False
    frame_count = 0
    det_count = 0

    cv2.namedWindow("YOLO Live - Fridge", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("YOLO Live - Fridge", 960, 720)

    try:
        while True:
            if conn is None:
                try:
                    conn, addr = server.accept()
                    print(f"Connected: {addr}")
                    buf.clear()
                    conn.settimeout(0.5)
                except socket.timeout:
                    continue

            try:
                chunk = conn.recv(65536)
                if not chunk:
                    print("Connection closed")
                    conn.close()
                    conn = None
                    continue
                buf.extend(chunk)
            except socket.timeout:
                pass
            except ConnectionResetError:
                conn.close()
                conn = None
                continue

            frames = find_jpeg_boundaries(buf)
            for start, end in frames:
                jpeg_data = bytes(buf[start:end])
                frame_count += 1

                nparr = np.frombuffer(jpeg_data, np.uint8)
                img = _quiet_decode(nparr)
                if img is None:
                    continue

                if paused:
                    cv2.imshow("YOLO Live - Fridge", img)
                else:
                    results = model(img, imgsz=args.imgsz, conf=args.conf, verbose=False)
                    detections = []
                    if len(results) > 0 and results[0].boxes is not None:
                        h, w = img.shape[:2]
                        for box in results[0].boxes:
                            cls_id = int(box.cls[0].item())
                            xyxy = box.xyxy[0].cpu().numpy()
                            detections.append({
                                "class_id": cls_id,
                                "class_name": class_names.get(cls_id, f"cls_{cls_id}"),
                                "confidence": float(box.conf[0].item()),
                                "bbox_abs": [int(xyxy[0]), int(xyxy[1]),
                                             int(xyxy[2]), int(xyxy[3])],
                            })
                        det_count += len(detections)

                    img_boxed = draw_boxes(img.copy(), detections, class_names)
                    cv2.imshow("YOLO Live - Fridge", img_boxed)

                    status = f"Frame:{frame_count} Det:{det_count}"
                    if detections:
                        top3 = sorted(detections, key=lambda d: -d["confidence"])[:3]
                        status += " | " + " ".join(
                            f"{d['class_name']}({d['confidence']:.2f})" for d in top3)
                    print(f"\r{status}", end="")

                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    raise KeyboardInterrupt
                elif key == ord('s'):
                    fname = f"yolo_snap_{time.strftime('%H%M%S')}.jpg"
                    cv2.imwrite(fname, img_boxed if not paused else img)
                    print(f"\nSaved: {fname}")
                elif key == ord('p'):
                    paused = not paused
                    print(f"\n{'PAUSED' if paused else 'RESUMED'}")

            if frames:
                buf = buf[frames[-1][1]:]
            if len(buf) > 10 * 1024 * 1024:
                buf.clear()

    except KeyboardInterrupt:
        print(f"\nDone. {frame_count} frames, {det_count} detections.")
    finally:
        if conn:
            conn.close()
        server.close()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
