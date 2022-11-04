#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;

//三个线程交替打印ABC  假设打印5次

mutex mtx;
condition_variable mcon;
const int TIMES = 5;
int state = 0; //转态转移

void printa() {
    unique_lock<mutex> lc(mtx);
    for (int i = 0; i < TIMES; ++i) {
        while (state != 0) mcon.wait(lc);
        cout << "a";
        state = 1;
        mcon.notify_all();
    }
    cout << "print a finish\n";
};

void printb() {
    unique_lock<mutex> lc(mtx);
    for (int i = 0; i < TIMES; ++i) {
        while (state != 1) mcon.wait(lc);
        cout << "b";
        state = 2;
        mcon.notify_all();
    }
    cout << "print b finish\n";
}

void printc() {
    unique_lock<mutex> lc(mtx);
    for (int i = 0; i < TIMES; ++i) {
        while (state != 2) mcon.wait(lc);
        cout << "c";
        state = 0;
        mcon.notify_all();
    }
    cout << "print c finish\n";
}



int main() {
    thread a(printa);
    thread b(printb);
    thread c(printc);
    a.join();
    b.join();
    c.join();
    return 0;
}