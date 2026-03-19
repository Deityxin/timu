param(
    [switch]$DryRun,
    [switch]$UpdateExisting,
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

    if ($null -eq $Object) {
        return $Default
    }

    $prop = $Object.PSObject.Properties[$Name]
    if ($null -eq $prop) {
        return $Default
    }

    return $prop.Value
}

function Split-TagString {
    param([string]$Value)

    if ([string]::IsNullOrWhiteSpace($Value)) {
        return @()
    }

    return @($Value -split '[|,;]' | ForEach-Object { $_.Trim() } | Where-Object { $_ } | Select-Object -Unique)
}

function Invoke-NotionApi {
    param(
        [string]$Method,
        [string]$Url,
        [hashtable]$Headers,
        [object]$Body = $null,
        [int]$RetryCount = 5,
        [string]$Operation = ""
    )

    $attempt = 0
    while ($true) {
        try {
            if ($null -eq $Body) {
                return Invoke-RestMethod -Method $Method -Uri $Url -Headers $Headers
            }

            $jsonBody = $Body | ConvertTo-Json -Depth 20 -Compress
            return Invoke-RestMethod -Method $Method -Uri $Url -Headers $Headers -Body $jsonBody -ContentType "application/json"
        }
        catch {
            $attempt++
            $response = $_.Exception.Response
            $statusCode = 0
            if ($response -and $response.StatusCode) {
                $statusCode = [int]$response.StatusCode
            }

            $retryAfterSeconds = 0
            if ($response -and $response.Headers) {
                $retryAfterRaw = [string]$response.Headers["Retry-After"]
                if (-not [string]::IsNullOrWhiteSpace($retryAfterRaw)) {
                    [void][int]::TryParse($retryAfterRaw, [ref]$retryAfterSeconds)
                }
            }

            $messageText = [string]$_.Exception.Message
            if ($_.ErrorDetails -and -not [string]::IsNullOrWhiteSpace($_.ErrorDetails.Message)) {
                $messageText = [string]$_.ErrorDetails.Message
            }
            if ($null -eq $messageText) {
                $messageText = ""
            }
            if ($messageText.Length -gt 600) {
                $messageText = $messageText.Substring(0, 600) + "..."
            }

            $isTransientStatus = $statusCode -in @(408, 409, 425, 429, 500, 502, 503, 504)
            $isTransientMessage = $messageText -match "timed out|timeout|temporarily|remote host|forcibly closed|connection reset|ssl connection could not be established|ssl handshake|强迫关闭|连接被重置|无法连接|name resolution"

            if (($isTransientStatus -or $isTransientMessage) -and $attempt -le $RetryCount) {
                $baseDelay = [Math]::Min(30, [int][Math]::Pow(2, [Math]::Min($attempt, 5)))
                $jitter = Get-Random -Minimum 0 -Maximum 1000
                $sleepSeconds = [Math]::Min(30, $baseDelay + [int][Math]::Floor($jitter / 400.0))
                if ($statusCode -eq 429 -and $retryAfterSeconds -gt 0) {
                    $sleepSeconds = [Math]::Min(60, [Math]::Max(1, $retryAfterSeconds))
                }

                $opText = if ([string]::IsNullOrWhiteSpace($Operation)) { "notion_api" } else { $Operation }
                Write-Host "[RETRY][$opText] $Method status=$statusCode attempt=$attempt/$RetryCount wait=${sleepSeconds}s" -ForegroundColor Yellow
                Start-Sleep -Seconds $sleepSeconds
                continue
            }

            $errorType = "NON_RETRYABLE"
            switch ($statusCode) {
                401 { $errorType = "AUTH" }
                403 { $errorType = "PERMISSION" }
                404 { $errorType = "NOT_FOUND" }
                400 { $errorType = "VALIDATION" }
                422 { $errorType = "VALIDATION" }
                429 { $errorType = "RATE_LIMIT" }
                default {
                    if ($isTransientStatus -or $isTransientMessage) {
                        $errorType = "TRANSIENT_EXHAUSTED"
                    }
                }
            }

            $opText = if ([string]::IsNullOrWhiteSpace($Operation)) { "notion_api" } else { $Operation }
            throw "[$errorType][$opText] $Method $Url failed (status=$statusCode): $messageText"
        }
    }
}

