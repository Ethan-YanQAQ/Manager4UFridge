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


# ---- Patch check_amp：用当前模型做 AMP 检查，不下载 yolo26n.pt ----
# 原版 check_amp 硬编码 amp_allclose(YOLO("yolo26n.pt"), im)，网络超时(OSError)不被
# ConnectionError 捕获 → 无限重试。修成用传入的 model 直接验证 AMP。
#
# 两个补丁点（缺一不可）：
#   1) ultralytics.utils.checks.check_amp — 模块级函数本体
#   2) ultralytics.engine.trainer.check_amp — trainer.py:46 用 from import
#      拿到的本地引用，trainer 内部只走本地引用，不走模块本体。
#   3) ultralytics.utils.torch_utils.check_amp — YOLO.__init__ 中的冗余复本
#      （同文件 autocast 被 trainer 直接 from import，可能 check_amp 也被复制）

def _make_fixed_check_amp():
    """构建 patched check_amp（闭包工厂，避免重复粘贴函数体）。
    用传入的 model 直接验证 AMP，不下载 yolo26n.pt。
    model 是裸 DetectionModel（trainer 传入的 self.model），只接受 tensor。"""
    from ultralytics.utils.checks import colorstr, ASSETS as _ASSETS
    from ultralytics.utils.torch_utils import autocast
    import re
    import cv2

    def _fixed_check_amp(model):
        device = next(model.parameters()).device
        prefix = colorstr("AMP: ")
        if device.type in {"cpu", "mps"}:
            return False
        pattern = re.compile(
            r"(nvidia|geforce|quadro|tesla).*?(1660|1650|1630|t400|t550|t600|t1000|t1200|t2000|k40m)",
            re.IGNORECASE,
        )
        gpu = torch.cuda.get_device_name(device)
        if bool(pattern.search(gpu)):
            print(f"{prefix}checks failed - {gpu} GPU may have AMP issues, disabling AMP")
            return False

        print(f"{prefix}running AMP checks with current model (skipping yolo26n download)...")
        try:
            # 加载并预处理图像为 tensor（裸模型只接受 tensor，不接受路径）
            imgsz = max(256, int(model.stride.max() * 4))
            img = cv2.imread(str(_ASSETS / "bus.jpg"))
            if img is None:
                raise FileNotFoundError("bus.jpg not found in ultralytics assets")
            img = cv2.resize(img, (imgsz, imgsz))          # HWC, BGR
            img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)     # → RGB
            tensor = torch.from_numpy(img).float() / 255.0  # HWC [0,1]
            tensor = tensor.permute(2, 0, 1).unsqueeze(0)   # → 1CHW
            batch = tensor.expand(8, -1, -1, -1).to(device) # [8, 3, H, W]

            a = model(batch)[0].boxes.data                    # FP32 inference
            with autocast(enabled=True):
                b = model(batch)[0].boxes.data                # AMP inference
            ok = a.shape == b.shape and torch.allclose(a, b.float(), atol=0.5)
            if ok:
                print(f"{prefix}checks passed")
            else:
                print(f"{prefix}checks failed - FP32/AMP mismatch, disabling AMP")
            return ok
        except Exception as e:
            print(f"{prefix}checks failed ({e}), enabling AMP with warning")
            return True

    return _fixed_check_amp


def _patch_check_amp():
    import ultralytics.utils.checks as _checks
    import ultralytics.utils.torch_utils as _torch_utils

    _fixed = _make_fixed_check_amp()

    # 补丁 1：checks 模块本体
    _checks.check_amp = _fixed
    # 补丁 2：torch_utils 中可能存在的复本
    if hasattr(_torch_utils, "check_amp"):
        _torch_utils.check_amp = _fixed

    print("[PATCH] check_amp (stage 1/2): checks + torch_utils 已替换")

_patch_check_amp()


def _patch_trainer_check_amp():
    """补丁 3：修正 trainer 模块的本地 from-import 引用。
    YOLO 在第 22 行已导入（trainer 模块随之加载），此时可安全修补。"""
    import ultralytics.engine.trainer as _trainer
    _fixed = _make_fixed_check_amp()
    _trainer.check_amp = _fixed
    print("[PATCH] check_amp (stage 2/2): trainer 本地引用已替换")

