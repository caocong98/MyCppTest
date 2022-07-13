#include <iostream>
#include "Single_pattern.h"
using namespace std;

int main() {
    //懒汉测试1
    static SingleP1* sp1 = SingleP1::getmyinstance();
    sp1->test();
    //懒汉测试2
    static SingleP2* sp2 = SingleP2::getmyinstance();
    sp2->test();
    //饿汉模式
    static SingleP3* sp3 = SingleP3::getmyinstance();
    sp3->test();
    return 0;
}