#!/bin/bash

echo -n "Enter a filename: "
read filename

while read -r line
do
	echo $line
done < $filename