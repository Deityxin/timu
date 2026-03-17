param(
    [string]$RepoPath = "d:\timu",
    [string]$TaskName = "timu-auto-push-pending",
    [int]$IntervalMinutes = 15
)

$ErrorActionPreference = "Stop"

if ($IntervalMinutes -le 0) {
    throw "IntervalMinutes must be greater than 0"
}

$scriptPath = Join-Path $RepoPath "scripts\auto-push-pending.ps1"
if (!(Test-Path $scriptPath)) {
    throw "Auto push script not found: $scriptPath"
}

$hiddenRunnerPath = Join-Path $RepoPath "scripts\run-hidden.vbs"
if (!(Test-Path $hiddenRunnerPath)) {
    throw "Hidden runner script not found: $hiddenRunnerPath"
}

$pwshPath = (Get-Command pwsh -ErrorAction Stop).Source
$startTime = (Get-Date).AddMinutes(1).ToString("HH:mm")
$taskCommand = @(
    'wscript.exe',
    ('"' + $hiddenRunnerPath + '"'),
    ('"' + $pwshPath + '"'),
    '-NoProfile',
    '-ExecutionPolicy',
    'Bypass',
    '-File',
    ('"' + $scriptPath + '"'),
    '-RepoPath',
    ('"' + $RepoPath + '"')
) -join ' '

schtasks /Create /TN $TaskName /SC MINUTE /MO $IntervalMinutes /ST $startTime /TR $taskCommand /RL LIMITED /F | Out-Null
if ($LASTEXITCODE -ne 0) {
    throw "schtasks create failed"
}

Write-Host "Registered scheduled task '$TaskName' every $IntervalMinutes minutes"