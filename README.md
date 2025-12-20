# 题目刷题与环境总览（C++）

- 题单路线：`cpp-practice-roadmap.md`
- 每周计划：`cpp-weekly-plan.md`
- 模板目录：`templates/`（DSU、Fenwick、SegTree、Dijkstra、KMP、LCA、快速幂、筛）
- 模式切换说明：`README-模式切换说明.md`
- 脚本运行策略与签名：`scripts/README-执行策略与签名.md`
 - 题源平台：默认以洛谷（Luogu）为主，题号以 P 开头；其他平台可自行替换为等价题。

## 一键切换练习模式
- 考试模式（无联想，保留括号自动补全）：`Ctrl+Shift+Space`
- 正常模式（恢复联想）：`Ctrl+Alt+1`
- 任务入口：Ctrl+Shift+P → Tasks: Run Task → `一键: 考试模式` / `一键: 正常模式`

## 编译与运行
- 任务：`C++: Run Current File`（已配置，自动构建当前文件并运行）
- 命令行：
```pwsh
g++ -std=gnu++17 -O2 -Wall -Wextra -I d:\timu your_file.cpp -o your_file.exe
.\your_file.exe
```

## 题源平台约定
- 默认平台：洛谷（Luogu）。本仓库路线与示例优先给出洛谷链接与 P 题号。
- 平台替换：若你已有他平台题单，可按主题替换为等价的洛谷 P 题继续刷；或将洛谷题替换回你熟悉的平台，不影响仓库模板/任务使用。
- 计划文件：如 `cpp-weekly-plan.md` 与 `cpp-practice-roadmap.md` 出现多平台混合，可按需一键切为“纯洛谷版”，我也可以帮你统一迁移与校对。

## 快速起步
- 片段：在新文件中输入 `cp` → 回车，生成主程序骨架；输入 `inc-temp` 引入常用模板头。
- 模板示例：`templates/template_main.cpp`

## VS Code Profiles（可导入）
- `profiles/exam.code-profile`：考试模式配置
- `profiles/normal.code-profile`：正常模式配置
- 导入：Ctrl+Shift+P → `Profiles: Import Profile...` → 选择对应 `.code-profile`

## 常见问题速查
- 快捷键无效：已迁移到“用户级”快捷键。若仍无效，用“键盘快捷方式”中的“记录按键”确认是否被其他扩展占用；备用组合：`Ctrl+Alt+E / Ctrl+Alt+N`。
- 未见弹窗：脚本包含 WinForms → WScript → 打开 notice 文件 → 终端警告多级兜底；仍无提示时，手动查看 `.vscode/MODE.notice.txt` 与 `MODE.exam/MODE.normal` 标记。
- 脚本被阻止：见 `scripts/README-执行策略与签名.md`，设置执行策略或签名。
