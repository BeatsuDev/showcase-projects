#include <string>
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>

using namespace std;

void run_worker_threads(int worker_count);
void worker();
list<function<void()>> tasks;
mutex cout_lock; // For when printing with cout
mutex task_lock; // For when retrieving tasks

int main() {
    // Add tasks
    for (int i = 0; i < 10; i++) {
        tasks.emplace_back([i] {
            cout_lock.lock();
            cout << "Hi! I'm task "
                 << i
                 << " speaking from thread"
                 << this_thread::get_id()
                 << endl;
            cout_lock.unlock();

            this_thread::sleep_for(1s);

            cout_lock.lock();
            cout << "[task " << i << "]: Wow! That took a while..." << endl;
            cout_lock.unlock();
        });
    }

    // Run the worker threads
    run_worker_threads(4);

    // Should be complete now!
    return 0;
}

void run_worker_threads(int worker_count) {
    list<thread> worker_threads;
    for (int i = 0; i < worker_count; i++) {
        worker_threads.emplace_back(worker);
    }
    for (thread &t : worker_threads) {
        t.join();
    }
}

// A single worker
void worker() {
    while (!tasks.empty()) {
        // Define the task out of scope. We will want to run the task outside of the mutex lock
        function<void()> task;
        {
            // Lock the current scope while the worker retrieves the next task
            lock_guard<mutex> lock(task_lock);
            task = tasks.front();
            tasks.pop_front();
        }
        task();
    }
}