function Get-TitleText {
    param([object]$PropertyValue)

    if ($null -eq $PropertyValue -or $null -eq $PropertyValue.title) {
        return ""
    }

    return (($PropertyValue.title | ForEach-Object { $_.plain_text }) -join "").Trim()
}

function Get-ExistingKeyMap {
    param(
        [string]$DatabaseId,
        [string]$DedupeProperty,
        [hashtable]$Headers
    )

    $map = @{}
    $hasMore = $true
    $cursor = $null

    while ($hasMore) {
        $body = @{ page_size = 100 }
        if ($cursor) {
            $body.start_cursor = $cursor
        }

        $result = Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/databases/$DatabaseId/query" -Headers $Headers -Body $body -Operation "query_existing"
        foreach ($page in $result.results) {
            $propValue = Get-ObjectValue -Object $page.properties -Name $DedupeProperty
            if ($null -eq $propValue) {
                continue
            }

            $key = Get-TitleText -PropertyValue $propValue
            if ($key) {
                $map[$key] = $page.id
            }
        }

        $hasMore = [bool]$result.has_more
        $cursor = $result.next_cursor
    }

    return $map
}

function Get-DatabaseSchemaMap {
    param(
        [string]$DatabaseId,
        [hashtable]$Headers
    )

    $result = Invoke-NotionApi -Method "GET" -Url "https://api.notion.com/v1/databases/$DatabaseId" -Headers $Headers -Operation "fetch_schema"
    $map = @{}
    foreach ($property in $result.properties.PSObject.Properties) {
        $map[$property.Name] = [string]$property.Value.id
    }
    return $map
}

function New-NotionProperties {
    param(
        [hashtable]$Record,
        [object]$Config,
        [hashtable]$PropertyIdMap
    )

    $properties = @{}
    foreach ($column in $Config.columns.PSObject.Properties) {
        $rule = $column.Value
        $notionName = [string]$rule.notion_name
        if (-not $Record.ContainsKey($notionName)) {
            continue
        }
        if (-not $PropertyIdMap.ContainsKey($notionName)) {
            throw "Property missing in database schema: $notionName"
        }

        $value = [string]$Record[$notionName]
        if ([string]::IsNullOrWhiteSpace($value)) {
            continue
        }

        $propertyKey = $PropertyIdMap[$notionName]

        switch ([string]$rule.type) {
            "title" {
                $properties[$propertyKey] = @{ title = @(@{ text = @{ content = $value } }) }
            }
            "rich_text" {
                $properties[$propertyKey] = @{ rich_text = @(@{ text = @{ content = $value } }) }
            }
            "select" {
                $properties[$propertyKey] = @{ select = @{ name = $value } }
            }
            "multi_select" {
                $properties[$propertyKey] = @{ multi_select = @(Split-TagString -Value $value | ForEach-Object { @{ name = $_ } }) }
            }
            "date" {
                $properties[$propertyKey] = @{ date = @{ start = $value } }
            }
            default {
                throw "Unsupported property type: $($rule.type)"
            }
        }
    }

    return $properties
}

$configFile = Join-Path $PSScriptRoot $ConfigPath
if (-not (Test-Path $configFile)) {
    throw "Config file not found: $configFile"
}

$config = Get-Content -Raw -Encoding UTF8 $configFile | ConvertFrom-Json
$fieldIds = Get-ObjectValue -Object $config -Name "field_ids"
if ($null -eq $fieldIds) {
    throw "Config is missing field_ids"
}

$fieldTitle = [string](Get-ObjectValue -Object $fieldIds -Name "title")
$fieldType = [string](Get-ObjectValue -Object $fieldIds -Name "type")
$fieldDifficulty = [string](Get-ObjectValue -Object $fieldIds -Name "difficulty")
$fieldStatus = [string](Get-ObjectValue -Object $fieldIds -Name "status")
$fieldLastReview = [string](Get-ObjectValue -Object $fieldIds -Name "last_review")
$fieldNextReview = [string](Get-ObjectValue -Object $fieldIds -Name "next_review")
$fieldErrorTags = [string](Get-ObjectValue -Object $fieldIds -Name "error_tags")
$fieldBreakthrough = [string](Get-ObjectValue -Object $fieldIds -Name "breakthrough")

