#!/bin/bash

for a in *.po
do
LND=`basename $a .po`
echo converting $a to $LNG.mo
msgfmt $a -o $LND.mo
done


for f in *.mo
do 
LNG=`basename $f .mo`
echo moving $f to release package
mv $f ../../Release/Lang/$LNG/HDLBinst.mo
done
