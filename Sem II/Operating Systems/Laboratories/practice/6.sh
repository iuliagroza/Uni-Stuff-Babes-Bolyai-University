#!/bin/bash

for dir in $(find $1 -type d)
do
	files=$(\ls -l $dir | grep -Ev '^total')
	echo 
	before="$(echo "$file" | awk '{print$1}') $dir/$files"

	echo $before

	chmod o-w "${dir}/${files}"

	after=$(\ls -l "$dir/$filename" | awk '{print $1, ${NF)}')
	echo "$after"
	
done
