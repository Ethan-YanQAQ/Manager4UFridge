"""恢复中断的 v2 教师模型训练 — 复用 train_kd 的 AMP 补丁"""
import os
os.environ["ULTRALYTICS_OFFLINE"] = "1"

# 导入 train_kd 以触发 _patch_check_amp()（模块级自动执行）
import train_kd

from ultralytics import YOLO

model = YOLO("runs/detect/runs/detect/fridge36_11m_v2/weights/last.pt")
model.train(resume=True)
