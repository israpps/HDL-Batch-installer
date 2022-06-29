@echo off
cd /d %~dp0
:A
set /p SEARCH=_/
type gamename.csv | findstr /I /L "/C:%SEARCH%"

PAUSE
cls
goto A