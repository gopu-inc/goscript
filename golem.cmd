@echo off
setlocal
set "GOSCRIPT_SHARE_DIR=%~dp0..\share\goscript"
set "PATH=%~dp0;%PATH%"
"%~dp0gd.exe" "%GOSCRIPT_SHARE_DIR%\golem-cli.gjs" %*
exit /b %ERRORLEVEL%
