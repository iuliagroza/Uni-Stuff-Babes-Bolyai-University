#!/bin/bash

if [ "$#" -lt 4 ]; then
    echo "ERROR: Provide a word, 2 numbers, and at least one file."
    exit 1
fi

w="$1"
m="$2"
n="$3"

shift 3
for file in "$@"
do
    nthline=$(cat "$file" | tail -n +"$n" | head -n 1)
    matches=$(echo "$nthline" | grep -Eo "${w}" | wc -l)
    
    if [ "$matches" -ge "$m" ]; then
        echo "$file"
    fi
done

