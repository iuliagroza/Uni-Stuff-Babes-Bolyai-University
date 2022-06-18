#!/bin/bash

#
# Doing simple math in Bash
#
# Shell script variables are by default treated as strings, not numbers.
#

# read the first number
echo -n "First number: "
read num1

# read the second number
echo -n "Second number: "
read num2

# 1. Using compound command (( expresion ))
sum=$((num1+num2))

# 2. Using let built-in command
#let sum=num1+num2

# 3. Using expr extern command
#sum=`expr $num1 + $num2`					# put spaces around + sign

# 4. Using declare built-in command
#declare -i sum
#sum=num1+num2

echo "The result is:" $sum
