"""
Build fridge_v6 from 3 raw datasets:
  food.v1i.yolov8.zip  — Roboflow food v1 (78 classes, 10,858 images)
  food.v4i.yolov8.zip  — Roboflow food v4 (78 classes, 4,209 images)
  archive.zip          — Fruits detection (6 classes, 8,479 images)

Pipeline:
  1. Extract all
  2. MD5 dedup (v4 > v1 where overlap; fruit archive is independent)
  3. Map classes → target classes + merge/delete
  4. Remove high-density fruit images (inst/img > threshold)
  5. Train/val/test split
"""
import zipfile, os, glob, shutil, hashlib, random
from collections import defaultdict
from pathlib import Path

random.seed(42)

WORK = Path('c:/Users/29264/Desktop/QS/_v6_work')
DST = Path('c:/Users/29264/Desktop/QS/YOLOv8forSTM/datasets/fridge_v6')

# Clean work dir
if WORK.exists():
    shutil.rmtree(WORK)
WORK.mkdir(parents=True)

# ==================================================================
# CLASS MAPPING
# ==================================================================

# Target classes (final order after all merges/deletes)
TARGET_NAMES = [
    'beef', 'pork', 'poultry',  # chicken+duck merged
    'fish', 'shrimp',
    'eel_seacrab',          # merged: eel + sea_crab
    'egg', 'tofu', 'bean_sprouts',
    'cabbage', 'carrot', 'cauliflower_broccoli', 'corn', 'cucumber',
    'eggplant', 'allium',   # merged: garlic + onion
    'potato', 'tomato', 'pumpkin', 'bitter_gourd',
    'leafy_greens',         # merged: amaranth + mustard_greens + water_morning_glory
    'mushroom',             # merged: common_mushrooms + shiitake_mushroom
    'Apple', 'Banana', 'Grape', 'Orange', 'Pineapple', 'Watermelon',
]
TARGET_IDX = {name: i for i, name in enumerate(TARGET_NAMES)}
NC = len(TARGET_NAMES)
print(f'Target: {NC} classes')

# Mapping from food dataset (78 classes) → target
FOOD_MAP = {
    'beef': 'beef', 'pork': 'pork', 'chicken': 'poultry', 'duck': 'poultry',
    'fish': 'fish', 'shrimp': 'shrimp',
    'eel': 'eel_seacrab', 'sea_crab': 'eel_seacrab',
    'egg': 'egg', 'tofu': 'tofu', 'bean_sprouts': 'bean_sprouts',
    'cabbage': 'cabbage', 'carrot': 'carrot',
    'cauliflower_broccoli': 'cauliflower_broccoli',
    'corn': 'corn', 'cucumber': 'cucumber', 'eggplant': 'eggplant',
    'garlic': 'allium', 'onion': 'allium',
    'potato': 'potato', 'tomato': 'tomato',
    'pumpkin': 'pumpkin', 'bitter_gourd': 'bitter_gourd',
    'common_mushrooms': 'mushroom', 'shiitake_mushroom': 'mushroom',
    'amaranth': 'leafy_greens', 'mustard_greens': 'leafy_greens',
    'water_morning_glory': 'leafy_greens',
    'pineapple': 'Pineapple',
}
# Classes to DELETE (squid, clams)
FOOD_DELETE = {'squid', 'clams'}

# Fruit dataset (archive.zip) → target (already matches)
FRUIT_MAP = {
    'Apple': 'Apple', 'Banana': 'Banana', 'Grape': 'Grape',
    'Orange': 'Orange', 'Pineapple': 'Pineapple', 'Watermelon': 'Watermelon',
}

# ==================================================================
# STEP 1: Extract all datasets
# ==================================================================
print('\n=== Step 1: Extract ===')

ZIPS = [
    ('food.v1i.yolov8.zip', 'c:/Users/29264/Desktop/QS/food.v1i.yolov8.zip'),
    ('food.v4i.yolov8.zip', 'c:/Users/29264/Desktop/QS/food.v4i.yolov8.zip'),
    ('archive.zip', 'c:/Users/29264/Desktop/QS/archive.zip'),
]

for name, path in ZIPS:
    dest = WORK / name.replace('.zip', '')
    print(f'Extracting {name}...')
    with zipfile.ZipFile(path) as z:
        z.extractall(dest)
    imgs = len(list(dest.rglob('*.jpg'))) + len(list(dest.rglob('*.jpeg'))) + len(list(dest.rglob('*.png')))
    lbls = len(list(dest.rglob('*.txt')))
    print(f'  {imgs} images, {lbls} labels')

# ==================================================================
# STEP 2: Collect images + labels with MD5 dedup
# ==================================================================
print('\n=== Step 2: Collect & MD5 dedup ===')

seen_md5 = set()          # MD5 → (source, class_list)
all_samples = []          # (img_path, label_path, source, classes_in_img)

