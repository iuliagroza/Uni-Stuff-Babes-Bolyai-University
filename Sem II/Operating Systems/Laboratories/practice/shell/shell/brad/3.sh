#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "ERROR: Provide a word and at least one file."
    exit 1
fi

w="$1"

shift 1
for file in "$@"
do
    matches=$(cat "$file" | grep -Eo "${w}" | wc -l)
    echo "$matches $file"
done

