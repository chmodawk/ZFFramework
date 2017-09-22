@echo off
setlocal

set WORK_DIR=%~dp0
set BUILD_TYPE=%~1%
set PROJ_NAME=%~2%
set PROJ_PATH=%~3%

if not defined BUILD_TYPE goto :usage
if not defined PROJ_NAME goto :usage
if not defined PROJ_PATH goto :usage
goto :run
:usage
echo usage:
echo   Android_release.bat BUILD_TYPE PROJ_NAME PROJ_PATH
exit /b 1
:run

set ZF_ROOT_PATH=%WORK_DIR%\..\..
set ZF_TOOLS_PATH=%ZF_ROOT_PATH%\tools

call "%ZF_TOOLS_PATH%\common\file_exist.bat" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\libs\libs" "*.so"
if "%errorlevel%" == "0" (
    exit /b 0
)

set _OLD_DIR=%cd%

cd "%PROJ_PATH%\zfproj\Android\%PROJ_NAME%"
call "gradlew.bat" assembleRelease

cd "%_OLD_DIR%"

