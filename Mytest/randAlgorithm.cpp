#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <time.h>
using namespace std;

vector<int> rand1(int n, int m) {
    //n 个数中取 m 个数  每个数只能选1次， 一个一个选
    //每次随机选中一个后交换至容器尾部，下次不会选中
    // 默认从1 ~ n中选
    srand(time(NULL));  //随机种子
    assert(n >= m);
    vector<int> nums(n);
    vector<int> ans;
    for (int i = 0; i < n; ++i) nums[i] = i + 1;  // 初始化奖池
    for (int i = 1; i <= m; ++i) {
        int chooseId = rand() % (n - i + 1);
        ans.push_back(nums[chooseId]);
        swap(nums[chooseId], nums[n - i]);
    }
    return ans;
}


vector<int> rand2(int n, int m) {
    //蓄水池算法，等概率（m/n）选出 m 个数， 遍历一遍数据流，不用一次性读入所有数据
    // lc  382 398
    assert(n >= m);
    srand(time(NULL));
    vector<int> nums(n);
    vector<int> ans(m);
    for (int i = 0; i < n; ++i) nums[i] = i + 1;  //初始化奖池
    //前m个数放入选中数组
    for (int i = 0; i < m; ++i) ans[i] = nums[i];

    for (int i = m; i < n; ++i) {
        int chooseId = rand() % (i + 1);  // 当前选中概率为 m / i + 1;
        if (chooseId < m) {  //选中  
            ans[chooseId] = nums[i];
        }
    }
    return ans;
}

int main() {
    vector<int> test1 = rand1(10, 3);
    for (auto num : test1) cout << num << ' ';
    cout << endl;
    vector<int> test2 = rand2(10, 3);
    for (auto num : test2) cout << num << ' ';
    cout << endl;
    return 0;
}