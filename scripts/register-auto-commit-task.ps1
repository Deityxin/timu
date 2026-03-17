param(
    [string]$RepoPath = "d:\timu",
    [string]$TaskName = "timu-daily-auto-commit",
    [string]$Time = "21:00",
    [switch]$Push
)

$ErrorActionPreference = "Stop"

$scriptPath = Join-Path $RepoPath "scripts\auto-commit.ps1"
if (!(Test-Path $scriptPath)) {
    throw "Auto commit script not found: $scriptPath"
}

$hiddenRunnerPath = Join-Path $RepoPath "scripts\run-hidden.vbs"
if (!(Test-Path $hiddenRunnerPath)) {
    throw "Hidden runner script not found: $hiddenRunnerPath"
}

$pwshPath = (Get-Command pwsh -ErrorAction Stop).Source
$runUser = [System.Security.Principal.WindowsIdentity]::GetCurrent().Name

$timeParts = $Time.Split(":")
if ($timeParts.Count -ne 2) {
    throw "Time must be in HH:mm format. Example: 21:00"
}

$hour = [int]$timeParts[0]
$minute = [int]$timeParts[1]
$triggerTime = [datetime]::Today.AddHours($hour).AddMinutes($minute)

$runnerArguments = @(
    ('"' + $hiddenRunnerPath + '"'),
    ('"' + $pwshPath + '"'),
    '-NoProfile',
    '-ExecutionPolicy',
    'Bypass',
    '-File',
    ('"' + $scriptPath + '"'),
    '-RepoPath',
    ('"' + $RepoPath + '"')
)

if ($Push) {
    $runnerArguments += '-Push'
}

$action = New-ScheduledTaskAction -Execute "wscript.exe" -Argument ($runnerArguments -join ' ')
$trigger = New-ScheduledTaskTrigger -Daily -At $triggerTime
$settings = New-ScheduledTaskSettingsSet -StartWhenAvailable -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries
$principal = New-ScheduledTaskPrincipal -UserId $runUser -LogonType Interactive -RunLevel Limited

if (Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue) {
    Unregister-ScheduledTask -TaskName $TaskName -Confirm:$false
}

Register-ScheduledTask -TaskName $TaskName -Action $action -Trigger $trigger -Settings $settings -Principal $principal -Description "Daily auto-commit for $RepoPath"

Write-Host "Registered scheduled task '$TaskName' at $Time for $runUser"