$databaseId = ([string]$config.database_id).Replace("-", "")
$notionVersion = if ($config.notion_version) { [string]$config.notion_version } else { "2022-06-28" }
$dedupeProperty = [string]$config.dedupe_property

if (-not $env:NOTION_TOKEN) {
    $userToken = [Environment]::GetEnvironmentVariable("NOTION_TOKEN", "User")
    if (-not [string]::IsNullOrWhiteSpace($userToken)) {
        $env:NOTION_TOKEN = $userToken
    }
}

if (-not $env:NOTION_TOKEN) {
    throw "NOTION_TOKEN is missing"
}

$headers = @{
    "Authorization" = "Bearer $($env:NOTION_TOKEN)"
    "Notion-Version" = $notionVersion
}

$propertyIdMap = Get-DatabaseSchemaMap -DatabaseId $databaseId -Headers $headers

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..\")).Path
$sourceDirs = @(Get-ObjectValue -Object $config -Name "auto_source_dirs" -Default @("bits/test", "bits/shiyan"))
$ignoreFileNames = @(Get-ObjectValue -Object $config -Name "auto_ignore_file_names" -Default @("tempCodeRunnerFile.cpp"))

$defaults = Get-ObjectValue -Object $config -Name "auto_default_values"
$defaultType = [string](Get-ObjectValue -Object $defaults -Name "type" -Default "default")
$defaultDifficulty = [string](Get-ObjectValue -Object $defaults -Name "difficulty" -Default "medium")
$defaultStatusDone = [string](Get-ObjectValue -Object $defaults -Name "status_done" -Default "done")
$defaultStatusTodo = [string](Get-ObjectValue -Object $defaults -Name "status_todo" -Default "todo")
$defaultBreakthrough = [string](Get-ObjectValue -Object $defaults -Name "breakthrough" -Default "Auto imported from local source file")

$records = @()
$existingIndices = @{}
foreach ($relativeDir in $sourceDirs) {
    $sourcePath = Join-Path $repoRoot $relativeDir
    if (-not (Test-Path $sourcePath)) {
        continue
    }

    $files = Get-ChildItem -Path $sourcePath -Filter "*.cpp" -File -Recurse
    foreach ($file in $files) {
        if ($ignoreFileNames -contains $file.Name) {
            continue
        }

        $idx = Get-NotionSyncNumericIndexFromBaseName -BaseName $file.BaseName
        if ($null -ne $idx) {
            $existingIndices[$idx] = $true
        }

        $relativePath = $file.FullName.Substring($repoRoot.Length).TrimStart('\\') -replace '\\', '/'
        $smart = Get-NotionSyncClassification -File $file -RelativePath $relativePath -DefaultType $defaultType -DefaultDifficulty $defaultDifficulty -DefaultStatusDone $defaultStatusDone -DefaultStatusTodo $defaultStatusTodo -DefaultBreakthrough $defaultBreakthrough -Config $config

        $records += @{
            $fieldTitle = $relativePath
            $fieldType = [string]$smart.type
            $fieldDifficulty = [string]$smart.difficulty
            $fieldStatus = [string]$smart.status
            $fieldLastReview = $file.LastWriteTime.ToString("yyyy-MM-dd")
            $fieldNextReview = $file.LastWriteTime.AddDays(2).ToString("yyyy-MM-dd")
            $fieldErrorTags = [string]$smart.tags
            $fieldBreakthrough = [string]$smart.breakthrough
        }
    }
}

$pendingRows = @(Get-NotionSyncLuoguPendingRows -Config $config -ExistingIndices $existingIndices)
foreach ($pending in $pendingRows) {
    $records += @{
        $fieldTitle = [string]$pending.title
        $fieldType = [string]$pending.type
        $fieldDifficulty = [string]$pending.difficulty
        $fieldStatus = [string]$pending.status
        $fieldLastReview = [string]$pending.last_review
        $fieldNextReview = [string]$pending.next_review
        $fieldErrorTags = [string]$pending.error_tags
        $fieldBreakthrough = [string]$pending.breakthrough
        "__legacy_title" = [string]$pending.legacy_title
    }
}

if ($records.Count -eq 0) {
    Write-Host "No .cpp files found to sync." -ForegroundColor Yellow
    $global:LASTEXITCODE = 0
    return
}

$existingMap = Get-ExistingKeyMap -DatabaseId $databaseId -DedupeProperty $dedupeProperty -Headers $headers

