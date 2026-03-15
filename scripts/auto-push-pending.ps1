param(
    [string]$RepoPath = "d:\timu",
    [switch]$DryRun
)

$ErrorActionPreference = "Stop"

function Write-Log {
    param(
        [string]$Message
    )

    $logRoot = Join-Path $env:LOCALAPPDATA "timu\logs"
    if (!(Test-Path $logRoot)) {
        New-Item -ItemType Directory -Path $logRoot -Force | Out-Null
    }

    $logPath = Join-Path $logRoot "auto-push.log"
    $line = "[{0}] {1}" -f (Get-Date -Format "yyyy-MM-dd HH:mm:ss"), $Message
    Add-Content -Path $logPath -Value $line -Encoding UTF8
    Write-Host $line
}

if (!(Test-Path $RepoPath)) {
    throw "Repository path not found: $RepoPath"
}

Push-Location $RepoPath
try {
    if (!(Test-Path (Join-Path $RepoPath ".git"))) {
        throw "Not a git repository: $RepoPath"
    }

    $remoteUrl = git remote get-url origin 2>$null
    if ($LASTEXITCODE -ne 0 -or -not $remoteUrl) {
        Write-Log "No origin remote configured. Nothing to do."
        exit 0
    }

    $branch = git rev-parse --abbrev-ref HEAD
    if ($LASTEXITCODE -ne 0 -or -not $branch) {
        throw "git rev-parse failed"
    }

    git ls-remote --exit-code origin HEAD *> $null
    if ($LASTEXITCODE -ne 0) {
        Write-Log "Remote unavailable. Skip auto push."
        exit 0
    }

    $hasUpstream = $true
    git rev-parse --abbrev-ref --symbolic-full-name '@{u}' *> $null
    if ($LASTEXITCODE -ne 0) {
        $hasUpstream = $false
    }

    if ($hasUpstream) {
        $aheadText = git rev-list --count '@{u}..HEAD'
        if ($LASTEXITCODE -ne 0) {
            throw "git rev-list failed"
        }

        $aheadCount = [int]$aheadText
        if ($aheadCount -le 0) {
            Write-Log "No pending commits to push."
            exit 0
        }
    }

    if ($DryRun) {
        Write-Log "Pending push detected on branch $branch. Dry run only."
        exit 0
    }

    git push origin HEAD
    if ($LASTEXITCODE -ne 0) {
        throw "git push failed"
    }

    Write-Log "Push completed for branch $branch."
}
catch {
    Write-Log "ERROR: $($_.Exception.Message)"
    throw
}
finally {
    Pop-Location
}