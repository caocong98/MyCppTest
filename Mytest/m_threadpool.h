#ifndef __THREADPOOL__H
#define __THREADPOLL__H

#include <thread>
#include <assert.h>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <queue>

using namespace std;

class ThreadPool{
public:
    ThreadPool(int ThreadNum = 8) : m_pool(make_shared<pool>()) {
        assert(ThreadNum > 0);
        for (int i = 0; i < ThreadNum; ++i) {
            thread([Pool = m_pool] () {
                unique_lock<mutex> lock(Pool->mtx);
                while (true) {
                    if (!Pool->tasks.empty()) {
                        auto task = Pool->tasks.front();
                        Pool->tasks.pop();
                        lock.unlock();
                        task();
                        lock.lock();
                    }
                    else if (Pool->isClosed) break;
                    else Pool->cond.wait(lock);
                }
            }).detach();
        }
    }

    ~ThreadPool() {
        if (m_pool) {
            {
                lock_guard<mutex> lock(m_pool->mtx);
                m_pool->isClosed = true;
                m_pool->cond.notify_all();
            }
        }
    }


    void AddTask(function<void()> task) {
        {
            lock_guard<mutex> lock(m_pool->mtx);
            m_pool->tasks.emplace(task);
        }
        m_pool->cond.notify_one();
    }

private:
    struct pool{
        bool isClosed;
        queue<function<void()>> tasks;
        mutex mtx;
        condition_variable cond;
    };
    shared_ptr<pool> m_pool;
};





#endif