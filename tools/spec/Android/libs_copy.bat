@echo off
setlocal

set WORK_DIR=%~dp0
set PROJ_NAME=%~1%
set PROJ_PATH=%~2%

if not defined PROJ_NAME goto :usage
if not defined PROJ_PATH goto :usage
goto :run
:usage
echo usage:
echo   libs_copy.bat PROJ_NAME PROJ_PATH
exit /b 1
:run

set ZF_ROOT_PATH=%WORK_DIR%\..\..\..

mkdir "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\libs\libs" >nul 2>&1
xcopy /s/e/y/r/h "%PROJ_PATH%\zflib\build\intermediates\bundles\default\jni\*.so" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\libs\libs" >nul 2>&1
call "%ZF_ROOT_PATH%\tools\util\copy_header.bat" "%PROJ_PATH%\..\..\..\zfsrc" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\libs\include" >nul 2>&1

for /f "delims=" %%a in ("%PROJ_PATH%\zflib\build\intermediates\bundles\default\classes.jar") do set JAR_FILE_SIZE=%%~za
if %JAR_FILE_SIZE% gtr 1024 (
    echo f | xcopy /s/e/y/r/h "%PROJ_PATH%\zflib\build\intermediates\bundles\default\classes.jar" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\libs\%PROJ_NAME%.jar" >nul 2>&1
)

call "%ZF_ROOT_PATH%\tools\util\copy_res.bat" "%PROJ_PATH%\..\..\..\zfres" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%\src\main\assets\zfres" >nul 2>&1

call "%ZF_ROOT_PATH%\tools\common\copy_check.bat" "%ZF_ROOT_PATH%\_release\Android\module\%PROJ_NAME%" "%ZF_ROOT_PATH%\_release\Android\all" >nul 2>&1

exit /b 0

