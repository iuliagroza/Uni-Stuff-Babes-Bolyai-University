#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "ERROR: Provide a number, and at least one file."
    exit 1
fi

n="$1"

shift 1
for file in "$@"
do
    echo "${file}:"
    freq=$(cat "$file" | tr ' ' '\n' | sort | uniq -c | sort -n -r -k 1,1 | awk -v n="$n" '{if($1>n) print $1, $2}')
    echo "$freq"
done

