param(
    [string]$RepoPath = "d:\timu",
    [switch]$Push,
    [switch]$DryRun
)

$ErrorActionPreference = "Stop"

function Get-FileCategory {
    param(
        [string]$Path
    )

    $normalized = ($Path -replace '\\', '/').ToLowerInvariant()
    if ($normalized -match '^bits/(test|shiyan|test01)/.*\.cpp$') { return "题解" }
    if ($normalized -match '^templates/.*\.(hpp|cpp|h)$') { return "模板" }
    if ($normalized -match '^scripts/.*\.ps1$') { return "脚本" }
    if ($normalized -match '(^|/)readme.*\.md$' -or $normalized -match '\.md$') { return "文档" }
    if ($normalized -match '^profiles/' -or $normalized -match '^\.vscode/') { return "配置" }
    if ($normalized -match '\.(cpp|hpp|h)$') { return "C++代码" }
    return "其他"
}

function Get-ChangeActionText {
    param(
        [hashtable]$Ops
    )

    $add = [int]($Ops["A"])
    $mod = [int]($Ops["M"])
    $del = [int]($Ops["D"])
    $ren = [int]($Ops["R"])

    if ($add -gt 0 -and $mod -eq 0 -and $del -eq 0 -and $ren -eq 0) { return "新增" }
    if ($del -gt 0 -and $add -eq 0 -and $mod -eq 0 -and $ren -eq 0) { return "清理" }
    if ($ren -gt 0 -and $add -eq 0 -and $mod -eq 0 -and $del -eq 0) { return "重命名" }
    return "更新"
}

function Get-AutoCommitMessage {
    $nameStatusLines = git diff --cached --name-status
    if ($LASTEXITCODE -ne 0) {
        throw "git diff --cached --name-status failed"
    }

    $numstatLines = git diff --cached --numstat
    if ($LASTEXITCODE -ne 0) {
        throw "git diff --cached --numstat failed"
    }

    $ops = @{ "A" = 0; "M" = 0; "D" = 0; "R" = 0 }
    $categoryCount = @{}
    $scopeRoots = @{}
    $changedFiles = New-Object System.Collections.Generic.List[string]

    foreach ($line in $nameStatusLines) {
        if ([string]::IsNullOrWhiteSpace($line)) { continue }

        $parts = $line -split "`t"
        if ($parts.Count -lt 2) { continue }

        $statusRaw = $parts[0]
        $status = if ($statusRaw.StartsWith("R")) { "R" } else { $statusRaw.Substring(0, 1) }
        if ($ops.ContainsKey($status)) {
            $ops[$status] = [int]$ops[$status] + 1
        }

        $path = if ($status -eq "R" -and $parts.Count -ge 3) { $parts[2] } else { $parts[1] }
        $changedFiles.Add("$status`t$path")

        $category = Get-FileCategory -Path $path
        if ($categoryCount.ContainsKey($category)) {
            $categoryCount[$category] = [int]$categoryCount[$category] + 1
        }
        else {
            $categoryCount[$category] = 1
        }

        $normalized = ($path -replace '\\', '/')
        $root = ($normalized -split '/')[0]
        if (-not [string]::IsNullOrWhiteSpace($root)) {
            $scopeRoots[$root] = $true
        }
    }

    $additions = 0
    $deletions = 0
    foreach ($line in $numstatLines) {
        if ([string]::IsNullOrWhiteSpace($line)) { continue }
        $parts = $line -split "`t"
        if ($parts.Count -lt 3) { continue }

        if ($parts[0] -ne "-") { $additions += [int]$parts[0] }
        if ($parts[1] -ne "-") { $deletions += [int]$parts[1] }
    }

    $sortedCategories = $categoryCount.GetEnumerator() |
        Sort-Object -Property Value -Descending

    $topCategories = @($sortedCategories | Select-Object -First 2 | ForEach-Object { $_.Key })
    if ($topCategories.Count -eq 0) {
        $topCategories = @("代码")
    }

    $categoryText = [string]::Join("与", $topCategories)
    $actionText = Get-ChangeActionText -Ops $ops
    $fileCount = $changedFiles.Count

    $subject = "chore(auto): ${actionText}${categoryText} (${fileCount} files, +${additions}/-${deletions})"

    $scopeText = ""
    if ($scopeRoots.Count -gt 0) {
        $scopeText = (($scopeRoots.Keys | Sort-Object) -join ", ")
    }

    $bodyLines = New-Object System.Collections.Generic.List[string]
    $bodyLines.Add("Auto-generated summary") | Out-Null
    if ($scopeText) {
        $bodyLines.Add("scope: $scopeText") | Out-Null
    }
    $bodyLines.Add("stats: $fileCount files, +$additions/-$deletions") | Out-Null
    $bodyLines.Add("") | Out-Null
    $bodyLines.Add("changed files:") | Out-Null

    $maxList = 20
    $index = 0
    foreach ($item in $changedFiles) {
        if ($index -ge $maxList) { break }
        $splitItem = $item -split "`t", 2
        $bodyLines.Add("- [$($splitItem[0])] $($splitItem[1])") | Out-Null
        $index++
    }

    if ($changedFiles.Count -gt $maxList) {
        $bodyLines.Add("- ... and $($changedFiles.Count - $maxList) more files") | Out-Null
    }

    return @{
        Subject = $subject
        Body = ($bodyLines -join "`n")
    }
}

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

    $commitMessage = Get-AutoCommitMessage
    $subject = $commitMessage.Subject
    $body = $commitMessage.Body
    git commit -m $subject -m $body
    if ($LASTEXITCODE -ne 0) {
        throw "git commit failed"
    }

    Write-Log "Created commit: $subject"

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