#!/usr/bin/env python3
"""
door_inventory.py — Fridge Door Open/Close YOLO + IoU Inventory Tracker.

Receives JPEG frames from STM32H743 via WiFi TCP.
User presses keys to mark door-open (before) and door-close (after) frames.
Runs YOLO on both, matches via greedy IoU, determines:
  - ADDED   (存入): in after-frame, not in before-frame
  - REMOVED (取出): in before-frame, not in after-frame
  - STILL   (仍在): matched in both frames

Outputs results to markdown table + CSV file.

Usage:
    conda activate fridge_ai
    python door_inventory.py                              # default
    python door_inventory.py --conf 0.5                   # confidence threshold
    python door_inventory.py --iou-threshold 0.35         # IoU match threshold

Keyboard:
    'o'  — capture OPEN DOOR frame (before)
    'c'  — capture CLOSE DOOR frame (after), run analysis
    'q'  — quit
"""

import sys
import os
import argparse
import socket
import time
from datetime import datetime
import csv
import warnings
import numpy as np
import cv2
import os as _os
_devnull = _os.open(_os.devnull, _os.O_WRONLY)
_old_stderr = _os.dup(2)
def _quiet_decode(buf):
    _os.dup2(_devnull, 2)
    img = cv2.imdecode(buf, cv2.IMREAD_COLOR)
    _os.dup2(_old_stderr, 2)
    return img

warnings.filterwarnings("ignore")

# ─── Paths ───
PROJECT_ROOT = r"E:\VScodeProjects\QS"
DEFAULT_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "best.pt")
STUDENT_MODEL = os.path.join(PROJECT_ROOT, "YOLOforSTM", "v6_results", "student_best.pt")
OUTPUT_DIR = os.path.dirname(os.path.abspath(__file__))


# ═══════════════════════════════════════════════════════════
# IoU + matching logic (standalone, no Phase_0 dependency)
# ═══════════════════════════════════════════════════════════

def bbox_iou(a, b):
    """IoU of two [x1, y1, x2, y2] absolute-pixel boxes."""
    x1 = max(a[0], b[0]); y1 = max(a[1], b[1])
    x2 = min(a[2], b[2]); y2 = min(a[3], b[3])
    iw = max(0, x2 - x1); ih = max(0, y2 - y1)
    inter = iw * ih
    area_a = max(0, (a[2] - a[0]) * (a[3] - a[1]))
    area_b = max(0, (b[2] - b[0]) * (b[3] - b[1]))
    union = area_a + area_b - inter
    return inter / union if union > 1e-8 else 0.0


def greedy_iou_match(dets_before, dets_after, iou_threshold=0.30):
    """
    Match detections between before/after frames by IoU within same class.
    Returns list of dicts: {event, class_name, confidence, bbox, iou}
    """
    results = []
    matched_before = set()
    matched_after = set()

    # Group by class
    classes = set(d["class_id"] for d in dets_before) | set(d["class_id"] for d in dets_after)
    for cls_id in classes:
        prev = [i for i, d in enumerate(dets_before) if d["class_id"] == cls_id]
        curr = [i for i, d in enumerate(dets_after) if d["class_id"] == cls_id]
        if not prev or not curr:
            continue

        # Greedy best-IoU matching
        while True:
            best_iou, best_p, best_c = 0.0, -1, -1
            for p in prev:
                if p in matched_before:
                    continue
                for c in curr:
                    if c in matched_after:
                        continue
                    iou = bbox_iou(dets_before[p]["bbox"], dets_after[c]["bbox"])
                    if iou > best_iou:
                        best_iou, best_p, best_c = iou, p, c
            if best_iou < iou_threshold or best_p < 0:
                break
            d = dets_after[best_c]
            results.append({"event": "STILL", "class_name": d["class_name"],
                            "confidence": d["confidence"], "bbox": d["bbox"],
                            "iou": round(best_iou, 3)})
            matched_before.add(best_p)
            matched_after.add(best_c)

    # Unmatched before → REMOVED
    for i, d in enumerate(dets_before):
        if i not in matched_before:
            results.append({"event": "REMOVED", "class_name": d["class_name"],
                            "confidence": d["confidence"], "bbox": d["bbox"], "iou": 0.0})

    # Unmatched after → ADDED
    for i, d in enumerate(dets_after):
        if i not in matched_after:
            results.append({"event": "ADDED", "class_name": d["class_name"],
                            "confidence": d["confidence"], "bbox": d["bbox"], "iou": 0.0})

    event_order = {"ADDED": 0, "REMOVED": 1, "STILL": 2}
    results.sort(key=lambda r: event_order[r["event"]])
    return results


