/**
 * 云函数 api — HTTP 入口
 * ESP8266 POST /api → 转发到 addDetection 逻辑
 * 小程序 GET  /api?action=getInventory → 返回库存
 * 小程序 GET  /api?action=getHistory → 返回历史
 *
 * 部署后需在云开发控制台 → 云函数 → api → 配置 HTTP 触发器
 */
const cloud = require('wx-server-sdk')
cloud.init({ env: cloud.DYNAMIC_CURRENT_ENV })
const db = cloud.database()
const _ = db.command

const THRESHOLDS = {
  FRESH:   { max: 3  },
  WARNING: { max: 7  },
  URGENT:  { max: 12 },
  EXPIRED: {         },
}

function calcFreshness(days) {
  if (days <= THRESHOLDS.FRESH.max)  return 'FRESH'
  if (days <= THRESHOLDS.WARNING.max) return 'WARNING'
  if (days <= THRESHOLDS.URGENT.max)  return 'URGENT'
  return 'EXPIRED'
}

exports.main = async (event, context) => {
  const httpMethod = event.httpMethod || event.httpMethod || 'GET'

  // ========== GET 请求：查询库存/历史 ==========
  if (httpMethod === 'GET') {
    const action = event.queryStringParameters?.action || 'getInventory'
    if (action === 'getHistory') {
      const res = await db.collection('history').orderBy('timestamp', 'desc').limit(50).get()
      return { statusCode: 200, body: JSON.stringify({ items: res.data }) }
    }
    const res = await db.collection('inventory').orderBy('daysStored', 'desc').get()
    return { statusCode: 200, body: JSON.stringify({ items: res.data }) }
  }

  // ========== POST 请求：STM32 上报检测结果 ==========
  if (httpMethod === 'POST') {
    const body = typeof event.body === 'string' ? JSON.parse(event.body) : event.body
    const detections = body.detections || []
    const now = new Date()
    const results = { added: [], removed: [], still: [] }

    for (const det of detections) {
      const { class: className, action } = det

      if (action === 'ADDED') {
        const exist = await db.collection('inventory').where({ class: className }).get()
        if (exist.data.length > 0) {
          await db.collection('inventory').doc(exist.data[0]._id).update({
            data: { count: _.inc(1), addedAt: now }
          })
        } else {
          await db.collection('inventory').add({
            data: { class: className, addedAt: now, freshness: 'FRESH', daysStored: 0, count: 1 }
          })
        }
        results.added.push(className)
      }

      if (action === 'REMOVED') {
        const exist = await db.collection('inventory').where({ class: className }).get()
        if (exist.data.length > 0) {
          const item = exist.data[0]
          if (item.count > 1) {
            await db.collection('inventory').doc(item._id).update({ data: { count: _.inc(-1) } })
          } else {
            await db.collection('inventory').doc(item._id).remove()
          }
        }
        results.removed.push(className)
      }

      if (action === 'STILL') {
        results.still.push(className)
      }

      await db.collection('history').add({ data: { class: className, action, timestamp: now } })
    }

    // 更新新鲜度
    const allItems = await db.collection('inventory').get()
    for (const item of allItems.data) {
      const days = Math.floor((now - new Date(item.addedAt)) / 86400000)
      const freshness = calcFreshness(days)
      if (days !== item.daysStored || freshness !== item.freshness) {
        await db.collection('inventory').doc(item._id).update({
          data: { daysStored: days, freshness }
        })
      }
    }

    return { statusCode: 200, body: JSON.stringify({ ok: true, results }) }
  }

  return { statusCode: 405, body: JSON.stringify({ error: 'Method not allowed' }) }
}