$created = 0
$updated = 0
$skipped = 0
$failed = 0
$migrated = 0
$errorSamples = New-Object System.Collections.Generic.List[string]

$records = $records | Sort-Object { $_[$fieldTitle] }
foreach ($record in $records) {
    $key = [string]$record[$fieldTitle]
    if ([string]::IsNullOrWhiteSpace($key)) {
        $skipped++
        continue
    }

    $properties = New-NotionProperties -Record $record -Config $config -PropertyIdMap $propertyIdMap
    if (-not $propertyIdMap.ContainsKey($dedupeProperty)) {
        $skipped++
        continue
    }
    if (-not $properties.ContainsKey($propertyIdMap[$dedupeProperty])) {
        $skipped++
        continue
    }

    $legacyTitle = ""
    if ($record.ContainsKey("__legacy_title")) {
        $legacyTitle = [string]$record["__legacy_title"]
    }

    $exists = $existingMap.ContainsKey($key)
    $legacyExists = (-not $exists) -and (-not [string]::IsNullOrWhiteSpace($legacyTitle)) -and $existingMap.ContainsKey($legacyTitle)
    $isMigratingTitle = $legacyExists
    $pageIdForUpdate = ""
    if ($exists) {
        $pageIdForUpdate = [string]$existingMap[$key]
    }
    elseif ($legacyExists) {
        $pageIdForUpdate = [string]$existingMap[$legacyTitle]
        $exists = $true
    }

    if ($DryRun) {
        if ($exists -and $UpdateExisting) {
            $updated++
            if ($isMigratingTitle) {
                Write-Host "[DRY-RUN] MIGRATE+UPDATE: $legacyTitle -> $key"
            }
            else {
                Write-Host "[DRY-RUN] UPDATE: $key"
            }
        }
        elseif ($exists) {
            $skipped++
            Write-Host "[DRY-RUN] SKIP: $key"
        }
        else {
            $created++
            Write-Host "[DRY-RUN] CREATE: $key"
        }
        continue
    }

    try {
        if ($exists -and $UpdateExisting) {
            $pageId = $pageIdForUpdate
            Invoke-NotionApi -Method "PATCH" -Url "https://api.notion.com/v1/pages/$pageId" -Headers $headers -Body @{ properties = $properties } -Operation "update_page" | Out-Null
            $updated++
            if ($isMigratingTitle) {
                $migrated++
                $existingMap.Remove($legacyTitle)
                $existingMap[$key] = $pageId
                Write-Host "[MIGRATED] $legacyTitle -> $key"
            }
            else {
                Write-Host "[UPDATED] $key"
            }
            Start-Sleep -Milliseconds 120
        }
        elseif ($exists) {
            $skipped++
            Write-Host "[SKIPPED] $key"
        }
        else {
            $createdResult = Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/pages" -Headers $headers -Body @{ parent = @{ database_id = $databaseId }; properties = $properties } -Operation "create_page"
            $newPageId = [string](Get-ObjectValue -Object $createdResult -Name "id" -Default "")
            if (-not [string]::IsNullOrWhiteSpace($newPageId)) {
                $existingMap[$key] = $newPageId
            }
            $created++
            Write-Host "[CREATED] $key"
            Start-Sleep -Milliseconds 120
        }
    }
    catch {
        $failed++
        $err = $_.Exception.Message
        if ([string]::IsNullOrWhiteSpace($err)) {
            $err = "unknown error"
        }
        Write-Host "[FAILED] $key -> $err" -ForegroundColor Yellow
        if ($errorSamples.Count -lt 5) {
            $errorSamples.Add("$key => $err")
        }
        continue
    }
}

Write-Host ""
Write-Host "Sync complete"
Write-Host "Created: $created"
Write-Host "Updated: $updated"
Write-Host "Skipped: $skipped"
Write-Host "Failed: $failed"
Write-Host "Migrated titles: $migrated"
Write-Host "Scanned: $($records.Count)"

if ($errorSamples.Count -gt 0) {
    Write-Host "Sample errors:" -ForegroundColor Yellow
    foreach ($item in $errorSamples) {
        Write-Host " - $item" -ForegroundColor Yellow
    }
}

$global:LASTEXITCODE = if ($failed -gt 0) { 1 } else { 0 }
