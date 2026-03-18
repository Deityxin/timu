# Notion 全自动同步（刷题库）

## 你现在已有的文件

- `sync_from_files.ps1`：零手动核心脚本（默认）
- `sync_to_notion.py`：CSV 同步脚本（可选）
- `run-sync.ps1`：一键运行脚本
- `config.json`：当前可用配置（已填你的数据库 ID）
- `notion_import.csv`：自动生成的导入文件（默认 CSV 数据源）
- `input.csv`：CSV 样例（可手动参考）

## 一次性准备（只做一次）

1. 确认你已经在 Notion 中把 Integration 添加到题库数据库（共享/连接）。
2. 安全设置 Token（推荐）：

   ```powershell
   .\set-token.ps1
   ```

   或手动执行：

   ```powershell
   setx NOTION_TOKEN "你的新Token"
   ```

3. 关闭并重新打开一个终端。

## 每次同步怎么做（零手动默认）

在 `scripts/notion-sync` 目录执行：

```powershell
.\run-sync.ps1 -DryRun
```

先演练（不写入），确认无误后执行：

```powershell
.\run-sync.ps1
```

脚本会自动扫描 `bits/test` 和 `bits/shiyan` 下的 `.cpp` 文件并同步到 Notion。

## 智能分类规则（已内置）

- 根据文件名/路径关键词自动识别题型（如 `dp`、`dijkstra`、`kmp`、`sieve`、`二分`、`贪心`）。
- 文件名/路径提示优先于正文噪声，降低误判（例如变量名偶然命中关键词）。
- 根据代码行数自动估计难度：短代码偏 `简单`，超长代码偏 `困难`。
- 文件名含 `未完成` / `todo` 自动标记为 `待做` 并附加错误标签。
- 文件名含 `修改` / `xiugai` 自动附加 `复盘修改` 标签。
- 可在 `config.json` 的 `auto_keyword_rules` 和 `auto_type_breakthrough_map` 自定义规则。

## 洛谷 105-200 待做计划（自动并入）

- 已内置 `luogu_pending_plan`：默认把 105-200 号计划题写入 Notion，状态为 `待做`。
- 这些记录会按学习阶段自动分配题型：`排序与模拟` → `前缀和与差分`
   → `并查集` → `线段树` → `背包 DP` → `最短路` → `LCA` → `快速幂`。
- 若对应编号已存在本地解题文件（例如 `bits/test/137.cpp`），会自动跳过该计划题，避免重复。
- 计划配置可在 `config.json` 的 `luogu_pending_plan` 修改（区间、分段题型、难度、突破口）。

## 如果你想“已存在就更新”

```powershell
.\run-sync.ps1 -UpdateExisting
```

## CSV 模式（可选）

只有你明确想从 CSV 导入时才用：

```powershell
.\run-sync.ps1 -UseCsv -DryRun
```

CSV 模式依赖 Python 3.9+。

`-UseCsv` 会先自动执行 `generate_import_csv.ps1`，再按 `config.json` 里的 `csv_path` 同步。

## 直接导入 Notion（推荐）

如果你想手动导入、并确保完全匹配这 8 列：

- 题号/标题
- 题型
- 难度
- 状态
- 最后复习
- 下次复习
- 错误标签
- 一句话突破口

执行：

```powershell
.\generate_import_csv.ps1
```

会生成：`notion_import.csv`（UTF-8 BOM，适合 Notion 导入）。

Notion 里操作：

1. 打开题库数据库
2. 右上角 `...` -> `Merge with CSV`（或导入 CSV）
3. 选择 `scripts/notion-sync/notion_import.csv`
4. 确认列名自动匹配为上述 8 列

## 以后固定使用流程（推荐）

每次刷题后只执行一条命令：

```powershell
.\one-click-sync.ps1
```

或直接双击运行：

- [scripts/notion-sync/run-notion-sync.bat](scripts/notion-sync/run-notion-sync.bat)
- [run-notion-sync.bat](run-notion-sync.bat)

它会自动：

1. 生成最新 `notion_import.csv`
2. 尝试 API 更新（可用就自动同步）
3. API 不稳定时自动降级：打开 CSV 所在目录 + 打开 Notion 页面，等你点一次 `Merge with CSV`

每周一次（提升识别精度）：

1. 找出识别不准的文件名
2. 在 `config.json` 里补 `auto_keyword_rules`
3. 重新执行 `generate_import_csv.ps1` 并再次导入

如果你希望每天全自动同步（无人值守，走 API），可以注册定时任务：

```powershell
.\register-one-click-task.ps1 -StartTime "22:30" -ApiRetry 4 `
   -RepeatEveryHours 2 -NotifyOnSuccess $true
```

说明：该任务会以 `ApiOnly + NoOpen` 模式运行，不弹窗、不中断；若 API 当次不可达，会按重试次数自动重试，并在当天后续时段（例如每 2 小时）继续自动重试。

新增：

- 每次定时运行都会写日志到 `scripts/notion-sync/logs/`（文件名如 `sync-20260318-223000.log`）
- 最近一次状态写到 `scripts/notion-sync/logs/last-status.json`
- 失败时会尝试发送 Windows 通知（优先 Toast，失败则回退 `msg.exe`）
- 成功通知默认为开启，但同一天只发第一次成功通知，避免刷屏

手动查看最近状态：

```powershell
Get-Content .\logs\last-status.json
```

建议：

- 你主流程优先用 CSV 导入；API 同步只作为备用
- 若文件名里有 `todo`、`temp`、`xiugai`，会自动加对应状态/标签
- 如果你希望更精准，可在文件里保留模板 include（如 `templates/dsu.hpp`、`templates/lca.hpp`），分类器会更容易识别

## 设置为每天自动同步（可选）

在 `scripts/notion-sync` 执行：

```powershell
.\register-sync-task.ps1 -StartTime "22:30"
```

默认任务名为 `Notion题库自动同步`，每天 22:30 自动运行。

## CSV 列说明（列名必须一致）

- 题号/标题
- 题型
- 难度
- 状态
- 最后复习（格式：YYYY-MM-DD）
- 下次复习（格式：YYYY-MM-DD）
- 错误标签（多标签可用 `|` 或 `,` 分隔）
- 一句话突破口

## 常见报错

- `未检测到环境变量 NOTION_TOKEN`：说明还没设置 token 或终端未重开。
- `HTTP 401`：token 无效，去 Notion 重新轮换 token。
- `HTTP 403`：Integration 没有题库权限，回数据库共享里重新添加 Integration。
- `HTTP 404`：database_id 错误，检查 `config.json` 中的 `database_id`。
- `CSV 模式需要 Python`：只在加了 `-UseCsv` 时才会报，默认零手动模式不需要 Python。
