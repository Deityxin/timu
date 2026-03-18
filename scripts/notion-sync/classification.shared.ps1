function Get-NotionSyncObjectValue {
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

function Split-NotionSyncTags {
    param([string]$Value)

    if ([string]::IsNullOrWhiteSpace($Value)) {
        return @()
    }

    return @($Value -split '[|,;，；]' | ForEach-Object { $_.Trim() } | Where-Object { $_ } | Select-Object -Unique)
}

function Get-NotionSyncLabel {
    param(
        [object]$Map,
        [string]$Key,
        [string]$Fallback
    )

    $value = Get-NotionSyncObjectValue -Object $Map -Name $Key -Default $null
    if ($null -eq $value) {
        return $Fallback
    }

    return [string]$value
}

function Get-NotionSyncTypeKey {
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
        @{ key = 'dp'; weight = 4; pattern = '\b(dp\s*\[|dp\s*<|dp\s*=|dynamic\s*programming|state\s*transition)' },
        @{ key = 'dp'; weight = 6; pattern = '背包|区间\s*dp|树形\s*dp|数位\s*dp|状压\s*dp|digit\s*dp|interval\s*dp|knapsack' },
        @{ key = 'graph'; weight = 5; pattern = 'dijkstra|spfa|floyd|bellman|kruskal|prim|topological|\bedge\b|\badj\b' },
        @{ key = 'graph'; weight = 6; pattern = '图论|最短路|最小生成树|拓扑|连通分量|强连通|割点|桥|二分图' },
        @{ key = 'graph'; weight = 3; pattern = '\bbfs\b|\bdfs\b|queue<|stack<' },
        @{ key = 'data_structure'; weight = 6; pattern = 'templates/(segment_tree|lazy_segment_tree|fenwick|dsu|trie|sparse_table|monotonic_queue)' },
        @{ key = 'data_structure'; weight = 4; pattern = 'segment\s*tree|fenwick|\bbit\b|dsu|union\s*find|trie|priority_queue' },
        @{ key = 'data_structure'; weight = 6; pattern = '线段树|树状数组|并查集|单调栈|单调队列|优先队列|堆|平衡树' },
        @{ key = 'tree'; weight = 5; pattern = 'templates/lca|\blca\b|binary\s*lifting|subtree|euler\s*tour|tree\s*dp' },
        @{ key = 'tree'; weight = 6; pattern = '最近公共祖先|树链剖分|重链剖分|倍增|树上' },
        @{ key = 'string'; weight = 5; pattern = 'templates/kmp|\bkmp\b|manacher|z-?function|suffix\s*(array|automaton)|rolling\s*hash' },
        @{ key = 'string'; weight = 3; pattern = '\bstring\b|getline\s*\(' },
        @{ key = 'string'; weight = 6; pattern = '字符串|字典树|前缀函数|失配|ac自动机|后缀数组|后缀自动机|哈希' },
        @{ key = 'number_theory'; weight = 5; pattern = 'templates/(sieve|fast_pow)|\bprime\b|sieve|gcd|lcm|mod\s*\d|pow\s*\(|phi|exgcd' },
        @{ key = 'number_theory'; weight = 6; pattern = '数论|同余|逆元|筛法|质因数|快速幂|欧拉函数|费马小定理|中国剩余定理' },
        @{ key = 'binary_search'; weight = 5; pattern = 'binary\s*search|lower_bound|upper_bound|while\s*\(\s*l\s*<=\s*r\s*\)|\bmid\s*=' },
        @{ key = 'binary_search'; weight = 6; pattern = '二分|答案二分|二分答案' },
        @{ key = 'greedy'; weight = 4; pattern = '\bgreedy\b|activity\s*selection|interval\s*scheduling' },
        @{ key = 'greedy'; weight = 6; pattern = '贪心|区间调度|局部最优' },
        @{ key = 'basic'; weight = 3; pattern = 'sort\s*\(|two[-_ ]?pointer|prefix\s*sum|difference\s*array' },
        @{ key = 'basic'; weight = 5; pattern = '模拟|枚举|前缀和|差分|双指针|滑动窗口' },
        @{ key = 'basic'; weight = 2; pattern = 'vector<|array<|for\s*\(|while\s*\(' }
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

function Get-NotionSyncDifficultyKey {
    param(
        [int]$LineCount,
        [string]$Text,
        [string]$TypeKey
    )

    if ($Text -match '\bhard\b') {
        return 'hard'
    }

    if ($Text -match '\beasy\b') {
        return 'easy'
    }

    $score = 0
    if ($LineCount -ge 320) {
        $score += 3
    }
    elseif ($LineCount -ge 220) {
        $score += 2
    }
    elseif ($LineCount -le 70) {
        $score -= 1
    }

    if ($Text -match 'for\s*\([^\)]*\)\s*\{?[\s\S]{0,180}for\s*\(') {
        $score += 1
    }
    if ($Text -match 'while\s*\([^\)]*\)\s*\{?[\s\S]{0,180}while\s*\(') {
        $score += 1
    }
    if ($Text -match '1e5|2e5|5e5|1e6|200000|1000000') {
        $score += 1
    }
    if ($Text -match 'templates/(segment_tree|lazy_segment_tree|lca|dijkstra|sparse_table)') {
        $score += 1
    }
    if ($Text -match 'bitmask|subset\s*dp|reroot|tarjan|dinic|min\s*cost\s*max\s*flow') {
        $score += 2
    }
    if ($TypeKey -in @('data_structure', 'graph', 'tree') -and $LineCount -ge 140) {
        $score += 1
    }

    if ($score -ge 4) {
        return 'hard'
    }
    if ($score -le 0) {
        return 'easy'
    }

    return 'medium'
}

function Get-NotionSyncClassification {
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

    $typeLabels = Get-NotionSyncObjectValue -Object $Config -Name 'type_labels' -Default ([pscustomobject]@{})
    $difficultyLabels = Get-NotionSyncObjectValue -Object $Config -Name 'difficulty_labels' -Default ([pscustomobject]@{})
    $tagLabels = Get-NotionSyncObjectValue -Object $Config -Name 'tag_labels' -Default ([pscustomobject]@{})
    $breakthroughMap = Get-NotionSyncObjectValue -Object $Config -Name 'auto_type_breakthrough_map' -Default ([pscustomobject]@{})

    $content = ''
    try {
        $content = Get-Content -Path $File.FullName -Raw -Encoding UTF8
    }
    catch {
        $content = ''
    }

    $searchText = ($RelativePath + ' ' + $File.BaseName + ' ' + $content).ToLowerInvariant()
    $hintText = ($RelativePath + ' ' + $File.BaseName).ToLowerInvariant()

    $lineCount = 0
    try {
        $lineCount = (Get-Content -Path $File.FullName -Encoding UTF8 | Measure-Object -Line).Lines
    }
    catch {
        $lineCount = 0
    }

    $hintTypeKey = Get-NotionSyncTypeKey -Text $hintText
    $typeKey = if ($hintTypeKey -ne 'default') { $hintTypeKey } else { Get-NotionSyncTypeKey -Text $searchText }
    $difficultyKey = Get-NotionSyncDifficultyKey -LineCount $lineCount -Text $searchText -TypeKey $typeKey

    $typeValue = Get-NotionSyncLabel -Map $typeLabels -Key $typeKey -Fallback $DefaultType
    $difficultyValue = Get-NotionSyncLabel -Map $difficultyLabels -Key $difficultyKey -Fallback $DefaultDifficulty
    $statusValue = $DefaultStatusDone
    $tags = New-Object System.Collections.Generic.List[string]

    if ($File.Name -match 'todo|temp') {
        $statusValue = $DefaultStatusTodo
        $tags.Add((Get-NotionSyncLabel -Map $tagLabels -Key 'todo' -Fallback 'todo'))
    }

    if ($lineCount -ge 260) {
        $tags.Add((Get-NotionSyncLabel -Map $tagLabels -Key 'long_code' -Fallback 'long_code'))
    }

    $breakthroughValue = Get-NotionSyncLabel -Map $breakthroughMap -Key $typeValue -Fallback $DefaultBreakthrough

    $rules = @(Get-NotionSyncObjectValue -Object $Config -Name 'auto_keyword_rules' -Default @())
    foreach ($rule in $rules) {
        $pattern = [string](Get-NotionSyncObjectValue -Object $rule -Name 'pattern' -Default '')
        if ([string]::IsNullOrWhiteSpace($pattern)) {
            continue
        }

        if ($searchText -match $pattern) {
            $overrideType = Get-NotionSyncObjectValue -Object $rule -Name 'type' -Default $null
            if ($null -ne $overrideType) {
                $typeValue = [string]$overrideType
                $breakthroughValue = Get-NotionSyncLabel -Map $breakthroughMap -Key $typeValue -Fallback $breakthroughValue
            }

            $overrideDifficulty = Get-NotionSyncObjectValue -Object $rule -Name 'difficulty' -Default $null
            if ($null -ne $overrideDifficulty) {
                $difficultyValue = [string]$overrideDifficulty
            }

            $overrideStatus = Get-NotionSyncObjectValue -Object $rule -Name 'status' -Default $null
            if ($null -ne $overrideStatus) {
                $statusValue = [string]$overrideStatus
            }

            $overrideTags = Get-NotionSyncObjectValue -Object $rule -Name 'tags' -Default $null
            if ($null -ne $overrideTags) {
                foreach ($tag in (Split-NotionSyncTags -Value ([string]$overrideTags))) {
                    $tags.Add($tag)
                }
            }

            $overrideBreakthrough = Get-NotionSyncObjectValue -Object $rule -Name 'breakthrough' -Default $null
            if ($null -ne $overrideBreakthrough) {
                $breakthroughValue = [string]$overrideBreakthrough
            }
        }
    }

    return @{
        type = $typeValue
        difficulty = $difficultyValue
        status = $statusValue
        tags = (($tags | Select-Object -Unique) -join '|')
        breakthrough = $breakthroughValue
        line_count = $lineCount
    }
}

function Get-NotionSyncNumericIndexFromBaseName {
    param([string]$BaseName)

    $value = 0
    if ([int]::TryParse($BaseName, [ref]$value)) {
        return $value
    }
    return $null
}

function Get-NotionSyncPendingStage {
    param(
        [int]$Index,
        [object]$PlanConfig
    )

    $stages = @(Get-NotionSyncObjectValue -Object $PlanConfig -Name 'stages' -Default @())
    foreach ($stage in $stages) {
        $from = [int](Get-NotionSyncObjectValue -Object $stage -Name 'from' -Default -1)
        $to = [int](Get-NotionSyncObjectValue -Object $stage -Name 'to' -Default -1)
        if ($from -le $Index -and $Index -le $to) {
            return $stage
        }
    }

    return $null
}

function Get-NotionSyncLuoguTitleByProblemId {
    param([string]$ProblemId)

    if ([string]::IsNullOrWhiteSpace($ProblemId)) {
        return $null
    }

    $normalized = $ProblemId.Trim().ToUpperInvariant()
    if ($normalized -notmatch '^P\d{4}$') {
        return $null
    }

    $url = "https://www.luogu.com.cn/problem/$normalized"
    $retryCount = 3
    for ($attempt = 1; $attempt -le $retryCount; $attempt++) {
        try {
            $resp = Invoke-WebRequest -Uri $url -UseBasicParsing -TimeoutSec 30
            $content = [string]$resp.Content
            if ([string]::IsNullOrWhiteSpace($content)) {
                continue
            }

            $jsonMatch = [regex]::Match($content, '<script id="lentille-context" type="application/json">(?<json>[\s\S]*?)</script>')
            if (-not $jsonMatch.Success) {
                continue
            }

            $jsonText = $jsonMatch.Groups['json'].Value
            if ([string]::IsNullOrWhiteSpace($jsonText)) {
                continue
            }

            $ctx = $jsonText | ConvertFrom-Json
            $dataObj = Get-NotionSyncObjectValue -Object $ctx -Name 'data' -Default $null
            $problemObj = Get-NotionSyncObjectValue -Object $dataObj -Name 'problem' -Default $null
            $title = Get-NotionSyncObjectValue -Object $problemObj -Name 'title' -Default $null
            if (-not [string]::IsNullOrWhiteSpace([string]$title)) {
                return [string]$title
            }
        }
        catch {
            if ($attempt -lt $retryCount) {
                Start-Sleep -Seconds ([Math]::Min(6, 2 * $attempt))
                continue
            }
        }
    }

    return $null
}

function Get-NotionSyncLuoguTitleCache {
    param([string]$CachePath)

    $cache = @{}
    if (-not (Test-Path $CachePath)) {
        return $cache
    }

    try {
        $json = Get-Content -Raw -Encoding UTF8 $CachePath
        if ([string]::IsNullOrWhiteSpace($json)) {
            return $cache
        }

        $obj = $json | ConvertFrom-Json
        foreach ($prop in $obj.PSObject.Properties) {
            $cache[[string]$prop.Name] = [string]$prop.Value
        }
    }
    catch {
        return @{}
    }

    return $cache
}

function Save-NotionSyncLuoguTitleCache {
    param(
        [string]$CachePath,
        [hashtable]$Cache
    )

    $ordered = [ordered]@{}
    foreach ($key in ($Cache.Keys | Sort-Object)) {
        $ordered[$key] = [string]$Cache[$key]
    }

    $ordered | ConvertTo-Json -Depth 5 | Set-Content -Path $CachePath -Encoding UTF8
}

function Get-NotionSyncLuoguTitleMap {
    param(
        [string[]]$ProblemIds,
        [string]$CachePath,
        [switch]$DisableNetwork
    )

    $cache = Get-NotionSyncLuoguTitleCache -CachePath $CachePath
    $changed = $false

    $uniqueProblemIds = @($ProblemIds | Where-Object { -not [string]::IsNullOrWhiteSpace($_) } | ForEach-Object { $_.Trim().ToUpperInvariant() } | Where-Object { $_ -match '^P\d{4}$' } | Select-Object -Unique)
    foreach ($pid in $uniqueProblemIds) {
        if ($cache.ContainsKey($pid) -and -not [string]::IsNullOrWhiteSpace([string]$cache[$pid])) {
            continue
        }

        if ($DisableNetwork) {
            continue
        }

        $title = Get-NotionSyncLuoguTitleByProblemId -ProblemId $pid
        if (-not [string]::IsNullOrWhiteSpace($title)) {
            $cache[$pid] = [string]$title
            $changed = $true
        }
    }

    if ($changed) {
        Save-NotionSyncLuoguTitleCache -CachePath $CachePath -Cache $cache
    }

    return $cache
}

function Get-NotionSyncLuoguPendingRows {
    param(
        [object]$Config,
        [hashtable]$ExistingIndices
    )

    $plan = Get-NotionSyncObjectValue -Object $Config -Name 'luogu_pending_plan' -Default $null
    if ($null -eq $plan) {
        return @()
    }

    $enabled = [bool](Get-NotionSyncObjectValue -Object $plan -Name 'enabled' -Default $false)
    if (-not $enabled) {
        return @()
    }

    $start = [int](Get-NotionSyncObjectValue -Object $plan -Name 'start' -Default 105)
    $end = [int](Get-NotionSyncObjectValue -Object $plan -Name 'end' -Default 200)
    if ($start -gt $end) {
        $tmp = $start
        $start = $end
        $end = $tmp
    }

    $titlePrefix = [string](Get-NotionSyncObjectValue -Object $plan -Name 'title_prefix' -Default '洛谷训练')
    $titleFormat = [string](Get-NotionSyncObjectValue -Object $plan -Name 'title_format' -Default '{0}-{1:D3}')
    $pendingTag = [string](Get-NotionSyncObjectValue -Object $plan -Name 'pending_tag' -Default '未完成|洛谷计划题')
    $pendingStatus = [string](Get-NotionSyncObjectValue -Object $plan -Name 'status' -Default '待做')
    $nextReviewOffsetDays = [int](Get-NotionSyncObjectValue -Object $plan -Name 'next_review_offset_days' -Default 1)

    $defaultType = [string](Get-NotionSyncObjectValue -Object $plan -Name 'default_type' -Default '基础算法')
    $defaultDifficulty = [string](Get-NotionSyncObjectValue -Object $plan -Name 'default_difficulty' -Default '中等')
    $defaultBreakthrough = [string](Get-NotionSyncObjectValue -Object $plan -Name 'default_breakthrough' -Default '先做题型判断，再选模板并控制复杂度')
    $disableTitleResolve = [bool](Get-NotionSyncObjectValue -Object $plan -Name 'disable_title_resolve' -Default $false)
    $cacheFile = [string](Get-NotionSyncObjectValue -Object $plan -Name 'title_cache_file' -Default 'luogu-title-cache.json')
    $cachePath = Join-Path $PSScriptRoot $cacheFile

    $today = (Get-Date).ToString('yyyy-MM-dd')
    $nextReview = (Get-Date).AddDays($nextReviewOffsetDays).ToString('yyyy-MM-dd')

    $pendingItems = @()
    $allProblemIds = @()
    $rows = @()
    for ($idx = $start; $idx -le $end; $idx++) {
        if ($ExistingIndices.ContainsKey($idx)) {
            continue
        }

        $stage = Get-NotionSyncPendingStage -Index $idx -PlanConfig $plan
        $typeValue = $defaultType
        $difficultyValue = $defaultDifficulty
        $breakthroughValue = $defaultBreakthrough

        if ($null -ne $stage) {
            $typeOverride = Get-NotionSyncObjectValue -Object $stage -Name 'type' -Default $null
            $difficultyOverride = Get-NotionSyncObjectValue -Object $stage -Name 'difficulty' -Default $null
            $breakthroughOverride = Get-NotionSyncObjectValue -Object $stage -Name 'breakthrough' -Default $null
            if ($null -ne $typeOverride) {
                $typeValue = [string]$typeOverride
            }
            if ($null -ne $difficultyOverride) {
                $difficultyValue = [string]$difficultyOverride
            }
            if ($null -ne $breakthroughOverride) {
                $breakthroughValue = [string]$breakthroughOverride
            }
        }

        $problemId = $null
        if ($null -ne $stage) {
            $stageFrom = [int](Get-NotionSyncObjectValue -Object $stage -Name 'from' -Default $idx)
            $stageProblemIds = @(Get-NotionSyncObjectValue -Object $stage -Name 'problem_ids' -Default @())
            $offset = $idx - $stageFrom
            if ($offset -ge 0 -and $offset -lt $stageProblemIds.Count) {
                $candidate = [string]$stageProblemIds[$offset]
                if (-not [string]::IsNullOrWhiteSpace($candidate)) {
                    $normalized = $candidate.Trim().ToUpperInvariant()
                    if ($normalized -match '^P\d{4}$') {
                        $problemId = $normalized
                        $allProblemIds += $problemId
                    }
                }
            }
        }

        $legacyTitle = [string]::Format($titleFormat, $titlePrefix, $idx)

        $pendingItems += [pscustomobject]@{
            source_index = $idx
            legacy_title = $legacyTitle
            problem_id = $problemId
            type = $typeValue
            difficulty = $difficultyValue
            status = $pendingStatus
            last_review = $today
            next_review = $nextReview
            error_tags = $pendingTag
            breakthrough = $breakthroughValue
        }
    }

    $titleMap = Get-NotionSyncLuoguTitleMap -ProblemIds $allProblemIds -CachePath $cachePath -DisableNetwork:$disableTitleResolve

    foreach ($item in $pendingItems) {
        $titleValue = [string]$item.legacy_title
        $problemId = [string]$item.problem_id
        if (-not [string]::IsNullOrWhiteSpace($problemId)) {
            $problemTitle = $null
            if ($titleMap.ContainsKey($problemId)) {
                $problemTitle = [string]$titleMap[$problemId]
            }

            if (-not [string]::IsNullOrWhiteSpace($problemTitle)) {
                $titleValue = "$problemId $problemTitle"
            }
            else {
                $titleValue = $problemId
            }
        }

        $rows += [pscustomobject]@{
            title = $titleValue
            type = [string]$item.type
            difficulty = [string]$item.difficulty
            status = [string]$item.status
            last_review = [string]$item.last_review
            next_review = [string]$item.next_review
            error_tags = [string]$item.error_tags
            breakthrough = [string]$item.breakthrough
            source_index = [int]$item.source_index
            legacy_title = [string]$item.legacy_title
            problem_id = [string]$item.problem_id
        }
    }

    return $rows
}
