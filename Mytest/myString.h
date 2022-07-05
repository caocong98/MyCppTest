#ifndef __MYSTRING__
#define __MYSTRING__

#include <assert.h>
using namespace std;

int Mystrlen(const char* s) {
    assert(s != nullptr);
    int len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

char* Mystrcpy(char* a, const char* b) {
    assert(a != nullptr && b != nullptr);
    int len = Mystrlen(b);
    for (int i = 0; i < len; ++i) {
        a[i] = b[i];
    }
    a[len] = '\0';
    return a;
}


class Mystring {
public:
    Mystring(const char* c = nullptr) {
        if (c == nullptr) {
            my_data = new char[1];
            my_data[0] = '\0';
        }
        else {
            int len = Mystrlen(c);
            my_data = new char[len + 1];
            Mystrcpy(my_data, c);
        }
    }
    Mystring(const Mystring& s) {
        // int len = Mystrlen(s.my_data);
        int len = s.Len();
        my_data = new char[len + 1];
        Mystrcpy(my_data, s.my_data);
    }

    Mystring& operator = (const Mystring& rhs) {
        if (&rhs == this) return *this;
        delete [] my_data;
        int len = rhs.Len();
        my_data = new char[len + 1];
        Mystrcpy(my_data, rhs.my_data);
        return *this;
    }
    void print() { cout << my_data << endl; }
    int Len() const { return Mystrlen(my_data); }   // !!! const

    ~Mystring() { delete [] my_data; }

private:
    char* my_data;
};


#endif