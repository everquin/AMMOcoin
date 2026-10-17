@echo off
rem Installs the Sapling parameters AMMOcoin needs into %APPDATA%\AMMOcoinParams.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0install-params.ps1"
set RC=%ERRORLEVEL%
echo.
pause
exit /b %RC%
