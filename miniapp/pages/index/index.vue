<template>
  <view class="page">
    <!-- 加载骨架屏 -->
    <view v-if="loading" class="skeleton">
      <view class="sk-header"></view>
      <view class="sk-stats">
        <view class="sk-card" v-for="i in 3" :key="i"></view>
      </view>
      <view class="sk-list">
        <view class="sk-row" v-for="i in 4" :key="i"></view>
      </view>
    </view>

    <template v-else>
      <view class="header animate-in" style="animation-delay: 0s">
        <text class="header-overline">食材管理</text>
        <text class="header-title">我的冰箱</text>
        <text class="header-sub" v-if="lastUpdate !== '--'">更新于 {{ lastUpdate }}</text>
      </view>

      <view class="stats-grid">
        <view class="stat-card total animate-in" style="animation-delay: 0.1s" @click="goTab('inventory')">
          <view class="stat-badge" style="background: var(--color-sage-light)">
            <text class="stat-num">{{ totalCount }}</text>
          </view>
          <text class="stat-label">库存</text>
        </view>
        <view class="stat-card-side">
          <view class="stat-card-sm warning animate-in" style="animation-delay: 0.15s" @click="goTab('inventory')">
            <text class="stat-num-sm">{{ warningCount }}</text>
            <text class="stat-label-sm">预警</text>
          </view>
          <view class="stat-card-sm expired animate-in" style="animation-delay: 0.2s" @click="goTab('inventory')">
            <text class="stat-num-sm">{{ expiredCount }}</text>
            <text class="stat-label-sm">过期</text>
          </view>
        </view>
      </view>

      <view class="section animate-in" style="animation-delay: 0.25s">
        <text class="section-title">最近操作</text>
        <view v-if="recentHistory.length === 0" class="empty-state">
          <text class="empty-icon">🧊</text>
          <text class="empty-text">冰箱空空的</text>
        </view>
        <view v-for="(item, idx) in recentHistory" :key="item._id" class="history-item" :style="'animation-delay:' + (0.3 + idx * 0.05) + 's'">
          <view class="dot" :class="item.action === 'ADDED' ? 'dot-in' : 'dot-out'"></view>
          <view class="item-content">
            <text class="item-name">{{ getEmoji(item.class) }} {{ item.class }}</text>
            <text class="item-action-text" :style="{ color: item.action === 'ADDED' ? 'var(--color-accent)' : 'var(--color-expired)' }">
              {{ item.action === 'ADDED' ? '放入' : '取出' }}
            </text>
          </view>
          <text class="item-time">{{ formatTime(item.timestamp) }}</text>
        </view>
      </view>

      <!-- AI 智能体卡片 -->
      <view class="ai-card animate-in" style="animation-delay: 0.35s">
        <view class="ai-header">
          <text class="ai-title">AI 助手</text>
          <text class="ai-subtitle" v-if="aiData">{{ aiData.analysis ? '已分析' : '加载中...' }}</text>
        </view>

        <!-- 加载态 -->
        <view v-if="aiLoading" class="ai-loading" @click="loadAI">
          <text class="ai-thinking">🤔 正在分析你的冰箱...</text>
        </view>

        <!-- 错误态 -->
        <view v-else-if="aiError" class="ai-loading" @click="loadAI">
          <text class="ai-thinking">AI 暂不可用，点击重试</text>
        </view>

        <!-- AI 三个 Tab -->
        <view v-else-if="aiData" class="ai-body">
          <view class="ai-tabs">
            <text class="ai-tab" :class="{ active: aiTab === 'analysis' }" @click="aiTab = 'analysis'">库存分析</text>
            <text class="ai-tab" :class="{ active: aiTab === 'recipes' }" @click="aiTab = 'recipes'">推荐菜谱</text>
            <text class="ai-tab" :class="{ active: aiTab === 'shopping' }" @click="aiTab = 'shopping'">采购建议</text>
          </view>

          <view class="ai-content">
            <text v-if="aiTab === 'analysis'" class="ai-text">{{ aiData.analysis }}</text>
            <view v-if="aiTab === 'recipes'">
              <view v-for="(r, i) in aiData.recipes" :key="i" class="ai-recipe">
                <text class="ai-recipe-name">🍳 {{ r.name }}</text>
                <text class="ai-recipe-info">用料: {{ r.ingredients.join(', ') }}</text>
              </view>
              <text v-if="!aiData.recipes || aiData.recipes.length === 0" class="ai-text">暂无菜谱推荐</text>
            </view>
            <view v-if="aiTab === 'shopping'">
              <view v-for="(s, i) in aiData.shopping" :key="i" class="ai-shop-item">
                <text class="ai-shop-name">{{ s.priority === '高' ? '🔴' : s.priority === '中' ? '🟡' : '🟢' }} {{ s.name }}</text>
                <text class="ai-shop-reason">{{ s.reason }}</text>
              </view>
              <text v-if="!aiData.shopping || aiData.shopping.length === 0" class="ai-text">暂无采购建议</text>
            </view>
          </view>
        </view>
      </view>
    </template>
  </view>
