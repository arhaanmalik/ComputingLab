#include <iostream>
#include <pthread.h>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;

// Define a struct to hold input parameters and result
struct OperationData {
    int x;
    int y;
    double result; // Result is double for division, can hold int for other operations
    bool thread_failed; // Track if thread creation failed
};

// Mathematical operations
int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
double divide(int x, int y) { return y != 0 ? static_cast<double>(x) / y : 0; } // Handle division by zero
int power(int x, int y) { return pow(x, y); }

// Wrapper functions for threading
void* add_wrapper(void* arg) {
    OperationData* data = (OperationData*)arg;
    data->result = add(data->x, data->y);
    return nullptr;
}

void* subtract_wrapper(void* arg) {
    OperationData* data = (OperationData*)arg;
    data->result = subtract(data->x, data->y);
    return nullptr;
}

void* multiply_wrapper(void* arg) {
    OperationData* data = (OperationData*)arg;
    data->result = multiply(data->x, data->y);
    return nullptr;
}

void* divide_wrapper(void* arg) {
    OperationData* data = (OperationData*)arg;
    data->result = divide(data->x, data->y);
    return nullptr;
}

void* power_wrapper(void* arg) {
    OperationData* data = (OperationData*)arg;
    data->result = power(data->x, data->y);
    return nullptr;
}

int main() {
    pthread_t threads[5];
    OperationData data[5];

    // Get user input for each operation
    cout << "Enter two numbers for Addition:" << endl;
    cin >> data[0].x >> data[0].y; // For addition

    cout << "Enter two numbers for Subtraction:" << endl;
    cin >> data[1].x >> data[1].y; // For subtraction

    cout << "Enter two numbers for Multiplication:" << endl;
    cin >> data[2].x >> data[2].y; // For multiplication

    cout << "Enter two numbers for Division:" << endl;
    cin >> data[3].x >> data[3].y; // For division

    cout << "Enter two numbers for Exponentiation:" << endl;
    cin >> data[4].x >> data[4].y; // For exponentiation

    // Initialize thread_failed to false for all operations
    for (int i = 0; i < 5; i++) {
        data[i].thread_failed = false;
    }

    // Create threads for each operation
    if (pthread_create(&threads[0], nullptr, add_wrapper, &data[0]) != 0) {
        data[0].thread_failed = true;
    }

    if (pthread_create(&threads[1], nullptr, subtract_wrapper, &data[1]) != 0) {
        data[1].thread_failed = true;
    }

    if (pthread_create(&threads[2], nullptr, multiply_wrapper, &data[2]) != 0) {
        data[2].thread_failed = true;
    }

    if (pthread_create(&threads[3], nullptr, divide_wrapper, &data[3]) != 0) {
        data[3].thread_failed = true;
    }

    if (pthread_create(&threads[4], nullptr, power_wrapper, &data[4]) != 0) {
        data[4].thread_failed = true;
    }

    // Wait for all threads to finish if they were created successfully
    for (int i = 0; i < 5; i++) {
        if (!data[i].thread_failed) {
            pthread_join(threads[i], nullptr);
        }
    }

    // Display results
    cout << "Results:" << endl;
    cout << "Addition: " << data[0].x << " + " << data[0].y << " = " 
         << (data[0].thread_failed ? "Thread failed" : to_string(static_cast<int>(data[0].result))) << endl;
    cout << "Subtraction: " << data[1].x << " - " << data[1].y << " = " 
         << (data[1].thread_failed ? "Thread failed" : to_string(static_cast<int>(data[1].result))) << endl;
    cout << "Multiplication: " << data[2].x << " * " << data[2].y << " = " 
         << (data[2].thread_failed ? "Thread failed" : to_string(static_cast<int>(data[2].result))) << endl;
    cout << "Division: " << data[3].x << " / " << data[3].y << " = " 
         << (data[3].thread_failed ? "Thread failed" : to_string(data[3].result)) << endl;
    cout << "Exponentiation: " << data[4].x << " ^ " << data[4].y << " = " 
         << (data[4].thread_failed ? "Thread failed" : to_string(static_cast<int>(data[4].result))) << endl;

    // Random operations for testing performance
    auto start = chrono::high_resolution_clock::now(); // Start timer
    for (int i = 0; i < 500; i++) {
        // Perform random operation (for simplicity, we'll do addition here)
        if (pthread_create(&threads[0], nullptr, add_wrapper, &data[0]) == 0) {
            pthread_join(threads[0], nullptr);
        }
    }
    auto end = chrono::high_resolution_clock::now(); // End timer
    auto total_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // Display total time taken for 500 operations
    cout << "Total time taken for 500 operations: " << total_duration << " microseconds" << endl;

    return 0;
}
