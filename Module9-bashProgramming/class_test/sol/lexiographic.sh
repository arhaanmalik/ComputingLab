#!/bin/bash

# Error handling for incorrect number of arguments
if [ $# -ne 2 ]; then
  echo "Usage: $0 <input_directory> <output_directory>"
  exit 1
fi

# Assign command-line arguments to variables
input_directory="$1"
output_directory="$2"

# Error handling for input directory not found
if [ ! -d "$input_directory" ]; then
  echo "Error: Input directory '$input_directory' not found"
  exit 1
fi

# Create output directory if it doesn't exist
if [ ! -d "$output_directory" ]; then
  mkdir -p "$output_directory"
fi

# Create 26 empty files (A.txt to Z.txt) in the output directory
for letter in {A..Z}; do
  > "$output_directory/$letter.txt"
done

# Gather names from input files and sort them into respective files
for file in "$input_directory"/*.txt; do
  if [ -f "$file" ]; then
    while IFS= read -r name; do
      first_char="${name:0:1}"
      if [[ "$first_char" =~ [A-Za-z] ]]; then
        first_char_upper="${first_char^^}"
        echo "$name" >> "$output_directory/$first_char_upper.txt"
      fi
    done < "$file"
  fi
done

# Sort the names in each output file lexicographically
for letter in {A..Z}; do
  sort -o "$output_directory/$letter.txt" "$output_directory/$letter.txt"
done
