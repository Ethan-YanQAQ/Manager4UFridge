"""
合并 v1 + v4 数据集，筛选 30 个冰箱相关类别，去重后生成训练数据。
"""

import zipfile
import os
import shutil
import hashlib
from pathlib import Path
from collections import defaultdict

V1_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/food.v1i.yolov8.zip"
V4_ZIP = "C:/Users/29264/Desktop/QS/YOLOv8forSTM/food.v4i.yolov8.zip"
OUT_DIR = Path("C:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_30")

# ─── 30 个冰箱相关类别 ───
SELECTED_CLASSES = [
    # 肉类 Meats (4)
    'beef', 'chicken', 'pork', 'duck',
    # 海鲜 Seafood (6)
    'fish', 'shrimp', 'squid', 'clams', 'eel', 'sea_crab',
    # 蛋/豆制品 Others (3)
    'egg', 'tofu', 'bean_sprouts',
    # 常见蔬菜 Common Vegetables (10)
    'cabbage', 'carrot', 'cauliflower_broccoli', 'corn', 'cucumber',
    'eggplant', 'garlic', 'onion', 'potato', 'tomato',
    # 瓜类 Gourds (2)
    'pumpkin', 'bitter_gourd',
    # 绿叶菜 Leafy Greens (3)
    'mustard_greens', 'water_morning_glory', 'amaranth',
    # 菌菇 Mushrooms (2)
    'common_mushrooms', 'shiitake_mushroom',
]

# 读 v1 data.yaml 获取原始类别名→ID映射
import sys
sys.stdout.reconfigure(encoding='utf-8')

def get_class_map(zip_path):
    """从 zip 中读取 data.yaml，返回 {class_name: class_id}"""
    zf = zipfile.ZipFile(zip_path, 'r')
    content = zf.read('data.yaml').decode('utf-8')
    zf.close()
    # 解析 names 列表
    lines = content.split('\n')
    in_names = False
    names = []
    for line in lines:
        if line.startswith('names:'):
            in_names = True
            names_str = line.split('names:')[1].strip()
            if names_str.startswith('['):
                # 单行列表
                import ast
                names = ast.literal_eval(names_str)
                break
        elif in_names and line.strip().startswith('- '):
            names.append(line.strip()[2:].strip("'").strip('"'))
    return {name: i for i, name in enumerate(names)}

def get_selected_ids(class_map):
    """获取选中类别的 ID 列表及其新 ID 映射"""
    # 按 SELECTED_CLASSES 顺序分配新 ID
    new_id_map = {}
    for new_id, cls in enumerate(SELECTED_CLASSES):
        if cls in class_map:
            new_id_map[class_map[cls]] = new_id
        else:
            print(f"警告: {cls} 不在数据集中!")
    return new_id_map

# 获取原类别 ID
v1_class_map = get_class_map(V1_ZIP)
print(f"v1 类别数: {len(v1_class_map)}")
v4_class_map = get_class_map(V4_ZIP)
print(f"v4 类别数: {len(v4_class_map)}")

# 检查一致性
assert v1_class_map == v4_class_map, "v1 和 v4 类别映射不一致!"
class_map = v1_class_map
old_to_new = get_selected_ids(class_map)

print(f"\n选中 {len(old_to_new)} 类的样本")
print(f"目标类别: {SELECTED_CLASSES}")
print(f"原始 ID → 新 ID: {old_to_new}")

# 创建输出目录
for split in ['train', 'valid', 'test']:
    (OUT_DIR / 'images' / split).mkdir(parents=True, exist_ok=True)
    (OUT_DIR / 'labels' / split).mkdir(parents=True, exist_ok=True)

