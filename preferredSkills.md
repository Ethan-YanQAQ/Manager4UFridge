# Preferred Skills for Manager4UFridge

> 自动生成于 2026-07-01 | 基于当前项目技术栈分析 | 运行 `/skill-advisor` 刷新

## 项目概况
- **类型**: 嵌入式 IoT + ML 训练 + 微信小程序（多子系统）
- **技术栈**: Python（算法/ML）、C（STM32 固件）、JavaScript/Vue3（小程序）、YAML
- **框架**: ultralytics YOLO、STM32H743 HAL + ESP-01S、uni-app + Vue 3 + Pinia、微信云开发
- **当前阶段**: 小程序开发中；STM32 WiFi 集成；Phase_0 算法完成；YOLO v6 训练完成（Teacher mAP50=0.958, Student mAP50=0.935）

---

## 强烈推荐 (★★★★★)

### /planning-with-files — 持久化任务规划
- **用途**: 多子系统项目管理，跨 session 追踪进度
- **使用场景**: 小程序开发阶段管理 (`task_plan_miniapp.md`)、YOLO 训练流水线、固件+云端+前端协同
- **状态**: ✅ 已在用

### /git-manager — 自动化 Git 全流程
- **用途**: Conventional Commits 提交、README 同步更新、.gitignore 检查
- **使用场景**: 训练状态变更后提交，新模块代码入库，大文件检查
- **状态**: ✅ 已在用

### /smarter-debug — 智能调试助手
- **用途**: 追溯 Last Known Good，日志驱动诊断，多语言调试
- **使用场景**: STM32 ESP-01S WiFi 调试、YOLO 检测流程、云函数报错、小程序运行时错误
- **状态**: ✅ 已在用

### /frontend-design — 前端/小程序 UI 设计
- **用途**: 微信小程序专用 UI 规范（rpx 单位、触控区域、卡片布局、骨架屏）
- **使用场景**: 库存页面新鲜度色标、历史时间线、首页统计卡片
- **状态**: ⬜ 已安装，推荐立即采用

### /code-review — 代码审查
- **用途**: 多语言 diff 审查，检查正确性和简化机会
- **使用场景**: 云函数、Phase_0 算法改动、STM32 固件修改提交前审查

### /verify — 变更验证
- **用途**: 确认修改实际生效
- **使用场景**: 改完 detector.py/iou_matcher.py 后跑 MOCK 模式验证；改完小程序页面后确认编译通过

---

## 推荐 (★★★☆☆)

### /simplify — 代码简化重构
- **用途**: Python 算法去复杂化，C 固件去冗余，Vue 组件精简
- **使用场景**: 定期清理 Phase_0 模块、精简云函数逻辑

### /fewer-permission-prompts — 减少权限弹窗
- **用途**: 扫描 transcript，自动添加项目特定 allowlist
- **使用场景**: 随项目扩展持续优化权限配置

### /update-config — 管理 settings.json
- **用途**: 权限配置、hooks 设置、环境变量管理
- **使用场景**: 为小程序开发添加新权限，配置 hook

### /deep-research — 深度调研
- **用途**: 多源搜索 + 引用报告
- **使用场景**: STM32 INT8 量化方案调研、微信云开发最佳实践、MQTT 协议细节

### /daymade-skill:skills-search — 搜索社区 skill
- **用途**: 发现和安装新 skill
- **使用场景**: 搜索嵌入式开发、小程序相关 skill

---

## 按需使用 (★★☆☆☆)

| Skill | 用途 | 触发场景 |
|-------|------|----------|
| `/security-review` | 安全审计 | 云函数上线前、MQTT 认证配置 |
| `/loop` | 定时任务 | 轮询远程训练进度 |
| `/claude-api` | API 参考 | 未来 AI 菜谱推荐功能 |
| `/daymade-skill:skill-creator` | 创建自定义 skill | 制作 STM32 专用 skill |
| `/daymade-skill:skill-reviewer` | Skill 质量审查 | 优化自定义 skill |
| `/init` | 初始化 CLAUDE.md | 子目录文档创建 |

---

## 如何使用

在 Claude Code 中输入 `/` 然后选择 skill 名称即可调用。
部分 skill 会自动触发，无需手动调用（如 `planning-with-files` 在每次提交和写入时自动激活）。

## 已安装的自定义 Skill

| Skill | 位置 | 状态 |
|-------|------|------|
| `planning-with-files` | `~/.claude/skills/` | ✅ 项目在用 |
| `git-manager` | `~/.claude/skills/` | ✅ 项目在用 |
| `smarter-debug` | `~/.claude/skills/` | ✅ 项目在用 |
| `frontend-design` | `~/.claude/skills/` | ⬜ 推荐采用 |
| `skill-advisor` | `~/.claude/skills/` | 🆕 本次创建 |
| `daymade-skill` | plugin | ✅ 已安装 |

## 安装更多 Skill

- 浏览官方市场：`/plugin`
- 搜索社区 skill：`/skills-search`
