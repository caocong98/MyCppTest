#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <assert.h>
#include <windows.h>
using namespace std;

thread_local int sum = 0;

class ThreadPool {
public:
    ThreadPool(int threadNum = 8) : m_pool(make_shared<Pool>()) {
        assert(threadNum > 0);
        for (int i = 0; i < threadNum; ++i) {
            thread([=] {
                unique_lock<mutex> locker(m_pool->mtx);
                while (true) {
                    if (!m_pool->tasks.empty()) {
                        auto task = move(m_pool->tasks.front());
                        m_pool->tasks.pop();
                        locker.unlock();
                        task();
                        locker.lock();
                    }
                    else if (m_pool->isClosed) break;
                    else m_pool->cond.wait(locker);
                }
            }).detach();
        }
    }

    ~ThreadPool() {
        if (m_pool) {
            m_pool->isClosed = true;
            m_pool->cond.notify_all();
        }
    }

    void AddTask(function<void()> task) {
        {
            lock_guard<mutex> locker(m_pool->mtx);
            m_pool->tasks.emplace(task);
        }
        m_pool->cond.notify_one();
    }

private:
    struct Pool {
        mutex mtx;
        condition_variable cond;
        queue<function<void()>> tasks;
        bool isClosed;
    };
    shared_ptr<Pool> m_pool;
};

void func(int n) {
    // int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    cout << sum << endl;
}


int main() {
    unique_ptr<ThreadPool> m_Pool(make_unique<ThreadPool>(4));
    int taskNum = 4;
    int num = 0;
    for (int i = 1; i <= taskNum; ++i) {
        m_Pool->AddTask(bind(func, i));
    }
    Sleep(2000);
    return 0;
}