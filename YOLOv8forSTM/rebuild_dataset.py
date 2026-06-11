"""
重建 fridge_36：v4 优先，v1 去重，再合并水果 6 类。
重复图片：保留 v4，丢弃 v1。
"""

import zipfile
import os
import hashlib
from pathlib import Path
from collections import defaultdict

V1_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/food.v1i.yolov8.zip"
V4_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/food.v4i.yolov8.zip"
FRUIT_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/archive.zip"  # 水果数据集
OUT_DIR = Path("C:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_36")

# ---------- 类别定义 ----------
FRIDGE30 = [
    'beef','chicken','pork','duck',
    'fish','shrimp','squid','clams','eel','sea_crab',
    'egg','tofu','bean_sprouts',
    'cabbage','carrot','cauliflower_broccoli','corn','cucumber',
    'eggplant','garlic','onion','potato','tomato',
    'pumpkin','bitter_gourd',
    'mustard_greens','water_morning_glory','amaranth',
    'common_mushrooms','shiitake_mushroom',
]
FRUIT6 = ['Apple','Banana','Grape','Orange','Pineapple','Watermelon']
ALL36 = FRIDGE30 + FRUIT6

# ---------- 类别 ID 映射 ----------
def get_class_id_map(zip_path):
    """读取 zip 中 data.yaml，返回 {class_name: old_id}"""
    zf = zipfile.ZipFile(zip_path, 'r')
    content = zf.read('data.yaml').decode('utf-8')
    zf.close()
    # 简单解析
    lines = content.split('\n')
    names_str = None
    for line in lines:
        if line.startswith('names:'):
            names_str = line.split('names:')[1].strip()
            break
    if names_str and names_str.startswith('['):
        import ast
        names = ast.literal_eval(names_str)
    else:
        names = []
    return {n: i for i, n in enumerate(names)}

# Roboflow 78 类映射
rb_map = get_class_id_map(V1_ZIP)
# 验证 v1 v4 一致
rb_map4 = get_class_id_map(V4_ZIP)
assert rb_map == rb_map4, "v1 v4 类别不一致"

# 水果 6 类映射
fruit_map = {'Apple':0,'Banana':1,'Grape':2,'Orange':3,'Pineapple':4,'Watermelon':5}

# 构建 Roboflow 78 → fridge_30 的 ID 映射
rb78_to_f30 = {}  # {rb78_class_id: fridge30_id}
for f30_id, cls in enumerate(FRIDGE30):
    rb78_to_f30[rb_map[cls]] = f30_id

# ---------- 创建输出目录 ----------
for split in ['train','valid','test']:
    (OUT_DIR/'images'/split).mkdir(parents=True, exist_ok=True)
    (OUT_DIR/'labels'/split).mkdir(parents=True, exist_ok=True)

# ---------- 工具函数 ----------
def process_roboflow(zip_path, tag, seen_hashes, is_primary):
    """
    从 Roboflow zip 提取 30 类数据。
    is_primary=True 时，记录 hash 但不跳过。
    is_primary=False 时，跳过 seen_hashes 中已有的。
    """
    zf = zipfile.ZipFile(zip_path, 'r')

    # 收集 label/image 配对
    pairs = defaultdict(dict)  # (split,stem) -> {'label':path, 'image':path}
    for member in zf.namelist():
        parts = member.split('/')
        if len(parts) < 3:
            continue
        split = parts[0]  # train/valid/test
        if split not in ('train','valid','test'):
            continue
        subdir = parts[1]  # images/labels
        filename = parts[2]
        if not filename:
            continue
        stem = os.path.splitext(filename)[0]
        key = (split, stem)
        if subdir == 'labels':
            pairs[key]['label'] = member
        elif subdir == 'images':
            pairs[key]['image'] = member

    stats = defaultdict(int)
    extracted = 0
    skipped_dup = 0
    skipped_class = 0

    for (split, stem), entry in pairs.items():
        lbl_path = entry.get('label')
        img_path = entry.get('image')
        if not lbl_path or not img_path:
            continue

        label_raw = zf.read(lbl_path).decode('utf-8').strip()
        if not label_raw:
            continue

        # 过滤 + 重映射类别 ID
        new_lines = []
        for line in label_raw.split('\n'):
            parts_line = line.strip().split()
            if not parts_line:
                continue
            old_cls = int(parts_line[0])
            if old_cls in rb78_to_f30:
                new_lines.append(f"{rb78_to_f30[old_cls]} {' '.join(parts_line[1:])}")

        if not new_lines:
            skipped_class += 1
            continue

        # 读图片算 hash
        img_data = zf.read(img_path)
        h = hashlib.md5(img_data).hexdigest()

        if is_primary:
            # v4: 总是写入，记录 hash
            seen_hashes.add(h)
        else:
            # v1: 如果 v4 已存在则跳过
            if h in seen_hashes:
                skipped_dup += 1
                continue
            seen_hashes.add(h)

        cls_name = FRIDGE30[int(new_lines[0].split()[0])]
        out_name = f"rb__{cls_name}__{stem}"
        with open(OUT_DIR/'images'/split/f"{out_name}.jpg", 'wb') as f:
            f.write(img_data)
        with open(OUT_DIR/'labels'/split/f"{out_name}.txt", 'w') as f:
            f.write('\n'.join(new_lines))

        stats[cls_name] += 1
        extracted += 1

    zf.close()
    print(f"  [{tag}] 提取 {extracted} 张, 跳过(非目标类) {skipped_class}, "
          f"跳过(v4重复) {skipped_dup}, hash累计 {len(seen_hashes)}")
    return stats

