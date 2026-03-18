param(
    [switch]$SkipApi,
    [switch]$NoOpen,
    [switch]$ApiOnly,
    [int]$ApiRetry = 3
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

function Get-UserToken {
    $token = $env:NOTION_TOKEN
    if ([string]::IsNullOrWhiteSpace($token)) {
        $token = [Environment]::GetEnvironmentVariable("NOTION_TOKEN", "User")
    }
    return $token
}

function Test-NotionApi {
    param(
        [string]$DatabaseId,
        [string]$NotionVersion,
        [string]$Token
    )

    if ([string]::IsNullOrWhiteSpace($Token)) {
        return $false
    }

    $headers = @{
        "Authorization" = "Bearer $Token"
        "Notion-Version" = $NotionVersion
    }

    try {
        Invoke-RestMethod -Method GET -Uri "https://api.notion.com/v1/databases/$DatabaseId" -Headers $headers -TimeoutSec 45 | Out-Null
        return $true
    } catch {
        return $false
    }
}

$config = Get-Content -Raw -Encoding UTF8 (Join-Path $PSScriptRoot "config.json") | ConvertFrom-Json
$databaseId = ([string]$config.database_id).Replace("-", "")
$notionVersion = if ($config.notion_version) { [string]$config.notion_version } else { "2022-06-28" }
$notionUrl = ""
if ($config.PSObject.Properties.Name -contains "notion_database_url") {
    $notionUrl = [string]$config.notion_database_url
}

Write-Host "[1/3] Generate CSV..." -ForegroundColor Cyan
& "$PSScriptRoot\generate_import_csv.ps1"
if (-not $?) {
    Write-Host "CSV generation failed." -ForegroundColor Red
    $global:LASTEXITCODE = 1
    return
}

$csvPath = Join-Path $PSScriptRoot "notion_import.csv"
Write-Host "CSV ready: $csvPath" -ForegroundColor Green

if ($SkipApi) {
    Write-Host "[2/3] API sync skipped by parameter." -ForegroundColor Yellow
} else {
    $token = Get-UserToken
    Write-Host "[2/3] Try API sync..." -ForegroundColor Cyan

    if ([string]::IsNullOrWhiteSpace($token)) {
        if ($ApiOnly) {
            Write-Host "NOTION_TOKEN missing. API-only mode cannot continue." -ForegroundColor Red
            $global:LASTEXITCODE = 1
            return
        }
        Write-Host "NOTION_TOKEN missing, fallback to CSV import." -ForegroundColor Yellow
    }
    else {
        $ok = $false
        $tryCount = [Math]::Max(1, $ApiRetry)
        for ($attempt = 1; $attempt -le $tryCount; $attempt++) {
            if (-not (Test-NotionApi -DatabaseId $databaseId -NotionVersion $notionVersion -Token $token)) {
                Write-Host "[API] precheck failed at attempt $attempt/$tryCount, continue to sync try" -ForegroundColor Yellow
            }

            try {
                Write-Host "[API] attempt $attempt/$tryCount" -ForegroundColor DarkCyan
                & "$PSScriptRoot\run-sync.ps1" -UpdateExisting
                $syncExit = [int]$global:LASTEXITCODE
                if ($? -and $syncExit -eq 0) {
                    $ok = $true
                    break
                }
            }
            catch {
                Write-Host "[API] attempt $attempt failed: $($_.Exception.Message)" -ForegroundColor Yellow
            }

            if ($attempt -lt $tryCount) {
                $waitSeconds = [Math]::Min(20, 3 * $attempt)
                Start-Sleep -Seconds $waitSeconds
            }
        }

        if ($ok) {
            Write-Host "API sync completed." -ForegroundColor Green
            Write-Host "[3/3] Done." -ForegroundColor Green
            $global:LASTEXITCODE = 0
            return
        }

        if ($ApiOnly) {
            Write-Host "API-only mode failed after retries." -ForegroundColor Red
            $global:LASTEXITCODE = 1
            return
        }

        Write-Host "API sync failed, fallback to CSV import." -ForegroundColor Yellow
    }
}

Write-Host "[3/3] Manual merge fallback" -ForegroundColor Cyan
Write-Host "In Notion: open DB -> ... -> Merge with CSV -> choose notion_import.csv" -ForegroundColor Yellow

if (-not $NoOpen) {
    Start-Process explorer.exe "/select,$csvPath" | Out-Null
    if (-not [string]::IsNullOrWhiteSpace($notionUrl)) {
        Start-Process $notionUrl | Out-Null
    }
}

$global:LASTEXITCODE = 0
