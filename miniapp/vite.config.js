import { defineConfig } from 'vite'
import uni from '@dcloudio/vite-plugin-uni'
import copyPlugin from 'vite-plugin-files-copy'

export default defineConfig({
  plugins: [
    uni(),
    copyPlugin({
      patterns: [
        { from: './cloudfunctions', to: './dist/dev/mp-weixin/cloudfunctions' }
      ]
    })
  ]
})
