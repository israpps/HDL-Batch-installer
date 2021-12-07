@echo off
cd /d  "%~dp0"
::
:: "-sot" OR "--stay-on-top" 				= forces the GUI to stay on top of every program
:: "-rdl" OR "--redirect-text" 			= redirects log messages from console into two text files found inside log/ folder
:: "--force-max-debug"              = Program will behave as if highest debug level was selected, independently of the value written on the config file

HDL-Batch-installer.exe --stay-on-top 
exit
