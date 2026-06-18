"""Create fridge_33_v4: delete clams+squid + fruit density downsampling."""
import os, glob, random, shutil
from collections import defaultdict

random.seed(42)

SRC = '/root/YOLOv8forSTM/datasets/fridge_33_v3'
DST = '/root/YOLOv8forSTM/datasets/fridge_33_v4'

# Class mapping: delete 6(squid), 7(clams), shift >=8 down by 2
DELETE = {6, 7}
SHIFT_START = 8
SHIFT_BY = 2

def remap_cls(c):
    if c in DELETE:
        return None
    if c >= SHIFT_START:
        return c - SHIFT_BY
    return c

# ==================== Step 1: Remap labels ====================
for split in ['train', 'valid', 'test']:
    src_label_dir = f'{SRC}/labels/{split}'
    src_image_dir = f'{SRC}/images/{split}'
    os.makedirs(f'{DST}/labels/{split}', exist_ok=True)
    os.makedirs(f'{DST}/images/{split}', exist_ok=True)

    for lf in glob.glob(f'{src_label_dir}/*.txt'):
        stem = os.path.splitext(os.path.basename(lf))[0]
        new_lines = []

        with open(lf) as f:
            for line in f:
                parts = line.strip().split()
                old_cls = int(parts[0])
                if old_cls in DELETE:
                    continue  # drop this bbox
                new_cls = remap_cls(old_cls)
                parts[0] = str(new_cls)
                new_lines.append(' '.join(parts) + '\n')

        # Skip image if all bboxes were deleted
        if not new_lines:
            continue

        # Write new label
        with open(f'{DST}/labels/{split}/{stem}.txt', 'w') as f:
            f.writelines(new_lines)

        # Copy image
        src_img = f'{src_image_dir}/{stem}.jpg'
        if os.path.exists(src_img):
            shutil.copy2(src_img, f'{DST}/images/{split}/{stem}.jpg')

# Quick stats
train_imgs = len(glob.glob(f'{DST}/labels/train/*.txt'))
valid_imgs = len(glob.glob(f'{DST}/labels/valid/*.txt'))
test_imgs = len(glob.glob(f'{DST}/labels/test/*.txt'))
print(f'Step 1 - Remap done: train={train_imgs}, valid={valid_imgs}, test={test_imgs}')

# ==================== Step 2: Fruit density downsampling (train only) ====================
FRUIT_CLASSES = {25, 26, 27, 28, 29, 30}
FRUIT_NAMES = {25: 'Apple', 26: 'Banana', 27: 'Grape', 28: 'Orange', 29: 'Pineapple', 30: 'Watermelon'}
TARGETS = {25: 800, 27: 1200, 28: 1200}

label_dir = f'{DST}/labels/train'
image_dir = f'{DST}/images/train'

# Build per-class density data
fruit_img_data = {c: [] for c in FRUIT_CLASSES}

for lf in glob.glob(f'{label_dir}/*.txt'):
    stem = os.path.splitext(os.path.basename(lf))[0]
    classes = set()
    inst_per_cls = defaultdict(int)
    with open(lf) as f:
        for line in f:
            cls = int(line.split()[0])
            classes.add(cls)
            inst_per_cls[cls] += 1

    if classes and classes.issubset(FRUIT_CLASSES):
        for c in classes & FRUIT_CLASSES:
            fruit_img_data[c].append((inst_per_cls[c], stem))

# Drop highest density images
dropped_stems = set()
for cls in FRUIT_CLASSES:
    target = TARGETS.get(cls, 999999)
    data = sorted(fruit_img_data[cls], key=lambda x: x[0], reverse=True)
    current_total = sum(d[0] for d in data)
    print(f'{FRUIT_NAMES[cls]}: {current_total} inst, {len(data)} imgs, target={target}')

    removed_inst = 0
    for inst, stem in data:
        if current_total - removed_inst > target:
            dropped_stems.add(stem)
            removed_inst += inst
        else:
            break

    kept = sum(d[0] for d in data if d[1] not in dropped_stems)
    kept_imgs = sum(1 for d in data if d[1] not in dropped_stems)
    print(f'  -> Keep {kept_imgs} imgs, {kept} inst (dropped {removed_inst} inst)')

# Delete dropped
for stem in dropped_stems:
    try:
        os.remove(f'{label_dir}/{stem}.txt')
        os.remove(f'{image_dir}/{stem}.jpg')
    except:
        pass

# ==================== Final stats ====================
final_imgs = len(glob.glob(f'{label_dir}/*.txt'))
final_counts = defaultdict(int)
for lf in glob.glob(f'{label_dir}/*.txt'):
    with open(lf) as f:
        for line in f:
            final_counts[int(line.split()[0])] += 1

print(f'\n=== Final v4 ===')
print(f'Train images: {final_imgs}')
max_inst = max(final_counts.values())
min_inst = min(final_counts.values())
print(f'Max: {max_inst}, Min: {min_inst}, Ratio: {max_inst/min_inst:.1f}x')
for k in sorted(final_counts):
    name = FRUIT_NAMES.get(k, f'class{k}')
    print(f'  {name:<12s} {final_counts[k]:5d}')
