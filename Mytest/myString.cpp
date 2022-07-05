#include <iostream>
#include "myString.h"
using namespace std;

int main() {
    Mystring s1("abc");
    Mystring s2(s1);
    Mystring s3;
    s3 = s1;
    s1.print();
    s2.print();
    s3.print();
    const char* tets = "nullptr";
    cout << Mystrlen("abc") << endl;
    cout << Mystrlen(tets) << endl;
    cout << tets[1] << endl;

    char a[] = "tttt";
    char b[] = "ccc";
    cout << a << endl;
    cout << Mystrlen(Mystrcpy(a, b)) << endl;
    cout << a << endl;

    char c[] = "tttt";
    char d[] = "ccccc";
    cout << c << endl;
    Mystrcpy(c, d);
    cout << c << endl;

}