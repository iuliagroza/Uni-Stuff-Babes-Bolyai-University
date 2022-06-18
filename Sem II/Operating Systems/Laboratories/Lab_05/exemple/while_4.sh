#!/bin/bash

if [ $# -eq 0 ]
	then
	echo "Error: You must enter a filename."
	exit 1
elif !(test -r $1)
	then
	echo "File $1 does not exist."
	exit 1
fi

while read -r line
do
	echo $line
done
