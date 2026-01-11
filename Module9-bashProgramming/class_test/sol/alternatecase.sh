#!/bin/bash

# Error handling for incorrect number of arguments
if [ $# -ne 2 ]; then
  echo "Usage: $0 <input_file> <search_word>"
  exit 1
fi

# Assign command-line arguments to variables
input_file="$1"
search_word="$2"

# Error handling for file not found
if [ ! -f "$input_file" ]; then
  echo "Error: File '$input_file' not found"
  exit 1
fi

# Function to convert a string to alternating case
alternating_case() {
  local input_string="$1"
  local output_string=""
  local upper=true

  for (( i=0; i<${#input_string}; i++ )); do
    char="${input_string:$i:1}"
    if [[ "$char" =~ [a-zA-Z] ]]; then
      if [ "$upper" = true ]; then
        output_string+="${char^^}"
      else
        output_string+="${char,,}"
      fi
      upper=$([ "$upper" = true ] && echo false || echo true)
    else
      output_string+="$char"
    fi
  done

  echo "$output_string"
}

# Process each line of the input file
line_number=0
while IFS= read -r line; do
  line_number=$((line_number + 1))
  if echo "$line" | grep -iq "$search_word"; then
    # If the line contains the search word (case-insensitive), convert it to alternating case
    echo "$(alternating_case "$line")"
  else
    # Otherwise, print the line as is
    echo "$line"
  fi
done < "$input_file"
