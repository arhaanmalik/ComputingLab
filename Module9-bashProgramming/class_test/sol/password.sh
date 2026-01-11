#!/bin/bash

# Check if exactly one argument is provided (password length)
if [ $# -ne 1 ]; then
    echo "Usage: ./password.sh <length>"
    exit 1
fi

# Validate that the input length is a positive integer and at least 4
if ! [[ "$1" =~ ^[0-9]+$ ]] || [ "$1" -lt 4 ]; then
    echo "Error: Password length must be a positive integer of at least 4."
    exit 1
fi

# Assign the password length
length=$1

# Define character sets for the password
uppercase="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
lowercase="abcdefghijklmnopqrstuvwxyz"
digits="0123456789"
special="!@#\$%&*()"

# Ensure the password contains at least one of each required type
password="${uppercase:RANDOM%26:1}"
password+="${lowercase:RANDOM%26:1}"
password+="${digits:RANDOM%10:1}"
password+="${special:RANDOM%10:1}"

# Generate the rest of the password randomly from all character sets
all_characters="${uppercase}${lowercase}${digits}${special}"
for ((i=4; i<length; i++)); do
    password+="${all_characters:RANDOM%${#all_characters}:1}"
done

# Shuffle the password to randomize the order of characters
shuffled_password=$(echo "$password" | fold -w1 | shuf | tr -d '\n')

# Display the generated password
echo "Generated password: $shuffled_password"
