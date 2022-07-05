#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int n = 2;
    string s;
    int a = 0;
    while (n--) {
        cin >> a;
        cin.ignore(); //不加改行 cin 后会多一个回车被getline读取
        getline(cin, s);
        cout << a << ' ' << s << endl;
    }
    string ss = "aa bb cc";
    istringstream is(ss);
    string temp;
    while (is >> temp) cout << temp << ' ';
    return 0;
}