#!/bin/bash

for A in $@
do
    if test -f $A
    then
        echo $A is a file
    elif test -d $A
    then
        echo $A is a dir
    elif echo $A | grep -q "^[0-9]\+$"; then
        echo $A is a number
    else
        echo We do not know what $A is
    fi
done
