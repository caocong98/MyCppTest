#include <iostream>
using namespace std;


int myatoi(const char* num) {
    int op = 1;
    int ans = 0;
    int i = 0;
    while (num[i] != '\0' && num[i] == ' ') ++i;
    if (num[i] == '\0') return ans;
    if (num[i] == '+') ++i;
    if (num[i] == '-') {
        ++i;
        op = -1;
    }
    while (num[i] != '\0') {
        if (!(num[i] >= '0' && num[i] <= '9')) return ans * op;
        ans = ans * 10 + (num[i] - '0');
        ++i;
    }
    return ans * op;
}


int main() {
    const char* num = "  -12 ";
    cout << myatoi(num) << endl;
    return 0;
}