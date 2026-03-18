param(
    [string]$OutputPath = "",
    [string]$ConfigPath = "config.json"
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

$classificationModule = Join-Path $PSScriptRoot "classification.shared.ps1"
if (-not (Test-Path $classificationModule)) {
    throw "Shared classification module not found: $classificationModule"
}
. $classificationModule

function Get-ObjectValue {
    param(
        [object]$Object,
        [string]$Name,
        [object]$Default = $null
    )

    if ($null -eq $Object) { return $Default }
    $prop = $Object.PSObject.Properties[$Name]
    if ($null -eq $prop) { return $Default }
    return $prop.Value
}

$configFile = Join-Path $PSScriptRoot $ConfigPath
if (-not (Test-Path $configFile)) {
    throw "Config file not found: $configFile"
}

$config = Get-Content -Raw -Encoding UTF8 $configFile | ConvertFrom-Json
$headers = Get-ObjectValue -Object $config -Name 'csv_export_headers'
if ($null -eq $headers) {
    $headers = [pscustomobject]@{
        title = "title"
        type = "type"
        difficulty = "difficulty"
        status = "status"
        last_review = "last_review"
        next_review = "next_review"
        error_tags = "error_tags"
        breakthrough = "breakthrough"
    }
}

$defaults = Get-ObjectValue -Object $config -Name 'auto_default_values' -Default ([pscustomobject]@{})
$defaultType = [string](Get-ObjectValue -Object $defaults -Name 'type' -Default 'default')
$defaultDifficulty = [string](Get-ObjectValue -Object $defaults -Name 'difficulty' -Default 'medium')
$defaultStatusDone = [string](Get-ObjectValue -Object $defaults -Name 'status_done' -Default 'done')
$defaultStatusTodo = [string](Get-ObjectValue -Object $defaults -Name 'status_todo' -Default 'todo')
$defaultBreakthrough = [string](Get-ObjectValue -Object $defaults -Name 'breakthrough' -Default 'Auto imported from local source file')

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..\")).Path
$sourceRelDirs = @(Get-ObjectValue -Object $config -Name 'auto_source_dirs' -Default @('bits/test', 'bits/shiyan'))
$scanDirs = @($sourceRelDirs | ForEach-Object { Join-Path $repoRoot $_ })
$ignoreNames = @(Get-ObjectValue -Object $config -Name 'auto_ignore_file_names' -Default @('tempCodeRunnerFile.cpp'))

$resolvedOutputPath = $OutputPath
if ([string]::IsNullOrWhiteSpace($resolvedOutputPath)) {
    $resolvedOutputPath = [string](Get-ObjectValue -Object $config -Name 'csv_path' -Default 'notion_import.csv')
}
if ([string]::IsNullOrWhiteSpace($resolvedOutputPath)) {
    $resolvedOutputPath = 'notion_import.csv'
}

$rows = New-Object System.Collections.Generic.List[object]
$existingIndices = @{}

foreach ($dir in $scanDirs) {
    if (-not (Test-Path $dir)) { continue }

    $files = Get-ChildItem -Path $dir -Filter '*.cpp' -File -Recurse
    foreach ($file in $files) {
        if ($ignoreNames -contains $file.Name) { continue }

        $idx = Get-NotionSyncNumericIndexFromBaseName -BaseName $file.BaseName
        if ($null -ne $idx) {
            $existingIndices[$idx] = $true
        }

        $relativePath = $file.FullName.Substring($repoRoot.Length).TrimStart('\\') -replace '\\', '/'

        $smart = Get-NotionSyncClassification -File $file -RelativePath $relativePath -DefaultType $defaultType -DefaultDifficulty $defaultDifficulty -DefaultStatusDone $defaultStatusDone -DefaultStatusTodo $defaultStatusTodo -DefaultBreakthrough $defaultBreakthrough -Config $config

        $lastReview = $file.LastWriteTime.ToString('yyyy-MM-dd')
        $nextReview = $file.LastWriteTime.AddDays(2).ToString('yyyy-MM-dd')

        $rows.Add([pscustomobject]@{
            ([string]$headers.title) = $relativePath
            ([string]$headers.type) = [string]$smart.type
            ([string]$headers.difficulty) = [string]$smart.difficulty
            ([string]$headers.status) = [string]$smart.status
            ([string]$headers.last_review) = $lastReview
            ([string]$headers.next_review) = $nextReview
            ([string]$headers.error_tags) = [string]$smart.tags
            ([string]$headers.breakthrough) = [string]$smart.breakthrough
        })
    }
}

$pendingRows = @(Get-NotionSyncLuoguPendingRows -Config $config -ExistingIndices $existingIndices)
foreach ($pending in $pendingRows) {
    $rows.Add([pscustomobject]@{
        ([string]$headers.title) = [string]$pending.title
        ([string]$headers.type) = [string]$pending.type
        ([string]$headers.difficulty) = [string]$pending.difficulty
        ([string]$headers.status) = [string]$pending.status
        ([string]$headers.last_review) = [string]$pending.last_review
        ([string]$headers.next_review) = [string]$pending.next_review
        ([string]$headers.error_tags) = [string]$pending.error_tags
        ([string]$headers.breakthrough) = [string]$pending.breakthrough
    })
}

$rows = $rows | Sort-Object ([string]$headers.title)
$csvLines = $rows | ConvertTo-Csv -NoTypeInformation
$target = Join-Path $PSScriptRoot $resolvedOutputPath
[System.IO.File]::WriteAllLines($target, $csvLines, [System.Text.UTF8Encoding]::new($true))

Write-Host "CSV generated: $target"
Write-Host "Rows: $($rows.Count)"
