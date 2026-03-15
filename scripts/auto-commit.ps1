param(
    [string]$RepoPath = "d:\timu",
    [switch]$Push,
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

    $logPath = Join-Path $logRoot "auto-commit.log"
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

    $statusLines = git status --porcelain=v1
    if ($LASTEXITCODE -ne 0) {
        throw "git status failed"
    }

    if (-not $statusLines) {
        Write-Log "No changes detected. Nothing to do."
        exit 0
    }

    if ($DryRun) {
        Write-Log "Changes detected. Dry run only, no commit created."
        $statusLines | ForEach-Object { Write-Log "PENDING: $_" }
        exit 0
    }

    Write-Log "Changes detected. Starting automatic commit."
    git add -A
    if ($LASTEXITCODE -ne 0) {
        throw "git add failed"
    }

    git diff --cached --quiet --ignore-submodules --
    if ($LASTEXITCODE -eq 0) {
        Write-Log "No staged changes after git add -A. Nothing to do."
        exit 0
    }
    if ($LASTEXITCODE -ne 1) {
        throw "git diff --cached check failed"
    }

    $stamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $message = "chore(auto): daily backup $stamp"
    git commit -m $message
    if ($LASTEXITCODE -ne 0) {
        throw "git commit failed"
    }

    Write-Log "Created commit: $message"

    if ($Push) {
        git push origin HEAD
        if ($LASTEXITCODE -ne 0) {
            throw "git push failed"
        }
        Write-Log "Push completed."
    }
}
catch {
    Write-Log "ERROR: $($_.Exception.Message)"
    throw
}
finally {
    Pop-Location
}