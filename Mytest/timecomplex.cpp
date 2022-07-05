#include <iostream>
using namespace std;

// 求x的n次方复杂度分析

// 1 迭代法  On

int func1(int x, int n) {
    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        ans *= x;
    }
    return ans;
}

// 2 递归 On

int func2(int x, int n) {
    if (n == 1) return x;
    return func2(x, n - 1) * x;
}

// 3 递归 Ologn

int func3(int x, int n) {
    if (n == 1) return x;
    int temp = func3(x, n / 2);
    if (n % 2) {
        return temp * temp * x;
    }
    else {
        return temp * temp;
    }
}


int main() {
    cout << func2(2, 4) << endl;
    cout << func3(2, 4) << endl;
    cout << func3(2, 5) << endl;
    return 0;
}