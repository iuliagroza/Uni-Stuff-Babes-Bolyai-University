#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "ERROR: Provide a number and at least one C source file."
    exit 1
fi

n="$1"
shift 1

libs=""
for file in "$@"
do
    while IFS= read -r line
    do
        if echo "$line" | grep -Eq '^#include'; then
            libs="${libs}${line}"$'\n'
        fi
    done < $file
done

result=$(echo "${libs::-1}" | sort | uniq -c | sort -n -r -k 1,1 | head -n $n)
echo "$result"

