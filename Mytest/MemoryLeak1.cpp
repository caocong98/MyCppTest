#include <iostream>
#include <thread>
// #include "windows.h"
using namespace std;

//内存泄漏指的是进程还未结束的情况，若进程结束，所有堆上分配的内存都会由OS释放


long long fun1() {
    int* fun1a = new int(2);
    cout << "the address of point fun1a: " << &fun1a << endl;
    // 进程未结束 fun1a申请的内存处于泄漏情况
    return (long long) fun1a;
}

long long fun2() {
    int* fun2a = new int(2);
    printf("the address of point fun2a: %p\n", &fun2a);
    return (long long) fun2a;
}

int main() {
    // 该例中fun1 和fun2中对象地址相同，根据栈区特性
    int* b;
    cout << sizeof(b) << endl;  // 64为 指针占8字节
    long long c = fun1(); // 该堆上内容不能在进程结束后重新取出地址的实际数值
    cout << c << endl;
    b = (int*)c;
    cout << *b << endl;
    int d = 3;
    fun2();
    return 0;
}