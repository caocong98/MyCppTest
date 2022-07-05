#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A create.\n";
    }
    virtual void foo() {
        cout << "A\n";
    }
    virtual ~A() {
        cout << "A destroy.\n";
    }
};

class B: public A {
public:
    B() {
        cout << "B create.\n";
    }
    void foo() {
        cout << "B\n";
    }
    ~B() {
        cout << "B destroy.\n";
    }
};

int main() {
    A* x = new B();
    x->foo();
    x->A::foo();
    delete x;
    string s = "\\";  // 输出\需要反义字符
    char c = '\\';
    cout << c << endl;
    return 0;
}