Task 1: Handling Signals
File: 24CS60R81_A10_T1.c
Description:
This program continuously reads input characters from the user in a loop. It handles different input cases as follows:

If the input is an alphabet (excluding 'x'), the program prints the character.
If the input is not an alphabet, it prints the message "Do you speak my language?".
If the user presses Ctrl + C (which sends the SIGINT signal), the program intercepts this and prints "I am unstoppable!" instead of terminating.
If the input is the character 'x', the program prints "Valar Morghulis" and terminates.

Compilation:
Use the following command to compile the code:
       gcc 24CS60R81_A10_T1.c -o problem1
Execution:
    ./problem




Task 2: Using Mutexes and Pthreads for Synchronization
File: 24CS60R81_A10_T2.c
Description:
This program simulates synchronization using pthreads and mutexes. It creates a matrix M of random integers and utilizes multiple threads to perform the following operations:

Chaos Thread:

Randomly updates 30 elements of the matrix at random positions.
After each update, it records the row that was changed.
The chaos thread sleeps for 2 seconds after each update and terminates after 30 updates.
Order Threads:

Three order threads continuously monitor for any rows updated by the chaos thread.
Once an updated row is detected, an order thread sorts that row in non-decreasing order.
The order thread prints the row both before and after sorting.
Each order thread terminates once all updates are processed.
Compilation:
Use the following command to compile the code:
     gcc -pthread 24CS60R81_A10_T2.c -o problem2
Execution :
      ./problem2
