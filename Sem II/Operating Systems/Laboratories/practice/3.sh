#!/bin/bash

findres=$(find dir -name '*.log')

count=0
for file in $findres
do
	sort $file -o $file
	((count++))
done 

echo "Sorted $count log files."
