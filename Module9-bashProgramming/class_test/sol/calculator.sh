#!/bin/bash

if [ $# -ne 3 ]; then
 echo "Usage : ./calculator.sh <number1> <operator> <number2>"
 exit 1

fi

num1=$1
operator=$2
num2=$3

case $operator in 
  +) result=$(echo "scale=2; $num1 + $num2" | bc);;
  -) result=$(echo "scale=2; $num1 - $num2" | bc);;
  \*) result=$(echo "scale=2; $num1 * $num2" | bc);;
    /)
      if [ "$num2" -eq  0 ]; then
       echo "Error: Div by zero"
       exit 1
      else
       result=$(echo "scale=2; $num1 / $num2"|bc)
      fi
      ;;
    *)
     echo "Error : Invalid operator"
     exit 1
     ;;
esac
echo "$result"
