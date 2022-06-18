#!/bin/bash

result=""
for user in $(cat last.fake | awk '{print $1}' | sort | uniq)
do
    count=$(cat last.fake | grep -Ec "^${user}")
    result="$result$count $user"$'\n'
done

result=$(echo "$result" | sort -n -r -k 1,1)
echo "$result"