def collect_from_food(dataset_dir, source_name):
    """Collect from Roboflow food dataset (has train/valid/test splits)."""
    data_yaml = list(dataset_dir.rglob('data.yaml'))[0]
    base_dir = data_yaml.parent

    for split in ['train', 'valid', 'test']:
        label_dir = base_dir / split / 'labels'
        image_dir = base_dir / split / 'images'
        if not label_dir.exists():
            continue
        for lf in label_dir.glob('*.txt'):
            # Find corresponding image
            stem = lf.stem
            img = None
            for ext in ['.jpg', '.jpeg', '.png', '.JPG', '.JPEG', '.PNG']:
                candidate = image_dir / f'{stem}{ext}'
                if candidate.exists():
                    img = candidate
                    break
            if img is None:
                continue
            all_samples.append((img, lf, source_name))

def collect_from_fruit(dataset_dir):
    """Collect from fruit detection dataset."""
    for split in ['train', 'valid', 'test']:
        label_dir = list(dataset_dir.rglob(f'*/{split}/labels'))
        image_dir = list(dataset_dir.rglob(f'*/{split}/images'))
        if not label_dir:
            continue
        label_dir = label_dir[0]
        image_dir = image_dir[0]
        for lf in label_dir.glob('*.txt'):
            stem = lf.stem
            img = None
            for ext in ['.jpg', '.jpeg', '.png', '.JPG', '.JPEG', '.PNG']:
                candidate = image_dir / f'{stem}{ext}'
                if candidate.exists():
                    img = candidate
                    break
            if img is None:
                continue
            all_samples.append((img, lf, 'fruit'))

# Collect: v4 first (newer), then v1, then fruit
collect_from_food(WORK / 'food.v4i.yolov8', 'food_v4')
collect_from_food(WORK / 'food.v1i.yolov8', 'food_v1')
collect_from_fruit(WORK / 'archive')

print(f'Total raw samples: {len(all_samples)}')

# MD5 dedup: keep first occurrence (v4 > v1 > fruit)
deduped = []
dup_count = 0
for img_path, label_path, source in all_samples:
    with open(img_path, 'rb') as f:
        md5 = hashlib.md5(f.read()).hexdigest()
    if md5 in seen_md5:
        dup_count += 1
        continue
    seen_md5.add(md5)
    deduped.append((img_path, label_path, source))

print(f'After dedup: {len(deduped)} ({dup_count} duplicates removed)')

# ==================================================================
# STEP 3: Remap classes
# ==================================================================
print('\n=== Step 3: Class remapping ===')

remapped_samples = []  # (img_path, new_lines[], source)
class_img_count = defaultdict(int)  # target_class → image count
class_inst_count = defaultdict(int)  # target_class → instance count
skipped_empty = 0
skipped_unknown = 0

for img_path, label_path, source in deduped:
    new_lines = []
    classes_in_img = set()

    # Determine which mapping to use
    if source == 'fruit':
        mapper = FRUIT_MAP
    else:
        mapper = FOOD_MAP

    with open(label_path) as f:
        for line in f:
            parts = line.strip().split()
            if not parts:
                continue
            old_cls_id = int(parts[0])

            # Get class name from source
            if source == 'fruit':
                # 6 classes, order: Apple,Banana,Grape,Orange,Pineapple,Watermelon
                fruit_names = ['Apple', 'Banana', 'Grape', 'Orange', 'Pineapple', 'Watermelon']
                if old_cls_id < 0 or old_cls_id >= len(fruit_names):
                    continue
                src_name = fruit_names[old_cls_id]
            else:
                # Food dataset: need to get class names from data.yaml
                # We already know the 78-class list
                food_names = ['amaranth', 'ash_gourd', 'bamboo_shoots', 'banana_flower',
                    'bean_sprouts', 'beef', 'bell_pepper', 'bitter_gourd', 'bottle_gourd',
                    'bread', 'cabbage', 'carrot', 'cassava', 'cauliflower_broccoli', 'chayote',
                    'chicken', 'chili_pepper', 'clams', 'common_mushrooms', 'corn', 'cucumber',
                    'dracontomelon', 'dried_fish', 'dried_shrimp', 'dry_noodles', 'duck', 'eel',
                    'egg', 'eggplant', 'field_crab', 'fish', 'frog_meat', 'galangal', 'garlic',
                    'ginger', 'green_banana', 'green_beans', 'green_onion', 'green_papaya',
                    'instant_noodles', 'jute_leaves', 'katuk', 'kohlrabi', 'lemon_lime',
                    'lemongrass', 'lotus_root', 'malabar_spinach', 'mustard_greens', 'okra',
                    'onion', 'oyster', 'pineapple', 'piper_lolot', 'pork', 'pork_paste', 'potato',
                    'pumpkin', 'pumpkin_leaves', 'raw_rice', 'raw_sausage', 'salmon', 'sea_crab',
                    'sea_fish', 'shallot', 'shiitake_mushroom', 'shrimp', 'snail', 'sponge_gourd',
                    'squid', 'starfruit', 'sweet_potato', 'tamarind', 'tofu', 'tomato', 'turmeric',
                    'water_morning_glory', 'white_radish', 'wood_ear_mushroom']
                if old_cls_id < 0 or old_cls_id >= len(food_names):
                    continue
                src_name = food_names[old_cls_id]

            # Check delete
            if src_name in FOOD_DELETE:
                continue

            # Map
            target_name = mapper.get(src_name)
            if target_name is None:
                continue  # skip irrelevant classes

            target_id = TARGET_IDX[target_name]
            parts[0] = str(target_id)
            new_lines.append(' '.join(parts) + '\n')
            classes_in_img.add(target_id)

    if not new_lines:
        skipped_empty += 1
        continue

    remapped_samples.append((img_path, new_lines, source, classes_in_img))
    for c in classes_in_img:
        class_img_count[c] += 1
        class_inst_count[c] += len([l for l in new_lines if int(l.split()[0]) == c])

