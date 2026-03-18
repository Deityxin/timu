@echo off
setlocal
cd /d "%~dp0"

powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0one-click-sync.ps1"

if errorlevel 1 (
  echo.
  echo [FAILED] One-click sync returned an error.
  pause
  exit /b 1
)

echo.
echo [DONE] One-click sync finished.
pause
exit /b 0
