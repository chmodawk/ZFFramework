@echo off
setlocal

set WORK_DIR=%~dp0
set PROJ_ROOT=%~1%
set PROJ_NAME=%~2%

if not defined PROJ_ROOT goto :usage
if not defined PROJ_NAME goto :usage
goto :run
:usage
echo usage:
echo   cleanup_AndroidStudio.bat PROJ_ROOT PROJ_NAME
exit /b 1
:run

rem ============================================================
rem AndroidStudio
rmdir /s/q "%PROJ_ROOT%\.gradle" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\.idea" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\build" >nul 2>&1
del /f/s/q "%PROJ_ROOT%\local.properties" >nul 2>&1
del /f/s/q "%PROJ_ROOT%\*.iml" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\lib\.externalNativeBuild" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\lib\build" >nul 2>&1
del /f/s/q "%PROJ_ROOT%\lib\*.iml" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\app\.externalNativeBuild" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\app\build" >nul 2>&1
del /f/s/q "%PROJ_ROOT%\app\*.iml" >nul 2>&1
rmdir /s/q "%PROJ_ROOT%\app\src\main\assets\zfres" >nul 2>&1

exit /b 0

