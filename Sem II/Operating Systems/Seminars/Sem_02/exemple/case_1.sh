#!/bin/bash

if [ $# -eq 0 ]
	then
	echo "Error: You must enter an option."
	exit 1
fi

case $1 in
	-[a-z] ) echo "You enter a letter";;
	-[0-9] ) echo "You enter a digit";;
	* )	echo "Unknown option";;
esac
