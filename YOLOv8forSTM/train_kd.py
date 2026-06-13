"""
YOLO11 知识蒸馏训练器
Stage 1: 训练 YOLO11m 教师模型（标准训练）
Stage 2: 蒸馏 → YOLO11n 学生模型（响应式 KD）

KD 损失：
  - 分类 KD：教师-学生 score 分布的 KL 散度（温度 T=3.0）
  - 框回归 KD：教师-学生 box 参数的 MSE

用法:
  # Stage 1 — 训练教师
  python train_kd.py --stage 1

  # Stage 2 — 蒸馏
  python train_kd.py --stage 2 --teacher runs/detect/train/weights/best.pt
"""

import torch
import torch.nn.functional as F
from ultralytics.models.yolo.detect import DetectionTrainer
from ultralytics.utils import DEFAULT_CFG_DICT
from ultralytics import YOLO
import argparse
import sys
import os
import types as _types


# ---- 模块级 KD loss 函数（通过 model._kd_* 属性传递状态） ----

def _kd_loss(self, batch, preds=None):
    """
    KD loss — self 是 DetectionModel 实例。
    model._kd_* 属性由 KDTrainer.set_model_attributes() 注入。
    """
    # 预计算学生 preds（避免 orig_loss_fn 内部重复前向）
    if preds is None:
        preds = self.forward(batch["img"])

    # 验证 / warmup 时 preds 可能是 tuple（非 raw dict），走原始 loss 跳过 KD
    if not isinstance(preds, dict):
        return self._kd_orig_loss(batch, preds)

    # 1) 原始检测损失
    loss, loss_items = self._kd_orig_loss(batch, preds)

    # 2) 教师前向（无梯度）
    with torch.no_grad():
        t_preds = self._kd_teacher(batch["img"])

    # 3) 分类 KD：KL 散度
    T = self._kd_temp
    nc = self._kd_nc
    s_scores = preds["scores"][:, :nc, :]
    t_scores = t_preds["scores"][:, :nc, :]

    s_log_prob = F.log_softmax(s_scores / T, dim=1)
    t_prob = F.softmax(t_scores / T, dim=1)
    kd_cls = F.kl_div(s_log_prob, t_prob, reduction="mean") * (T * T)

    # 4) 框回归 KD：MSE
    kd_box = F.mse_loss(preds["boxes"], t_preds["boxes"])

    # 5) 总损失
    kd_total = self._kd_cls_w * kd_cls + self._kd_box_w * kd_box
    loss = loss + kd_total

    # 追加 KD 项到 loss_items（日志用）
    kd_items = torch.tensor(
        [kd_cls.detach(), kd_box.detach(), kd_total.detach()],
        device=loss.device,
    )
    loss_items = torch.cat([loss_items, kd_items])

    return loss, loss_items


