#include <iostream>
#include "externb.cpp"
#include <assert.h>
using namespace std;

extern int i;

class A {
public:
    A () : i(2) {
        cout << "run constructor1.\n";
    }
    A (int x) : i(x) {
        cout << "run constructor2.\n";
    }
    //拷贝构造
    A (const A& rhs) {
        i = rhs.i;
        cout << "run copy constructor.\n";
    }
    //拷贝赋值
    A& operator = (const A& rhs) {
        cout << "run copy assign.\n";
        if (this == &rhs) return *this;
        i = rhs.i;
        return *this;
    }

    int i;
};

int func(int a) {
    assert(a >= 0);
    return a;
}

int main() {

    cout << i << endl;
    A a;
    A b(1);
    cout << a.i << ' ' << b.i << endl;
    A c = 5;
    A d = a;
    c = b;


    int* x = new int[3]();
    cout << *(x + 1) << endl;

    A* y = new A[3];
    cout << (y + 1)->i << endl;

    cout << func(-1) << endl;
    return 0;
}