# ═══════════════════════════════════════════════════════════
# YOLO inference helper
# ═══════════════════════════════════════════════════════════

def run_yolo(model, img, conf, imgsz):
    """Run YOLO and return list of detection dicts."""
    results = model(img, imgsz=imgsz, conf=conf, verbose=False)
    dets = []
    if results and results[0].boxes is not None:
        h, w = img.shape[:2]
        for box in results[0].boxes:
            cls_id = int(box.cls[0].item())
            xyxy = box.xyxy[0].cpu().numpy()
            dets.append({
                "class_id": cls_id,
                "class_name": model.names.get(cls_id, f"cls_{cls_id}"),
                "confidence": float(box.conf[0].item()),
                "bbox": [int(xyxy[0]), int(xyxy[1]), int(xyxy[2]), int(xyxy[3])],
            })
    return dets


# ═══════════════════════════════════════════════════════════
# Output generation
# ═══════════════════════════════════════════════════════════

def generate_output(before_img, after_img, dets_before, dets_after, results, ts):
    """Generate markdown + CSV report."""
    base = os.path.join(OUTPUT_DIR, f"inventory_{ts}")

    # Save frame images
    cv2.imwrite(base + "_before.jpg", before_img)
    cv2.imwrite(base + "_after.jpg", after_img)

    # ─── Markdown report ───
    md_path = base + ".md"
    with open(md_path, "w", encoding="utf-8") as f:
        f.write(f"# Inventory Report — {ts}\n\n")
        f.write(f"| Event | Item | Confidence | IoU |\n")
        f.write(f"|-------|------|------------|-----|\n")
        for r in results:
            emoji = {"ADDED": "📥", "REMOVED": "📤", "STILL": "📌"}.get(r["event"], "")
            f.write(f"| {emoji} {r['event']} | {r['class_name']} | "
                    f"{r['confidence']:.2f} | {r['iou']:.3f} |\n")
        f.write(f"\n**Before** ({len(dets_before)} items): "
                f"{', '.join(d['class_name'] for d in dets_before)}\n\n")
        f.write(f"**After** ({len(dets_after)} items): "
                f"{', '.join(d['class_name'] for d in dets_after)}\n\n")
        f.write(f"![Before]({base}_before.jpg)\n\n")
        f.write(f"![After]({base}_after.jpg)\n")

    # ─── CSV ───
    csv_path = base + ".csv"
    with open(csv_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["Event", "Item", "Confidence", "IoU", "Timestamp"])
        for r in results:
            writer.writerow([r["event"], r["class_name"], r["confidence"], r["iou"], ts])

    # ─── Console summary ───
    print(f"\n{'='*60}")
    print(f"  INVENTORY REPORT — {ts}")
    print(f"{'='*60}")
    added = [r for r in results if r["event"] == "ADDED"]
    removed = [r for r in results if r["event"] == "REMOVED"]
    still = [r for r in results if r["event"] == "STILL"]
    print(f"  📥 ADDED   ({len(added)}):  {', '.join(r['class_name'] for r in added) or '(none)'}")
    print(f"  📤 REMOVED ({len(removed)}): {', '.join(r['class_name'] for r in removed) or '(none)'}")
    print(f"  📌 STILL   ({len(still)}):  {', '.join(r['class_name'] for r in still) or '(none)'}")
    print(f"{'='*60}")
    print(f"  Report: {md_path}")
    print(f"  CSV:    {csv_path}")
    print(f"  Images: {base}_before.jpg / _after.jpg")


