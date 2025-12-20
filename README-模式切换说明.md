# 模式切换使用说明（Windows + VS Code）

## 快速使用
- 考试模式（关闭联想，保留括号自动补全）
  - 快捷键：Ctrl+Shift+Space 或 Ctrl+Alt+E
  - 任务：Ctrl+Shift+P → Tasks: Run Task → 一键: 考试模式
  - 命令行：
    ```pwsh
    pwsh -File "d:\timu\scripts\toggle-exam.ps1" -Mode exam -ShowNotice
    ```
- 正常模式（恢复联想与参数提示）
  - 快捷键：Ctrl+Alt+1 或 Ctrl+Alt+N
  - 任务：Ctrl+Shift+P → Tasks: Run Task → 一键: 正常模式
  - 命令行：
    ```pwsh
    pwsh -File "d:\timu\scripts\toggle-exam.ps1" -Mode normal -ShowNotice
    ```

## 切换后有什么提示
- 会弹出“模式切换成功”的系统弹窗（多重兜底：WinForms → WScript → 打开文件 → 终端警告）。
- 会写入文件：`d:\timu\.vscode\MODE.notice.txt`（包含当前模式说明）。
- 会写入标记文件：`d:\timu\.vscode\MODE.exam` 或 `MODE.normal`。
- 不会自动重载窗口（如需手动）：Ctrl+Shift+P → Developer: Reload Window。

## 设置内容概览
- 考试模式（profiles/exam.json）：
  - 关闭：`editor.quickSuggestions`、`editor.suggestOnTriggerCharacters`、`editor.inlineSuggest.enabled`、`editor.parameterHints.enabled`、`editor.snippetSuggestions`、`editor.hover.enabled`
  - C/C++ 扩展：`C_Cpp.autocomplete = "Disabled"`、`C_Cpp.intelliSenseEngine = "Disabled"`
  - 保留：`editor.autoClosingBrackets = "always"`、`editor.autoClosingQuotes = "always"`、括号配对可视化
- 正常模式（profiles/normal.json）：
  - 恢复上述联想/提示为开启，并将 C/C++ 扩展改回 `Default`

## 快捷键位置
- 已写入“用户级”快捷键：`%APPDATA%\Code\User\keybindings.json`
- 工作区级快捷键文件已移除，避免冲突。

## 使用 VS Code Profiles（可选）
- 已提供两套可导入配置：
  - `profiles/exam.code-profile`（考试模式）
  - `profiles/normal.code-profile`（正常模式）
- 导入方式：`Ctrl+Shift+P` → `Profiles: Import Profile...` → 选择相应 `.code-profile`

## 备份位置
- 每次切换会备份当前工作区设置到：`d:\timu\.vscode\backup-YYYYMMDD-HHMMSS\settings.json`

## 故障排查
- 快捷键无响应：
  - 打开“键盘快捷方式”（Ctrl+K Ctrl+S），使用“记录按键”检查是否映射到 `workbench.action.tasks.runTask`，参数为对应任务。
  - 试备用组合：Ctrl+Alt+E / Ctrl+Alt+N。
  - 直接运行任务：Ctrl+Shift+P → Tasks: Run Task → 选择“一键”任务。
- 没有弹窗：
  - 查看 `d:\timu\.vscode\MODE.notice.txt` 是否已更新。
  - 查看是否存在 `MODE.exam` 或 `MODE.normal` 标记文件。
 - 脚本无法执行：
   - 设置执行策略：`Set-ExecutionPolicy -Scope CurrentUser RemoteSigned -Force`
   - 或先解除阻止：`Unblock-File -Path d:\timu\scripts\toggle-exam.ps1`
   - 需要签名的环境：参考 `scripts/README-执行策略与签名.md`

## 推荐扩展
- `ms-vscode.cpptools`（C/C++ 智能提示）
- `ms-vscode.powershell`（更佳的 PowerShell 体验）
