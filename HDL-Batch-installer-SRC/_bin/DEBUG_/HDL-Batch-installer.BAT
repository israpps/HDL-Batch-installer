@echo off
cd /d  "%~dp0"
::
:: "-sot" OR "--stay-on-top" 				= forces the GUI to stay on top of every program
:: "-rdl" OR "--redirect-text" 				= redirects log messages from console into two text files found inside log/ folder
HDL-Batch-installer.exe --stay-on-top >ndea.log
exit