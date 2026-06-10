"""
detector.py - YOLO 检测器封装
加载 YOLO 模型权重，对单帧图像进行目标检测，返回检测列表。
"""

import os
import numpy as np
from typing import List, Dict, Optional
import logging

logger = logging.getLogger(__name__)


class Detection:
    """单个检测结果"""
    __slots__ = ("class_id", "class_name", "confidence", "bbox")

    def __init__(self, class_id: int, class_name: str, confidence: float, bbox: np.ndarray):
        """
        bbox: [x1, y1, x2, y2] 左上+右下坐标，归一化到 [0,1]
        """
        self.class_id = class_id
        self.class_name = class_name
        self.confidence = confidence
        self.bbox = bbox

    def to_dict(self) -> Dict:
        return {
            "class_id": self.class_id,
            "class_name": self.class_name,
            "confidence": round(float(self.confidence), 3),
            "bbox": [round(float(v), 4) for v in self.bbox],
        }

    def __repr__(self) -> str:
        return f"Detection({self.class_name}, conf={self.confidence:.2f}, bbox={self.bbox.tolist()})"


class YOLODetector:
    """
    YOLO 目标检测器

    支持两种模式：
    1. real_weights: 加载真实 YOLO 权重（ultralytics 库）
    2. mock: 返回模拟检测结果，用于纯算法验证（无需权重文件）
    """

    def __init__(self, config: Dict):
        cfg = config.get("model", {})
        self.conf_threshold = cfg.get("conf_threshold", 0.25)
        self.iou_nms = cfg.get("iou_nms", 0.45)
        self.imgsz = cfg.get("imgsz", 320)
        self.weights_path = cfg.get("weights", "models/yolov8n.pt")
        self.model = None

    def load_model(self) -> bool:
        """
        尝试加载真实 YOLO 模型。成功返回 True，否则 False。
        """
        try:
            import os as _os
            _os.environ.setdefault("ULTRALYTICS_OFFLINE", "1")
            from ultralytics import YOLO
            # 转绝对路径，避免 ultralytics 把相对路径当模型名去 GitHub 下载
            abs_weights = _os.path.abspath(self.weights_path)
            self.model = YOLO(abs_weights)
            logger.info(f"[DETECTOR] YOLO model loaded from {abs_weights}")
            return True
        except ImportError:
            logger.warning("[DETECTOR] ultralytics not installed. Running in MOCK mode.")
            return False
        except FileNotFoundError:
            logger.warning(f"[DETECTOR] Weight file not found: {self.weights_path}. Running in MOCK mode.")
            return False
        except Exception as e:
            logger.warning(f"[DETECTOR] Failed to load model: {e}. Running in MOCK mode.")
            return False

    def detect(self, image: np.ndarray) -> List[Detection]:
        """
        对单帧图像进行目标检测

        Args:
            image: RGB 图像 (H, W, 3), uint8

        Returns:
            List[Detection]: 检测结果列表，按置信度降序排列
        """
        if self.model is not None:
            return self._detect_real(image)
        else:
            logger.warning("[DETECTOR] Using MOCK detections for demo.")
            return self._detect_mock(image)

    def _detect_real(self, image: np.ndarray) -> List[Detection]:
        results = self.model(image, imgsz=self.imgsz, conf=self.conf_threshold,
                             iou=self.iou_nms, verbose=False)
        detections = []
        if len(results) > 0:
            result = results[0]
            if result.boxes is not None:
                h, w = image.shape[:2]
                for box in result.boxes:
                    cls_id = int(box.cls[0].item())
                    cls_name = self.model.names.get(cls_id, f"class_{cls_id}")
                    conf = float(box.conf[0].item())
                    xyxy = box.xyxy[0].cpu().numpy()
                    bbox = np.array([
                        xyxy[0] / w, xyxy[1] / h,
                        xyxy[2] / w, xyxy[3] / h,
                    ])
                    detections.append(Detection(cls_id, cls_name, conf, bbox))
        detections.sort(key=lambda d: d.confidence, reverse=True)
        return detections

    def _detect_mock(self, image: np.ndarray) -> List[Detection]:
        return []


# ─── 模拟检测数据预置（用于纯算法测试） ───

MOCK_DETECTIONS_FRAME_BEFORE = [
    Detection(47, "apple",   0.92, np.array([0.10, 0.20, 0.25, 0.40])),
    Detection(47, "apple",   0.89, np.array([0.55, 0.15, 0.70, 0.35])),
    Detection(52, "banana",  0.95, np.array([0.20, 0.50, 0.45, 0.70])),
    Detection(57, "pizza",   0.88, np.array([0.60, 0.55, 0.85, 0.80])),
    Detection(44, "bottle",  0.91, np.array([0.30, 0.25, 0.40, 0.50])),
]

MOCK_DETECTIONS_FRAME_AFTER = [
    Detection(47, "apple",   0.90, np.array([0.12, 0.22, 0.27, 0.42])),
    Detection(47, "apple",   0.87, np.array([0.75, 0.60, 0.90, 0.80])),
    Detection(52, "banana",  0.93, np.array([0.22, 0.52, 0.47, 0.72])),
    Detection(44, "bottle",  0.90, np.array([0.32, 0.27, 0.42, 0.52])),
]