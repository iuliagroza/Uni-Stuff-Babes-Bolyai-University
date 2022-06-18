#!/bin/sh

if [ $# -eq 0 ]
then
	echo "Error: Not enough arguments."
	exit 1
fi

for arg in $*
do
   echo $arg
done
