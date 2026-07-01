<template>
  <view class="page">
    <view v-if="loading" class="skeleton">
      <view v-for="i in 5" :key="i" class="sk-group">
        <view class="sk-date"></view>
        <view class="sk-row" v-for="j in 3" :key="j"></view>
      </view>
    </view>

    <view v-else-if="history.length === 0" class="empty-state">
      <text class="empty-icon">📋</text>
      <text class="empty-text">暂无存取记录</text>
    </view>

    <template v-else>
      <view v-for="(group, gIdx) in groupedHistory" :key="group.date" class="group animate-in" :style="'animation-delay:' + (gIdx * 0.1) + 's'">
        <view class="date-header">
          <text class="date-text">{{ group.date }}</text>
          <text class="date-count">{{ group.items.length }} 条</text>
        </view>

        <view v-for="item in group.items" :key="item._id" class="history-card">
          <view class="timeline">
            <view class="timeline-dot" :class="item.action === 'ADDED' ? 'dot-in' : 'dot-out'"></view>
            <view class="timeline-line"></view>
          </view>

          <view class="card-main">
            <view class="card-header">
              <text class="card-emoji">{{ getEmoji(item.class) }}</text>
              <text class="card-name">{{ item.class }}</text>
            </view>
            <view class="card-footer">
              <text class="card-action" :style="{ color: item.action === 'ADDED' ? '#7D9B76' : '#A85A5A' }">
                {{ item.action === 'ADDED' ? '→ 放入冰箱' : '← 取出冰箱' }}
              </text>
              <text class="card-time">{{ formatTime(item.timestamp) }}</text>
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
      history: []
    }
  },
  computed: {
    groupedHistory() {
      var groups = {}
      this.history.forEach(function(item) {
        var d = new Date(item.timestamp)
        var key = d.getFullYear() + '/' + String(d.getMonth()+1).padStart(2,'0') + '/' + String(d.getDate()).padStart(2,'0')
        if (!groups[key]) groups[key] = []
        groups[key].push(item)
      })
      var result = []
      Object.keys(groups).forEach(function(date) {
        result.push({ date: date, items: groups[date] })
      })
      return result
    }
  },
  onShow() { this.loadData() },
  methods: {
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
      try {
        var db = wx.cloud.database()
        var res = await db.collection('history').orderBy('timestamp', 'desc').limit(100).get()
        this.history = res.data
      } catch (e) { console.error(e) }
      finally { this.loading = false }
    }
  }
}
</script>

<style scoped>
.page { padding: 20rpx 32rpx 120rpx; position: relative; z-index: 1; }
.skeleton { padding-top: 20rpx; }
.sk-group { margin-bottom: 40rpx; }
.sk-date { height: 40rpx; width: 200rpx; border-radius: var(--radius-sm); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 16rpx; }
.sk-row { height: 100rpx; border-radius: var(--radius-md); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 12rpx; }
.empty-state { padding: 200rpx 0; text-align: center; }
.empty-icon { font-size: 80rpx; display: block; margin-bottom: 16rpx; }
.empty-text { color: var(--color-text-tertiary); font-size: 28rpx; }
.group { margin-bottom: 40rpx; }
.date-header { display: flex; align-items: center; gap: 12rpx; margin-bottom: 20rpx; padding-left: 56rpx; }
.date-text { font-family: var(--font-display); font-size: 32rpx; }
.date-count { font-family: var(--font-mono); font-size: 22rpx; color: var(--color-text-tertiary); }
.history-card { display: flex; margin-bottom: 8rpx; }
.timeline { width: 40rpx; display: flex; flex-direction: column; align-items: center; flex-shrink: 0; margin-right: 16rpx; }
.timeline-dot { width: 20rpx; height: 20rpx; border-radius: 50%; flex-shrink: 0; margin-top: 28rpx; }
.timeline-dot.dot-in { background: #7D9B76; box-shadow: 0 0 0 6rpx #E8EEE4; }
.timeline-dot.dot-out { background: #A85A5A; box-shadow: 0 0 0 6rpx #FBE8E8; }
.timeline-line { width: 2rpx; flex: 1; background: linear-gradient(to bottom, rgba(0,0,0,0.08), transparent); margin-top: 4rpx; }
.card-main { flex: 1; background: var(--color-surface); border-radius: var(--radius-md); padding: 24rpx; box-shadow: var(--shadow-card); }
.card-header { display: flex; align-items: center; gap: 12rpx; }
.card-emoji { font-size: 40rpx; }
.card-name { font-size: 30rpx; font-weight: 500; }
.card-footer { display: flex; justify-content: space-between; align-items: center; margin-top: 12rpx; }
.card-action { font-size: 24rpx; }
.card-time { font-family: var(--font-mono); font-size: 22rpx; color: var(--color-text-tertiary); }
</style>
