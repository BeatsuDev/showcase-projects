#include <list>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>

namespace workers {
    class Workers {
        private:
            std::list<std::thread> worker_threads;
            std::list<std::function<void()>> task_list;
            std::atomic<bool> running;
            int worker_count;

        public:
            Workers(int worker_count);
            void start();
            void post(std::function<void()>);
            void join();
    };
}