/**
 * 云函数 addDetection
 * 接收 STM32/ESP8266 上报的检测结果，写入云数据库
 *
 * 请求格式（HTTP POST body）:
 * {
 *   "detections": [
 *     {"class": "Apple", "action": "ADDED"},
 *     {"class": "Banana", "action": "REMOVED"}
 *   ]
 * }
 */
const cloud = require('wx-server-sdk')
cloud.init({ env: cloud.DYNAMIC_CURRENT_ENV })
const db = cloud.database()
const _ = db.command

// 腐坏天数阈值（与 Phase_0 config.yaml 保持一致）
const THRESHOLDS = {
  FRESH:    { max: 3,  label: '新鲜' },   // 0-3天
  WARNING:  { max: 7,  label: '预警' },   // 4-7天
  URGENT:   { max: 12, label: '紧急' },   // 8-12天
  EXPIRED:  {          label: '过期' },   // >12天
}

function calcFreshness(daysStored) {
  if (daysStored <= THRESHOLDS.FRESH.max)   return 'FRESH'
  if (daysStored <= THRESHOLDS.WARNING.max) return 'WARNING'
  if (daysStored <= THRESHOLDS.URGENT.max)  return 'URGENT'
  return 'EXPIRED'
}

exports.main = async (event, context) => {
  const now = new Date()
  const detections = event.detections || []
  const results = { added: [], removed: [], still: [] }

  for (const det of detections) {
    const { class: className, action } = det

    if (action === 'ADDED') {
      // 检查是否已存在同类的库存记录
      const exist = await db.collection('inventory')
        .where({ class: className })
        .get()

      if (exist.data.length > 0) {
        // 同类已存在，更新计数
        await db.collection('inventory').doc(exist.data[0]._id).update({
          data: { count: _.inc(1), addedAt: now }
        })
      } else {
        await db.collection('inventory').add({
          data: {
            class: className,
            addedAt: now,
            freshness: 'FRESH',
            daysStored: 0,
            count: 1
          }
        })
      }
      results.added.push(className)
    }

    if (action === 'REMOVED') {
      const exist = await db.collection('inventory')
        .where({ class: className })
        .get()

      if (exist.data.length > 0) {
        const item = exist.data[0]
        if (item.count > 1) {
          await db.collection('inventory').doc(item._id).update({
            data: { count: _.inc(-1) }
          })
        } else {
          await db.collection('inventory').doc(item._id).remove()
        }
      }
      results.removed.push(className)
    }

    if (action === 'STILL') {
      results.still.push(className)
    }

    // 写入历史记录
    await db.collection('history').add({
      data: {
        class: className,
        action: action,
        timestamp: now
      }
    })
  }

  // 更新所有库存的存放天数 + 新鲜度
  const allItems = await db.collection('inventory').get()
  for (const item of allItems.data) {
    const days = Math.floor((now - new Date(item.addedAt)) / 86400000)
    const freshness = calcFreshness(days)
    if (days !== item.daysStored || freshness !== item.freshness) {
      await db.collection('inventory').doc(item._id).update({
        data: { daysStored: days, freshness: freshness }
      })
    }
  }

  return { ok: true, results }
}
