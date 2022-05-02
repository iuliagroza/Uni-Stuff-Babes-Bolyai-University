#!/bin/sh

# Count all the number of files per provided directory.

for a in  $*
do
	#echo $a
	if [ -d "$a" ]; then
		#echo "$a contains `ls -1 "$a"|grep -c "^-" ` entries"
		echo  "$a contains `find "$a" -type f | wc -l` entries"
	fi
done
