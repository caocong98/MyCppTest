#ifndef __VECTOR_H
#define __VECTOR_H

#include <assert.h>

template<class T>
class Vector {
public:
    // 构造函数
    // Vector() : len_(0), cap_(20), ptr_(new T[cap_]()) {}
    Vector(int sz = 0) : len_(sz), cap_(sz + 20), ptr_(new T[cap_]()) {}
    Vector(int sz, const T& x) : len_(sz), cap_(sz + 20), ptr_(new T[cap_]()) {
        for (int i = 0; i < len_; ++i) {
            *(ptr_ + i) = x;
        }
    }

    Vector(const Vector& rhs) : len_(rhs.size()), cap_(rhs.capacity()), ptr_(new T[cap_]()) {
        for (int i = 0; i < len_; ++i) {
            ptr_[i] = rhs[i];
        }
    }


    Vector& operator = (const Vector& rhs) {
        if (this == &rhs) return *this;
        delete [] ptr_;
        len_ = rhs.size();
        cap_ = rhs.capacity();
        ptr_ = new T[cap_]();
        for (int i = 0; i < len_; ++i) {
            ptr_[i] = rhs[i];
        }
        return *this;
    }
    //初始化列表构造


    Vector(std::initializer_list<T> li) : len_(li.size()), cap_(len_ + 20), ptr_(new T[cap_]()) {
        int i = 0;
        for (auto& num : li) {
            ptr_[i++] = num;
        }
    }

    //初始化列表赋值
    Vector& operator = (std::initializer_list<T> li) {
        len_ = li.size();
        cap_ = len_ + 20;
        delete [] ptr_;
        ptr_ = new T[cap_]();
        int i = 0;
        for (auto& num : li) {
            ptr_[i++] = num; 
        }
        return *this;
    }

    ~Vector() { delete [] ptr_; }

    void push_back(const T& x) {
        if (len_ == cap_) {
            expand();
        }
        ptr_[len_] = x;
        ++len_;
    }


    void pop_back() {
        assert(len_ > 0);
        --len_;
    }

    void insert(int location, const T& x) {
        assert(location <= len_);
        if (len_ == cap_) {
            expand();
        }
        for (int i = len_; i > location; --i) {
            ptr_[i] = ptr_[i - 1];
        }
        ptr_[location] = x;
        ++len_;
    }

    void erase(int location) {
        assert(location < len_);
        --len_;
        for (int i = location; i < len_; ++i) {
            ptr_[i] = ptr_[i + 1];
        }
    }


    T& operator [] (int ind) { 
        assert(ind < len_);
        return ptr_[ind];
    }

    const T& operator [] (int ind) const {
        assert(ind < len_);
        return ptr_[ind];
    }

    void expand() { //两倍扩容
        cap_ *= 2;
        T* newVec = new T[cap_]();
        for (int i = 0; i < len_; ++i) {
            newVec[i] = ptr_[i];
        }
        delete [] ptr_;
        ptr_ = newVec;
    }


    void clear() { len_ = 0; }
    bool empty() { return len_ == 0; }

    int size() const { return len_; }
    int capacity() const { return cap_; }

    T* begin() { return ptr_; }
    const T* begin() const { return ptr_; }

    T* end() { return ptr_ + len_; }
    const T* end() const { return ptr_ + len_; }



private:
    int len_;
    int cap_;
    T* ptr_;
};


#endif