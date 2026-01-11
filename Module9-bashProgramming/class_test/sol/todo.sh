#!/bin/bash

# File to store the to-do list
todo_file="todo_list.txt"

# Ensure the to-do file exists
touch "$todo_file"

# Function to sanitize input (removes extra spaces)
sanitize() {
    echo "$1" | xargs
}

# Function to add a new task
add_task() {
    local description
    description=$(sanitize "$1")  # Sanitize the description input
    local priority="$2"

    # Validate priority level
    if [[ "$priority" != "high" && "$priority" != "medium" && "$priority" != "low" ]]; then
        echo "Error: Invalid priority level. Use 'high', 'medium', or 'low'."
        exit 1
    fi

    # Check if a task with the same exact description already exists
    if awk -F '|' -v desc="$description" '$2 ~ "^\s*"desc"\s*$" {exit 1}' "$todo_file"; then
        echo "Error: A task with the same description already exists."
        exit 1
    fi

    # Generate a unique task ID
    local last_id=$(awk -F '|' '{print $1}' "$todo_file" | sort -n | tail -1)
    if [[ -z "$last_id" ]]; then
        last_id=0  # If no tasks exist, start with ID 1
    fi
    local task_id=$((last_id + 1))

    # Add the new task
    echo "$task_id | $description | $priority | incomplete" >> "$todo_file"
    echo "Task added successfully with ID: $task_id"
}

# Function to mark a task as complete
complete_task() {
    local task_id="$1"

    # Check if the task ID exists
    if ! grep -q "^$task_id |" "$todo_file"; then
        echo "Error: Task ID $task_id not found."
        exit 1
    fi

    # Mark the task as complete
    sed -i "s/^$task_id | \(.*\) | incomplete$/$task_id | \1 | complete/" "$todo_file"
    echo "Task $task_id marked as complete."
}

# Function to display tasks sorted by priority and status
show_tasks() {
    echo "Tasks (Sorted by Priority and Status):"
    echo "-------------------------------------"
    echo "ID | Description         | Priority | Status"

    # Remove duplicate lines from the file (if any)
    awk '!seen[$0]++' "$todo_file" > temp.txt && mv temp.txt "$todo_file"

    # Print incomplete tasks first, sorted by priority and ID
    awk -F '|' '$4 ~ /incomplete/ {print $0}' "$todo_file" | sort -t '|' -k3,3 -k1,1n

    # Print completed tasks, sorted by priority and ID
    awk -F '|' '$4 ~ /complete/ {print $0}' "$todo_file" | sort -t '|' -k3,3 -k1,1n
}

# Main logic to handle operations
case "$1" in
    add)
        if [ $# -ne 3 ]; then
            echo "Usage: ./todo.sh add <task_description> <priority>"
            exit 1
        fi
        add_task "$2" "$3"
        ;;
    complete)
        if [ $# -ne 2 ]; then
            echo "Usage: ./todo.sh complete <task_id>"
            exit 1
        fi
        complete_task "$2"
        ;;
    show)
        if [ $# -ne 1 ]; then
            echo "Usage: ./todo.sh show"
            exit 1
        fi
        show_tasks
        ;;
    *)
        echo "Error: Invalid operation. Use 'add', 'complete', or 'show'."
        exit 1
        ;;
esac
