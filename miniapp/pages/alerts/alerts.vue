<template>
  <view class="page">
    <view v-if="loading" class="skeleton">
      <view class="sk-row" v-for="i in 6" :key="i"></view>
    </view>

    <template v-else>
      <!-- 统计条 -->
      <view class="summary-bar">
        <view class="summary-item warn"><text class="sum-num">{{ warningItems.length }}</text><text class="sum-label">预警</text></view>
        <view class="summary-item urg"><text class="sum-num">{{ urgentItems.length }}</text><text class="sum-label">紧急</text></view>
        <view class="summary-item exp"><text class="sum-num">{{ expiredItems.length }}</text><text class="sum-label">过期</text></view>
      </view>

      <view v-if="allItems.length === 0" class="empty-state">
        <text class="empty-icon">✅</text>
        <text class="empty-text">没有预警或过期食材</text>
      </view>

      <!-- 表格 -->
      <view v-else class="table animate-in">
        <view class="table-header">
          <text class="th name">食材</text>
          <text class="th days">存放</text>
          <text class="th count">数量</text>
          <text class="th status">状态</text>
        </view>
        <view v-for="item in allItems" :key="item._id" class="table-row">
          <text class="td name">{{ getEmoji(item.class) }} {{ item.class }}</text>
          <text class="td days">{{ item.daysStored }}天</text>
          <text class="td count">{{ item.count || 1 }}</text>
          <text class="td status" :class="'status-' + item.freshness">{{ freshnessLabel(item.freshness) }}</text>
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
      items: []
    }
  },
  computed: {
    warningItems() { return this.items.filter(function(i) { return i.freshness === 'WARNING' }) },
    urgentItems()  { return this.items.filter(function(i) { return i.freshness === 'URGENT' })  },
    expiredItems() { return this.items.filter(function(i) { return i.freshness === 'EXPIRED' }) },
    allItems()     { return this.warningItems.concat(this.urgentItems).concat(this.expiredItems) }
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
    async loadData() {
      try {
        var db = wx.cloud.database()
        var res = await db.collection('inventory')
          .where(db.command.or([
            { freshness: 'WARNING' },
            { freshness: 'URGENT' },
            { freshness: 'EXPIRED' }
          ]))
          .orderBy('daysStored', 'desc')
          .limit(50)
          .get()
        this.items = res.data
      } catch (e) { console.error(e) }
      finally { this.loading = false }
    }
  }
}
</script>

<style scoped>
.page { padding: 20rpx 32rpx; }
.skeleton { padding-top: 20rpx; }
.sk-row { height: 100rpx; border-radius: var(--radius-md); background: linear-gradient(90deg, #f5f0e8 0%, #e8e0d0 50%, #f5f0e8 100%); background-size: 800rpx 100%; animation: shimmer 1.5s infinite; margin-bottom: 12rpx; }

.summary-bar { display: flex; gap: 16rpx; margin-bottom: 24rpx; }
.summary-item { flex: 1; padding: 20rpx; border-radius: var(--radius-md); text-align: center; }
.summary-item.warn { background: #FDF3E0; }
.summary-item.urg  { background: #FDE9E0; }
.summary-item.exp  { background: #FBE8E8; }
.sum-num { font-size: 48rpx; font-weight: bold; display: block; }
.sum-label { font-size: 24rpx; color: var(--color-text-secondary); display: block; margin-top: 4rpx; }

.empty-state { padding: 120rpx 0; text-align: center; }
.empty-icon { font-size: 72rpx; display: block; margin-bottom: 16rpx; }
.empty-text { color: var(--color-text-tertiary); font-size: 28rpx; }

.table { background: var(--color-surface); border-radius: var(--radius-lg); overflow: hidden; box-shadow: var(--shadow-card); }
.table-header { display: flex; padding: 24rpx; background: #f9f9f9; border-bottom: 1rpx solid rgba(0,0,0,0.06); }
.table-row { display: flex; padding: 20rpx 24rpx; border-bottom: 1rpx solid rgba(0,0,0,0.03); }
.th, .td { font-size: 26rpx; }
.name { flex: 3; }
.days { flex: 1; text-align: center; }
.count { flex: 1; text-align: center; }
.status { flex: 2; text-align: right; font-weight: 500; }
.th { color: var(--color-text-tertiary); font-size: 24rpx; }
.th.name { color: var(--color-text-tertiary); font-size: 24rpx; }
.status-WARNING { color: #D4A853; }
.status-URGENT  { color: #C27B5C; }
.status-EXPIRED { color: #A85A5A; }
</style>