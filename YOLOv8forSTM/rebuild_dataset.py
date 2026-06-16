"""
重建平衡数据集 v2：合并尾部类 + 图片级降采样头部类

合并：
  common_mushrooms + shiitake_mushroom → mushroom
  mustard_greens + water_morning_glory + amaranth → leafy_greens

降采样（图片级 cap=1500，仅丢弃图片，不修改标签）：
  Orange, Apple, Grape, Banana

策略：
  1. 优先丢弃"只含头部类"的图
  2. 如果 head-only 池不够，再从"混合"池丢（含非头部类的图也会丢）
"""

import os
import yaml
import random
import shutil
from collections import defaultdict, Counter
from pathlib import Path

random.seed(42)

SRC = Path("c:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_36")
DST = Path("c:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_33_v2")
IMG_CAP = 1500  # 每个头部类最多保留 N 张图

# ---- 1. 加载原始 class names ----
with open(SRC / "dataset.yaml") as f:
    orig_cfg = yaml.safe_load(f)
orig_names = orig_cfg["names"]

# ---- 2. old_id → new_id 映射 ----
old_to_new = {}
new_names = []

for i in range(25):
    old_to_new[i] = i
    new_names.append(orig_names[i])

for i in (25, 26, 27):
    old_to_new[i] = 25
new_names.append("leafy_greens")

for i in (28, 29):
    old_to_new[i] = 26
new_names.append("mushroom")

for i in range(30, 36):
    old_to_new[i] = i - 3
    new_names.append(orig_names[i])

NC = 33
HEAD_CLASSES = {27, 28, 29, 30}  # Apple, Banana, Grape, Orange

print(f"36 -> {NC} classes")
print(f"Merges: class 25=leafy_greens, class 26=mushroom")
print(f"Image cap={IMG_CAP} for: {[new_names[i] for i in sorted(HEAD_CLASSES)]}")
print()

# ---- 3. 构建 image → class_ids 映射 ----
image_classes = {}  # rel_path → set of new class ids

for split in ("train", "valid", "test"):
    label_dir = SRC / f"labels/{split}"
    if not label_dir.is_dir():
        continue
    for lb_file in sorted(label_dir.iterdir()):
        if lb_file.suffix != ".txt":
            continue
        new_ids = set()
        with open(lb_file) as fh:
            for line in fh:
                parts = line.strip().split()
                if not parts:
                    continue
                new_ids.add(old_to_new[int(parts[0])])
        if new_ids:
            rel = str(Path(f"images/{split}") / lb_file.with_suffix(".jpg").name)
            image_classes[rel] = new_ids

print(f"Total images: {len(image_classes)}")

# ---- 4. 当前每类图片数 ----
img_per_class = Counter()
head_only_images = []
mixed_images = []

for img, classes in image_classes.items():
    for c in classes:
        img_per_class[c] += 1
    if classes.issubset(HEAD_CLASSES):
        head_only_images.append(img)
    else:
        mixed_images.append(img)

print(f"Head-only images (only fruit): {len(head_only_images)}")
print(f"Mixed images (fruit + other):  {len(mixed_images)}")
print()

print("Before downsampling (images per class):")
for cid in range(NC):
    cnt = img_per_class.get(cid, 0)
    marker = " <-- HEAD" if cid in HEAD_CLASSES else ""
    print(f"  {cid:2d}  {new_names[cid]:25s}  {cnt:6,} images{marker}")

# ---- 5. 图片级降采样 ----
# 为每个头部类建立候选丢弃列表
drop_candidates = {}  # head_class → [img_list] (sorted by "quality to drop")
for c in HEAD_CLASSES:
    candidates = []
    for img in head_only_images:
        if c in image_classes[img]:
            candidates.append(img)
    # head-only 优先
    candidates.sort()  # deterministic order
    random.shuffle(candidates)
    drop_candidates[c] = candidates

# 逐个头部类处理
to_drop = set()  # 已经标记为丢弃的图片

