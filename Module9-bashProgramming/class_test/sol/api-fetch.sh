#!/bin/bash

# Check if exactly one argument (search keyword) is provided
if [ $# -ne 1 ]; then
    echo "Usage: ./api-fetch.sh <search_keyword>"
    exit 1
fi

# Assign the search keyword to a variable
search_keyword=$1

# Check if the API links file exists
api_file="api-links_5.txt"
if [ ! -f "$api_file" ]; then
    echo "Error: API links file not found!"
    exit 1
fi

# Initialize the JSON output file
json_output="combined_issues.json"
echo "[]" > "$json_output"  # Start with an empty JSON array

# Temporary file to accumulate issues
temp_issues="temp_issues.json"
> "$temp_issues"  # Empty the temp file

# Loop through each API link and fetch data
while read -r url; do
    if [[ -n "$url" ]]; then
        echo "Fetching data from: $url"  # Debugging output
        response=$(curl -s "$url")

        # Validate if the response is a valid JSON object or array
        if echo "$response" | jq empty 2>/dev/null; then
            # Handle both array and single object cases
            if echo "$response" | jq 'type' | grep -q '"array"'; then
                # If the response is an array, extract each issue
                echo "$response" | jq -c '.[] | {id, number, title, user: .user.login, labels: ([.labels[].name] // [])}' >> "$temp_issues"
            else
                # If the response is a single object, extract issue data
                echo "$response" | jq -c '{id, number, title, user: .user.login, labels: ([.labels[].name] // [])}' >> "$temp_issues"
            fi
        else
            echo "Error: Invalid JSON response from $url"
        fi
    fi
done < "$api_file"

# Combine all fetched issue data into a single JSON array
jq -s '.' "$temp_issues" > "$json_output"
rm "$temp_issues"  # Clean up temporary file

# Display the combined JSON content (optional)
echo "Combined Issues JSON:"
cat "$json_output" | jq

# Search for the keyword in titles or labels (case-insensitive)
echo "Matching Results:"
jq -r --arg keyword "$search_keyword" '
    .[] | select(
        (.title | ascii_downcase | contains($keyword | ascii_downcase)) or
        ([.labels[]] | join(" ") | ascii_downcase | contains($keyword | ascii_downcase))
    ) | "ID: \(.id) Title: \(.title)"
' "$json_output"
