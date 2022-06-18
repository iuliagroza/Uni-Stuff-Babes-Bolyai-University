#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "ERROR: Provide exactly one directory argument."
    exit 1
fi

count=0
for file in $(find $1 -name '*.c')
do
    if [ $(wc -l $file | awk '{print $1}') -gt 500 ]; then
        echo $file
        ((count++))
    fi

    if [ $count -ge 2 ]; then
        break
    fi
done

