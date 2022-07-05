#include <iostream>
#include <vector>
#include "Vector.h"

using std::cout; 
using std::endl;

struct X{
    X(int a = 0) {x=a;cout << "constructor X()" << a << endl;}
    X(const X& Xa) {x=Xa.x; cout << "X(const X&)" << x << endl;}
    X& operator = (const X& rhs) {
        cout << "operator = " << endl;
        if (this == &rhs) return *this;
        x = rhs.x;
        return *this;
    }
    ~X(){cout << "~X()" << x << endl;}
	int x;
};

int main(int argc, char **argv)
{
    // cout << "定义局部变量：" << endl;
    // // X x(1);
	// X y(2);

    // std::vector<X> vec;
    // cout << "\n存放在容器：" << endl;
    // vec.push_back(y);
    // // vec.push_back(y);
	// // vec.push_back(x);
	// // vec.push_back(y);
    // cout << endl;

    // cout << "程序结束！！！" << endl;

    cout << "定义局部变量：" << endl;
    // X x(1);
	X y(2);

    Vector<X> vec;
    cout << "\n存放在容器：" << endl;
    vec.push_back(y);
    // vec.push_back(y);
	// vec.push_back(x);
	// vec.push_back(y);
    cout << endl;

    cout << "程序结束！！！" << endl;

    // // 测试存指针
    // std::vector<int*> v8;
    // int* x = new int(2);
    // v8.push_back(x);
    // cout << *v8[0] << endl;
    // *x = 3;
    // cout << *v8[0] << endl;    
    return 0;
}
