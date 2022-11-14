#include <iostream>
#include <functional>
using namespace std;

//RTTI 原理演示 ， 通过虚表指针得到虚函数表，虚函数表-1索引位置type_info有对象相关信息,从而调用相应函数，dynamic_cast同样依据这个。
//对象首地址即为虚函数指针的地址

//两种情况 1、子类不重写虚函数   
//        2、子类重写虚函数


class A {
public:
    virtual void func1() { cout << "A::func1()\n"; }
    virtual void func2() { cout << "A::func2()\n"; }
};

class B : public A{
public:
    virtual void func1() { cout << "B::func1()\n"; }   //func1 重写
    // virtual void func2() { cout << "B1::func2()\n"; }
};


int main() {
    //利用引用测试多态
    B b1;
    A& a1 = b1;
    a1.func1(); //通过父类引用子类可以表现多态性质
    a1.A::func1(); //通过作用域符调用父类虚函数

    //情况1,2 及type_info获取测试
    A* a2 = new B();
    A* a3 = new A();

    long long* vptr1 = (long long*)a2;  //获取虚函数表指针,64位系统 long long 8位
    long long* vptr2 = (long long*)a3;

    long long* vtbl1 = (long long*)(*vptr1); //获取虚函数表首地址,表中存放函数地址
    long long* vtbl2 = (long long*)(*vptr2);

    // long long* vtbl1_t =  * (long long**) a2; //获取虚表地址等价写法1用long long形式表示地址
    // long long* vtbl2_t =  * (long long**) a3;

    long long** vtbl1_t = (long long**) * (long long**) a2; //获取虚表地址等价写法2用long long* 形式表示地址
    // int** vtbl1_t = (int**) * (int**) a2; //获取虚表地址等价写法2用int* 形式表示地址，调用没问题，取该地址的数值结果会损失精度
    long long** vtbl2_t = (long long**) * (long long**) a3;

    cout << vtbl1_t[0] << ' ' << vtbl2_t[0] << endl; //重写函数地址不同,这里表现为0x地址格式

    cout << vtbl1 << ' ' << vtbl2 << endl; //父类和子类虚表地址不同

    cout << vtbl1[0] << ' ' << vtbl2[0] << endl; //重写函数地址不同,这里表示为long long形式输出
    cout << vtbl1[1] << ' ' << vtbl2[1] << endl; //未重写函数地址相同
    // cout << *(vtbl1 + 1) << ' ' << *(vtbl2 + 1) << endl; //等价上一句
    // 获得type_info对象的指针，并调用其name成员函数 , -1索引位置
    cout << "\t[-1]: " << (vtbl1[-1]) << " -> " << ((type_info*)vtbl1[-1])->name() << endl;
    cout << "\t[-1]: " << (vtbl2[-1]) << " -> " << ((type_info*)vtbl2[-1])->name() << endl;
    cout << endl;
    cout << "\t[-1]: " << (vtbl1_t[-1]) << " -> " << ((type_info*)vtbl1_t[-1])->name() << endl;
    cout << "\t[-1]: " << (vtbl2_t[-1]) << " -> " << ((type_info*)vtbl2_t[-1])->name() << endl;
    // 利用虚函数表调用相应函数
    function<void()> f1 = (void(*)())vtbl1[0];
    function<void()> f2 = (void(*)())vtbl1_t[1];  //等价调用s
    f1();
    f2();
    function<void()> f3 = (void(*)())vtbl2[0];
    function<void()> f4 = (void(*)())vtbl2_t[0];
    f3();
    f4();
    return 0;
}

