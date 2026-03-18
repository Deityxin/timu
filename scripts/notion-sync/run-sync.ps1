param(
    [switch]$DryRun,
    [switch]$UpdateExisting,
    [switch]$UseCsv
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

if (-not $env:NOTION_TOKEN) {
    $userToken = [Environment]::GetEnvironmentVariable("NOTION_TOKEN", "User")
    if (-not [string]::IsNullOrWhiteSpace($userToken)) {
        $env:NOTION_TOKEN = $userToken
    }
}

if (-not $env:NOTION_TOKEN) {
    Write-Host "NOTION_TOKEN is missing." -ForegroundColor Yellow
    Write-Host 'Run once: setx NOTION_TOKEN "your_new_token"' -ForegroundColor Yellow
    $global:LASTEXITCODE = 1
    return
}

if (-not $UseCsv) {
    $global:LASTEXITCODE = 0
    & "$PSScriptRoot\sync_from_files.ps1" -DryRun:$DryRun -UpdateExisting:$UpdateExisting
    $childExit = [int]$global:LASTEXITCODE
    if ($? -and $childExit -eq 0) {
        $global:LASTEXITCODE = 0
        return
    }
    $global:LASTEXITCODE = 1
    return
}

$pythonCmd = $null
if (Get-Command py -ErrorAction SilentlyContinue) {
    $pythonCmd = "py"
}
elseif (Get-Command python -ErrorAction SilentlyContinue) {
    $pythonCmd = "python"
}
else {
    Write-Host "CSV mode requires python or py." -ForegroundColor Red
    $global:LASTEXITCODE = 1
    return
}

$args = @("sync_to_notion.py", "--config", "config.json")
if ($DryRun) {
    $args += "--dry-run"
}
if ($UpdateExisting) {
    $args += "--update-existing"
}

if ($pythonCmd -eq "py") {
    & py -3 @args
}
else {
    & python @args
}
