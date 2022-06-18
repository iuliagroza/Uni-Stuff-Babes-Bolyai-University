#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "ERROR: Provide exactly one directory argument."
    exit 1
fi

count=0
for file in $(find $1 -name '*.log')
do
    sort $file -o $file
    ((count++))
done

echo "Sorted $count log files."

