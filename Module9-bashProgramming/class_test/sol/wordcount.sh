#!/bin/bash

# Check if exactly two arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: ./wordcount.sh <filename> <search_word>"
    exit 1
fi

# Assign arguments to variables
file=$1
search_word=$2

# Check if the file exists and is readable
if [ ! -f "$file" ] || [ ! -r "$file" ]; then
    echo "Error: File not found or not readable!"
    exit 1
fi

# Calculate total number of lines
total_lines=$(wc -l < "$file")

# Calculate total number of words
total_words=$(wc -w < "$file")

# Calculate total number of characters
total_chars=$(wc -m < "$file")

# Calculate frequency of the search word (case-insensitive)
word_frequency=$(grep -io "\\b$search_word\\b" "$file" | wc -l)

# Display the results
echo "Total Lines: $total_lines"
echo "Total Words: $total_words"
echo "Total Characters: $total_chars"
echo "Frequency of word '$search_word': $word_frequency"
