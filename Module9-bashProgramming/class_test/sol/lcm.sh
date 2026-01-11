#!/bin/bash

# Check if exactly one argument is provided (filename)
if [ $# -ne 1 ]; then
    echo "Usage: ./lcm.sh <filename>"
    exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
    echo "Error: File not found!"
    exit 1
fi

# Function to calculate GCD of two numbers
gcd() {
    local a=$1
    local b=$2
    while [ "$b" -ne 0 ]; do
        local temp=$b
        b=$((a % b))
        a=$temp
    done
    echo $a
}

# Function to calculate LCM of two numbers
lcm() {
    local a=$1
    local b=$2
    local gcd_result=$(gcd "$a" "$b")
    echo $(( (a * b) / gcd_result ))
}

# Initialize result to 1
result=1

# Read numbers from the file and calculate LCM
while read -r num; do
    # Trim any leading or trailing whitespace
    num=$(echo "$num" | xargs)

    # Check if the input is a valid positive integer
    if ! [[ "$num" =~ ^[0-9]+$ ]]; then
        echo "Error: Invalid number '$num' in the file."
        exit 1
    fi

    # Calculate the cumulative LCM
    result=$(lcm "$result" "$num")
done < "$1"

# Display the final LCM result
echo "LCM: $result"
