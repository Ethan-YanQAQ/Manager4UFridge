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
    // === 对话模式 ===
    if (event.chat) {
      const userMessage = event.message || ''
      const chatHistory = event.history || []

      // 读取库存上下文
      const invRes = await db.collection('inventory').limit(50).get()
      const inventory = invRes.data
      const invCtx = inventory.length === 0 ? '冰箱是空的' : inventory.map(i =>
        `${i.class}: ${i.count||1}件, ${i.daysStored}天, ${i.freshness}`
      ).join('; ')

      // history 已含当前用户消息，去掉最后一条避免重复
      var prevMsgs = chatHistory.slice(0, -1)
      const msgs = [
        { role: 'system', content: `你是冰箱管理助手。当前库存: ${invCtx}。简短友好回复，不超过200字。` },
        ...prevMsgs.map(m => ({ role: m.role === 'user' ? 'user' : 'assistant', content: m.content })),
        { role: 'user', content: userMessage }
      ]

      const aiRes = await require('axios').post(DEEPSEEK_URL, {
        model: 'deepseek-chat',
        messages: msgs,
        temperature: 0.7,
        max_tokens: 500
      }, {
        headers: { 'Content-Type': 'application/json', 'Authorization': `Bearer ${DEEPSEEK_API_KEY}` },
        timeout: 15000
      })

      return { ok: true, data: { reply: aiRes.data.choices[0].message.content } }
    }

    // === 分析模式（原逻辑）===
    const invRes = await db.collection('inventory').limit(200).get()
    const inventory = invRes.data

    // 2. 读取最近历史记录
    const histRes = await db.collection('history')
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
        { role: 'system', content: '简短回复，JSON格式，不要markdown。' },
        { role: 'user', content: prompt }
      ],
      temperature: 0.5,
      max_tokens: 600
    }, {
      headers: {
        'Content-Type': 'application/json',
        'Authorization': `Bearer ${DEEPSEEK_API_KEY}`
      },
      timeout: 15000
    })

    // 5. 解析响应
    const content = aiRes.data.choices[0].message.content
    // 提取第一个 { 到最后一个 }，剥离 markdown/多余文字
    let cleanJson = content.replace(/```json\n?|```/g, '').trim()
    const firstBrace = cleanJson.indexOf('{')
    const lastBrace = cleanJson.lastIndexOf('}')
    if (firstBrace >= 0 && lastBrace > firstBrace) {
      cleanJson = cleanJson.slice(firstBrace, lastBrace + 1)
    }
    let result
    try {
      result = JSON.parse(cleanJson)
    } catch (parseErr) {
      console.error('JSON parse failed, raw content:', content)
      // 解析失败时把原文作为 analysis 返回，至少不空白
      return {
        ok: true,
        data: { analysis: content.slice(0, 300), recipes: [], shopping: [] }
      }
    }

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
