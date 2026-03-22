# PowerShell script to help user apply keybindings
# Note: VS Code keybindings cannot be modified programmatically for security reasons.
# This script prints the JSON snippet the user needs to add.

Write-Host "⚠️ VS Code does not allow scripts to modify keybindings.json directly." -ForegroundColor Yellow
Write-Host "Please manually add the following to your keybindings.json (Open Palette -> Preferences: Open Keyboard Shortcuts (JSON)):" -ForegroundColor Cyan
Write-Host ""
Write-Host "  {"
Write-Host "    `"key`": `"ctrl+alt+c`","
Write-Host "    `"command`": `"workbench.action.chat.open`","
Write-Host "    `"args`": { `"query`": `"/cp-check`" }"
Write-Host "  },"
Write-Host "  {"
Write-Host "    `"key`": `"ctrl+alt+p`","
Write-Host "    `"command`": `"workbench.action.chat.open`","
Write-Host "    `"args`": { `"query`": `"/cp-plan`" }"
Write-Host "  },"
Write-Host "  {"
Write-Host "    `"key`": `"ctrl+alt+s`","
Write-Host "    `"command`": `"workbench.action.chat.open`","
Write-Host "    `"args`": { `"query`": `"/cp-archive`" }"
Write-Host "  }"
Write-Host ""
Write-Host "Done! Copy the JSON objects above into your keybindings.json [] array." -ForegroundColor Green
