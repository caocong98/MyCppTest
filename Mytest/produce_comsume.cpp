#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <windows.h>
#include <thread>
// #include <bits/stdc++.h>
using namespace std;
// 生产消费模型  共享缓冲区， 同一时刻只能一个人操作缓冲区
// 通过全局变量，及条件变量互斥锁实现线程同步机制

queue<int> goods;
const int GOODSIZE = 10;  //缓冲区能存最大商品数量
mutex mtx;
condition_variable mycondition;
int ProgoodId = 0;
int CongoodId = 0;

//四个生产者、消费者
const int PRODUCERNUM = 4;
const int CONSUMERNUM = 4;

// version1  不限总生产数量，无限循环
void produce1(int proID) {
    while (true) {
        Sleep(500);  //控制速度 （结果输出等）
        unique_lock<mutex> lk(mtx);  //管理锁的辅助类工具
        // mycondition.wait(lk, []() { return goods.size() < GOODSIZE; });   // 写法1 可以解决虚假唤醒
        while (goods.size() >= 10) {  //循环判断写法，解决虚假唤醒
            mycondition.wait(lk);
        }
        ++ProgoodId;
        int data = rand();  // 实际生产过程
        goods.push(data);   // 加入缓冲区
        mycondition.notify_all(); // 提醒等待消费者进行消费
        cout << "Producer" << proID << " procude good" << ProgoodId << ": " << data << endl;
        //  Sleep(1000)  模拟生产者生产后的工作。
    }
}

void consume1(int conID) {
    while (true) {
        unique_lock<mutex> lk(mtx);
        while (goods.empty()) {
            mycondition.wait(lk);
        }
        int data = goods.front();
        ++CongoodId;
        goods.pop();
        mycondition.notify_all();  //通知等待生产的生产者生产
        cout << "\tConsumer" << conID << " consume good" << CongoodId << ": " << data << endl;
        // Sleep(1000) 模拟消费者消费后动作
    }
}

// version2 限制总生产数量100；
const int TOTALGOOD = 100;

void produce2(int proID) {
    while (true) {
        Sleep(500);  //控制速度 （结果输出等）
        unique_lock<mutex> lk(mtx);  //管理锁的辅助类工具
        // mycondition.wait(lk, []() { return goods.size() < GOODSIZE; });   // 写法1 可以解决虚假唤醒
        while (goods.size() >= 10 && ProgoodId < TOTALGOOD) {  //循环判断写法，解决虚假唤醒
            mycondition.wait(lk);
        }
        if (ProgoodId >= TOTALGOOD) break;
        ++ProgoodId;
        int data = rand();  // 实际生产过程
        goods.push(data);   // 加入缓冲区
        mycondition.notify_all(); // 提醒等待消费者进行消费
        cout << "Producer" << proID << " procude good" << ProgoodId << ": " << data << endl;
        //  Sleep(1000)  模拟生产者生产后的工作。
    }
    cout << "Producer" << proID << " quit." << endl;
}

void consume2(int conID) {
    while (true) {
        unique_lock<mutex> lk(mtx);
        while (goods.empty() && CongoodId < TOTALGOOD) {
            mycondition.wait(lk);
        }
        if (CongoodId >= TOTALGOOD) break;
        int data = goods.front();
        ++CongoodId;
        goods.pop();
        mycondition.notify_all();  //通知等待生产的生产者生产
        cout << "\tConsumer" << conID << " consume good" << CongoodId << ": " << data << endl;
        // Sleep(1000) 模拟消费者消费后动作
    }
    cout << "\tConsumer" << conID << " quit." << endl;
}

int main() {

    thread PRODUCERPOOL[PRODUCERNUM];
    thread CONSUMERPOOL[CONSUMERNUM];
    for (int i = 0; i < PRODUCERNUM; ++i) {
        // PRODUCERPOOL[i] = thread(produce1, i + 1);
        PRODUCERPOOL[i] = thread(produce2, i + 1);  // version2
    }

    for (int i = 0; i < CONSUMERNUM; ++i) {
        // CONSUMERPOOL[i] = thread(consume1, i + 1);
        CONSUMERPOOL[i] = thread(consume2, i + 1);
    }
    for (int i = 0; i < PRODUCERNUM; i++)
    {
        PRODUCERPOOL[i].join();  //第一次运行就阻塞在这
    }

    cout << "test\n";

    for (int i = 0; i < CONSUMERNUM; i++)
    {
        CONSUMERPOOL[i].join();
    }

    return 0;
}




