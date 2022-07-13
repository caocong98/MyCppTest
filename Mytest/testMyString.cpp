#include <iostream>
#include "myString.h"
using namespace std;

int main() {
    Mystring s1("abc");
    Mystring s2(s1);
    Mystring s3;
    s3 = s1;
    cout << s3 << endl;
    const char* tets = "nullptr";
    cout << Mystrlen("abc") << endl;
    cout << Mystrlen(tets) << endl;
    cout << tets[1] << endl;
    return 0;
}