#include "myString.h"
using namespace std;

int main() {
    myString s1("abc");
    myString s2(s1);
    myString s3;
    s3 = s1;
    s1.print();
    s2.print();
    s3.print();
    const char* tets = "nullptr";
    cout << myStrlen("abc") << endl;
    cout << myStrlen(tets) << endl;
    cout << tets[1] << endl;

    char a[] = "tttt";
    char b[] = "ccc";
    cout << a << endl;
    cout << myStrlen(myStrcpy(a, b)) << endl;
    cout << a << endl;

    char c[] = "tttt";
    char d[] = "ccccc";
    cout << c << endl;
    myStrcpy(c, d);
    cout << c << endl;

}