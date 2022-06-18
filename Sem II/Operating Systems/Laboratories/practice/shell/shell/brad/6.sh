#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "ERROR: Provide a file and at least one username."
    exit 1
fi

f="$1"
shift 1

while IFS= read -r dir
do
    if [ -d "$dir" ] && [ -r "$dir" ]; then
        for sub in $(find $dir -type d 2>&1 | grep -Ev 'denied$')
        do
            echo $sub
        done
    else
        echo "Unable to read directory from file: $dir"
    fi
done < $f

for user in "$@"
do
    data=$(cat '/etc/passwd' | grep -E "^${user}")
    if [ ! -z "$data" ];then
        homedir=$(echo "$data" | awk -F ':' '{print $(NF-1)}')
        
        if [ -r "$homedir" ]; then
            for sub in $(find $homedir -type d)
            do
                echo $sub
            done
        else
            echo "Unable to read home directory: $homedir"
        fi
    fi
done

