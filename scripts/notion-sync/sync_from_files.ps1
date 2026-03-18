param(
    [switch]$DryRun,
    [switch]$UpdateExisting,
    [string]$ConfigPath = "config.json"
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

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
        [int]$RetryCount = 3
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

            $messageText = [string]$_.Exception.Message
            $isTransientStatus = $statusCode -in @(408, 409, 425, 429, 500, 502, 503, 504)
            $isTransientMessage = $messageText -match "timed out|timeout|temporarily|remote host|forcibly closed|connection reset|ssl connection could not be established|ssl handshake|强迫关闭|连接被重置|无法连接|name resolution"

            if (($isTransientStatus -or $isTransientMessage) -and $attempt -le $RetryCount) {
                $sleepSeconds = [Math]::Min(20, [int][Math]::Pow(2, $attempt))
                Write-Host "[RETRY] $Method $Url attempt=$attempt wait=${sleepSeconds}s" -ForegroundColor Yellow
                Start-Sleep -Seconds $sleepSeconds
                continue
            }
            throw
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

        $result = Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/databases/$DatabaseId/query" -Headers $Headers -Body $body
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

    $result = Invoke-NotionApi -Method "GET" -Url "https://api.notion.com/v1/databases/$DatabaseId" -Headers $Headers
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

function Get-MappedBreakthrough {
    param(
        [string]$TypeName,
        [string]$Fallback,
        [object]$Config
    )

    $map = Get-ObjectValue -Object $Config -Name "auto_type_breakthrough_map"
    if ($null -eq $map) {
        return $Fallback
    }

    $mapped = Get-ObjectValue -Object $map -Name $TypeName -Default $null
    if ($null -eq $mapped) {
        return $Fallback
    }

    return [string]$mapped
}

function Get-TypeLabel {
    param(
        [string]$Key,
        [object]$Config,
        [string]$Fallback
    )

    $map = Get-ObjectValue -Object $Config -Name "type_labels"
    $value = Get-ObjectValue -Object $map -Name $Key -Default $null
    if ($null -eq $value) {
        return $Fallback
    }
    return [string]$value
}

function Get-DifficultyLabel {
    param(
        [string]$Key,
        [object]$Config,
        [string]$Fallback
    )

    $map = Get-ObjectValue -Object $Config -Name "difficulty_labels"
    $value = Get-ObjectValue -Object $map -Name $Key -Default $null
    if ($null -eq $value) {
        return $Fallback
    }
    return [string]$value
}

function Get-TagLabel {
    param(
        [string]$Key,
        [object]$Config,
        [string]$Fallback
    )

    $map = Get-ObjectValue -Object $Config -Name "tag_labels"
    $value = Get-ObjectValue -Object $map -Name $Key -Default $null
    if ($null -eq $value) {
        return $Fallback
    }
    return [string]$value
}

function Get-SmartClassification {
    param(
        [object]$File,
        [string]$RelativePath,
        [string]$DefaultType,
        [string]$DefaultDifficulty,
        [string]$DefaultStatusDone,
        [string]$DefaultStatusTodo,
        [string]$DefaultBreakthrough,
        [object]$Config
    )

    $searchText = ($RelativePath + " " + $File.BaseName).ToLowerInvariant()
    try {
        $fileText = (Get-Content -Path $File.FullName -Raw -Encoding UTF8).ToLowerInvariant()
        $searchText += " " + $fileText
    }
    catch {
        $fileText = ""
    }

    $isTodo = ($File.Name -like "*temp*") -or ($File.Name -like "*todo*")
    $lineCount = 0
    try {
        $lineCount = (Get-Content -Path $File.FullName -Encoding UTF8 | Measure-Object -Line).Lines
    }
    catch {
        $lineCount = 0
    }

    $typeKey = "default"
    if ($searchText -match "\bdp\b|dynamic programming") {
        $typeKey = "dp"
    }
    elseif ($searchText -match "dijkstra|spfa|floyd|graph|\bbfs\b|\bdfs\b|topo") {
        $typeKey = "graph"
    }
    elseif ($searchText -match "\blca\b|tree") {
        $typeKey = "tree"
    }
    elseif ($searchText -match "segment|fenwick|\bbit\b|dsu|trie|union find") {
        $typeKey = "data_structure"
    }
    elseif ($searchText -match "kmp|string|manacher|suffix") {
        $typeKey = "string"
    }
    elseif ($searchText -match "prime|sieve|gcd|lcm|pow|math") {
        $typeKey = "number_theory"
    }
    elseif ($searchText -match "binary search|lower_bound|upper_bound|mid") {
        $typeKey = "binary_search"
    }
    elseif ($searchText -match "greedy") {
        $typeKey = "greedy"
    }
    elseif ($searchText -match "sort|two[-_ ]?pointer") {
        $typeKey = "basic"
    }

    $difficultyKey = "medium"
    if ($lineCount -gt 220) {
        $difficultyKey = "hard"
    }
    elseif ($lineCount -gt 0 -and $lineCount -le 70) {
        $difficultyKey = "easy"
    }

    if ($searchText -match "\bhard\b") {
        $difficultyKey = "hard"
    }
    elseif ($searchText -match "\beasy\b") {
        $difficultyKey = "easy"
    }

    $typeValue = Get-TypeLabel -Key $typeKey -Config $Config -Fallback $DefaultType
    $difficultyValue = Get-DifficultyLabel -Key $difficultyKey -Config $Config -Fallback $DefaultDifficulty
    $statusValue = if ($isTodo) { $DefaultStatusTodo } else { $DefaultStatusDone }
    $tags = @()

    if ($isTodo) {
        $tags += Get-TagLabel -Key "todo" -Config $Config -Fallback "todo"
    }
    if ($lineCount -gt 220) {
        $tags += Get-TagLabel -Key "long_code" -Config $Config -Fallback "long_code"
    }

    $breakthroughValue = Get-MappedBreakthrough -TypeName $typeValue -Fallback $DefaultBreakthrough -Config $Config

    $rules = Get-ObjectValue -Object $Config -Name "auto_keyword_rules" -Default @()
    foreach ($rule in $rules) {
        $pattern = [string](Get-ObjectValue -Object $rule -Name "pattern" -Default "")
        if ([string]::IsNullOrWhiteSpace($pattern)) {
            continue
        }

        if ($searchText -match $pattern) {
            $typeOverride = Get-ObjectValue -Object $rule -Name "type" -Default $null
            if ($null -ne $typeOverride) {
                $typeValue = [string]$typeOverride
            }

            $difficultyOverride = Get-ObjectValue -Object $rule -Name "difficulty" -Default $null
            if ($null -ne $difficultyOverride) {
                $difficultyValue = [string]$difficultyOverride
            }

            $statusOverride = Get-ObjectValue -Object $rule -Name "status" -Default $null
            if ($null -ne $statusOverride) {
                $statusValue = [string]$statusOverride
            }

            $tagOverride = Get-ObjectValue -Object $rule -Name "tags" -Default $null
            if ($null -ne $tagOverride) {
                $tags += Split-TagString -Value ([string]$tagOverride)
            }

            $breakthroughOverride = Get-ObjectValue -Object $rule -Name "breakthrough" -Default $null
            if ($null -ne $breakthroughOverride) {
                $breakthroughValue = [string]$breakthroughOverride
            }
        }
    }

    return @{
        type = $typeValue
        difficulty = $difficultyValue
        status = $statusValue
        tags = (($tags | Select-Object -Unique) -join "|")
        breakthrough = $breakthroughValue
    }
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

        $relativePath = $file.FullName.Substring($repoRoot.Length).TrimStart('\\') -replace '\\', '/'
        $smart = Get-SmartClassification -File $file -RelativePath $relativePath -DefaultType $defaultType -DefaultDifficulty $defaultDifficulty -DefaultStatusDone $defaultStatusDone -DefaultStatusTodo $defaultStatusTodo -DefaultBreakthrough $defaultBreakthrough -Config $config

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

    $exists = $existingMap.ContainsKey($key)
    if ($DryRun) {
        if ($exists -and $UpdateExisting) {
            $updated++
            Write-Host "[DRY-RUN] UPDATE: $key"
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
            $pageId = $existingMap[$key]
            Invoke-NotionApi -Method "PATCH" -Url "https://api.notion.com/v1/pages/$pageId" -Headers $headers -Body @{ properties = $properties } | Out-Null
            $updated++
            Write-Host "[UPDATED] $key"
        }
        elseif ($exists) {
            $skipped++
            Write-Host "[SKIPPED] $key"
        }
        else {
            Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/pages" -Headers $headers -Body @{ parent = @{ database_id = $databaseId }; properties = $properties } | Out-Null
            $created++
            Write-Host "[CREATED] $key"
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
Write-Host "Scanned: $($records.Count)"

if ($errorSamples.Count -gt 0) {
    Write-Host "Sample errors:" -ForegroundColor Yellow
    foreach ($item in $errorSamples) {
        Write-Host " - $item" -ForegroundColor Yellow
    }
}

$global:LASTEXITCODE = if ($failed -gt 0) { 1 } else { 0 }
