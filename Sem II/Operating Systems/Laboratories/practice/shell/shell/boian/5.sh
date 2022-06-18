#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "ERROR: Provide at least one dangerous program argument."
    exit 1
fi

while true
do
    for proc in "$@"
    do
        found=$(ps | grep -E "${proc}$")
        
        if [ ! -z "$found" ]; then
            pid=$(echo "$found" | awk '{print $1}')

            kill -9 "$pid"
            echo "Killed program: $proc"
        fi 
    done
    
    echo "Waiting..."
	sleep 1
done

