@echo off
cd /d %~dp0
REM WGET.EXE --spider -q https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamenamez.csv
echo [%errorlevel%]
WGET.EXE --spider -q --show-progress https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamenamez.csv -O gamemame.csv
echo [%errorlevel%]
REM wget.exe --help
PAUSE