print(f'Remapped: {len(remapped_samples)} images')
print(f'Skipped empty: {skipped_empty}')
print()

for i, name in enumerate(TARGET_NAMES):
    print(f'  {name:<20s} {class_img_count.get(i, 0):>5d} imgs  {class_inst_count.get(i, 0):>6d} inst')

# ==================================================================
# STEP 4: Remove high-density fruit images
# ==================================================================
print('\n=== Step 4: Remove high-density fruit images ===')

FRUIT_TARGET_IDS = {TARGET_IDX[n] for n in ['Apple', 'Banana', 'Grape', 'Orange', 'Pineapple', 'Watermelon']}
MAX_DENSITY = 5  # max instances per image per fruit class

high_density_dropped = 0
final_samples = []

for img_path, lines, source, classes_in_img in remapped_samples:
    # Only check pure-fruit images
    if classes_in_img and classes_in_img.issubset(FRUIT_TARGET_IDS):
        inst_per_class = defaultdict(int)
        for line in lines:
            inst_per_class[int(line.split()[0])] += 1

        # Check if any fruit class exceeds max density
        too_dense = any(inst_per_class[c] > MAX_DENSITY for c in classes_in_img if c in FRUIT_TARGET_IDS)
        if too_dense:
            high_density_dropped += 1
            continue

    final_samples.append((img_path, lines, source))

print(f'High-density dropped: {high_density_dropped}')
print(f'Final images: {len(final_samples)}')

# ==================================================================
# STEP 5: Split and write output
# ==================================================================
print('\n=== Step 5: Train/val/test split & write ===')

# Clean dest
if DST.exists():
    shutil.rmtree(DST)

random.shuffle(final_samples)
n = len(final_samples)
train_split = int(n * 0.80)
val_split = int(n * 0.90)

splits = {
    'train': final_samples[:train_split],
    'valid': final_samples[train_split:val_split],
    'test': final_samples[val_split:],
}

final_counts = defaultdict(int)
for split_name, samples in splits.items():
    os.makedirs(DST / 'images' / split_name, exist_ok=True)
    os.makedirs(DST / 'labels' / split_name, exist_ok=True)

    for img_path, lines, source in samples:
        stem = hashlib.md5(str(img_path).encode()).hexdigest()[:12]
        # Copy image
        ext = img_path.suffix
        shutil.copy2(img_path, DST / 'images' / split_name / f'{stem}{ext}')
        # Write label
        with open(DST / 'labels' / split_name / f'{stem}.txt', 'w') as f:
            f.writelines(lines)

        for line in lines:
            final_counts[int(line.split()[0])] += 1

    print(f'{split_name}: {len(samples)} images')

# Write dataset.yaml
yaml_content = f"""# Fridge v6: merged from Roboflow v1+v4 + Fruit detection
# Pipeline: dedup → class merge/delete → remove high-density fruit
# MD5 dedup across all sources, v4 priority over v1

path: /root/YOLOv8forSTM/datasets/fridge_v6
train: images/train
val: images/valid
test: images/test

nc: {NC}
names: {TARGET_NAMES}
"""

with open(DST / 'dataset.yaml', 'w') as f:
    f.write(yaml_content)

# ==================================================================
# STEP 6: Final stats
# ==================================================================
print(f'\n=== Final v6 stats ===')
print(f'Classes: {NC}')
print(f'Train: {len(splits["train"])}, Valid: {len(splits["valid"])}, Test: {len(splits["test"])}')
print(f'Total: {n}')

max_inst = max(final_counts.values())
min_inst = min(final_counts.values())
max_cls = TARGET_NAMES[max(final_counts, key=final_counts.get)]
min_cls = TARGET_NAMES[min(final_counts, key=final_counts.get)]
print(f'Max: {max_cls} = {max_inst}')
print(f'Min: {min_cls} = {min_inst}')
print(f'Ratio: {max_inst/min_inst:.1f}x')

print()
for i, name in enumerate(TARGET_NAMES):
    c = final_counts.get(i, 0)
    bar = '█' * int(c / max(final_counts.values()) * 30)
    print(f'  {name:<20s} {c:>6d}  {bar}')

# Clean work dir
print(f'\nCleaning work dir...')
shutil.rmtree(WORK)
print('Done!')
