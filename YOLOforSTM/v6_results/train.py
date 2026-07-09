"""
Fridge v6 训练脚本
  --stage teacher   YOLO11l 教师模型
  --stage student   YOLO11n 学生模型（直接训练，不蒸馏）
"""
import argparse
from ultralytics import YOLO

# ---------- 共享配置 ----------
SHARED = dict(
    data="datasets/fridge_v6/dataset.yaml",
    imgsz=640,
    device=0,
    workers=8,
    cache=True,
    cos_lr=True,
    close_mosaic=20,
    patience=50,
    amp=True,
    scale=0.9,
    mixup=0.15,
    copy_paste=0.1,
    dropout=0.1,
    weight_decay=0.001,
    warmup_epochs=5,
)

# ---------- Teacher ----------
TEACHER = dict(
    model="yolo11l.pt",
    epochs=150,
    batch=14,
    project="/root/YOLOv8forSTM/runs",
    name="fridge_v6_teacher",
)

# ---------- Student ----------
STUDENT = dict(
    model="yolo11n.pt",
    epochs=150,
    batch=32,
    project="/root/YOLOv8forSTM/runs",
    name="fridge_v6_student",
)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--stage", choices=["teacher", "student"])
    opt = parser.parse_args()

    cfg = TEACHER if opt.stage == "teacher" else STUDENT
    model = YOLO(cfg.pop("model"))

    print(f"Stage: {opt.stage} | model={model.model_name} | data=fridge_v6")
    model.train(**SHARED, **cfg)
