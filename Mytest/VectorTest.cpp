#include <iostream>
// #include <vector>
#include "Vector1.h"


using namespace std;

int main() {

    // 拷贝函数
    Vector<int> v0;
    printf("constructor1 run.\t capacity: %d\n", v0.capacity());
    Vector<int> v1(10, 10);
    printf("constructor2 run.\t v1[5]: %d\n", v1[5]);
    Vector<int> v2(10);
    printf("constructor3 run.\t v2[5]: %d\n", v2[5]);
    // 拷贝构造
    Vector<int> v3(v1);
    printf("copy constructor run.\t v3[5]: %d\n", v3[5]);
    // 拷贝赋值
    Vector<int> v4;
    v4 = v1;
    printf("copy assign run.\t v4[5]: %d\n", v4[5]);
    // 初始化列表
    const Vector<int> v5{1, 2, 3, 4};
    printf("Initialize list1 run.\t v5[1]: %d\n", v5[1]);
    Vector<int> v6;
    v6 = {1, 2, 3, 4};
    printf("Initialize list2 assign run.\t v6[1]: %d\n", v6[1]);
    // begin() test
    auto it = v5.begin();
    cout << *it << endl;
    // push_back() test;
    Vector<int> v7;
    for (int i = 0; i < 20; ++i) {
        v7.push_back(i);
        cout << v7[i] << ' ';
    }
    cout << endl;
    cout << v7.size() << ' ' << v7.capacity() << endl;
    v7.push_back(20);
    cout << v7[20] << ' ' << v7.size() << ' ' << v7.capacity() << endl;
    // 测试insert
    v7.insert(0, 21);
    cout << v7[0] << ' ' << v7.size() << ' ' << v7.capacity() << endl;
    // v7.insert(-1, 22);
    // 测试erase
    v7.erase(0);
    cout << v7[0] << endl;
    v7.erase(30);

    return 0;
}