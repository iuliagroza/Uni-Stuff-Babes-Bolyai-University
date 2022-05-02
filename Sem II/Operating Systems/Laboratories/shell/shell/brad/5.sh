#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "ERROR: Provide two files and at least one username."
    exit 1
fi

f1="$1"
f2="$2"
shift 2

result=""
for user in "$@"
do
    data=$(cat '/etc/passwd' | grep -E "^${user}")
    if [ ! -z "$data" ];then
        homedir=$(echo "$data" | awk -F ':' '{print $(NF-1)}')
        size=$(du -bs $homedir)

        name=$(echo "$data" | awk -F ':' '{print $5}')
        result="$result$size $name"$'\n'
    else
        echo $user >> $f1
    fi
done

result=$(echo "${result::-1}" | sort -n -r -k 1,1)
echo "$result" > $f2

