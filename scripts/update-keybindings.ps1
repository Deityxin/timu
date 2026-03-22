$ErrorActionPreference = "Stop"

# Define the target file path
$KeybindingsPath = "$env:APPDATA\Code\User\keybindings.json"

if (-not (Test-Path $KeybindingsPath)) {
    Write-Error "Keybindings file not found at: $KeybindingsPath"
    exit 1
}

# Read existing JSON
try {
    $RawJson = Get-Content $KeybindingsPath -Raw -Encoding UTF8
    if ([string]::IsNullOrWhiteSpace($RawJson)) {
        $Keybindings = @()
    } else {
        $Keybindings = $RawJson | ConvertFrom-Json
    }
} catch {
    Write-Error "Failed to parse keybindings.json: $_"
    exit 1
}

# Define new bindings to add
$NewBindings = @(
    @{
        "key"     = "ctrl+alt+c"
        "command" = "workbench.action.chat.open"
        "args"    = @{ "query" = "/cp-check" }
    },
    @{
        "key"     = "ctrl+alt+p"
        "command" = "workbench.action.chat.open"
        "args"    = @{ "query" = "/cp-plan" }
    },
    @{
        "key"     = "ctrl+alt+s"
        "command" = "workbench.action.chat.open"
        "args"    = @{ "query" = "/cp-archive" }
    }
)

# Merge bindings (Avoiding duplicates based on key)
$Modified = $false
foreach ($NewBinding in $NewBindings) {
    $Existing = $Keybindings | Where-Object { $_.key -eq $NewBinding.key }
    if ($null -eq $Existing) {
        $Keybindings += $NewBinding
        Write-Host "Adding binding: $($NewBinding.key)" -ForegroundColor Green
        $Modified = $true
    } else {
        Write-Host "Binding for $($NewBinding.key) already exists, skipping." -ForegroundColor Yellow
        # Could update existing binding here if needed, but safer to skip to avoid overwriting user prefs
    }
}

# Write back if changed
if ($Modified) {
    try {
        $Keybindings | ConvertTo-Json -Depth 5 | Set-Content $KeybindingsPath -Encoding UTF8
        Write-Host "Successfully updated keybindings.json!" -ForegroundColor Cyan
    } catch {
        Write-Error "Failed to write keybindings.json: $_"
        exit 1
    }
} else {
    Write-Host "No changes needed." -ForegroundColor Cyan
}
