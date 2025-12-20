param(
    [ValidateSet("exam", "normal")]
    [string]$Mode = "exam",
    [switch]$ShowNotice
)

$ws = "d:\timu"
$vscode = Join-Path $ws ".vscode"
$settingsPath = Join-Path $vscode "settings.json"
$profilePath = Join-Path (Join-Path $ws "profiles") ("$Mode.json")
$modeMarkerExam = Join-Path $vscode "MODE.exam"
$modeMarkerNormal = Join-Path $vscode "MODE.normal"

if (!(Test-Path $vscode)) { New-Item -ItemType Directory -Path $vscode -Force | Out-Null }
if (!(Test-Path $profilePath)) { Write-Error "Profile file not found: $profilePath"; exit 1 }

$ts = Get-Date -Format "yyyyMMdd-HHmmss"
$bkDir = Join-Path $vscode ("backup-" + $ts)
New-Item -ItemType Directory -Path $bkDir -Force | Out-Null
if (Test-Path $settingsPath) { Copy-Item $settingsPath -Destination (Join-Path $bkDir "settings.json") -ErrorAction SilentlyContinue }

Copy-Item $profilePath -Destination $settingsPath -Force
if ($Mode -eq "exam") {
    if (Test-Path $modeMarkerNormal) { Remove-Item $modeMarkerNormal -Force -ErrorAction SilentlyContinue }
    Set-Content -Path $modeMarkerExam -Value "exam" -Encoding UTF8
} else {
    if (Test-Path $modeMarkerExam) { Remove-Item $modeMarkerExam -Force -ErrorAction SilentlyContinue }
    Set-Content -Path $modeMarkerNormal -Value "normal" -Encoding UTF8
}
Write-Host "Switched to '$Mode' mode. Backup: $bkDir"

if ($ShowNotice) {
    $noticePath = Join-Path $vscode "MODE.notice.txt"
    $msg = if ($Mode -eq "exam") { "当前为【考试模式】：已关闭自动联想，保留括号自动补全。" } else { "当前为【正常模式】：已开启自动联想与参数提示。" }
    Set-Content -Path $noticePath -Value $msg -Encoding UTF8
    
    # 弹窗优先：WinForms -> WScript.Shell Popup -> 打开提醒文件 -> 终端警告
    $shown = $false
    try {
        Add-Type -AssemblyName System.Windows.Forms -ErrorAction Stop
        [void][System.Windows.Forms.MessageBox]::Show($msg, "模式切换成功", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
        $shown = $true
    } catch {}

    if (-not $shown) {
        try {
            $wshell = New-Object -ComObject Wscript.Shell
            [void]$wshell.Popup($msg, 0, "模式切换成功", 64)
            $shown = $true
        } catch {}
    }

    if (-not $shown) {
        try {
            if (Get-Command code -ErrorAction SilentlyContinue) {
                code --reuse-window "$noticePath" | Out-Null
            } else {
                Invoke-Item "$noticePath"
            }
            $shown = $true
        } catch {}
    }

    if (-not $shown) {
        Write-Warning "`n################################################"
        Write-Warning $msg
        Write-Warning "################################################`n"
    }
}
