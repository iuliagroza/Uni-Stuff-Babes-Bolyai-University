#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "ERROR: Provide exactly one directory argument."
    exit 1
fi

for file in $(find $1 -type l)
do
    if [ -L $file ] && [ ! -e $file ]; then
        echo $file
    fi
done

