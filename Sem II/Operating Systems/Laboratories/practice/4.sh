#!/bin/bash

findres=$(find dir -type l)

for file in $findres
do
	if [ -L $file ] && [ ! -e $file ]; then
		echo $file
	fi
done
