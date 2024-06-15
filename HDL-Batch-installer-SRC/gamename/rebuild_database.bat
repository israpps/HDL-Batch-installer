@echo off
echo --- rebuilding gamename database
wget -q --show-progress https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamename.csv -O gamename.csv
if not exist gamename.csv (
    echo FAILED TO DOWNLOAD DB. ABORTING
    goto QUIT
)
set /a CNT=0
echo #include "database.h">database.cpp
echo std::map^<std::string, std::string^>GameNameDB = {>>database.cpp
for /f "delims=; tokens=1,*" %%a in (gamename.csv) do (
    echo     {"%%a", "%%b"},>>database.cpp
    set /a CNT+=1
)
echo };>>database.cpp
echo %CNT% entries found
del gamename.csv>nul
:QUIT