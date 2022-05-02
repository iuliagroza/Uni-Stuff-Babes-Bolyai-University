#!/bin/bash

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
