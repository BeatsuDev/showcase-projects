#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

void solution1();
void solution2();
void solution3();

int main() {
    auto start = high_resolution_clock::now();
    solution1();
    // solution2();
    // solution3();
    auto stop = high_resolution_clock::now();
    cout << "Program run time: " << duration_cast<milliseconds>(stop - start).count() << "ms." << endl;
    return 0;
}

// A natural straight forward solution to a problem where you want a
// thread to run as long as some condition or flag is true.
void solution1() {
    bool flag = true;

    thread t([&flag] {
        // Run as long as the flag is true.
        while (flag) {}
    });

    this_thread::sleep_for(2s);
    flag = false;

    t.join();
}

// Using atomic values instead.
void solution2() {
    atomic<bool> flag(true);

    thread t([&flag] {
        while (flag) {}
    });

    this_thread::sleep_for(2s);
    flag = false;

    t.join();
}

// Less CPU strain by adding a sleep inside the spawned thread
void solution3() {
    atomic<bool> flag(true);

    thread t([&flag] {
        while (flag) {
            this_thread::sleep_for(20ms);
        }
    });

    this_thread::sleep_for(2s);
    flag = false;

    t.join();
}

