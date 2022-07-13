#include <iostream>
#include <memory>
using namespace std;

// //死锁 shared_ptr
// class B;
// class A
// {
// public:
//     A() { cout << "A()\n"; }
//     ~A() { cout << "~A()\n"; }

//     shared_ptr<B> ptra;
// };
// class B 
// {
// public:
//     B() { cout << "B()\n"; }
//     ~B() { cout << "~B()\n"; }

//     shared_ptr<A> ptrb;
// };

// weak_prt
class B;
class A
{
public:
    A() { cout << "A()\n"; }
    ~A() { cout << "~A()\n"; }

    weak_ptr<B> ptra;
};
class B 
{
public:
    B() { cout << "B()\n"; }
    ~B() { cout << "~B()\n"; }

    weak_ptr<A> ptrb;
};

int main() {
    shared_ptr<A> a(new A());
    shared_ptr<B> b(new B());
    a->ptra = b;
    b->ptrb = a;
    shared_ptr<int> c = make_shared<int>(3);
    cout << *c << endl;
    cout << *c.get() <<  endl;
    weak_ptr<int> d = c;
    // cout << *d << endl;  //wrong
    cout << *d.lock() << endl;
    return 0;
}