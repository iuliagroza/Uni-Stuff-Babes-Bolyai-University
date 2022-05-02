#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "ERROR: Provide exactly one directory argument."
    exit 1
fi

result=""
files=()
for file in $(find $1 -type f)
do
    already_added=0
    checksum=$(md5sum "$file" | awk '{print $1}')

    for i in "${files[@]}"
    do
        if [ "$i" == "$checksum" ]; then
            result="$result$checksum $file"$'\n'
            already_added=1
            break
        fi
    done
    
    if [ $already_added -eq 0 ]; then
        files+=("$checksum")
    fi
done

result=$(echo "${result::-1}" | sort)
echo "$result"

