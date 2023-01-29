@echo off
echo Choose device letter to unmount
set /p DEVICE= 
"%dokanlibrary1%/dokanctl.exe" /u %DEVICE%
PAUSE