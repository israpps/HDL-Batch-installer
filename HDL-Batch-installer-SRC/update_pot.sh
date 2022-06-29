#!/bin/bash
CPP_FILE_LIST=$(find ./ -name '*.cpp' -print)
xgettext -d app_name -s --keyword=_ -p ./ -o HDLBinst.pot $CPP_FILE_LIST