</template>

<script>
export default {
  data() {
    return {
      loading: true,
      totalCount: 0,
      warningCount: 0,
      expiredCount: 0,
      lastUpdate: '--',
      recentHistory: [],
      aiLoading: true,
      aiTab: 'analysis',
      aiData: null
    }
  },
  onShow() { this.loadData() },
  onPullDownRefresh() { this.loadData().then(function() { uni.stopPullDownRefresh() }) },
  methods: {
    goTab(tab) { uni.switchTab({ url: '/pages/' + tab + '/' + tab }) },
    getEmoji(cls) {
      var m = { Apple: '🍎', Banana: '🍌', Grape: '🍇', Orange: '🍊', Pineapple: '🍍', Watermelon: '🍉', beef: '🥩', pork: '🥩', poultry: '🍗', fish: '🐟', shrimp: '🦐', eel_seacrab: '🦀', egg: '🥚', tofu: '🧈', cabbage: '🥬', carrot: '🥕', cauliflower_broccoli: '🥦', corn: '🌽', cucumber: '🥒', eggplant: '🍆', allium: '🧅', potato: '🥔', tomato: '🍅', pumpkin: '🎃', bitter_gourd: '🥒', leafy_greens: '🥬', mushroom: '🍄', bean_sprouts: '🌱' }
      return m[cls] || '📦'
    },
    formatTime(ts) {
      var diff = Math.floor((Date.now() - new Date(ts).getTime()) / 60000)
      if (diff < 1) return '刚刚'
      if (diff < 60) return diff + '分钟前'
      var h = Math.floor(diff / 60)
      if (h < 24) return h + '小时前'
      return Math.floor(h / 24) + '天前'
    },
    async loadData() {
      wx.showLoading({ title: '加载中...' })
      try {
        var db = wx.cloud.database()
        var invRes = await db.collection('inventory').limit(200).get()
        var items = invRes.data
        this.totalCount = items.length
        this.warningCount = items.filter(function(i) { return i.freshness === 'WARNING' }).length
        this.expiredCount = items.filter(function(i) { return i.freshness === 'URGENT' || i.freshness === 'EXPIRED' }).length
        if (items.length > 0) {
          var latest = items.reduce(function(a, b) { return new Date(a.addedAt) > new Date(b.addedAt) ? a : b })
          this.lastUpdate = this.formatTime(latest.addedAt)
        }
        var histRes = await db.collection('history').orderBy('timestamp', 'desc').limit(50).get()
        this.recentHistory = histRes.data

        // 加载 AI 分析
        this.loadAI()
      } catch (e) {
        console.error('Load error:', e)
        wx.showToast({ title: '加载失败,请下拉刷新', icon: 'none', duration: 2000 })
      } finally {
        wx.hideLoading()
        this.loading = false
      }
    },
    async loadAI() {
      try {
        var cached = uni.getStorageSync('aiCache')
        if (cached && cached.time && (Date.now() - cached.time < 3600000)) {
          this.aiData = cached.data
          this.aiLoading = false
          return
        }
        var res = await wx.cloud.callFunction({ name: 'aiAdvisor' })
        if (res.result && res.result.ok && res.result.data) {
          this.aiData = res.result.data
          uni.setStorageSync('aiCache', { time: Date.now(), data: res.result.data })
        } else {
          this.aiData = { analysis: 'AI 助手暂无可分析内容', recipes: [], shopping: [] }
        }
      } catch (e) {
        console.error('AI error:', e)
        this.aiData = { analysis: 'AI 助手暂时不可用,下拉刷新重试', recipes: [], shopping: [] }
      } finally {
        this.aiLoading = false
      }
    }
  }
}
</script>

