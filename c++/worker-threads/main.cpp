#include "workers.h"
#include <iostream>
#include <mutex>
#include <string>

using namespace std;

mutex cout_lock;

void print_thread_safe(string message) {
    {
        lock_guard<mutex> lock(cout_lock);
        cout << message << "\n";
    }
}

int main() {
    workers::Workers worker_threads(4);
    workers::Workers event_loop(1);

    this_thread::sleep_for(1s);

    worker_threads.start();
    event_loop.start();

    this_thread::sleep_for(1s);

    worker_threads.post([] {
        // Task A
        this_thread::sleep_for(1s);
        print_thread_safe("Hello from task A!");
    });

    worker_threads.post([] {
        this_thread::sleep_for(1s);
        print_thread_safe("Hello from task B!");
        // Task B
        // Might run in parallel with task A
    });

    event_loop.post([] {
        this_thread::sleep_for(0.5s);
        print_thread_safe("Hello from task C!");
        // Task C
        // Might run in parallel with task A and B
    });
    event_loop.post([] {
        this_thread::sleep_for(1s);
        print_thread_safe("Hello from task D!");
        // Task D
        // Will run after task C
        // Might run in parallel with task A and B
    });

    worker_threads.join();
    event_loop.join();
    return 0;
}