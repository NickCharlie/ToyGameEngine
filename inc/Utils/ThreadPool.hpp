#pragma once

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <functional>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t num_threads)
        : pool(num_threads) // 初始化线程池
    {
    }

    ~ThreadPool() 
    {
        // 等待所有任务完成
        pool.join();
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 提交任务到线程池
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

private:
    boost::asio::thread_pool pool;
};

template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {

    using return_type = decltype(f(args...));

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    boost::asio::post(pool, [task]() {
        (*task)();
    });

    return res;
}