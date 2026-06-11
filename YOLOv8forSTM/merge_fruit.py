"""
合并 fridge_30（肉海鲜蔬菜 30 类）+ fruit 6 类 = fridge_36
"""

import zipfile
import os
import hashlib
from pathlib import Path

FRUIT_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/archive.zip"
FRIDGE30_DIR = Path("C:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_30")
OUT_DIR = Path("C:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_36")

# fridge_30 的类别（保持原有顺序）
FRIDGE_CLASSES = [
    'beef', 'chicken', 'pork', 'duck',
    'fish', 'shrimp', 'squid', 'clams', 'eel', 'sea_crab',
    'egg', 'tofu', 'bean_sprouts',
    'cabbage', 'carrot', 'cauliflower_broccoli', 'corn', 'cucumber',
    'eggplant', 'garlic', 'onion', 'potato', 'tomato',
    'pumpkin', 'bitter_gourd',
    'mustard_greens', 'water_morning_glory', 'amaranth',
    'common_mushrooms', 'shiitake_mushroom',
]

# 水果类别（新增）
FRUIT_CLASSES = ['Apple', 'Banana', 'Grape', 'Orange', 'Pineapple', 'Watermelon']

ALL_CLASSES = FRIDGE_CLASSES + FRUIT_CLASSES
print(f"合并后类别数: {len(ALL_CLASSES)}")
print(f"Fridge 30 类 + Fruit 6 类 = {len(ALL_CLASSES)} 类")

# 创建输出目录
for split in ['train', 'valid', 'test']:
    (OUT_DIR / 'images' / split).mkdir(parents=True, exist_ok=True)
    (OUT_DIR / 'labels' / split).mkdir(parents=True, exist_ok=True)

# ─── Step 1: 复制 fridge_30（保持原 ID） ───
print("\n复制 fridge_30 ...")
seen_hashes = set()
total_fridge = 0
for split in ['train', 'valid', 'test']:
    img_src = FRIDGE30_DIR / 'images' / split
    lbl_src = FRIDGE30_DIR / 'labels' / split
    if not img_src.exists():
        continue
    n = 0
    for f in img_src.iterdir():
        if not f.suffix.lower() in ('.jpg', '.jpeg', '.png'):
            continue
        stem = f.stem
        lbl_file = lbl_src / f"{stem}.txt"
        if not lbl_file.exists():
            continue

        # 读图片 hash 用于去重
        with open(f, 'rb') as fh:
            h = hashlib.md5(fh.read()).hexdigest()

        if h in seen_hashes:
            continue
        seen_hashes.add(h)

        # 复制
        with open(f, 'rb') as src:
            with open(OUT_DIR / 'images' / split / f.name, 'wb') as dst:
                dst.write(src.read())
        with open(lbl_file, 'r') as src:
            with open(OUT_DIR / 'labels' / split / f"{stem}.txt", 'w') as dst:
                dst.write(src.read())

        n += 1
    total_fridge += n
    print(f"  {split}: {n} 张")

print(f"  fridge_30 总计: {total_fridge} 张")

# ─── Step 2: 提取水果数据集 ───
print("\n提取水果数据集 ...")
zf = zipfile.ZipFile(FRUIT_ZIP, 'r')
prefix = "Fruits-detection/"

# 水果类别 ID 偏移（从 30 开始）
fruit_id_offset = len(FRIDGE_CLASSES)

total_fruit = 0
skipped_dup = 0

for split, zip_subdir in [('train', 'train'), ('valid', 'valid'), ('test', 'test')]:
    n = 0
    # 收集该 split 下的所有 label 文件
    label_members = {}
    image_members = {}

    for member in zf.namelist():
        if not member.startswith(prefix):
            continue
        rel = member[len(prefix):]
        parts = rel.replace('\\', '/').split('/')
        if len(parts) < 3:
            continue
        folder = parts[0]  # train, valid, test
        subdir = parts[1]  # images, labels
        filename = parts[2]

        if folder != zip_subdir:
            continue
        if not filename:
            continue

        stem = os.path.splitext(filename)[0]

        if subdir == 'labels':
            label_members[stem] = member
        elif subdir == 'images':
            image_members[stem] = member

    for stem, lbl_path in label_members.items():
        img_path = image_members.get(stem)
        if not img_path:
            continue

        # 读取标签，修改 class_id
        lbl_content = zf.read(lbl_path).decode('utf-8').strip()
        if not lbl_content:
            continue

        new_lines = []
        for line in lbl_content.split('\n'):
            parts_l = line.strip().split()
            if not parts_l:
                continue
            old_id = int(parts_l[0])
            new_id = old_id + fruit_id_offset
            new_lines.append(f"{new_id} {' '.join(parts_l[1:])}")

        # 读取图片
        img_data = zf.read(img_path)
        h = hashlib.md5(img_data).hexdigest()
        if h in seen_hashes:
            skipped_dup += 1
            continue
        seen_hashes.add(h)

        # 写入
        cls_name = FRUIT_CLASSES[int(lbl_content.split()[0])]
        out_name = f"fruit__{cls_name}__{stem}"
        with open(OUT_DIR / 'images' / split / f"{out_name}.jpg", 'wb') as f:
            f.write(img_data)
        with open(OUT_DIR / 'labels' / split / f"{out_name}.txt", 'w') as f:
            f.write('\n'.join(new_lines))

        n += 1

    total_fruit += n
    print(f"  {split}: {n} 张")

zf.close()
print(f"  fruit 总计: {total_fruit} 张 (去重跳过 {skipped_dup} 张)")

# ─── 统计 ───
print(f"\n{'='*60}")
print(f"合并完成: {total_fridge + total_fruit} 张图片, {len(ALL_CLASSES)} 类")

for split in ['train', 'valid', 'test']:
    n_img = len(list((OUT_DIR / 'images' / split).iterdir()))
    n_lbl = len(list((OUT_DIR / 'labels' / split).iterdir()))
    print(f"  {split}: {n_img} images, {n_lbl} labels")

# ─── 生成 dataset.yaml ───
yaml_content = f"""# Fridge 36 — 冰箱食材检测数据集（完整版）
# fridge_30 (Roboflow food-kcmrd v1+v4) + Fruit Detection 6
# 覆盖：肉类、海鲜、蔬菜、水果

path: {OUT_DIR.as_posix()}
train: images/train
val: images/valid
test: images/test

nc: {len(ALL_CLASSES)}
names: {ALL_CLASSES}
"""
with open(OUT_DIR / 'dataset.yaml', 'w', encoding='utf-8') as f:
    f.write(yaml_content)

print(f"\n✅ dataset.yaml 已生成: {OUT_DIR / 'dataset.yaml'}")
print(f"✅ 合并完成！36 类数据集就绪")
