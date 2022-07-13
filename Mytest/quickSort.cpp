#include <iostream>
#include <vector>
using namespace std;

void quickSort(vector<int>& nums, int l, int r) {
    if (l >= r) return;
    int b = l, e = r;
    int p = nums[l];
    while (l < r) {
        while (l < r && nums[r] >= p) --r;
        if (l < r) nums[l++] = nums[r];
        while (l < r && nums[l] <= p) ++l;
        if (l < r) nums[r--] = nums[l];
    }
    nums[l] = p;
    quickSort(nums, b, l - 1);
    quickSort(nums, l + 1, e);
}


int main() {
    // cout << argc << endl;
    // for (int i = 0; i < argc; ++i) cout << argv[i] << endl;
    vector<int> test{4, 3, 1, 6, 7, 2};
    quickSort(test, 0, test.size() - 1);
    for (auto num : test) {
        cout << num << ' ';
    }
    return 0;
}