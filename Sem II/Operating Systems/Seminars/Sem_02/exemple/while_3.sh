#!/bin/bash

# Read the console input until the user
# provides a filename that exists and can be read

F=””
while [ -z "$F" ] || [ ! -f "$F" ] || [ ! -r "$F" ]
do
  read -p "Provide an existing and readable file path:" F
done