<style scoped>
.page { padding: 40rpx 32rpx; position: relative; z-index: 1; }
.skeleton { padding: 40rpx 0; }
.sk-header { height: 120rpx; width: 60%; border-radius: var(--radius-md); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 40rpx; }
.sk-stats { display: flex; gap: 24rpx; margin-bottom: 40rpx; }
.sk-card { flex: 1; height: 200rpx; border-radius: var(--radius-lg); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; }
.sk-list { background: var(--color-surface); border-radius: var(--radius-lg); padding: 32rpx; }
.sk-row { height: 60rpx; border-radius: var(--radius-sm); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 16rpx; }
.header { padding: 20rpx 0 40rpx; }
.header-overline { font-family: var(--font-mono); font-size: 22rpx; color: var(--color-text-tertiary); letter-spacing: 6rpx; }
.header-title { font-family: var(--font-display); font-size: 64rpx; font-weight: 400; color: var(--color-text-primary); display: block; margin: 8rpx 0; }
.header-sub { font-size: 24rpx; color: var(--color-text-tertiary); display: block; }
.stats-grid { display: flex; gap: 20rpx; margin-bottom: 48rpx; }
.stat-card { flex: 1; background: var(--color-surface); border-radius: var(--radius-lg); padding: 32rpx; box-shadow: var(--shadow-card); display: flex; flex-direction: column; gap: 12rpx; }
.stat-badge { width: 120rpx; height: 120rpx; border-radius: 50%; display: flex; align-items: center; justify-content: center; }
.stat-num { font-family: var(--font-display); font-size: 72rpx; color: var(--color-text-primary); }
.stat-label { font-family: var(--font-mono); font-size: 22rpx; color: var(--color-text-secondary); letter-spacing: 4rpx; }
.stat-card-side { flex: 1; display: flex; flex-direction: column; gap: 20rpx; }
.stat-card-sm { background: var(--color-surface); border-radius: var(--radius-md); padding: 24rpx; box-shadow: var(--shadow-card); }
.stat-card-sm.warning { border-left: 8rpx solid var(--color-warning); }
.stat-card-sm.expired { border-left: 8rpx solid var(--color-expired); }
.stat-num-sm { font-family: var(--font-display); font-size: 44rpx; }
.stat-label-sm { font-size: 24rpx; color: var(--color-text-secondary); display: block; margin-top: 4rpx; }
.section { background: var(--color-surface); border-radius: var(--radius-lg); padding: 36rpx; box-shadow: var(--shadow-card); }
.section-title { font-family: var(--font-display); font-size: 36rpx; display: block; margin-bottom: 24rpx; }
.empty-state { padding: 80rpx 0; text-align: center; }
.empty-icon { font-size: 72rpx; display: block; margin-bottom: 16rpx; }
.empty-text { font-size: 28rpx; color: var(--color-text-tertiary); }
.history-item { display: flex; align-items: center; padding: 20rpx 0; border-bottom: 1rpx solid rgba(0,0,0,0.04); animation: fadeInUp 0.5s var(--ease-spring) both; }
.dot { width: 16rpx; height: 16rpx; border-radius: 50%; margin-right: 20rpx; flex-shrink: 0; }
.dot-in { background: var(--color-accent); }
.dot-out { background: var(--color-expired); }
.item-content { flex: 1; }
.item-name { font-size: 30rpx; }
.item-action-text { font-size: 24rpx; display: block; margin-top: 2rpx; }
.item-time { font-family: var(--font-mono); font-size: 22rpx; color: var(--color-text-tertiary); }

/* === AI 卡片 === */
.ai-card { background: linear-gradient(135deg, #F5F7FA 0%, #E8EEE4 100%); border-radius: var(--radius-lg); padding: 32rpx; margin-top: 24rpx; box-shadow: var(--shadow-card); }
.ai-header { display: flex; align-items: center; gap: 12rpx; margin-bottom: 20rpx; }
.ai-title { font-family: var(--font-display); font-size: 34rpx; }
.ai-subtitle { font-size: 22rpx; color: var(--color-text-tertiary); }
.ai-loading { text-align: center; padding: 40rpx 0; }
.ai-thinking { font-size: 28rpx; color: var(--color-text-secondary); }
.ai-tabs { display: flex; gap: 12rpx; margin-bottom: 20rpx; }
.ai-tab { padding: 10rpx 24rpx; border-radius: 20rpx; font-size: 24rpx; background: rgba(255,255,255,0.6); color: var(--color-text-secondary); }
.ai-tab.active { background: var(--color-accent); color: #fff; }
.ai-content { background: rgba(255,255,255,0.5); border-radius: var(--radius-sm); padding: 20rpx; }
.ai-text { font-size: 26rpx; line-height: 1.8; color: var(--color-text-secondary); }
.ai-recipe { padding: 12rpx 0; border-bottom: 1rpx solid rgba(0,0,0,0.04); }
.ai-recipe-name { font-size: 28rpx; font-weight: 500; display: block; }
.ai-recipe-info { font-size: 24rpx; color: var(--color-text-tertiary); display: block; margin-top: 4rpx; }
.ai-shop-item { padding: 12rpx 0; border-bottom: 1rpx solid rgba(0,0,0,0.04); }
.ai-shop-name { font-size: 28rpx; font-weight: 500; display: block; }
.ai-shop-reason { font-size: 24rpx; color: var(--color-text-tertiary); display: block; margin-top: 4rpx; }
</style>
