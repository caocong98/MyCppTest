#include <iostream>
#include <vector>
using namespace std;

//约瑟夫环问题，每一轮每隔m干掉一个，求最后剩下的那个。
//从最后一轮往前推，

int yuesefu(int n, int m) {
    //共n个人  每隔m干掉一个
    int p = 0;  //最后一轮存活者id为0
    for (int i = 2; i <= n; ++i) {
        //模拟前推 n - 1 轮得到答案
        p = (p + m) % i;  //当前轮第m个存活,由于是环对当前人数取余
    }

    return p + 1; //设序号从1开始排
}

int main() {

    return 0;
}