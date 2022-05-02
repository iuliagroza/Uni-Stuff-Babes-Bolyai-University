#!/bin/bash

findresult=$(find $1 -type l)

for file in $findresult
do
	if [ -L $file ] && [ ! -e $file ]; then
		echo "$file"
	fi	
done
