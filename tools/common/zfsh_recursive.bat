@echo off
setlocal
setlocal enabledelayedexpansion

set WORK_DIR=%~dp0
set SRC_DIR=%~1%
set FILE_NAME=%~2%

if not defined SRC_DIR goto :usage
if not defined FILE_NAME goto :usage
goto :run
:usage
echo usage:
echo   zfsh_recursive.sh SRC_DIR FILE_NAME [params...]
echo set ZF_EXCLUDE to exclude dirs, separated by space, match exact, e.g.
echo   set ZF_EXCLUDE=f0 f1
exit /b 1
:run

if not exist "%SRC_DIR%" (
    exit /b 0
)

rem ============================================================
rem default exclude dirs
set ZF_EXCLUDE_TMP=%ZF_EXCLUDE%
set ZF_EXCLUDE_TMP=%ZF_EXCLUDE_TMP% private zfres _release _tmp

rem ============================================================
for /f "tokens=2,* delims= " %%a in ("%*") do set ALL_VAR=%%b
for /f %%f in ('dir /a-d/s/b %SRC_DIR%\%FILE_NAME%') do (
    call :run_with_filter %%f
    if not "!errorlevel!" == "0" (
        exit /b 1
    )
)

goto :EOF

:run_with_filter
set _excluded=0
for %%f in (%ZF_EXCLUDE_TMP%) do (
    call :check_filter %1 %%f _excluded
)
if "%_excluded%" == "0" (
    echo running %1
    call "%WORK_DIR%\zfsh.bat" "%1" %ALL_VAR%
    if not "!errorlevel!" == "0" (
        echo error occurred when running %1
        exit /b 1
    )
)
goto :EOF

:check_filter
echo %1 | findstr "\%2\\" >nul 2>&1 && set %3=1
goto :EOF

