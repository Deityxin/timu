param(
    [int]$ApiRetry = 4,
    [bool]$NotifyOnFail = $true,
    [bool]$NotifyOnSuccess = $false,
    [bool]$NotifySuccessFirstPerDay = $true,
    [string]$LogDir = "logs"
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

function Send-WindowsNotice {
    param(
        [string]$Title,
        [string]$Message
    )

    $sent = $false

    try {
        if (Get-Command New-BurntToastNotification -ErrorAction SilentlyContinue) {
            New-BurntToastNotification -Text $Title, $Message | Out-Null
            $sent = $true
        }
    }
    catch {
    }

    if (-not $sent) {
        try {
            $userName = $env:USERNAME
            if (-not [string]::IsNullOrWhiteSpace($userName)) {
                & msg.exe $userName "$Title`n$Message" | Out-Null
                $sent = $true
            }
        }
        catch {
        }
    }

    return $sent
}

$logRoot = Join-Path $PSScriptRoot $LogDir
if (-not (Test-Path $logRoot)) {
    New-Item -Path $logRoot -ItemType Directory -Force | Out-Null
}

$startedAt = Get-Date
$stamp = $startedAt.ToString("yyyyMMdd-HHmmss")
$logFile = Join-Path $logRoot "sync-$stamp.log"
$statusFile = Join-Path $logRoot "last-status.json"
$successNotifyStateFile = Join-Path $logRoot "success-notify-state.json"

"=== Notion auto sync started: $($startedAt.ToString("yyyy-MM-dd HH:mm:ss")) ===" | Out-File -FilePath $logFile -Encoding UTF8

$exitCode = 1

try {
    & "$PSScriptRoot\one-click-sync.ps1" -NoOpen -ApiOnly -ApiRetry $ApiRetry *>&1 | Tee-Object -FilePath $logFile -Append | Out-Null
    $exitCode = [int]$global:LASTEXITCODE
}
catch {
    $exitCode = 1
    "Unhandled error: $($_.Exception.Message)" | Tee-Object -FilePath $logFile -Append | Out-Null
}

$endedAt = Get-Date
$durationSeconds = [Math]::Round(($endedAt - $startedAt).TotalSeconds, 2)
"=== Notion auto sync ended: $($endedAt.ToString("yyyy-MM-dd HH:mm:ss")), exit=$exitCode, duration=${durationSeconds}s ===" | Tee-Object -FilePath $logFile -Append | Out-Null

$noticeSent = $false
$noticeType = "none"
$noticeReason = "disabled_or_not_needed"

if ($exitCode -ne 0 -and $NotifyOnFail) {
    $title = "Notion 自动同步失败"
    $message = "请查看日志: $logFile"
    $sent = Send-WindowsNotice -Title $title -Message $message
    if (-not $sent) {
        "Notification: unavailable" | Tee-Object -FilePath $logFile -Append | Out-Null
        Write-Host "Notification not available. Check log: $logFile" -ForegroundColor Yellow
        $noticeType = "fail"
        $noticeReason = "unavailable"
    }
    else {
        "Notification: sent" | Tee-Object -FilePath $logFile -Append | Out-Null
        $noticeSent = $true
        $noticeType = "fail"
        $noticeReason = "sent"
    }
}
elseif ($exitCode -eq 0 -and $NotifyOnSuccess) {
    $shouldNotifySuccess = $true
    if ($NotifySuccessFirstPerDay) {
        $today = $endedAt.ToString("yyyy-MM-dd")
        $lastDate = ""
        if (Test-Path $successNotifyStateFile) {
            try {
                $state = Get-Content -Raw -Encoding UTF8 $successNotifyStateFile | ConvertFrom-Json
                if ($null -ne $state -and $state.PSObject.Properties.Name -contains "date") {
                    $lastDate = [string]$state.date
                }
            }
            catch {
                $lastDate = ""
            }
        }

        if ($lastDate -eq $today) {
            $shouldNotifySuccess = $false
            $noticeType = "success"
            $noticeReason = "skipped_already_sent_today"
            "Notification: skipped (already sent today)" | Tee-Object -FilePath $logFile -Append | Out-Null
        }
    }

    if ($shouldNotifySuccess) {
        $title = "Notion 自动同步成功"
        $message = "日志: $logFile"
        $sent = Send-WindowsNotice -Title $title -Message $message
        if ($sent) {
            "Notification: sent" | Tee-Object -FilePath $logFile -Append | Out-Null
            $noticeSent = $true
            $noticeType = "success"
            $noticeReason = "sent"

            if ($NotifySuccessFirstPerDay) {
                $successState = [ordered]@{
                    date = $endedAt.ToString("yyyy-MM-dd")
                    timestamp = $endedAt.ToString("yyyy-MM-dd HH:mm:ss")
                    log_file = $logFile
                }
                $successState | ConvertTo-Json -Depth 5 | Set-Content -Path $successNotifyStateFile -Encoding UTF8
            }
        }
        else {
            "Notification: unavailable" | Tee-Object -FilePath $logFile -Append | Out-Null
            $noticeType = "success"
            $noticeReason = "unavailable"
        }
    }
}

$statusObj = [ordered]@{
    timestamp = $endedAt.ToString("yyyy-MM-dd HH:mm:ss")
    exit_code = $exitCode
    duration_seconds = $durationSeconds
    log_file = $logFile
    notice_sent = $noticeSent
    notice_type = $noticeType
    notice_reason = $noticeReason
    notify_success_first_per_day = $NotifySuccessFirstPerDay
}

$statusObj | ConvertTo-Json -Depth 5 | Set-Content -Path $statusFile -Encoding UTF8

$global:LASTEXITCODE = $exitCode