#!/bin/bash

# Check for the correct number of arguments
if [ $# -ne 4 ]; then
    echo "Usage: ./search_books.sh <input_file> <search_phrase> <context_type> <num_context_words>"
    exit 1
fi

# Assign arguments to variables
input_file="$1"
search_phrase="$2"
context_type="$3"
num_context_words="$4"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File not found."
    exit 1
fi

# Validate context type
if [[ "$context_type" != "-before" && "$context_type" != "-after" && "$context_type" != "-both" ]]; then
    echo "Error: Invalid context type. Use -before, -after, or -both."
    exit 1
fi

# Convert search phrase to lowercase for case-insensitive matching
search_phrase=$(echo "$search_phrase" | tr '[:upper:]' '[:lower:]')

# Search the input file line by line
while IFS='|' read -r title author year summary; do
    # Convert the summary to lowercase for matching
    lower_summary=$(echo "$summary" | tr '[:upper:]' '[:lower:]')

    # Check if the search phrase exists in the summary
    if [[ "$lower_summary" == *"$search_phrase"* ]]; then
        echo "Book: $title | Author: $author"

        # Extract words from the summary
        words=($summary)

        # Find the index of the search phrase
        phrase_index=$(echo "${words[@]}" | grep -abo "\b$search_phrase\b" | cut -d: -f1)

        # Adjust the index for word array splitting
        word_count=${#words[@]}
        case "$context_type" in
            -before)
                start=$((phrase_index - num_context_words))
                [ $start -lt 0 ] && start=0
                context="${words[@]:$start:$num_context_words}"
                ;;
            -after)
                context="${words[@]:$((phrase_index + 1)):$num_context_words}"
                ;;
            -both)
                start=$((phrase_index - num_context_words))
                [ $start -lt 0 ] && start=0
                before="${words[@]:$start:$num_context_words}"
                after="${words[@]:$((phrase_index + 1)):$num_context_words}"
                context="$before ... $after"
                ;;
        esac

        echo "Context: $context"
        echo
    fi
done < "$input_file"
