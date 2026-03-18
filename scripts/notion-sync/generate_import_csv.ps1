param(
    [string]$OutputPath = "notion_import.csv",
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

    if ($null -eq $Object) { return $Default }
    $prop = $Object.PSObject.Properties[$Name]
    if ($null -eq $prop) { return $Default }
    return $prop.Value
}

function Split-Tags {
    param([string]$Value)

    if ([string]::IsNullOrWhiteSpace($Value)) { return @() }
    return @($Value -split '[|,;]' | ForEach-Object { $_.Trim() } | Where-Object { $_ } | Select-Object -Unique)
}

function Get-Label {
    param(
        [object]$Map,
        [string]$Key,
        [string]$Fallback
    )

    $value = Get-ObjectValue -Object $Map -Name $Key -Default $null
    if ($null -eq $value) { return $Fallback }
    return [string]$value
}

function Get-TypeKey {
    param([string]$Text)

    $scores = @{
        dp = 0
        graph = 0
        data_structure = 0
        tree = 0
        string = 0
        number_theory = 0
        binary_search = 0
        greedy = 0
        basic = 0
    }

    $rules = @(
        @{ key = 'dp'; weight = 4; pattern = '\b(dp\s*\[|dp\s*<|dp\s*=|dynamic\s*programming|state\s*transition)'; },
        @{ key = 'graph'; weight = 5; pattern = 'dijkstra|spfa|floyd|bellman|kruskal|prim|topological|\bedge\b|\badj\b'; },
        @{ key = 'graph'; weight = 3; pattern = '\bbfs\b|\bdfs\b|queue<|stack<'; },
        @{ key = 'data_structure'; weight = 6; pattern = 'templates/(segment_tree|lazy_segment_tree|fenwick|dsu|trie|sparse_table|monotonic_queue)'; },
        @{ key = 'data_structure'; weight = 4; pattern = 'segment\s*tree|fenwick|\bbit\b|dsu|union\s*find|trie|priority_queue'; },
        @{ key = 'tree'; weight = 5; pattern = 'templates/lca|\blca\b|binary\s*lifting|subtree|euler\s*tour|tree\s*dp'; },
        @{ key = 'string'; weight = 5; pattern = 'templates/kmp|\bkmp\b|manacher|z-?function|suffix\s*(array|automaton)|rolling\s*hash'; },
        @{ key = 'string'; weight = 3; pattern = '\bstring\b|getline\s*\('; },
        @{ key = 'number_theory'; weight = 5; pattern = 'templates/(sieve|fast_pow)|\bprime\b|sieve|gcd|lcm|mod\s*\d|pow\s*\(|phi|exgcd'; },
        @{ key = 'binary_search'; weight = 5; pattern = 'binary\s*search|lower_bound|upper_bound|while\s*\(\s*l\s*<=\s*r\s*\)|\bmid\s*='; },
        @{ key = 'greedy'; weight = 4; pattern = '\bgreedy\b|activity\s*selection|interval\s*scheduling'; },
        @{ key = 'basic'; weight = 3; pattern = 'sort\s*\(|two[-_ ]?pointer|prefix\s*sum|difference\s*array'; },
        @{ key = 'basic'; weight = 2; pattern = 'vector<|array<|for\s*\(|while\s*\('; }
    )

    foreach ($rule in $rules) {
        if ($Text -match $rule.pattern) {
            $scores[$rule.key] += [int]$rule.weight
        }
    }

    $bestKey = 'default'
    $bestScore = 0
    foreach ($entry in $scores.GetEnumerator()) {
        if ($entry.Value -gt $bestScore) {
            $bestScore = $entry.Value
            $bestKey = [string]$entry.Key
        }
    }

    return $bestKey
}

function Get-DifficultyKey {
    param(
        [int]$LineCount,
        [string]$Text,
        [string]$TypeKey
    )

    if ($Text -match '\bhard\b') { return 'hard' }
    if ($Text -match '\beasy\b') { return 'easy' }

    $score = 0
    if ($LineCount -ge 320) { $score += 3 }
    elseif ($LineCount -ge 220) { $score += 2 }
    elseif ($LineCount -le 70) { $score -= 1 }

    if ($Text -match 'for\s*\([^\)]*\)\s*\{?[\s\S]{0,180}for\s*\(') { $score += 1 }
    if ($Text -match 'while\s*\([^\)]*\)\s*\{?[\s\S]{0,180}while\s*\(') { $score += 1 }
    if ($Text -match '1e5|2e5|5e5|1e6|200000|1000000') { $score += 1 }
    if ($Text -match 'templates/(segment_tree|lazy_segment_tree|lca|dijkstra|sparse_table)') { $score += 1 }
    if ($Text -match 'bitmask|subset\s*dp|reroot|tarjan|dinic|min\s*cost\s*max\s*flow') { $score += 2 }

    if ($TypeKey -in @('data_structure', 'graph', 'tree') -and $LineCount -ge 140) { $score += 1 }

    if ($score -ge 4) { return 'hard' }
    if ($score -le 0) { return 'easy' }
    return 'medium'
}

$configFile = Join-Path $PSScriptRoot $ConfigPath
if (-not (Test-Path $configFile)) {
    throw "Config file not found: $configFile"
}

