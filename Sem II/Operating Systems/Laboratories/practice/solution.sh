#!/bin/bash

checksums=()
findresult=$(find $1 -type f)
solution=""

for file in $findresult
do
	checksum=$(md5sum $file | awk '{print $1}')
	
	ok=0
	for i in "${checksums[@]}"
	do
		if [ $i == $checksum ]; then
			ok=1
			solution="$solution $checksum $file"$'\n'
		fi		
	done
	if [ $ok -eq 0 ]; then
		checksums+=($checksum)
	fi
done
echo "$(echo "$solution" | sort)"

