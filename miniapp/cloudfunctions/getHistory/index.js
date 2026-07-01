const cloud = require('wx-server-sdk')
cloud.init({ env: cloud.DYNAMIC_CURRENT_ENV })
const db = cloud.database()

exports.main = async (event, context) => {
  const res = await db.collection('history')
    .orderBy('timestamp', 'desc')
    .limit(event.limit || 50)
    .get()
  return { items: res.data }
}
