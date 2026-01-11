#include <iostream>
#include <coroutine>
#include <future>
#include <thread>
#include <chrono>
#include <cmath>
#include <atomic>
#include <vector>
#include <functional>
#include <stdexcept>
#include <queue>
#include <memory>

using namespace std;

// Asynchronous Mathematical Functions (Coroutines)
auto async_addition(int a, int b) -> future<int> {
    return async([a, b]() {
        this_thread::sleep_for(chrono::seconds(2));  // Simulating delay
        return a + b;
    });
}

auto async_subtraction(int a, int b) -> future<int> {
    return async([a, b]() {
        this_thread::sleep_for(chrono::seconds(2));  // Simulating delay
        return a - b;
    });
}

auto async_multiplication(int a, int b) -> future<int> {
    return async([a, b]() {
        this_thread::sleep_for(chrono::seconds(2));  // Simulating delay
        return a * b;
    });
}

auto async_division(int a, int b) -> future<double> {
    return async([a, b]() {
        this_thread::sleep_for(chrono::seconds(2));  // Simulating delay
        if (b == 0) throw invalid_argument("Division by zero");
        return static_cast<double>(a) / b;
    });
}

auto async_exponentiation(int base, int exp) -> future<int> {
    return async([base, exp]() {
        this_thread::sleep_for(chrono::seconds(2));  // Simulating delay
        return static_cast<int>(pow(base, exp));
    });
}

// Lock-Free Queue using atomic pointers
template<typename T>
class LockFreeQueue {
public:
    LockFreeQueue() : head(new Node()), tail(head.load()) {}
    ~LockFreeQueue() {
        while (Node* old_head = head.load()) {
            head.store(old_head->next);
            delete old_head;
        }
    }

    void enqueue(T task) {
        Node* new_node = new Node(task);
        Node* old_tail = tail.exchange(new_node);
        old_tail->next = new_node;
    }

    bool dequeue(T& result) {
        Node* old_head = head.load();
        Node* next_node = old_head->next;
        if (next_node == nullptr) return false;  // Queue is empty
        result = next_node->task;
        head.store(next_node);
        delete old_head;
        return true;
    }

private:
    struct Node {
        T task;
        Node* next = nullptr;
        Node() {}
        Node(T t) : task(t), next(nullptr) {}
    };

    atomic<Node*> head;
    atomic<Node*> tail;
};

// Thread Pool Class with lock-free queue
class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void enqueueTask(function<void()> task);

private:
    vector<thread> workers;
    LockFreeQueue<function<void()>> taskQueue;
    atomic<bool> stop;
    void workerThread();
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { workerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    for (thread &worker : workers) {
        worker.join();
    }
}

void ThreadPool::enqueueTask(function<void()> task) {
    taskQueue.enqueue(task);
}

void ThreadPool::workerThread() {
    while (!stop) {
        function<void()> task;
        if (taskQueue.dequeue(task)) {
            task();  // Execute the task
        } else {
            this_thread::yield();  // Yield if no task is available (non-blocking)
        }
    }
}

// Coroutine Task System to manage tasks
void coroutine_task_system(vector<future<int>>& intTasks, vector<future<double>>& doubleTasks) {
    for (auto &task : intTasks) {
        try {
            cout << "Result (int): " << task.get() << endl;  // Blocks until the result is ready
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    for (auto &task : doubleTasks) {
        try {
            cout << "Result (double): " << task.get() << endl;  // Blocks until the result is ready
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// Assign jobs to the thread pool
void assign_jobs(ThreadPool &pool, vector<function<void()>> jobs) {
    for (auto &job : jobs) {
        pool.enqueueTask(job);  // Assign job to thread pool
    }
}

int main() {
    ThreadPool pool(50);  // Thread pool with 50 threads
    vector<function<void()>> jobs;
    vector<future<int>> intFutures;
    vector<future<double>> doubleFutures;
    int a, b;

    // Taking input from the user
    cout << "Enter two numbers (a and b): ";
    while (!(cin >> a >> b)) {
        cout << "Invalid input. Please enter valid integers: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Create jobs for basic operations with proper async execution and result fetching
    intFutures.push_back(async_addition(a, b));
    intFutures.push_back(async_subtraction(a, b));
    intFutures.push_back(async_multiplication(a, b));

    // Async division with exception handling for division by zero
    doubleFutures.push_back(async_division(a, b));

    intFutures.push_back(async_exponentiation(a, 3));

    // Assign jobs to thread pool and retrieve results
    coroutine_task_system(intFutures, doubleFutures);

    return 0;
}

