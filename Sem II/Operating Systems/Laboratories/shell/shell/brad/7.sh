#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "ERROR: Provide a number, a word, and at least one file."
    exit 1
fi

n="$1"
w="$2"

shift 2
for file in "$@"
do
    lines=$(cat "$file" | grep -E "${w}")
    nthline=$(echo "$lines" | tail -n +"$n" | head -n 1)
    
    echo "$nthline"
done

