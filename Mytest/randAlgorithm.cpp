#include <iostream>
#include <time.h>
#include <vector>
#include <assert.h>
using namespace std;


vector<int> rand1(vector<int> nums, int m) {
//nums中抽取m个,一次次抽，非等概率
    int n = nums.size();
    assert(n >= m);
    vector<int> ans;
    for (int i = 0; i < m; ++i) {
        int ind = rand() % (n - i);
        ans.push_back(nums[ind]);
        swap(nums[ind], nums[n - i - 1]);
    }
    return ans;
}

vector<int> rand2(vector<int> nums, int m) {
//蓄水池算法  n 选 m等概率
    int n = nums.size();
    assert(n >= m);
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) ans[i] = nums[i];  //前m个先放入奖池
    for (int i = m; i < n; ++i) {
        int ind = rand() % (i + 1);
        if (ind < m) ans[ind] = nums[i];
    }
    return ans;
}


int main() {
    srand(time(nullptr)); //放外面只调用1次
    vector<int> nums{1, 2, 3, 4, 5, 6, 7};
    vector<int> ans1 = rand1(nums, 3);
    vector<int> ans2 = rand1(nums, 3);
    vector<int> ans3 = rand1(nums, 3);
    cout << "ans1:";
    for (auto num : ans1) cout << num << ' ';
    cout << endl;
    cout << "ans2:";
    for (auto num : ans2) cout << num << ' ';
    cout << endl;
    cout << "ans3:";
    for (auto num : ans3) cout << num << ' ';
    cout << endl;

    vector<int> ans4 = rand2(nums, 3);
    cout << "ans4:";
    for (auto num : ans4) cout << num << ' ';
    cout << endl;
    cout << time(nullptr) << endl;
    return 0;
}