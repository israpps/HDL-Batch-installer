@echo off
cd /d "%~dp0"
del database.cpp
del database.h
IF EXIST gamename.csv del gamename.csv
wget -q --show-progress https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamename.csv -O gamename.csv
DBGEN.EXE -s
PAUSE