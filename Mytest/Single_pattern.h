#ifndef __SINGLEPATTERN__H
#define __SINGLEPATTERN__H


#include <mutex>
#include <iostream>


// 懒汉模式局部静态对象  C++11以上支持 不加锁

class SingleP1 {
public:
    static SingleP1* getmyinstance() {
        static SingleP1 SP;
        return &SP;
    }

    void test() {
        std::cout << "test success.\n";
    }

private:
    SingleP1(int v = 0) : value(v){};
    SingleP1(const SingleP1&);
    SingleP1& operator = (const SingleP1&);

private:
    int value;

};

// 懒汉模式双锁版本

class SingleP2 {

public:
    static SingleP2* getmyinstance() {
        if (SP == nullptr) {
            mtx.lock();
            if (SP == nullptr) {
                SP = new SingleP2();
            }
            mtx.unlock();
        }
        return SP;
    }

    void test() {
        std::cout << "test success.\n";
    }

private:
    SingleP2(int v = 0) : value(v) {};
    SingleP2(const SingleP2&);
    SingleP2& operator = (const SingleP2&);

    static SingleP2* SP;
    int value;
    static std::mutex mtx;

};

SingleP2* SingleP2::SP = nullptr;
std::mutex SingleP2::mtx; 


//饿汉模式，直接初始化好，不用加锁
class SingleP3 {
public:
    static SingleP3* getmyinstance() {
        return SP;
    }
    
    void test() {
        std::cout << "test success.\n";
    }

private:
    SingleP3(int v = 0) : value(v) {};
    SingleP3(const SingleP3&);
    SingleP3& operator = (const SingleP3&);

    static SingleP3* SP;
    int value;


};

SingleP3* SingleP3::SP = new SingleP3();


#endif