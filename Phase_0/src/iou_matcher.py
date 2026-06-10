"""
iou_matcher.py - IoU 前后帧匹配 + 存入/取出/静止 判定

核心算法：
  给定开门前帧 L0 和关门后帧 L1 的检测列表，
  在**同类别**内做 IoU 贪心匹配：
    - L0 中有、L1 中 IoU>θ  → STILL（仍在）
    - L0 中有、L1 中无匹配  → REMOVED（取出）
    - L1 中有、L0 中无匹配  → ADDED（存入）
"""

import numpy as np
from typing import List, Dict, Optional
from enum import Enum
import logging

from detector import Detection

logger = logging.getLogger(__name__)


class EventType(Enum):
    ADDED = "added"
    REMOVED = "removed"
    STILL = "still"


class MatchResult:
    """一次前后帧对比的匹配结果"""

    def __init__(self, event: EventType, detection: Detection,
                 matched_from: Optional[Detection] = None, iou: float = 0.0):
        self.event = event
        self.detection = detection          # 当前帧的检测
        self.matched_from = matched_from    # STILL/REMOVED 时指向来源帧的检测
        self.iou = iou

    def to_dict(self) -> Dict:
        return {
            "event": self.event.value,
            "class_name": self.detection.class_name,
            "confidence": round(float(self.detection.confidence), 3),
            "bbox": [round(float(v), 4) for v in self.detection.bbox],
            "iou": round(float(self.iou), 4),
        }

    def __repr__(self) -> str:
        return f"<{self.event.value.upper()}> {self.detection.class_name} (IoU={self.iou:.3f})"


def bbox_iou(a: np.ndarray, b: np.ndarray) -> float:
    """
    计算两个归一化 bbox 的 IoU [0, 1]
    a, b: [x1, y1, x2, y2]，坐标归一化到 [0,1]
    """
    x1 = max(a[0], b[0])
    y1 = max(a[1], b[1])
    x2 = min(a[2], b[2])
    y2 = min(a[3], b[3])

    inter_w = max(0.0, x2 - x1)
    inter_h = max(0.0, y2 - y1)
    inter_area = inter_w * inter_h

    area_a = max(0.0, (a[2] - a[0]) * (a[3] - a[1]))
    area_b = max(0.0, (b[2] - b[0]) * (b[3] - b[1]))

    union_area = area_a + area_b - inter_area
    if union_area <= 1e-8:
        return 0.0
    return inter_area / union_area


def greedy_iou_match(dets_prev: List[Detection],
                     dets_curr: List[Detection],
                     iou_threshold: float = 0.30) -> List[MatchResult]:
    """
    前后帧贪心 IoU 匹配，返回事件列表

    Args:
        dets_prev: 前一帧（开门前）的检测列表
        dets_curr: 当前帧（关门后）的检测列表
        iou_threshold: 判定为同一物体的 IoU 阈值

    Returns:
        List[MatchResult]: 按事件类型排列的匹配结果
    """
    results: List[MatchResult] = []

    # 按类别分组
    prev_by_class: Dict[int, List[int]] = {}
    curr_by_class: Dict[int, List[int]] = {}

    for i, d in enumerate(dets_prev):
        prev_by_class.setdefault(d.class_id, []).append(i)
    for j, d in enumerate(dets_curr):
        curr_by_class.setdefault(d.class_id, []).append(j)

    matched_prev = set()
    matched_curr = set()

    # 每个类别内贪心匹配
    for cls_id in set(list(prev_by_class.keys()) + list(curr_by_class.keys())):
        prev_indices = prev_by_class.get(cls_id, [])
        curr_indices = curr_by_class.get(cls_id, [])

        if not prev_indices or not curr_indices:
            continue

        # 计算所有 IoU 对
        iou_matrix = np.zeros((len(prev_indices), len(curr_indices)))
        for pi, p_idx in enumerate(prev_indices):
            for ci, c_idx in enumerate(curr_indices):
                iou_matrix[pi, ci] = bbox_iou(
                    dets_prev[p_idx].bbox, dets_curr[c_idx].bbox
                )

        # 贪心匹配：每次取最大 IoU 对，阈值以上保留
        while True:
            if iou_matrix.size == 0:
                break
            best_idx = np.unravel_index(np.argmax(iou_matrix), iou_matrix.shape)
            best_iou = iou_matrix[best_idx[0], best_idx[1]]

            if best_iou < iou_threshold:
                break

            pi = prev_indices[best_idx[0]]
            ci = curr_indices[best_idx[1]]

            results.append(MatchResult(
                event=EventType.STILL,
                detection=dets_curr[ci],
                matched_from=dets_prev[pi],
                iou=float(best_iou),
            ))
            matched_prev.add(pi)
            matched_curr.add(ci)

            # 删除已匹配的行/列
            mask_rows = np.ones(len(prev_indices), dtype=bool)
            mask_cols = np.ones(len(curr_indices), dtype=bool)
            mask_rows[best_idx[0]] = False
            mask_cols[best_idx[1]] = False
            prev_indices = [p for p, m in zip(prev_indices, mask_rows) if m]
            curr_indices = [c for c, m in zip(curr_indices, mask_cols) if m]
            iou_matrix = iou_matrix[mask_rows][:, mask_cols]

    # 未匹配的 prev → REMOVED
    for i, d in enumerate(dets_prev):
        if i not in matched_prev:
            results.append(MatchResult(
                event=EventType.REMOVED,
                detection=d,
                matched_from=d,
                iou=0.0,
            ))

    # 未匹配的 curr → ADDED
    for j, d in enumerate(dets_curr):
        if j not in matched_curr:
            results.append(MatchResult(
                event=EventType.ADDED,
                detection=d,
                iou=0.0,
            ))

    # 排序：ADDED → REMOVED → STILL
    event_order = {EventType.ADDED: 0, EventType.REMOVED: 1, EventType.STILL: 2}
    results.sort(key=lambda r: event_order[r.event])

    return results


def compare_frames(dets_before: List[Detection],
                   dets_after: List[Detection],
                   iou_threshold: float = 0.30) -> List[MatchResult]:
    """
    便捷接口：对比两帧检测结果，返回存取事件

    Args:
        dets_before: 开门前检测
        dets_after: 关门后检测
        iou_threshold: IoU 匹配阈值

    Returns:
        List[MatchResult]: 存取事件列表
    """
    return greedy_iou_match(dets_before, dets_after, iou_threshold)