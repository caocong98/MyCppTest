#include <iostream>
#include <thread>
#include "windows.h"
using namespace std;

//内存泄漏指的是进程还未结束的情况，若进程结束，所有堆上分配的内存都会由OS释放



long long fun1(int num) {
    int* fun2a = new int(num);
    printf("the address of point fun2a: %p\n", &fun2a);
    return (long long) fun2a;
}

void fun2(int num, int** p) {
    // detach后，主进程结束后仍取不到内存存储的值
    *p = new int(num);
    Sleep(100 * 1000);
    cout << **p << endl;
    // Sleep(1000);
}

int main() {
    long long p1, p2;
    //多线程 函数内变量地址不同
    // 多线程取线程返回值 示例   join version
    thread mythread1([&]{ p1 = fun1(1);});
    thread mythread2([&]{ p2 = fun1(2);});
    mythread1.join();
    mythread2.join();
    cout << *(int*) p1 << " " << *(int*) p2 << endl;

    // detach version
    thread mythread3([&]{ p1 = fun1(3);});
    thread mythread4([&]{ p2 = fun1(4);});
    mythread3.detach();
    mythread4.detach();
    Sleep(500);
    cout << *(int*) p1 << " " << *(int*) p2 << endl;


    return 0;
}