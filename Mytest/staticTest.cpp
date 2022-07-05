#include <iostream>
using namespace std;

class A {
public:
    A(int aa = 0) : a(aa) {}
    void printf1() {
        cout << a << endl;
    }
    static void printf() {
        cout << "test object use static fuc." << endl;
        cout << myInstance.a << endl;
    }
    int a;
    static A myInstance;
};

A A::myInstance(3);

int main() {
    A::printf();
    A a(4);
    a.printf1();
    A::myInstance.printf1();
    return 0;
}