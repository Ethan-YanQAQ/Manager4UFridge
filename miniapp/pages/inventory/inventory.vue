<template>
  <view class="page">
    <view v-if="loading" class="skeleton">
      <view class="sk-filter">
        <view class="sk-pill" v-for="i in 5" :key="i"></view>
      </view>
      <view class="sk-card" v-for="i in 6" :key="i"></view>
    </view>

    <template v-else>
      <scroll-view scroll-x class="filter-bar animate-in" style="animation-delay: 0s" :show-scrollbar="false">
        <text v-for="c in categories" :key="c"
          class="filter-pill" :class="{ active: activeCat === c }" @click="activeCat = c">{{ c }}</text>
      </scroll-view>

      <view v-if="filteredItems.length === 0" class="empty-state">
        <text class="empty-icon">🧊</text>
        <text class="empty-text">还没有食材</text>
      </view>

      <view v-for="(item, idx) in filteredItems" :key="item._id"
        class="food-card animate-in" :style="'animation-delay:' + (0.1 + idx * 0.06) + 's'"
        @click="showDetail(item)">
        <view class="freshness-strip" :class="'strip-' + item.freshness"></view>
        <view class="card-body">
          <view class="card-left">
            <text class="food-emoji">{{ getEmoji(item.class) }}</text>
          </view>
          <view class="card-mid">
            <text class="food-name">{{ item.class }}</text>
            <text class="food-meta">{{ item.daysStored }} 天 · {{ item.count || 1 }} 件</text>
          </view>
          <view class="card-right">
            <text class="freshness-badge" :class="'badge-' + item.freshness">{{ freshnessLabel(item.freshness) }}</text>
          </view>
        </view>
      </view>

      <view class="legend animate-in" style="animation-delay: 0.6s">
        <view v-for="l in legends" :key="l.label" class="legend-dot">
          <view class="legend-circle" :style="{ background: l.color }"></view>
          <text class="legend-text">{{ l.label }}</text>
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
      items: [],
      activeCat: '全部',
      legends: [
        { label: '新鲜 0-3天', color: '#7D9B76' },
        { label: '预警 4-7天', color: '#D4A853' },
        { label: '紧急 8-12天', color: '#C27B5C' },
        { label: '过期 >12天', color: '#A85A5A' }
      ]
    }
  },
  computed: {
    categories() {
      var cats = []
      var seen = {}
      this.items.forEach(function(i) {
        if (!seen[i.class]) { seen[i.class] = true; cats.push(i.class) }
      })
      cats.sort()
      return ['全部'].concat(cats)
    },
    filteredItems() {
      var self = this
      if (this.activeCat === '全部') return this.items
      return this.items.filter(function(i) { return i.class === self.activeCat || i.class.indexOf(self.activeCat) >= 0 })
    }
  },
  onShow() { this.loadData() },
  methods: {
    getEmoji(cls) {
      var m = { Apple: '🍎', Banana: '🍌', Grape: '🍇', Orange: '🍊', Pineapple: '🍍', Watermelon: '🍉', beef: '🥩', pork: '🥩', poultry: '🍗', fish: '🐟', shrimp: '🦐', eel_seacrab: '🦀', egg: '🥚', tofu: '🧈', cabbage: '🥬', carrot: '🥕', cauliflower_broccoli: '🥦', corn: '🌽', cucumber: '🥒', eggplant: '🍆', allium: '🧅', potato: '🥔', tomato: '🍅', pumpkin: '🎃', bitter_gourd: '🥒', leafy_greens: '🥬', mushroom: '🍄', bean_sprouts: '🌱' }
      return m[cls] || '📦'
    },
    freshnessLabel(f) {
      var m = { FRESH: '新鲜', WARNING: '预警', URGENT: '紧急', EXPIRED: '过期' }
      return m[f] || f
    },
    showDetail(item) {
      uni.showModal({
        title: item.class,
        content: '存放: ' + item.daysStored + '天\n状态: ' + this.freshnessLabel(item.freshness) + '\n数量: ' + (item.count || 1),
        showCancel: false,
        confirmColor: '#7D9B76'
      })
    },
    async loadData() {
      try {
        var db = wx.cloud.database()
        var res = await db.collection('inventory').orderBy('daysStored', 'desc').limit(200).get()
        this.items = res.data
      } catch (e) { console.error(e) }
      finally { this.loading = false }
    }
  }
}
</script>

<style scoped>
.page { padding: 20rpx 32rpx 120rpx; position: relative; z-index: 1; }
.skeleton { padding-top: 20rpx; }
.sk-filter { display: flex; gap: 16rpx; margin-bottom: 32rpx; }
.sk-pill { width: 140rpx; height: 60rpx; border-radius: 30rpx; background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; }
.sk-card { height: 140rpx; border-radius: var(--radius-md); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 16rpx; }
.filter-bar { white-space: nowrap; padding: 16rpx 0 20rpx; margin-bottom: 8rpx; }
.filter-pill { display: inline-block; padding: 12rpx 28rpx; margin-right: 14rpx; border-radius: 30rpx; background: var(--color-surface); font-size: 26rpx; color: var(--color-text-secondary); box-shadow: var(--shadow-card); }
.filter-pill.active { background: var(--color-text-primary); color: var(--color-bg); }
.empty-state { padding: 160rpx 0; text-align: center; }
.empty-icon { font-size: 80rpx; display: block; margin-bottom: 16rpx; }
.empty-text { color: var(--color-text-tertiary); font-size: 28rpx; }
.food-card { background: var(--color-surface); border-radius: var(--radius-md); margin-bottom: 16rpx; overflow: hidden; box-shadow: var(--shadow-card); display: flex; }
.freshness-strip { width: 8rpx; flex-shrink: 0; }
.strip-FRESH { background: #7D9B76; }
.strip-WARNING { background: #D4A853; }
.strip-URGENT { background: #C27B5C; }
.strip-EXPIRED { background: #A85A5A; }
.card-body { flex: 1; display: flex; align-items: center; padding: 24rpx 24rpx 24rpx 28rpx; }
.card-left { margin-right: 20rpx; }
.food-emoji { font-size: 52rpx; }
.card-mid { flex: 1; }
.food-name { font-size: 32rpx; font-weight: 500; display: block; }
.food-meta { font-size: 24rpx; color: var(--color-text-tertiary); display: block; margin-top: 4rpx; }
.card-right { flex-shrink: 0; }
.freshness-badge { padding: 8rpx 20rpx; border-radius: 20rpx; font-size: 22rpx; font-family: var(--font-mono); }
.badge-FRESH { background: #E8EEE4; color: #7D9B76; }
.badge-WARNING { background: #FDF3E0; color: #D4A853; }
.badge-URGENT { background: #FDE9E0; color: #C27B5C; }
.badge-EXPIRED { background: #FBE8E8; color: #A85A5A; }
.legend { display: flex; justify-content: center; gap: 32rpx; padding: 32rpx; margin-top: 16rpx; }
.legend-dot { display: flex; align-items: center; gap: 8rpx; }
.legend-circle { width: 16rpx; height: 16rpx; border-radius: 50%; }
.legend-text { font-size: 22rpx; color: var(--color-text-tertiary); }
</style>