class KDTrainer(DetectionTrainer):
    """
    带知识蒸馏的 DetectionTrainer。

    教师模型前向推理（无梯度），输出 boxes/scores 作为软目标。
    学生模型同时学习 ground truth（原始检测损失）和教师软标签（KD 损失）。

    自定义参数（通过 model.train() kwargs 传入，自动合并到 overrides）：
        teacher_weights (str): 教师模型 .pt 路径
        kd_temp (float): KL 散度温度，默认 3.0
        kd_cls_weight (float): 分类 KD 权重，默认 0.5
        kd_box_weight (float): 框回归 KD 权重，默认 0.3
    """

    def __init__(self, cfg=DEFAULT_CFG_DICT, overrides=None, _callbacks=None):
        overrides = dict(overrides) if overrides else {}
        self.teacher_weights = overrides.pop("teacher_weights", None)
        self.kd_temp = float(overrides.pop("kd_temp", 3.0))
        self.kd_cls_w = float(overrides.pop("kd_cls_weight", 0.5))
        self.kd_box_w = float(overrides.pop("kd_box_weight", 0.3))
        super().__init__(cfg=cfg, overrides=overrides, _callbacks=_callbacks)

    def set_model_attributes(self):
        """在父类设置完毕后，加载教师并注入 KD loss。"""
        super().set_model_attributes()

        if self.teacher_weights is None:
            return

        # -- 加载教师模型 --
        teacher_wrapper = YOLO(self.teacher_weights, task='detect')
        teacher = teacher_wrapper.model
        teacher.eval()
        for p in teacher.parameters():
            p.requires_grad_(False)

        # -- 将 KD 状态存入 model 实例 --
        self.model._kd_teacher = teacher.to(self.device)
        self.model._kd_nc = min(teacher.nc, self.model.nc)
        self.model._kd_temp = self.kd_temp
        self.model._kd_cls_w = self.kd_cls_w
        self.model._kd_box_w = self.kd_box_w
        self.model._kd_orig_loss = self.model.loss

        # -- 用 MethodType 替换 model.loss（正确绑定 self） --
        self.model.loss = _types.MethodType(_kd_loss, self.model)

        if teacher.nc != self.model.nc:
            print(f"[KD] 教师 nc={teacher.nc}，学生 nc={self.model.nc}，截断至 {self.model._kd_nc}")
        print(f"[KD] 教师模型已加载: {os.path.basename(self.teacher_weights)}")
        print(f"[KD]   T={self.kd_temp}  cls_w={self.kd_cls_w}  box_w={self.kd_box_w}")


def run_stage1():
    """训练 YOLO11m 教师模型（标准训练，无 KD）。"""
    print("=" * 60)
    print("Stage 1: 训练 YOLO11m 教师模型")
    print("=" * 60)

    model = YOLO("yolo11m.pt")

    results = model.train(
        data="datasets/fridge_36/dataset.yaml",
        epochs=200,
        batch=16,
        imgsz=640,
        device=0,
        workers=0,
        cos_lr=True,
        close_mosaic=10,
        patience=50,
        amp=True,
        project="runs/detect",
        name="fridge36_11m_teacher",
        exist_ok=True,
    )
    return results


def run_stage2(teacher_path):
    """蒸馏训练 YOLO11n 学生模型。"""
    print("=" * 60)
    print("Stage 2: 蒸馏 → YOLO11n 学生模型")
    print(f"教师模型: {teacher_path}")
    print("=" * 60)

    model = YOLO("yolo11n.pt")

    results = model.train(
        data="datasets/fridge_36/dataset.yaml",
        epochs=150,
        batch=20,
        imgsz=640,
        device=0,
        workers=0,
        cos_lr=True,
        close_mosaic=10,
        patience=30,
        amp=True,
        lrf=0.1,
        mixup=0.15,
        copy_paste=0.1,
        label_smoothing=0.1,
        project="runs/detect",
        name="fridge36_11n_kd",
        exist_ok=True,
        # --- KD 自定义参数（传给 KDTrainer）---
        trainer=KDTrainer,
        teacher_weights=teacher_path,
        kd_temp=3.0,
        kd_cls_weight=0.5,
        kd_box_weight=0.3,
    )
    return results


# ---------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="YOLO11 KD 训练")
    parser.add_argument("--stage", type=int, required=True, choices=[1, 2],
                        help="1 = 训教师, 2 = 蒸馏")
    parser.add_argument("--teacher", type=str, default=None,
                        help="Stage 2 教师权重路径（默认自动查找 Stage 1 输出）")
    args = parser.parse_args()

    os.environ["ULTRALYTICS_OFFLINE"] = "1"  # 禁止联网下载

    if args.stage == 1:
        run_stage1()

    elif args.stage == 2:
        teacher = args.teacher
        if teacher is None:
            # 自动查找 Stage 1 best
            candidate = "runs/detect/fridge36_11m_teacher/weights/best.pt"
            if os.path.exists(candidate):
                teacher = candidate
            else:
                print("[ERROR] 找不到教师模型，请用 --teacher 指定")
                sys.exit(1)
        if not os.path.exists(teacher):
            print(f"[ERROR] 教师模型不存在: {teacher}")
            sys.exit(1)
        run_stage2(teacher)