# ═══════════════════════════════════════════════════════════
# Main
# ═══════════════════════════════════════════════════════════

def main():
    parser = argparse.ArgumentParser(description="Door Inventory — YOLO + IoU tracker")
    parser.add_argument("--host", default="0.0.0.0")
    parser.add_argument("--port", type=int, default=8080)
    parser.add_argument("--model", default=STUDENT_MODEL)
    parser.add_argument("--teacher", action="store_true", help="Use teacher (YOLO11l) model")
    parser.add_argument("--conf", type=float, default=0.25)
    parser.add_argument("--iou-threshold", type=float, default=0.30)
    parser.add_argument("--imgsz", type=int, default=320)
    args = parser.parse_args()

    model_path = DEFAULT_MODEL if args.teacher else args.model
    if not os.path.exists(model_path):
        print(f"Model not found: {model_path}")
        sys.exit(1)

    from ultralytics import YOLO
    print(f"Loading: {model_path}")
    model = YOLO(model_path)
    print(f"Model ready: {len(model.names)} classes\n")

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((args.host, args.port))
    server.listen(1)
    server.settimeout(0.5)
    print(f"TCP server: {args.host}:{args.port}")
    print(f"KEYS: [o] open-door  [c] close-door (run analysis)  [q] quit\n")

    conn = None
    buf = bytearray()
    before_img = None
    after_img = None
    dets_before = None
    dets_after = None

    try:
        while True:
            if conn is None:
                try:
                    conn, addr = server.accept()
                    print(f"Connected: {addr}")
                    buf.clear()
                    conn.settimeout(0.1)
                except socket.timeout:
                    pass

            if conn:
                try:
                    chunk = conn.recv(65536)
                    if not chunk:
                        conn.close()
                        conn = None
                        continue
                    buf.extend(chunk)
                except (socket.timeout, ConnectionResetError):
                    pass

            # Extract frames
            i = 0
            while i < len(buf) - 1:
                if buf[i] == 0xFF and buf[i + 1] == 0xD8:
                    j = i + 2
                    while j < len(buf) - 1:
                        if buf[j] == 0xFF and buf[j + 1] == 0xD9:
                            jpeg = bytes(buf[i:j + 2])
                            arr = np.frombuffer(jpeg, np.uint8)
                            img = _quiet_decode(arr)
                            if img is not None:
                                latest_img = img
                            i = j + 2
                            break
                        j += 1
                    else:
                        break
                else:
                    i += 1
            if i > 0:
                buf = buf[i:]

            # Keyboard input
            key = cv2.waitKey(10) & 0xFF
            if key == ord('q'):
                raise KeyboardInterrupt
            elif key == ord('o'):
                if 'latest_img' in dir() and latest_img is not None:
                    before_img = latest_img.copy()
                    dets_before = run_yolo(model, before_img, args.conf, args.imgsz)
                    print(f"\n[DOOR OPEN]  Captured — {len(dets_before)} items: "
                          f"{', '.join(d['class_name'] for d in dets_before)}")
                    cv2.imshow("BEFORE - Door Open", before_img)
                else:
                    print("\nNo frame available yet")
            elif key == ord('c'):
                if 'latest_img' in dir() and latest_img is not None:
                    after_img = latest_img.copy()
                    dets_after = run_yolo(model, after_img, args.conf, args.imgsz)
                    print(f"\n[DOOR CLOSE] Captured — {len(dets_after)} items: "
                          f"{', '.join(d['class_name'] for d in dets_after)}")

                    if before_img is not None and dets_before is not None:
                        results = greedy_iou_match(dets_before, dets_after, args.iou_threshold)
                        ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                        generate_output(before_img, after_img, dets_before,
                                        dets_after, results, ts)
                        # Reset for next door cycle
                        before_img = None
                        dets_before = None
                    else:
                        print("ERROR: No BEFORE frame. Press 'o' first.")
                else:
                    print("\nNo frame available yet")

            if len(buf) > 10 * 1024 * 1024:
                buf.clear()

    except KeyboardInterrupt:
        print("\nDone.")
    finally:
        if conn:
            conn.close()
        server.close()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