$config = Get-Content -Raw -Encoding UTF8 $configFile | ConvertFrom-Json

$fieldIds = Get-ObjectValue -Object $config -Name 'field_ids'
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

$typeLabels = Get-ObjectValue -Object $config -Name 'type_labels' -Default ([pscustomobject]@{})
$difficultyLabels = Get-ObjectValue -Object $config -Name 'difficulty_labels' -Default ([pscustomobject]@{})
$tagLabels = Get-ObjectValue -Object $config -Name 'tag_labels' -Default ([pscustomobject]@{})
$breakthroughMap = Get-ObjectValue -Object $config -Name 'auto_type_breakthrough_map' -Default ([pscustomobject]@{})

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

$rows = New-Object System.Collections.Generic.List[object]

foreach ($dir in $scanDirs) {
    if (-not (Test-Path $dir)) { continue }

    $files = Get-ChildItem -Path $dir -Filter '*.cpp' -File -Recurse
    foreach ($file in $files) {
        if ($ignoreNames -contains $file.Name) { continue }

        $relativePath = $file.FullName.Substring($repoRoot.Length).TrimStart('\\') -replace '\\', '/'

        $content = ''
        try { $content = Get-Content -Path $file.FullName -Raw -Encoding UTF8 } catch { $content = '' }

        $searchText = ($relativePath + ' ' + $file.BaseName + ' ' + $content).ToLowerInvariant()
        $lineCount = 0
        try { $lineCount = (Get-Content -Path $file.FullName -Encoding UTF8 | Measure-Object -Line).Lines } catch { $lineCount = 0 }

        $typeKey = Get-TypeKey -Text $searchText
        $difficultyKey = Get-DifficultyKey -LineCount $lineCount -Text $searchText -TypeKey $typeKey

        $typeValue = Get-Label -Map $typeLabels -Key $typeKey -Fallback $defaultType
        $difficultyValue = Get-Label -Map $difficultyLabels -Key $difficultyKey -Fallback $defaultDifficulty
        $statusValue = $defaultStatusDone
        $tags = New-Object System.Collections.Generic.List[string]

        if ($file.Name -match 'todo|temp') {
            $statusValue = $defaultStatusTodo
            $tags.Add((Get-Label -Map $tagLabels -Key 'todo' -Fallback 'todo'))
        }
        if ($lineCount -ge 260) {
            $tags.Add((Get-Label -Map $tagLabels -Key 'long_code' -Fallback 'long_code'))
        }

        $breakthroughValue = Get-Label -Map $breakthroughMap -Key $typeValue -Fallback $defaultBreakthrough

        $rules = @(Get-ObjectValue -Object $config -Name 'auto_keyword_rules' -Default @())
        foreach ($rule in $rules) {
            $pattern = [string](Get-ObjectValue -Object $rule -Name 'pattern' -Default '')
            if ([string]::IsNullOrWhiteSpace($pattern)) { continue }

            if ($searchText -match $pattern) {
                $overrideType = Get-ObjectValue -Object $rule -Name 'type' -Default $null
                if ($null -ne $overrideType) {
                    $typeValue = [string]$overrideType
                    $breakthroughValue = Get-Label -Map $breakthroughMap -Key $typeValue -Fallback $breakthroughValue
                }

                $overrideDifficulty = Get-ObjectValue -Object $rule -Name 'difficulty' -Default $null
                if ($null -ne $overrideDifficulty) {
                    $difficultyValue = [string]$overrideDifficulty
                }

                $overrideStatus = Get-ObjectValue -Object $rule -Name 'status' -Default $null
                if ($null -ne $overrideStatus) {
                    $statusValue = [string]$overrideStatus
                }

                $overrideTags = Get-ObjectValue -Object $rule -Name 'tags' -Default $null
                if ($null -ne $overrideTags) {
                    foreach ($tag in (Split-Tags -Value ([string]$overrideTags))) {
                        $tags.Add($tag)
                    }
                }

                $overrideBreakthrough = Get-ObjectValue -Object $rule -Name 'breakthrough' -Default $null
                if ($null -ne $overrideBreakthrough) {
                    $breakthroughValue = [string]$overrideBreakthrough
                }
            }
        }

        $lastReview = $file.LastWriteTime.ToString('yyyy-MM-dd')
        $nextReview = $file.LastWriteTime.AddDays(2).ToString('yyyy-MM-dd')
        $tagsFinal = (($tags | Select-Object -Unique) -join '|')

        $rows.Add([pscustomobject]@{
            ([string]$headers.title) = $relativePath
            ([string]$headers.type) = $typeValue
            ([string]$headers.difficulty) = $difficultyValue
            ([string]$headers.status) = $statusValue
            ([string]$headers.last_review) = $lastReview
            ([string]$headers.next_review) = $nextReview
            ([string]$headers.error_tags) = $tagsFinal
            ([string]$headers.breakthrough) = $breakthroughValue
        })
    }
}

$rows = $rows | Sort-Object ([string]$headers.title)
$csvLines = $rows | ConvertTo-Csv -NoTypeInformation
$target = Join-Path $PSScriptRoot $OutputPath
[System.IO.File]::WriteAllLines($target, $csvLines, [System.Text.UTF8Encoding]::new($true))

Write-Host "CSV generated: $target"
Write-Host "Rows: $($rows.Count)"
