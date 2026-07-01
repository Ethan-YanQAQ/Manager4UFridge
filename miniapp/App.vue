<script>
export default {
  onLaunch: function() {
    wx.cloud.init({
      env: 'cloudbase-d2g76jjidb3acb8ba',
      traceUser: true
    })
  }
}
</script>

<style>
page {
  --color-bg:           #F9F6F0;
  --color-surface:      #FFFFFF;
  --color-text-primary: #2C2416;
  --color-text-secondary:#8B7E6E;
  --color-text-tertiary: #B8AD9E;
  --color-accent:       #7D9B76;
  --color-warning:      #D4A853;
  --color-urgent:       #C27B5C;
  --color-expired:      #A85A5A;
  --color-sage-light:   #E8EEE4;
  --color-cream:        #FCF9F2;
  --font-display:       'Georgia', serif;
  --font-body:          -apple-system, sans-serif;
  --font-mono:          'Courier New', monospace;
  --radius-sm:          12rpx;
  --radius-md:          20rpx;
  --radius-lg:          32rpx;
  --shadow-card:        0 2rpx 16rpx rgba(44,36,22,0.06);
  --ease-spring:        cubic-bezier(0.16, 1, 0.3, 1);

  background: var(--color-bg);
  font-family: var(--font-body);
  font-size: 28rpx;
  color: var(--color-text-primary);
  line-height: 1.6;
  font-synthesis: none;
}

@keyframes fadeInUp {
  from { opacity: 0; transform: translateY(32rpx); }
  to   { opacity: 1; transform: translateY(0); }
}
@keyframes shimmer {
  0%   { background-position: -400rpx 0; }
  100% { background-position: 400rpx 0; }
}
.animate-in {
  animation: fadeInUp 0.6s var(--ease-spring) both;
}
</style>
