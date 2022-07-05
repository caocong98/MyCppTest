#include <iostream>
using namespace std;

int main() {
    //大端高位地址放低位

    int a = 0x0123;
    char *b = (char*)&a;
    if(b[0] == 0x01) cout << "b[0]:" << b[0] << "big duan.\n";
    else cout << "b[0]:" << (int)b[0] << "small duan.\n";
    return 0; 
}