param(
    [string]$CsvPath = "notion_import.csv",
    [string]$ConfigPath = "config.json",
    [switch]$NoArchive
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

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

function Split-Tags {
    param([string]$Value)

    if ([string]::IsNullOrWhiteSpace($Value)) { return @() }
    return @($Value -split '[|,;，；]' | ForEach-Object { $_.Trim() } | Where-Object { $_ } | Select-Object -Unique)
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

            $json = $Body | ConvertTo-Json -Depth 50 -Compress
            return Invoke-RestMethod -Method $Method -Uri $Url -Headers $Headers -Body $json -ContentType "application/json"
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

function Get-DatabaseSchema {
    param(
        [string]$DatabaseId,
        [hashtable]$Headers
    )

    $result = Invoke-NotionApi -Method "GET" -Url "https://api.notion.com/v1/databases/$DatabaseId" -Headers $Headers -Operation "fetch_schema"
    $map = @{}
    foreach ($property in $result.properties.PSObject.Properties) {
        $map[$property.Name] = @{
            id = [string]$property.Value.id
            type = [string]$property.Value.type
        }
    }
    return $map
}

function Set-AllPagesArchived {
    param(
        [string]$DatabaseId,
        [hashtable]$Headers
    )

    $archived = 0
    $cursor = $null
    do {
        $body = @{ page_size = 100 }
        if ($cursor) { $body.start_cursor = $cursor }

        $query = Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/databases/$DatabaseId/query" -Headers $Headers -Body $body -Operation "query_all"
        foreach ($page in $query.results) {
            Invoke-NotionApi -Method "PATCH" -Url "https://api.notion.com/v1/pages/$($page.id)" -Headers $Headers -Body @{ archived = $true } -Operation "archive_page" | Out-Null
            $archived++
            Start-Sleep -Milliseconds 120
        }

        $cursor = $query.next_cursor
    } while ($query.has_more)

    return $archived
}

$configFile = Join-Path $PSScriptRoot $ConfigPath
if (-not (Test-Path $configFile)) {
    throw "Config file not found: $configFile"
}

$csvFile = Join-Path $PSScriptRoot $CsvPath
if (-not (Test-Path $csvFile)) {
    throw "CSV file not found: $csvFile"
}

$config = Get-Content -Raw -Encoding UTF8 $configFile | ConvertFrom-Json
$fieldIds = Get-ObjectValue -Object $config -Name "field_ids"
$headersMap = Get-ObjectValue -Object $config -Name "csv_export_headers"

if ($null -eq $fieldIds -or $null -eq $headersMap) {
    throw "config.json missing field_ids or csv_export_headers"
}

$token = $env:NOTION_TOKEN
if ([string]::IsNullOrWhiteSpace($token)) {
    $token = [Environment]::GetEnvironmentVariable("NOTION_TOKEN", "User")
}
if ([string]::IsNullOrWhiteSpace($token)) {
    throw "NOTION_TOKEN is missing"
}

$databaseId = ([string]$config.database_id).Replace("-", "")
$notionVersion = if ($config.notion_version) { [string]$config.notion_version } else { "2022-06-28" }
$headers = @{
    "Authorization" = "Bearer $token"
    "Notion-Version" = $notionVersion
}

$schema = Get-DatabaseSchema -DatabaseId $databaseId -Headers $headers

$requiredProps = @(
    [string]$fieldIds.title,
    [string]$fieldIds.type,
    [string]$fieldIds.difficulty,
    [string]$fieldIds.status,
    [string]$fieldIds.last_review,
    [string]$fieldIds.next_review,
    [string]$fieldIds.error_tags,
    [string]$fieldIds.breakthrough
)

foreach ($propName in $requiredProps) {
    if (-not $schema.ContainsKey($propName)) {
        throw "Database missing property: $propName"
    }
}

$rows = Import-Csv -Path $csvFile -Encoding UTF8
if (-not $rows -or $rows.Count -eq 0) {
    throw "CSV has no rows"
}

$archivedCount = 0
if (-not $NoArchive) {
    $archivedCount = Set-AllPagesArchived -DatabaseId $databaseId -Headers $headers
}

$created = 0
foreach ($row in $rows) {
    $titleValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.title) -Default "")
    if ([string]::IsNullOrWhiteSpace($titleValue)) {
        continue
    }

    $typeValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.type) -Default "")
    $difficultyValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.difficulty) -Default "")
    $statusValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.status) -Default "")
    $lastReviewValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.last_review) -Default "")
    $nextReviewValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.next_review) -Default "")
    $tagsValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.error_tags) -Default "")
    $breakthroughValue = [string](Get-ObjectValue -Object $row -Name ([string]$headersMap.breakthrough) -Default "")

    $properties = @{}

    $properties[$schema[[string]$fieldIds.title].id] = @{ title = @(@{ text = @{ content = $titleValue } }) }

    if (-not [string]::IsNullOrWhiteSpace($typeValue)) {
        $properties[$schema[[string]$fieldIds.type].id] = @{ select = @{ name = $typeValue } }
    }
    if (-not [string]::IsNullOrWhiteSpace($difficultyValue)) {
        $properties[$schema[[string]$fieldIds.difficulty].id] = @{ select = @{ name = $difficultyValue } }
    }
    if (-not [string]::IsNullOrWhiteSpace($statusValue)) {
        $properties[$schema[[string]$fieldIds.status].id] = @{ select = @{ name = $statusValue } }
    }
    if (-not [string]::IsNullOrWhiteSpace($lastReviewValue)) {
        $properties[$schema[[string]$fieldIds.last_review].id] = @{ date = @{ start = $lastReviewValue } }
    }
    if (-not [string]::IsNullOrWhiteSpace($nextReviewValue)) {
        $properties[$schema[[string]$fieldIds.next_review].id] = @{ date = @{ start = $nextReviewValue } }
    }

    $tagItems = Split-Tags -Value $tagsValue
    if ($tagItems.Count -gt 0) {
        $properties[$schema[[string]$fieldIds.error_tags].id] = @{ multi_select = @($tagItems | ForEach-Object { @{ name = $_ } }) }
    }

    if (-not [string]::IsNullOrWhiteSpace($breakthroughValue)) {
        $properties[$schema[[string]$fieldIds.breakthrough].id] = @{ rich_text = @(@{ text = @{ content = $breakthroughValue } }) }
    }

    $body = @{
        parent = @{ database_id = $databaseId }
        properties = $properties
    }

    Invoke-NotionApi -Method "POST" -Url "https://api.notion.com/v1/pages" -Headers $headers -Body $body -Operation "create_page" | Out-Null
    $created++
    Write-Host "[CREATED] $titleValue"
    Start-Sleep -Milliseconds 120
}

Write-Host ""
Write-Host "Reimport complete"
Write-Host "Archived old pages: $archivedCount"
Write-Host "Created new pages: $created"
Write-Host "CSV rows: $($rows.Count)"
