#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "ERROR: Provide exactly one directory argument."
    exit 1
fi

for dir in $(find $1 -type d)
do
    files=$(\ls -l $dir | grep -Ev '^total')
    echo "$files" | while IFS= read -r file
    do
        if echo "$file" | grep -Eq '^........w.'; then
            fileName=$(echo "$file" | awk '{print $(NF)}')

            before="$(echo "$file" | awk '{print $1}') $dir/$fileName"
            echo "$before"
            
            chmod o-w "${dir}/${fileName}"

            after=$(\ls -l "$dir/$fileName" | awk '{print $1, $(NF)}')
            echo "$after"
        fi
    done
done

