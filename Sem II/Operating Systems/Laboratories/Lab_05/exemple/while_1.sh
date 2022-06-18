#!/bin/bash

# Read user input until the input is stop
# The command read stores the user input in the variable given as argument

while true
do
  read X
  if test "$X" == "stop"
  then
    break
  fi
done
