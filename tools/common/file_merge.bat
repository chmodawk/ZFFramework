@echo off
setlocal

set WORK_DIR=%~dp0
set FILE1_PATH=%~1%
set FILE2_PATH=%~2%
set DST_PATH=%~3%

if not defined FILE1_PATH goto :usage
if not defined FILE2_PATH goto :usage
if not defined DST_PATH goto :usage
goto :run
:usage
echo usage:
echo   file_merge.bat FILE1_PATH FILE2_PATH DST_PATH
exit /b 1
:run

rem copy "%FILE1_PATH%" + "%FILE2_PATH%" "%DST_PATH%" >nul 2>&1
type "%FILE1_PATH%" > "%DST_PATH%"
type "%FILE2_PATH%" >> "%DST_PATH%"