# ─── 处理函数 ───
def extract_and_filter(zip_path, tag):
    """
    从 zip 提取选中类别的图片和标签。
    返回 {filename_stem: (split, img_path, lbl_path)}  用于去重
    """
    zf = zipfile.ZipFile(zip_path, 'r')
    # 收集所有相关文件
    label_files = {}
    image_files = {}

    for member in zf.namelist():
        parts = member.split('/')
        if len(parts) < 3:
            continue
        split = parts[0]  # train, valid, test
        subdir = parts[1]  # images, labels
        filename = parts[2]

        if split not in ('train', 'valid', 'test'):
            continue
        if not filename:
            continue

        stem = os.path.splitext(filename)[0]
        full_path = member

        if subdir == 'labels':
            label_files[(split, stem)] = full_path
        elif subdir == 'images':
            image_files[(split, stem)] = full_path

    print(f"\n[{tag}] 总文件: labels={len(label_files)}, images={len(image_files)}")

    stats = defaultdict(lambda: defaultdict(int))  # cls -> split -> count
    seen = set()
    extracted = 0
    skipped_class = 0

    for (split, stem), label_path in label_files.items():
        img_path = image_files.get((split, stem))
        if not img_path:
            continue

        # 读取标签，检查类别
        label_content = zf.read(label_path).decode('utf-8').strip()
        if not label_content:
            continue

        # 解析标签内容，过滤行
        filtered_lines = []
        for line in label_content.split('\n'):
            parts_l = line.strip().split()
            if not parts_l:
                continue
            old_cls_id = int(parts_l[0])
            if old_cls_id in old_to_new:
                new_cls_id = old_to_new[old_cls_id]
                filtered_lines.append(f"{new_cls_id} {' '.join(parts_l[1:])}")

        if not filtered_lines:
            skipped_class += 1
            continue

        # 去重（用 stem + image hash）
        img_data = zf.read(img_path)
        img_hash = hashlib.md5(img_data).hexdigest()

        if img_hash in seen:
            continue
        seen.add(img_hash)

        # 确定类名（取第一个框的类别）
        cls_name = SELECTED_CLASSES[int(filtered_lines[0].split()[0])]

        # 写入
        out_img = OUT_DIR / 'images' / split / f"{cls_name}__{stem}.jpg"
        out_lbl = OUT_DIR / 'labels' / split / f"{cls_name}__{stem}.txt"

        with open(out_img, 'wb') as f:
            f.write(img_data)
        with open(out_lbl, 'w') as f:
            f.write('\n'.join(filtered_lines))

        stats[cls_name][split] += 1
        extracted += 1

    zf.close()
    print(f"[{tag}] 提取: {extracted} 张, 跳过(非目标类): {skipped_class}, "
          f"去重后累计: {len(seen)}")
    return stats, seen

# 处理 v1 和 v4
print("\n" + "="*60)
print("提取 v1...")
stats1, seen_all = extract_and_filter(V1_ZIP, "v1")

print("\n提取 v4...")
stats2, _ = extract_and_filter(V4_ZIP, "v4")

# ─── 统计 ───
print("\n" + "="*60)
print("合并后数据集统计：")

total_train = total_valid = total_test = 0
for cls in SELECTED_CLASSES:
    t1 = stats1.get(cls, {}).get('train', 0)
    v1 = stats1.get(cls, {}).get('valid', 0)
    t2 = stats2.get(cls, {}).get('train', 0)
    v2 = stats2.get(cls, {}).get('valid', 0)
    e1 = stats1.get(cls, {}).get('test', 0)
    e2 = stats2.get(cls, {}).get('test', 0)
    t_total = t1 + t2
    v_total = v1 + v2
    e_total = e1 + e2
    total_train += t_total
    total_valid += v_total
    total_test += e_total
    print(f"  {cls:<30s}: train={t_total:>5d}, valid={v_total:>4d}, test={e_total:>4d}  (总计={t_total+v_total+e_total})")

print(f"\n{'─'*60}")
print(f"  总计: train={total_train}, valid={total_valid}, test={total_test}")
print(f"  合计: {total_train+total_valid+total_test} 张图片")

# ─── 生成 dataset.yaml ───
yaml_path = OUT_DIR / "dataset.yaml"
yaml_content = f"""# Fridge 30 — 冰箱食材检测数据集
# 来源: Roboflow food-kcmrd v1 + v4, CC BY 4.0
# 筛选 30 个冰箱常见类别

path: {OUT_DIR.as_posix()}
train: images/train
val: images/valid
test: images/test

nc: {len(SELECTED_CLASSES)}
names: {SELECTED_CLASSES}
"""
with open(yaml_path, 'w', encoding='utf-8') as f:
    f.write(yaml_content)

print(f"\n✅ 数据集已生成: {OUT_DIR}")
print(f"✅ data.yaml: {yaml_path}")
print("准备训练！")
