#include <iostream>
#include <thread>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <exception>

// Simulate time-consuming operations with random delay
void simulate_delay() {
    int delay = rand() % 5 + 3;  // Random delay between 3-7 seconds
    std::this_thread::sleep_for(std::chrono::seconds(delay));
}

// Mathematical operations with delay and exception handling
int add(int x, int y) { 
    simulate_delay(); 
    return x + y; 
}

int subtract(int x, int y) { 
    simulate_delay(); 
    return x - y; 
}

int multiply(int x, int y) { 
    simulate_delay(); 
    return x * y; 
}

double divide(int x, int y) { 
    simulate_delay(); 
    if (y == 0) throw std::runtime_error("Division by zero");
    return static_cast<double>(x) / y; 
}

double power(int x, int y) { 
    simulate_delay(); 
    return pow(x, y); 
}

// Wrapper functions for threading
void add_wrapper(int x, int y) {
    try {
        std::cout << "Addition result: " << add(x, y) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in addition: " << e.what() << std::endl;
    }
}

void subtract_wrapper(int x, int y) {
    try {
        std::cout << "Subtraction result: " << subtract(x, y) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in subtraction: " << e.what() << std::endl;
    }
}

void multiply_wrapper(int x, int y) {
    try {
        std::cout << "Multiplication result: " << multiply(x, y) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in multiplication: " << e.what() << std::endl;
    }
}

void divide_wrapper(int x, int y) {
    try {
        std::cout << "Division result: " << divide(x, y) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in division: " << e.what() << std::endl;
    }
}

void power_wrapper(int x, int y) {
    try {
        std::cout << "Power result: " << power(x, y) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in power calculation: " << e.what() << std::endl;
    }
}

// Function to take input from the user and run the operations sequentially
void take_user_input() {
    int x, y;
    
    // Addition
    std::cout << "Enter two numbers for Addition: ";
    std::cin >> x >> y;
    std::thread add_thread(add_wrapper, x, y);
    add_thread.join();  // Ensure the main thread waits for this to complete before continuing

    // Subtraction
    std::cout << "Enter two numbers for Subtraction: ";
    std::cin >> x >> y;
    std::thread subtract_thread(subtract_wrapper, x, y);
    subtract_thread.join();  // Wait for subtraction to complete

    // Multiplication
    std::cout << "Enter two numbers for Multiplication: ";
    std::cin >> x >> y;
    std::thread multiply_thread(multiply_wrapper, x, y);
    multiply_thread.join();  // Wait for multiplication to complete

    // Division
    std::cout << "Enter two numbers for Division: ";
    std::cin >> x >> y;
    std::thread divide_thread(divide_wrapper, x, y);
    divide_thread.join();  // Wait for division to complete

    // Power
    std::cout << "Enter base and exponent for Power Calculation: ";
    std::cin >> x >> y;
    std::thread power_thread(power_wrapper, x, y);
    power_thread.join();  // Wait for power calculation to complete
}

// Main function
int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    // Start timer for sequential thread execution
    auto start = std::chrono::steady_clock::now();

    // Take user input and run operations sequentially
    take_user_input();

    // End timer and display total time taken
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Total time taken for all operations: " << elapsed.count() << " seconds\n";

    // Now simulate 500 random operations
    std::cout << "\nRunning 500 random operations...\n";
    auto rand_start = std::chrono::steady_clock::now();

    for (int i = 0; i < 500; i++) {
        try {
            // Perform random operation (e.g., addition, subtraction, etc.)
            int x = rand() % 100;
            int y = rand() % 100;
            if (i % 5 == 0) divide(x, y);  // Introduce division by zero or valid division
            else if (i % 5 == 1) add(x, y);
            else if (i % 5 == 2) subtract(x, y);
            else if (i % 5 == 3) multiply(x, y);
            else power(x, y);  // Power calculation
        } catch (const std::exception &e) {
            std::cerr << "Exception during random operation: " << e.what() << std::endl;
        }
    }

    // End timer for random operations and display total time
    auto rand_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> rand_elapsed = rand_end - rand_start;
    std::cout << "Total time taken for 500 operations: " << rand_elapsed.count() << " seconds\n";

    return 0;
}
