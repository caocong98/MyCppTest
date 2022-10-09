#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <assert.h>
#include <iostream>

int Mystrlen(const char* str) {
    if (str == nullptr) return 0;
    int len = 0;
    while (str[len] != '\0') ++len;
    return len;
}

void Mystrcpy(char* a, const char* b) {
    if (b == nullptr) return;
    int i = 0;
    while (b[i] != '\0') a[i++] = b[i];
    a[i] = '\0';
}

class Mystring {
public:
    Mystring(const char* s = nullptr) {
        if (s == nullptr) {
            str = new char[1];
            str[0] = '\0';
        }
        else {
            int len = Mystrlen(s);
            str = new char[len + 1];
            Mystrcpy(str, s);
        }
    }
    Mystring(const Mystring& rhs) {
        int len = rhs.size();
        str = new char[len + 1];
        Mystrcpy(str, rhs.str);
    }
    Mystring& operator = (const Mystring& rhs) {
        if (this == &rhs) return *this;
        delete [] str;
        int len = rhs.size();
        str = new char[len + 1];
        Mystrcpy(str, rhs.str);
        return *this;
    }

    char& operator [] (int ind) {
        return str[ind];
    }

    ~Mystring() { delete [] str; }


    friend std::ostream& operator << (std::ostream&, const Mystring&);

    int size() const { return Mystrlen(str); }
    bool empty() const { return size() == 0; }

private:
    char* str;
};

std::ostream& operator << (std::ostream& out, const Mystring& obj) {
    out << obj.str;
    return out;
}



#endif