<template>
  <view class="page">
    <scroll-view scroll-y class="msg-list" :scroll-top="scrollTop" :scroll-into-view="scrollToView" enhanced :show-scrollbar="false" scroll-with-animation>
      <view v-if="messages.length === 0" class="empty-chat">
        <text class="empty-icon">🤖</text>
        <text class="empty-title">冰箱助手</text>
        <text class="empty-hint">询问你的冰箱里有什么、能做什么菜、需要买什么</text>
        <view class="quick-asks">
          <text v-for="q in quickQuestions" :key="q" class="quick-btn" @click="sendQuick(q)">{{ q }}</text>
        </view>
      </view>

      <view v-for="(msg, idx) in messages" :key="idx" :id="'msg-' + idx" class="msg-row" :class="msg.role === 'user' ? 'msg-row-right' : 'msg-row-left'">
        <view class="msg-bubble" :class="msg.role === 'user' ? 'bubble-right' : 'bubble-left'">
          <text class="msg-text">{{ msg.content }}</text>
          <text class="msg-time">{{ msg.time }}</text>
        </view>
      </view>

      <view v-if="thinking" class="msg-row msg-row-left">
        <view class="msg-bubble bubble-left thinking">
          <view class="dots"><view class="dot"></view><view class="dot"></view><view class="dot"></view></view>
        </view>
      </view>
    </scroll-view>

    <view class="input-bar">
      <input class="msg-input" v-model="inputText" placeholder="问冰箱..." confirm-type="send" @confirm="sendMsg" :disabled="thinking" />
      <view class="send-btn" @click="sendMsg" :class="{ disabled: !inputText || thinking }"><text>发送</text></view>
    </view>
  </view>
</template>

<script>
const STORAGE_KEY = 'chatHistory_v2'

export default {
  data() {
    return {
      messages: [],
      inputText: '',
      thinking: false,
      scrollTop: 0,
      scrollToView: '',
      quickQuestions: ['冰箱里有什么？', '今晚能做什么菜？', '需要买什么？', '哪些快过期了？']
    }
  },
  onLoad() {
    var saved = uni.getStorageSync(STORAGE_KEY)
    if (saved) this.messages = JSON.parse(saved)
  },
  methods: {
    sendQuick(q) { this.inputText = q; this.sendMsg() },
    async sendMsg() {
      if (!this.inputText.trim() || this.thinking) return
      var text = this.inputText.trim()
      this.inputText = ''
      var now = new Date()
      var t = String(now.getHours()).padStart(2,'0') + ':' + String(now.getMinutes()).padStart(2,'0')
      this.messages.push({ role: 'user', content: text, time: t })
      this.saveHistory()
      var self = this
      this.$nextTick(function() { self.scrollToView = 'msg-' + (self.messages.length - 1) })
      this.thinking = true
      try {
        var res = await wx.cloud.callFunction({
          name: 'aiAdvisor',
          data: { chat: true, message: text, history: this.messages.slice(-20) }
        })
        var reply = '抱歉，暂时无法回答。'
        if (res.result && res.result.ok && res.result.data) {
          reply = res.result.data.reply || JSON.stringify(res.result.data)
        }
        var t2 = String(now.getHours()).padStart(2,'0') + ':' + String(now.getMinutes()).padStart(2,'0')
        this.messages.push({ role: 'ai', content: reply, time: t2 })
      } catch (e) {
        console.error(e)
        var t3 = String(now.getHours()).padStart(2,'0') + ':' + String(now.getMinutes()).padStart(2,'0')
        this.messages.push({ role: 'ai', content: '网络错误，请重试', time: t3 })
      } finally {
        this.thinking = false
        this.saveHistory()
        var self2 = this
        this.$nextTick(function() { self2.scrollToView = 'msg-' + (self2.messages.length - 1) })
      }
    },
    saveHistory() {
      uni.setStorageSync(STORAGE_KEY, JSON.stringify(this.messages.slice(-40)))
    }
  }
}
</script>

<style scoped>
.page { display: flex; flex-direction: column; height: 100vh; margin: 0; padding: 0; box-sizing: border-box; background: var(--color-bg); }

.msg-list { flex: 1; padding: 20rpx 0 0 0; margin: 0; box-sizing: border-box; }
.msg-row { margin-bottom: 24rpx; padding: 0 40rpx; }

/* 消息行：用 text-align 控制左右 */
.msg-row { margin-bottom: 24rpx; }
.msg-row-right { text-align: right; }
.msg-row-left  { text-align: left;  }

/* 气泡：inline-block 跟随父级 text-align */
.msg-bubble { display: inline-block; max-width: 72%; padding: 16rpx 24rpx; border-radius: 20rpx; text-align: left; }
.bubble-right { background: var(--color-accent); color: #fff; border-bottom-right-radius: 6rpx; }
.bubble-left  { background: var(--color-surface); border-bottom-left-radius: 6rpx; box-shadow: var(--shadow-card); }

.msg-text { font-size: 28rpx; line-height: 1.6; display: block; }
.msg-time { font-size: 20rpx; opacity: 0.5; display: block; margin-top: 6rpx; }

/* 空状态 */
.empty-chat { text-align: center; padding: 80rpx 0; }
.empty-icon { font-size: 80rpx; display: block; }
.empty-title { font-size: 36rpx; font-weight: bold; display: block; margin: 16rpx 0 8rpx; }
.empty-hint { font-size: 24rpx; color: var(--color-text-tertiary); display: block; margin-bottom: 32rpx; }
.quick-asks { display: flex; flex-wrap: wrap; gap: 12rpx; justify-content: center; }
.quick-btn { padding: 12rpx 24rpx; background: var(--color-surface); border-radius: 24rpx; font-size: 24rpx; color: var(--color-accent); box-shadow: var(--shadow-card); }

/* 打字 */
.thinking { min-width: 100rpx; }
.dots { display: flex; gap: 8rpx; padding: 8rpx 0; }
.dot { width: 12rpx; height: 12rpx; border-radius: 50%; background: var(--color-text-tertiary); animation: dotBounce 0.6s infinite alternate; }
.dot:nth-child(2) { animation-delay: 0.2s; }
.dot:nth-child(3) { animation-delay: 0.4s; }
@keyframes dotBounce { to { transform: translateY(-10rpx); opacity: 0.3; } }

/* 输入 */
.input-bar { display: flex; align-items: center; padding: 16rpx 24rpx; padding-bottom: calc(16rpx + env(safe-area-inset-bottom)); background: var(--color-surface); border-top: 1rpx solid rgba(0,0,0,0.06); }
.msg-input { flex: 1; height: 72rpx; padding: 0 20rpx; background: var(--color-bg); border-radius: 36rpx; font-size: 28rpx; }
.send-btn { padding: 14rpx 28rpx; margin-left: 12rpx; background: var(--color-accent); border-radius: 36rpx; color: #fff; font-size: 26rpx; }
.send-btn.disabled { opacity: 0.4; }
</style>