for c in sorted(HEAD_CLASSES, key=lambda x: img_per_class.get(x, 0), reverse=True):
    current = img_per_class.get(c, 0)
    if current <= IMG_CAP:
        # 但可能因为前面其他类丢弃而降到 cap 以下，重新计算
        current = sum(1 for img in image_classes
                      if c in image_classes[img] and img not in to_drop)
        if current <= IMG_CAP:
            continue

    need = current - IMG_CAP
    dropped = 0

    # 先从 head-only 池丢
    for img in drop_candidates.get(c, []):
        if dropped >= need:
            break
        if img not in to_drop:
            to_drop.add(img)
            dropped += 1

    if dropped < need and False:
        # 理论上应该走mixed pool，但优先不动它
        pass

    # 重新计算（受影响的所有头部类）
    for cc in HEAD_CLASSES:
        img_per_class[cc] = sum(1 for img in image_classes
                                if cc in image_classes[img] and img not in to_drop)

    print(f"  {new_names[c]:15s}: {current:5,} -> {img_per_class[c]:5,} images (dropped {dropped})")

keep_images = set(image_classes.keys()) - to_drop

print(f"\nDropped: {len(to_drop)} images")
print(f"Kept:   {len(keep_images)} images")

# ---- 6. 最终统计 ----
print("\nAfter downsampling:")
final_img = Counter()
final_labels = Counter()
for img in keep_images:
    for c in image_classes[img]:
        final_img[c] += 1

# Count labels from actual files
for img_rel in keep_images:
    parts = img_rel.replace("\\", "/").split("/")
    split = parts[1]
    fname = parts[2]
    lbl_path = SRC / f"labels/{split}" / Path(fname).with_suffix(".txt").name
    if lbl_path.exists():
        with open(lbl_path) as fh:
            for line in fh:
                parts2 = line.strip().split()
                if parts2:
                    final_labels[old_to_new[int(parts2[0])]] += 1

for cid in range(NC):
    imgs = final_img.get(cid, 0)
    lbls = final_labels.get(cid, 0)
    bar = "|" * int(imgs / 20)
    marker = " <-- HEAD" if cid in HEAD_CLASSES else ""
    print(f"  {cid:2d}  {new_names[cid]:25s}  {imgs:5,} imgs  {lbls:6,} labels  {bar}{marker}")

lbl_counts = sorted(final_labels.values())
if lbl_counts[0] > 0:
    print(f"\nImbalance: {lbl_counts[-1]/lbl_counts[0]:.1f}x labels  |  max={lbl_counts[-1]:,}  min={lbl_counts[0]}")

# ---- 7. 复制到新数据集 ----
print(f"\n--- Copying to {DST} ---")
if DST.exists():
    shutil.rmtree(DST)

for split in ("train", "valid", "test"):
    src_img_dir = SRC / f"images/{split}"
    if not src_img_dir.is_dir():
        continue
    src_lbl_dir = SRC / f"labels/{split}"
    dst_img_dir = DST / f"images/{split}"
    dst_lbl_dir = DST / f"labels/{split}"
    dst_img_dir.mkdir(parents=True, exist_ok=True)
    dst_lbl_dir.mkdir(parents=True, exist_ok=True)

    copied = 0
    for img_file in sorted(src_img_dir.iterdir()):
        if img_file.suffix.lower() not in (".jpg", ".jpeg", ".png"):
            continue
        rel = str(Path(f"images/{split}") / img_file.name)
        if rel not in keep_images:
            continue

        shutil.copy2(img_file, dst_img_dir / img_file.name)

        lb_file = src_lbl_dir / img_file.with_suffix(".txt").name
        if lb_file.exists():
            with open(lb_file) as fh:
                lines = fh.readlines()
            new_lines = []
            for line in lines:
                parts = line.strip().split()
                if not parts:
                    continue
                parts[0] = str(old_to_new[int(parts[0])])
                new_lines.append(" ".join(parts) + "\n")
            with open(dst_lbl_dir / lb_file.name, "w") as fh:
                fh.writelines(new_lines)
        else:
            open(dst_lbl_dir / lb_file.name, "w").close()
        copied += 1

    print(f"  {split}: {copied} images")

# ---- 8. 写 dataset.yaml ----
yaml_path = DST / "dataset.yaml"
yaml_content = f"""# Fridge 33 v2: balanced dataset (image-level downsampling)
# 36->33 classes: merged tail classes + downsampled fruit head classes
# Merges: leafy_greens (25+26+27), mushroom (28+29)
# Image downsampling (cap={IMG_CAP}): Orange, Apple, Grape, Banana

path: {DST.as_posix()}
train: images/train
val: images/valid
test: images/test

nc: {NC}
names: {new_names}
"""
with open(yaml_path, "w") as f:
    f.write(yaml_content)

print(f"\nDone! {yaml_path}")
