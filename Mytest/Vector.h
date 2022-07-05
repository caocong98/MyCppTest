#ifndef __VECTOR__
#define __VECTOR__

#include <assert.h>

template <typename T>
class Vector
{
public:
    // 构造函数
    Vector() : len_(0), cap_(20), ptr_(new T[cap_]()) {
        //默认无参构造函数,调用T的默认构造函数 new T[cap_]()默认值初始化
        // printf("constructor1 run.\n");
    };
    Vector(int n) : len_(n), cap_(n + 20), ptr_(new T[cap_]()) {
        // printf("constructor2 run.\n");
    }
    Vector(int n, const T &x) : len_(n), cap_(n + 20), ptr_(new T[cap_]()) {
        // printf("constructor3 run.\n");
        for (int i = 0; i < n; ++i) {
            *(ptr_ + i) = x;
        }
    }
    // 拷贝构造
    Vector(const Vector &x) : len_(x.size()), cap_(x.capacity()), ptr_(new T[cap_]()) {
        // printf("copy constructor run.\n");
        for (int i = 0; i < len_; ++i) {
            *(ptr_ + i) = x[i];
        }
    }
    // 拷贝赋值
    Vector& operator = (const Vector& rhs) {
        // printf("aacopy assign run.\n");
        if (this == &rhs) return *this;
        delete [] ptr_;
        cap_ = rhs.capacity();
        len_ = rhs.size();
        ptr_ = new T[cap_]();
        for(int i = 0; i < len_; ++i) {
            *(ptr_ + i) = rhs[i];
        }
        return *this;
    }
    //初始化列表 构造
    Vector(std::initializer_list<T> li) : len_(0), cap_(li.size() + 20) , ptr_(new T[cap_]) {
        // printf("initialize constructor run\n");
        for (auto& it : li) {
            *(ptr_ + len_) = it;
            ++len_;
        }
    }
    //初始化列表 赋值
    Vector& operator = (std::initializer_list<T> li) {
        // printf("initialize assign run\n");
        delete [] ptr_;  // 释放原先内存
        cap_ = li.size() + 20;
        len_ = 0;
        ptr_ = new T[cap_]();
        for (auto& it : li) {
            *(ptr_ + len_) = it;
            ++len_;
        }
        return *this;
    }
    // 析构函数
    ~Vector() {
        delete [] ptr_;
    }

    void push_back(const T &x) {
        // T cp = T(x); //调用T拷贝构造 , 容器内存放对象应该与传入参数相独立
        if (len_ == cap_) {
            //当前容量已满则扩充容量至1.5倍, 将原先元素转移
            cap_ *= 1.5;
            T* new_ptr = new T[cap_]();
            for (int i = 0; i < len_; ++i) {
                *(new_ptr + i) = *(ptr_ + i); 
            }
            delete [] ptr_;
            ptr_ = new_ptr;
        }
        *(ptr_ + len_) = x;
        ++len_;
    }
    void pop_back() {
        assert(len_ > 0);
        --len_;
    }

    void insert(int pos, const T& rhs) {
        assert(pos >= 0 && pos <= len_);
        for (int i = len_; i > pos; --i) {
            *(ptr_ + i) = *(ptr_ + i -1);
        }
        *(ptr_ + pos) = rhs;
        ++len_;
    }

    void erase(int pos) {
        assert(pos >= 0 && pos < len_);
        --len_;
        for (; pos < len_; ++pos) {
            *(ptr_ + pos) = *(ptr_ + pos + 1);
        }
    }

    void clear() {
        len_ = 0;
    }
    int size() const {
        return len_;
    }
    int capacity() const {
        return cap_;
    }
    bool empty() const {
        return len_ == 0;
    }

    T& operator [] (int i) {
        return ptr_[i];
    }
    const T& operator [] (int i) const
    {
        return ptr_[i];
    }

    T* begin() {
        return ptr_;
    }
    T* end() {
        return ptr_ + len_;
    }
    const T* begin() const {
        return ptr_;
    }
    const T* end() const {
        return ptr_ + len_;
    }

private:
    int cap_; //容量 默认为 len_ + 20
    int len_; //元素个数
    T *ptr_;
};

#endif
