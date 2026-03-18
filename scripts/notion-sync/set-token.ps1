param(
    [string]$Token
)

$ErrorActionPreference = "Stop"

Write-Host "Setup NOTION_TOKEN for current session and user env" -ForegroundColor Cyan

if ([string]::IsNullOrWhiteSpace($Token)) {
    $Token = Read-Host "Input new token (must start with ntn_)"
}

if ([string]::IsNullOrWhiteSpace($Token)) {
    Write-Host "Token cannot be empty." -ForegroundColor Red
    $global:LASTEXITCODE = 1
    return
}

if (-not $Token.StartsWith("ntn_")) {
    Write-Host "Invalid token format. It must start with ntn_." -ForegroundColor Yellow
    $global:LASTEXITCODE = 1
    return
}

$env:NOTION_TOKEN = $Token
setx NOTION_TOKEN "$Token" | Out-Null

Write-Host "Done." -ForegroundColor Green
Write-Host "Current session is active; new terminals will also have it." -ForegroundColor Green