_patch_trainer_check_amp()


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
    # 但必须补齐 loss_items 到 6 列，否则 trainer/validator 尺寸不匹配
    if not isinstance(preds, dict):
        loss, loss_items = self._kd_orig_loss(batch, preds)
        kd_pad = torch.zeros(3, device=loss.device)
        loss_items = torch.cat([loss_items, kd_pad])
        return loss, loss_items

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

    _KD_ATTRS = [
        "loss",  # 保存前恢复原始 loss
        "_kd_teacher", "_kd_nc", "_kd_temp", "_kd_cls_w", "_kd_box_w",
        "_kd_orig_loss", "_kd_loss",
    ]

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

        # -- 替换 model.loss（MethodType 正确绑定 self） --
        # 同时把 _kd_loss 存入 model.__dict__，保证 deepcopy / pickle 时
        # nn.Module.__getattr__ 不会因为找不到 _kd_loss 而崩溃
        self.model._kd_loss = _kd_loss
        self.model.loss = _types.MethodType(_kd_loss, self.model)

        if teacher.nc != self.model.nc:
            print(f"[KD] 教师 nc={teacher.nc}，学生 nc={self.model.nc}，截断至 {self.model._kd_nc}")
        print(f"[KD] 教师模型已加载: {os.path.basename(self.teacher_weights)}")
        print(f"[KD]   T={self.kd_temp}  cls_w={self.kd_cls_w}  box_w={self.kd_box_w}")

    # ---- save_model：保存前剥离 KD 状态，避免污染 checkpoint ----

    @staticmethod
    def _strip_kd(model):
        """剥离模型的 KD 状态，返回备份 dict。model 为 None 时返回空。"""
        if model is None:
            return {}
        saved = {}
        d = model.__dict__
        # 1) 备份 __dict__ 中的 KD 属性（_kd_nc, _kd_temp, _kd_loss 等）
        for attr in KDTrainer._KD_ATTRS:
            if attr in d:
                saved[attr] = d[attr]
        # 2) _kd_teacher 是 nn.Module，存在 _modules 中，单独备份
        if "_kd_teacher" in model._modules:
            saved["_kd_teacher"] = model._modules["_kd_teacher"]
        # 3) 恢复原始 loss
        if "_kd_orig_loss" in saved:
            model.loss = saved["_kd_orig_loss"]
        # 4) 从 __dict__ 和 _modules 中删除 KD 属性
        for attr in KDTrainer._KD_ATTRS:
            d.pop(attr, None)
        model._modules.pop("_kd_teacher", None)
        return saved

    @staticmethod
    def _restore_kd(model, saved):
        """恢复模型被剥离的 KD 状态。"""
        if model is None or not saved:
            return
        for attr, val in saved.items():
            setattr(model, attr, val)

    def save_model(self):
        """保存 checkpoint 前剥离 KD 状态，保证 deepcopy 和 pickle 干净。"""
        from ultralytics.utils.torch_utils import unwrap_model

        model = unwrap_model(self.model)
        ema_model = unwrap_model(self.ema.ema) if self.ema else None

        saved_model = self._strip_kd(model)
        saved_ema = self._strip_kd(ema_model)

        try:
            return super().save_model()
        finally:
            self._restore_kd(model, saved_model)
            self._restore_kd(ema_model, saved_ema)


def run_stage1():
    """训练 YOLO11m 教师模型（v2：防过拟合改进）。

    改进点（vs v1 epoch 60 后过拟合）：
      - epochs 200→100，patience 50→30
      - 添加 mixup + label_smoothing 正则化
      - close_mosaic 10→15（更多微调时间）
    """
    print("=" * 60)
    print("Stage 1: 训练 YOLO11m 教师模型 (v2)")
    print("=" * 60)

    model = YOLO("yolo11m.pt")

    results = model.train(
        data="datasets/fridge_36/dataset.yaml",
        epochs=100,
        batch=16,
        imgsz=640,
        device=0,
        workers=0,
        cos_lr=True,
        close_mosaic=15,
        patience=30,
        amp=True,
        mixup=0.1,
        label_smoothing=0.1,
        project="runs/detect",
        name="fridge36_11m_v2",
        exist_ok=True,
    )
    return results


def run_stage2(teacher_path):
    """蒸馏训练 YOLO11n 学生模型（v2：更强 KD 推动）。

    改进点（vs v1 epoch 65 后 plateau）：
      - KD 权重提升：cls 0.5→0.8，box 0.3→0.5
      - 温度 3.0→4.0（更软的教师分布）
      - epochs 150→100，patience 30→25
      - label_smoothing 已弃用故移除
    """
    print("=" * 60)
    print("Stage 2: 蒸馏 → YOLO11n 学生模型 (v2)")
    print(f"教师模型: {teacher_path}")
    print("=" * 60)

    model = YOLO("yolo11n.pt")

    results = model.train(
        data="datasets/fridge_36/dataset.yaml",
        epochs=100,
        batch=20,
        imgsz=640,
        device=0,
        workers=0,
        cos_lr=True,
        close_mosaic=10,
        patience=25,
        amp=True,
        lrf=0.1,
        mixup=0.15,
        copy_paste=0.1,
        project="runs/detect",
        name="fridge36_11n_kd_v2",
        exist_ok=True,
        # --- KD 自定义参数 ---
        trainer=KDTrainer,
        teacher_weights=teacher_path,
        kd_temp=4.0,
        kd_cls_weight=0.8,
        kd_box_weight=0.5,
    )
    return results


# ---------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="YOLO11 KD 训练")
    parser.add_argument("--stage", type=int, required=True, choices=[1, 2],
                        help="1 = 训教师, 2 = 蒸馏")
    parser.add_argument("--teacher", type=str, default=None,
                        help="Stage 2 教师权重路径（默认自动查找 Stage 1 输出）")
    parser.add_argument("--resume", type=str, default=None,
                        help="从指定 last.pt 恢复训练（如 runs/detect/.../weights/last.pt）")
    args = parser.parse_args()

    os.environ["ULTRALYTICS_OFFLINE"] = "1"  # 禁止联网下载

    # AMP 补丁已在模块级自动应用

    # --resume 模式
    if args.resume:
        if not os.path.exists(args.resume):
            print(f"[ERROR] 恢复权重不存在: {args.resume}")
            sys.exit(1)
        print(f"[RESUME] 从 {args.resume} 恢复训练")
        model = YOLO(args.resume)
        model.train(resume=True)
        sys.exit(0)

    if args.stage == 1:
        run_stage1()

    elif args.stage == 2:
        teacher = args.teacher
        if teacher is None:
            # 自动查找 Stage 1 best（按优先级：v2 > v1）
            candidates = [
                "runs/detect/fridge36_11m_v2/weights/best.pt",
                "runs/detect/fridge36_11m_teacher/weights/best.pt",
            ]
            for c in candidates:
                if os.path.exists(c):
                    teacher = c
                    break
            else:
                print("[ERROR] 找不到教师模型，请用 --teacher 指定")
                sys.exit(1)
        if not os.path.exists(teacher):
            print(f"[ERROR] 教师模型不存在: {teacher}")
            sys.exit(1)
        run_stage2(teacher)
