$userDir = Join-Path $env:APPDATA "Code\User"
$kbPath = Join-Path $userDir "keybindings.json"

if (!(Test-Path $userDir)) {
  New-Item -ItemType Directory -Path $userDir -Force | Out-Null
}

# 备份
$ts = Get-Date -Format "yyyyMMdd-HHmmss"
$bk = Join-Path $userDir ("keybindings.backup-" + $ts + ".json")
if (Test-Path $kbPath) { Copy-Item $kbPath $bk -Force -ErrorAction SilentlyContinue }

# 读取现有快捷键
if (Test-Path $kbPath) {
  try { $arr = Get-Content $kbPath -Raw | ConvertFrom-Json } catch { $arr = @() }
} else { $arr = @() }
if ($null -eq $arr) { $arr = @() }
if ($arr.GetType().Name -ne 'Object[]') { $arr = @($arr) }

# 移除我们要占用的组合，避免重复与冲突
$occupied = @(
  "ctrl+shift+space",
  "ctrl+alt+1",
  "ctrl+alt+e",
  "ctrl+alt+n"
)
$arr = @($arr | Where-Object { -not ($null -ne $_.key -and $_.key -in $occupied) })

# 注入我们的快捷键
$bindings = @(
  @{ key = "ctrl+shift+space"; command = "-editor.action.triggerParameterHints"; when = "editorTextFocus" },
  @{ key = "ctrl+shift+space"; command = "workbench.action.tasks.runTask"; args = "一键: 考试模式"; when = "true" },
  @{ key = "ctrl+alt+1"; command = "workbench.action.tasks.runTask"; args = "一键: 正常模式"; when = "true" },
  @{ key = "ctrl+alt+e"; command = "workbench.action.tasks.runTask"; args = "一键: 考试模式"; when = "true" },
  @{ key = "ctrl+alt+n"; command = "workbench.action.tasks.runTask"; args = "一键: 正常模式"; when = "true" }
)

$final = @($arr + $bindings)
($final | ConvertTo-Json -Depth 8) | Set-Content -Path $kbPath -Encoding UTF8
Write-Host "User keybindings updated. Backup: $bk"