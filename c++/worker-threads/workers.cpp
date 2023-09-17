#include "workers.h"
#include <atomic>
#include <mutex>
#include <list>
#include <thread>
#include <iostream>
#include <functional>

using namespace std::chrono_literals;

namespace workers {
    std::mutex cout_lock;
    std::mutex task_lock;

    void worker(int i, std::atomic<bool> &running, std::list<std::function<void()>> &task_list) {
        {
            const std::lock_guard<std::mutex> lock(cout_lock);
            std::cout << "Hello from thread " << i << "\n";
        }
        while (running) {
            std::function<void()> task;
            {
                const std::lock_guard<std::mutex> lock(task_lock);
                if (!task_list.empty()) {
                    task = task_list.front();
                    task_list.pop_front();
                }
            }

            if (task) {
                task();
            } else {
                std::this_thread::sleep_for(1ms);
            }
        }
    }

    Workers::Workers(int worker_count) {
        this->worker_count = worker_count;
    }

    void Workers::start() {
        running = true;
        for (int i = 0; i < worker_count; i++) {
            worker_threads.emplace_back(std::thread(worker, i, std::ref(running), std::ref(task_list)));
        }

    }

    void Workers::post(std::function<void()> task) {
        {
            const std::lock_guard<std::mutex> lock(task_lock);
            task_list.emplace_back(task);
        }
    }

    void Workers::join() {
        {
            std::lock_guard<std::mutex> lock(cout_lock);
            // std::clog << "Waiting for tasks to finish...\n";
        }

        // Wait for the task list to become empty
        while (!task_list.empty()) {
            std::this_thread::sleep_for(1ms);
        }
        
        {
            std::lock_guard<std::mutex> lock(cout_lock);
            // std::cout << "Joining all threads!\n";
        }
        running = false;
        for (std::thread &t : worker_threads) {
            t.join();
        }
    }
}