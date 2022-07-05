#ifndef __SINGLEPATTERN__
#define __SINGLEPATTERN__

#include <mutex>
#include <thread>
#include <iostream>

// std::mutex mym;
// 懒汉模式 延时加载 双锁或局部静态对象
class SinglePa {
private:
    SinglePa(int aa = 0) : a(aa) { std::cout << "creat a object1." << std::endl;}
    SinglePa(const SinglePa&);
    SinglePa& operator = (const SinglePa&);
    int a;

    static SinglePa* myInstance;
    static std::mutex mym;              // 锁也放内部
public:
    void test() {

        std::cout << "test static use nostatic, a: " << a << std::endl;
    }
    ~SinglePa() { std::cout << "object1 delete." << std::endl; }
    static void destroy() { delete myInstance; }
    static SinglePa* get_instance() {
        if (nullptr == myInstance) {
            std::cout << "lock now." << std::endl;
            mym.lock();
            if (nullptr == myInstance) {
                myInstance = new SinglePa(4);
            }
            mym.unlock();
            std::cout << "unloce now." << std::endl;
        }
        // std::cout << "hhh" << std::endl;
        return myInstance;
    }
};

SinglePa* SinglePa::myInstance = nullptr;   // ！！！
std::mutex SinglePa::mym;                   // ！！！

// 懒汉模式  局部静态版本

class SinglePb {
private:
    SinglePb() { std::cout << "creat a object2." << std::endl; }
    SinglePb(const SinglePb&);
    SinglePb& operator = (const SinglePb&);

public:
    ~SinglePb() { std::cout << "object2 delete." << std::endl; }
    static SinglePb* get_instance() {
        static SinglePb myInstance;
        return &myInstance;
    }
};


// 饿汉模式

class SinglePc {
private:
    SinglePc() { std::cout << "create a object3." << std::endl; }
    SinglePc(const SinglePc&);
    SinglePc& operator = (const SinglePc&);

    static SinglePc* myInstance;

public:
    static void destroy() { delete myInstance; }
    ~SinglePc() { std::cout << "objectc delete." << std::endl; }
    static SinglePc* get_instance() {
        return myInstance;
    }

};

SinglePc* SinglePc::myInstance = new SinglePc();


#endif