def process_fruit(seen_hashes):
    """提取水果 6 类，ID 从 30 开始"""
    zf = zipfile.ZipFile(FRUIT_ZIP, 'r')
    prefix = "Fruits-detection/"

    pairs = defaultdict(dict)
    for member in zf.namelist():
        if not member.startswith(prefix):
            continue
        rel = member[len(prefix):]
        parts = rel.replace('\\','/').split('/')
        if len(parts) < 3:
            continue
        folder = parts[0]  # train/valid/test
        subdir = parts[1]  # images/labels
        filename = parts[2]
        if folder not in ('train','valid','test'):
            continue
        if not filename:
            continue
        stem = os.path.splitext(filename)[0]
        key = (folder, stem)
        if subdir == 'labels':
            pairs[key]['label'] = member
        elif subdir == 'images':
            pairs[key]['image'] = member

    stats = defaultdict(int)
    extracted = 0
    skipped_dup = 0
    fruit_offset = len(FRIDGE30)

    for (split, stem), entry in pairs.items():
        lbl_path = entry.get('label')
        img_path = entry.get('image')
        if not lbl_path or not img_path:
            continue

        label_raw = zf.read(lbl_path).decode('utf-8').strip()
        if not label_raw:
            continue

        new_lines = []
        for line in label_raw.split('\n'):
            parts_line = line.strip().split()
            if not parts_line:
                continue
            old_cls = int(parts_line[0])
            new_lines.append(f"{old_cls + fruit_offset} {' '.join(parts_line[1:])}")

        img_data = zf.read(img_path)
        h = hashlib.md5(img_data).hexdigest()
        if h in seen_hashes:
            skipped_dup += 1
            continue
        seen_hashes.add(h)

        cls_name = FRUIT6[int(label_raw.split('\n')[0].split()[0])]
        out_name = f"fruit__{cls_name}__{stem}"
        with open(OUT_DIR/'images'/split/f"{out_name}.jpg", 'wb') as f:
            f.write(img_data)
        with open(OUT_DIR/'labels'/split/f"{out_name}.txt", 'w') as f:
            f.write('\n'.join(new_lines))

        stats[cls_name] += 1
        extracted += 1

    zf.close()
    print(f"  [fruit] 提取 {extracted} 张, 跳过(v4重复) {skipped_dup}")
    return stats

# ---------- 主流程 ----------
print("=" * 60)
print("重建 fridge_36: v4 优先 → v1 去重 → 水果")

# Step 1: 清空输出目录
import shutil
if OUT_DIR.exists():
    shutil.rmtree(OUT_DIR)
for split in ['train','valid','test']:
    (OUT_DIR/'images'/split).mkdir(parents=True, exist_ok=True)
    (OUT_DIR/'labels'/split).mkdir(parents=True, exist_ok=True)

seen = set()

# Step 2: v4 优先
print("\n>> 处理 v4 (优先)...")
stats_v4 = process_roboflow(V4_ZIP, "v4", seen, is_primary=True)

# Step 3: v1 去重
print("\n>> 处理 v1 (去重: 跳过 v4 已有)...")
stats_v1 = process_roboflow(V1_ZIP, "v1", seen, is_primary=False)

# Step 4: 水果
print("\n>> 处理水果数据集...")
stats_fruit = process_fruit(seen)

# ---------- 统计 ----------
print("\n" + "=" * 60)
print("fridge_36 重建完成:")
total_train = total_valid = total_test = 0
for cls in ALL36:
    t4 = stats_v4.get(cls, 0)
    t1 = stats_v1.get(cls, 0)
    tf = stats_fruit.get(cls, 0)
    print(f"  {cls:<30s}  v4={t4:>4d}  v1={t1:>4d}  fruit={tf:>4d}  = {t4+t1+tf:>5d}")

# 按 split 统计
for split in ['train','valid','test']:
    n_img = len(list((OUT_DIR/'images'/split).iterdir()))
    if split == 'train':
        total_train = n_img
    elif split == 'valid':
        total_valid = n_img
    else:
        total_test = n_img

total_all = 0
for cls in ALL36:
    total_all += stats_v4.get(cls,0) + stats_v1.get(cls,0) + stats_fruit.get(cls,0)

print(f"\n  train={total_train}, valid={total_valid}, test={total_test}, 总计={total_all}")

# ---------- 写 dataset.yaml ----------
yaml_content = f"""# Fridge 36 -- Smart Fridge Food Detection Dataset
# v4 priority, v1 deduped + Fruit Detection 6
# 36 classes: meat, seafood, vegetables, fruits

path: {OUT_DIR.as_posix()}
train: images/train
val: images/valid
test: images/test

nc: {len(ALL36)}
names: {ALL36}
"""
with open(OUT_DIR/'dataset.yaml', 'w', encoding='utf-8') as f:
    f.write(yaml_content)

print("\ndataset.yaml written. Done!")
