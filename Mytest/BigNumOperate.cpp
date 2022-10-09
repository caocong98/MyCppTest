#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// 大数阶乘
class Bigjie {
public:
    const int  MAXN = 4000; //大数阶乘最大位数
    void solution(int n) {
        temp.assign(MAXN, 0);
        temp[0] = 1;
        for (int i = 2; i <= n; ++i) {
            //每一位都乘i
            int c = 0; // 进位数
            for (int j = 0; j < MAXN; ++j) {
                temp[j] = temp[j] * i + c;
                c = temp[j] / 10;
                temp[j] %= 10;
                if (j == MAXN - 1 && c > 0) { //位数超出
                    cout << "out of range" << endl;
                    return;
                } 
            }
        }
        int FirstId = MAXN - 1;
        while (temp[FirstId] == 0) --FirstId;
        while (FirstId >= 0) {
            cout << temp[FirstId--];
        }
        cout << endl;
    }
    vector<int> temp;
};


// 大数相乘
class BigC {
public:
    // m位数字 * n位数字 最大 m * n 位
    void solution(string a, string b) {
        if (a == "0" || b == "0") {
            cout << 0 << endl;
            return;
        }
        int m = a.size(), n = b.size(); // 进行 m次乘法， 最后相加， 进位最后处理
        reverse(a.begin(), a.end()); //从低位开始乘
        reverse(b.begin(), b.end());
        vector<vector<int>> temp(m + 1, vector<int>(m * n)); // 多开一行存储最后总和答案
        //模拟m次乘法
        for (int i = 0; i < m; ++i) {
            int id = i;
            int num1 = a[i] - '0';
            for (int j = 0; j < n; ++j) {
                int num2 = b[j] - '0';
                temp[i][id++] = num1 * num2;
            }
        }

        //将乘法结果相加
        int c = 0; // 进位位数
        for (int i = 0; i < m * n; ++i) {
            for (int j = 0; j < m; ++j) {
                temp[m][i] += temp[j][i];
            }
            temp[m][i] += c;
            c = temp[m][i] / 10;
            temp[m][i] %= 10;
        }
        //结果输出
        int FirstId = m * n - 1;
        while (temp[m][FirstId] == 0) --FirstId;
        while (FirstId >= 0) {
            cout << temp[m][FirstId--];
        }
        cout << endl;
    }
};


int main() {
    Bigjie().solution(100);

    BigC().solution("81", "422");
    BigC().solution("422", "81");
    return 0;
}