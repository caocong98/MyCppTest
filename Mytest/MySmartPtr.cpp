#include <iostream>
#include <memory>
using namespace std;

// template<class T>
// class Shared_ptr{
// public:
//     Shared_ptr() : _ptr(new T()), _refcount(new int(1)) {}
//     Shared_ptr(T* obj) : _ptr(obj), _refcount(new int(1)) {}

//     ~Shared_ptr() {
//         --(*_refcount);
//         if (_ptr && (*_refcount == 0)) {
//             delete _ptr;
//             delete _refcount;
//         }
//     }

//     Shared_ptr(const Shared_ptr& rhs) {
//         ++*rhs._refcount;
//         this->_ptr = rhs._ptr;
//         this->_refcount = rhs._refcount;
//     }

//     Shared_ptr& operator = (const Shared_ptr& rhs) {
//         if (this == &rhs) return *this;
//         --*(this->_refcount);
//         if (this->_ptr && this->_refcount == 0) {
//             delete this->_ptr;
//             delete this->_refcount;
//         }
//         ++*rhs._refcount;
//         this->_ptr = rhs._ptr;
//         this->_refcount = rhs._refcount;
//         return *this;
//     }

//     T& operator *() {
//         return *_ptr;
//     }

//     T* operator -> () {
//         return _ptr;
//     }

//     int get_refcount() {
//         return *(this->_refcount);
//     }
// private:
//     T* _ptr;
//     int* _refcount;
// };


template <class T>
class Shared_ptr {
public:
    Shared_ptr() : _ptr(new T()), _refcount(new int(1)) {}
    Shared_ptr(T* obj) : _ptr(obj), _refcount(new int(1)) {}

    ~Shared_ptr() {
        --*_refcount;
        if (_ptr && *_refcount == 0) {
            delete _ptr;
            delete _refcount;
        }
    }

    Shared_ptr(const Shared_ptr& obj) : _ptr(obj._ptr), _refcount(obj._refcount) {
        ++*_refcount;
    }

    Shared_ptr& operator = (const Shared_ptr& obj) {
        if (this == &obj) {
            return *this;
        }
        --*_refcount;
        if (_ptr && *_refcount == 0) {
            delete _ptr;
            delete _refcount;
        }
        _ptr = obj._ptr;
        _refcount = obj._refcount;
        ++*_refcount;
        return *this;
    }

    T& operator * () {
        return *_ptr;
    }

    T* operator -> () {
        return _ptr;
    }

    int get_refcount() {
        return *_refcount;
    }

private:
    T* _ptr;
    int* _refcount;
};


int main() {
    Shared_ptr<int> obj1(new int(3));
    cout << obj1.get_refcount() << endl;
    Shared_ptr<int> obj2(obj1);
    cout << obj1.get_refcount() << endl;
    Shared_ptr<int> obj3(new int(4));
    obj1 = obj2;
    cout << obj1.get_refcount() << endl;
    cout << obj2.get_refcount() << endl;
    obj1 = obj3;
    cout << obj1.get_refcount() << endl;
    cout << obj2.get_refcount() << endl;
    return 0;
}