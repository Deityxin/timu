param(
    [string]$TaskName = "Notion一键日更",
    [string]$StartTime = "22:30",
    [int]$ApiRetry = 4,
    [int]$RepeatEveryHours = 2,
    [bool]$NotifyOnSuccess = $true
)

$ErrorActionPreference = "Stop"
$scriptDir = $PSScriptRoot
$entry = Join-Path $scriptDir "auto-sync-job.ps1"

if (-not (Test-Path $entry)) {
    Write-Host "entry script not found: $entry" -ForegroundColor Red
    $global:LASTEXITCODE = 1
    return
}

$notifySuccessLiteral = if ($NotifyOnSuccess) { "`$true" } else { "`$false" }
$action = New-ScheduledTaskAction -Execute "powershell.exe" -Argument "-NoProfile -ExecutionPolicy Bypass -File `"$entry`" -ApiRetry $ApiRetry -NotifyOnFail `$true -NotifyOnSuccess $notifySuccessLiteral -NotifySuccessFirstPerDay `$true"

$repeat = [Math]::Max(1, $RepeatEveryHours)
$baseTime = [datetime]::ParseExact($StartTime, "HH:mm", [System.Globalization.CultureInfo]::InvariantCulture)
$triggers = @()
for ($hourOffset = 0; $hourOffset -lt 24; $hourOffset += $repeat) {
    $timeLabel = $baseTime.AddHours($hourOffset).ToString("HH:mm")
    $triggers += New-ScheduledTaskTrigger -Daily -At $timeLabel
}

$triggerCount = $triggers.Count
$settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable

Register-ScheduledTask -TaskName $TaskName -Action $action -Trigger $triggers -Settings $settings -Description "每天自动 API 同步 Notion（多时段自动重试）" -Force | Out-Null

Write-Host "task registered: $TaskName" -ForegroundColor Green
Write-Host "time: $StartTime" -ForegroundColor Green
Write-Host "mode: API-only unattended with logs+notify, retries=$ApiRetry" -ForegroundColor Green
Write-Host "success notify: $NotifyOnSuccess (first success per day only)" -ForegroundColor Green
Write-Host "repeat: every $repeat hour(s), slots=$triggerCount" -ForegroundColor Green
Write-Host "log path: $scriptDir\logs" -ForegroundColor Green
