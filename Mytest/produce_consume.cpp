#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <windows.h>
using namespace std;

queue<int> Q;
const int PRODUCER_NUM = 5;
const int CONSUMER_NUM = 5;
const int MAX_GOODS = 5;  // 队列中存在最多商品数量
const int TOTAL_GOODS = 100;  //生产总数
int PRO_NUM = 0, CON_NUM = 0;

mutex mtx;
condition_variable Mycon;

void produce1(int proID) {
    while (true) {
        Sleep(500);
        unique_lock<mutex> lk(mtx);
        while (Q.size() == MAX_GOODS) {
            Mycon.wait(lk);
        }
        ++PRO_NUM;
        int good = rand();
        Q.push(good);
        printf("Producer%d produce good%d\n", proID, PRO_NUM);
        Mycon.notify_all();
    }
}

void consume1(int conID) {
    while (true) {
        Sleep(500);
        unique_lock<mutex> lk(mtx);
        while (Q.empty()) {
            Mycon.wait(lk);
        }
        ++CON_NUM;
        Q.pop();
        printf("Consumer%d consume good%d\n", conID, CON_NUM);
        Mycon.notify_all();        
    }
}



int main() {
    thread PRODUCER[PRODUCER_NUM];
    thread CONSUMER[CONSUMER_NUM];
    for (int i = 0; i < PRODUCER_NUM; ++i) {
        PRODUCER[i] = thread(produce1, i + 1);
    }
    for (int i = 0; i < CONSUMER_NUM; ++i) {
        CONSUMER[i] = thread(consume1, i + 1);
    }
    for (int i = 0; i < PRODUCER_NUM; ++i) {
        PRODUCER[i].join();
        CONSUMER[i].join();
    }
    return 0;
}