@echo off
setlocal
cd /d "%~dp0scripts\notion-sync"
call "%~dp0scripts\notion-sync\run-notion-sync.bat"
exit /b %errorlevel%
