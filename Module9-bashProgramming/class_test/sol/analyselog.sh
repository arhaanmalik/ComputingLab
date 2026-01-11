#!/bin/bash

# Check for the correct number of arguments
if [ $# -ne 2 ]; then
    echo "Usage: ./analyselog.sh <log_file> <time_window_in_minutes>"
    exit 1
fi

log_file="$1"
window_minutes="$2"

# Validate the log file
if [ ! -f "$log_file" ]; then
    echo "Error: Log file not found."
    exit 1
fi

# Validate time window input
if ! [[ "$window_minutes" =~ ^[0-9]+$ ]] || [ "$window_minutes" -le 0 ]; then
    echo "Error: Time window must be a positive integer."
    exit 1
fi

# Function to convert a timestamp to seconds since epoch
timestamp_to_seconds() {
    date -d "$1" +%s
}

# Extract and sort log entries by timestamp
awk '{print substr($0, 2, 19), $2}' "$log_file" | sort > sorted_log.txt

# Initialize variables
max_entries=0
busiest_start=""
busiest_end=""
declare -A ip_count

# Read through the sorted log to find the busiest window
while read -r line; do
    start_time=$(echo "$line" | awk '{print $1, $2}')
    start_seconds=$(timestamp_to_seconds "$start_time")
    end_seconds=$((start_seconds + window_minutes * 60))

    # Get entries within the time window
    entries=$(awk -v start="$start_seconds" -v end="$end_seconds" '
    {
        split($1 " " $2, ts_parts, "[-:]")
        ts_seconds = mktime(ts_parts[1] " " ts_parts[2] " " ts_parts[3] " " ts_parts[4] " " ts_parts[5] " " ts_parts[6])
        if (ts_seconds >= start && ts_seconds <= end) {
            print $0
        }
    }' sorted_log.txt)

    entry_count=$(echo "$entries" | wc -l)

    # Update if a new busiest window is found
    if [ "$entry_count" -gt "$max_entries" ]; then
        max_entries=$entry_count
        busiest_start="$start_time"
        busiest_end=$(date -d "@$end_seconds" +"%Y-%m-%d %H:%M:%S")

        # Reset IP counts for this window
        ip_count=()

        # Count IP addresses within this window
        while IFS= read -r entry; do
            ip=$(echo "$entry" | awk '{print $2}') # Extract the IP address
            ((ip_count["$ip"]++)) # Increment the count for the IP address
        done <<< "$entries"
    fi
done < sorted_log.txt

# Display the results
echo "Start Time: $busiest_start"
echo "End Time: $busiest_end"
echo "Number of Entries: $max_entries"
echo "Top 3 IPs in the window:"

# Sort and display the top 3 IPs
for ip in "${!ip_count[@]}"; do
    echo "$ip - ${ip_count[$ip]}"
done | sort -rn -k2 | head -n 3

# Clean up the temporary file
rm -f sorted_log.txt
