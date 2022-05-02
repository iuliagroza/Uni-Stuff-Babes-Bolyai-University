#!/bin/bash

findres=$(find dir -name '*.c')

count=0
for file in $findres
do
	if [ $(wc -l $file | awk '{print $1}') ]; then
		echo $file
		((count++))
	fi

	if [ $count -ge 2 ]; then
		break
	fi
done
