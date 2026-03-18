param(
    [string]$TaskName = "Notion题库自动同步",
    [string]$StartTime = "22:30"
)

$ErrorActionPreference = "Stop"
$scriptDir = $PSScriptRoot
$runScript = Join-Path $scriptDir "run-sync.ps1"

if (-not (Test-Path $runScript)) {
    Write-Host "未找到 run-sync.ps1: $runScript" -ForegroundColor Red
    $global:LASTEXITCODE = 1
    return
}

if (-not $env:NOTION_TOKEN) {
    Write-Host "未检测到 NOTION_TOKEN。请先设置后再注册任务。" -ForegroundColor Yellow
    Write-Host '命令: setx NOTION_TOKEN "你的新Token"' -ForegroundColor Yellow
    $global:LASTEXITCODE = 1
    return
}

$action = New-ScheduledTaskAction -Execute "powershell.exe" -Argument "-NoProfile -ExecutionPolicy Bypass -File `"$runScript`""
$trigger = New-ScheduledTaskTrigger -Daily -At $StartTime
$settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable

Register-ScheduledTask -TaskName $TaskName -Action $action -Trigger $trigger -Settings $settings -Description "每天自动将 input.csv 同步到 Notion 题库" -Force | Out-Null

Write-Host "已注册计划任务: $TaskName" -ForegroundColor Green
Write-Host "执行时间: 每天 $StartTime" -ForegroundColor Green
Write-Host "你可在 任务计划程序 -> 任务计划程序库 中查看。" -ForegroundColor Green
