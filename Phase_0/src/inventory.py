"""
inventory.py - 食材清单管理（SQLite + 腐坏预警）

管理当前冰箱内的食材：
  - 存放时间追踪
  - 根据食材种类计算剩余保鲜天数
  - 腐坏预警
"""

import sqlite3
import datetime
from typing import List, Dict, Optional
import logging

logger = logging.getLogger(__name__)

# ─── 食材保鲜天数参考 ───
DEFAULT_FRESHNESS = {
    "apple": 14, "banana": 5, "orange": 10, "broccoli": 5,
    "carrot": 14, "pizza": 3, "hot_dog": 3, "sandwich": 2,
    "cake": 5, "milk": 7, "egg": 21, "bottle": 90,
    "cup": 90, "bowl": 90, "default": 7,
}


class FoodItem:
    """冰箱内一件食材"""
    __slots__ = ("id", "class_name", "stored_time", "fresh_days_total")

    def __init__(self, item_id: int, class_name: str,
                 stored_time: datetime.datetime, fresh_days: int):
        self.id = item_id
        self.class_name = class_name
        self.stored_time = stored_time
        self.fresh_days_total = fresh_days

    @property
    def days_stored(self) -> float:
        elapsed = datetime.datetime.now() - self.stored_time
        return elapsed.total_seconds() / 86400.0

    @property
    def fresh_days_left(self) -> float:
        return max(0.0, self.fresh_days_total - self.days_stored)

    @property
    def is_expired(self) -> bool:
        return self.fresh_days_left <= 0

    @property
    def status(self) -> str:
        if self.is_expired:
            return "EXPIRED"
        left = self.fresh_days_left
        if left < 1:
            return "URGENT"
        elif left < 3:
            return "WARNING"
        else:
            return "FRESH"

    def to_dict(self) -> Dict:
        return {
            "id": self.id,
            "class_name": self.class_name,
            "stored_time": self.stored_time.isoformat(),
            "days_stored": round(self.days_stored, 1),
            "fresh_days_total": self.fresh_days_total,
            "fresh_days_left": round(self.fresh_days_left, 1),
            "status": self.status,
        }

    def __repr__(self) -> str:
        return (f"FoodItem(id={self.id}, {self.class_name}, "
                f"stored={self.days_stored:.1f}d ago, "
                f"fresh_left={self.fresh_days_left:.1f}d, "
                f"status={self.status})")


class InventoryDB:
    """
    SQLite 食材清单数据库

    表结构：
        items(id INTEGER PK, class_name TEXT, stored_time TEXT, fresh_days INTEGER)
        history(id INTEGER PK, class_name TEXT, event TEXT, timestamp TEXT)
    """

    def __init__(self, db_path: str = "data/inventory.db"):
        self.db_path = db_path
        self.conn = sqlite3.connect(db_path, check_same_thread=False)
        self.conn.row_factory = sqlite3.Row
        self._init_tables()

    def _init_tables(self):
        cursor = self.conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS items (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                class_name TEXT NOT NULL,
                stored_time TEXT NOT NULL,
                fresh_days INTEGER NOT NULL DEFAULT 7
            )
        """)
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS history (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                class_name TEXT NOT NULL,
                event TEXT NOT NULL,
                timestamp TEXT NOT NULL
            )
        """)
        self.conn.commit()

    def add_item(self, class_name: str) -> int:
        """存入食材，返回分配的 ID"""
        now = datetime.datetime.now().isoformat()
        fresh_days = DEFAULT_FRESHNESS.get(class_name, DEFAULT_FRESHNESS["default"])
        cursor = self.conn.cursor()
        cursor.execute(
            "INSERT INTO items (class_name, stored_time, fresh_days) VALUES (?, ?, ?)",
            (class_name, now, fresh_days)
        )
        item_id = cursor.lastrowid

        # 记录操作历史
        cursor.execute(
            "INSERT INTO history (class_name, event, timestamp) VALUES (?, 'added', ?)",
            (class_name, now)
        )
        self.conn.commit()
        logger.info(f"[INVENTORY] ADDED  id={item_id}  {class_name}  (fresh {fresh_days}d)")
        return item_id

    def remove_item(self, item_id: int) -> bool:
        """取出食材"""
        item = self.get_item(item_id)
        if item is None:
            logger.warning(f"[INVENTORY] REMOVE failed: id={item_id} not found")
            return False

        cursor = self.conn.cursor()
        cursor.execute("DELETE FROM items WHERE id = ?", (item_id,))
        now = datetime.datetime.now().isoformat()
        cursor.execute(
            "INSERT INTO history (class_name, event, timestamp) VALUES (?, 'removed', ?)",
            (item.class_name, now)
        )
        self.conn.commit()
        logger.info(f"[INVENTORY] REMOVED id={item_id}  {item.class_name}")
        return True

    def get_item(self, item_id: int) -> Optional[FoodItem]:
        cursor = self.conn.cursor()
        cursor.execute("SELECT * FROM items WHERE id = ?", (item_id,))
        row = cursor.fetchone()
        if row is None:
            return None
        return FoodItem(
            item_id=row["id"],
            class_name=row["class_name"],
            stored_time=datetime.datetime.fromisoformat(row["stored_time"]),
            fresh_days=row["fresh_days"],
        )

    def get_all_items(self) -> List[FoodItem]:
        cursor = self.conn.cursor()
        cursor.execute("SELECT * FROM items ORDER BY stored_time ASC")
        items = []
        for row in cursor.fetchall():
            items.append(FoodItem(
                item_id=row["id"],
                class_name=row["class_name"],
                stored_time=datetime.datetime.fromisoformat(row["stored_time"]),
                fresh_days=row["fresh_days"],
            ))
        return items

    def get_statistics(self) -> Dict:
        """返回统计数据"""
        items = self.get_all_items()
        total = len(items)
        expired = sum(1 for i in items if i.is_expired)
        urgent = sum(1 for i in items if i.status == "URGENT")
        warning = sum(1 for i in items if i.status == "WARNING")
        return {
            "total": total,
            "expired": expired,
            "urgent": urgent,
            "warning": warning,
            "fresh": total - expired - urgent - warning,
            "items": [i.to_dict() for i in items],
        }

    def close(self):
        self.conn.close()