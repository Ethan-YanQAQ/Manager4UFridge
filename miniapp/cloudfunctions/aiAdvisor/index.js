/**
 * 云函数 aiAdvisor — AI 库存分析 + 菜谱推荐 + 购物建议
 * 调用 DeepSeek API，分析冰箱当前状态并给出建议
 */
const cloud = require('wx-server-sdk')
cloud.init({ env: cloud.DYNAMIC_CURRENT_ENV })
const db = cloud.database()

// DeepSeek API 配置
// 部署前在云函数设置中添加环境变量 DEEPSEEK_API_KEY
// 微信开发者工具 → 云开发控制台 → 云函数 → aiAdvisor → 环境变量
const DEEPSEEK_URL = 'https://api.deepseek.com/v1/chat/completions'
const DEEPSEEK_API_KEY = process.env.DEEPSEEK_API_KEY

if (!DEEPSEEK_API_KEY) {
  console.error('DEEPSEEK_API_KEY not configured')
}

exports.main = async (event, context) => {
  try {
    // 1. 读取库存数据
    const invRes = await db.collection('inventory').get()
    const inventory = invRes.data

    // 2. 读取最近 7 天历史
    const sevenDaysAgo = new Date(Date.now() - 7 * 86400000)
    const histRes = await db.collection('history')
      .where({ timestamp: db.command.gte(sevenDaysAgo) })
      .orderBy('timestamp', 'desc')
      .limit(50)
      .get()
    const history = histRes.data

    // 3. 构造 prompt
    const inventorySummary = inventory.map(i =>
      `${i.class}: ${i.count || 1}件, 存放${i.daysStored}天, 状态:${i.freshness}`
    ).join('\n')

    const historySummary = history.map(h =>
      `${h.action === 'ADDED' ? '放入' : '取出'} ${h.class} (${new Date(h.timestamp).toLocaleString('zh-CN')})`
    ).join('\n')

    const prompt = `你是一个智能冰箱管理助手。根据以下冰箱库存数据，给出分析建议。请用中文回复，输出JSON格式。

当前库存 (${inventory.length}种)：
${inventorySummary || '（冰箱是空的）'}

最近7天存取记录：
${historySummary || '（无记录）'}

请以JSON格式返回（不要包含markdown代码块标记）：
{
  "analysis": "库存健康度分析（2-3句话）：哪些快过期了，库存总体状态如何，消费习惯简评",
  "recipes": [
    {"name": "菜名", "ingredients": ["用到的食材"], "reason": "为什么推荐"}
  ],
  "shopping": [
    {"name": "食材名", "reason": "为什么建议买", "priority": "高/中/低"}
  ]
}
recipes推荐2-3道可用现有食材做的菜。shopping推荐2-4样采购建议。如果冰箱为空，analysis说明冰箱空着，recipes返回空数组。`

    // 4. 调用 DeepSeek API
    const response = await cloud.callFunction ? null : null // placeholder
    const axios = require('axios')
    const aiRes = await axios.post(DEEPSEEK_URL, {
      model: 'deepseek-chat',
      messages: [
        { role: 'system', content: '你是一个智能冰箱管理助手。始终以严格的JSON格式回复，不要在JSON外添加任何文字。' },
        { role: 'user', content: prompt }
      ],
      temperature: 0.7,
      max_tokens: 1500
    }, {
      headers: {
        'Content-Type': 'application/json',
        'Authorization': `Bearer ${DEEPSEEK_API_KEY}`
      },
      timeout: 30000
    })

    // 5. 解析响应
    const content = aiRes.data.choices[0].message.content
    // 去掉可能的 markdown 代码块标记
    const cleanJson = content.replace(/```json\n?|```/g, '').trim()
    const result = JSON.parse(cleanJson)

    return { ok: true, data: result }
  } catch (e) {
    console.error('aiAdvisor error:', e)
    // 降级返回空结果
    return {
      ok: true,
      data: {
        analysis: 'AI 助手暂时不可用，请稍后再试。',
        recipes: [],
        shopping: []
      }
    }
  }
}
