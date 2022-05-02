#!/bin/sh

c=12
for d in $@
do
	find "$d" -type f | while read f 
	do 
		if  file "$f" | grep -q "C source" ; then 
			echo "$f is a c source"
			c=$((c+1))
			echo "c: $c"	
		fi
	done
done

echo "We found $c c source files"
