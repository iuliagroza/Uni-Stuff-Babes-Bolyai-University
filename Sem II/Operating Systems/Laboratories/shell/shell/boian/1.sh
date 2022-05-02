#!/bin/bash

for user in $(cat who.fake | awk '{print $1}')
do
    proc=$(cat ps.fake | grep -Ec "^${user}")
    echo "$user $proc"
done

