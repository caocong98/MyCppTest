#include <iostream>
#include <vector>
using namespace std;


template<class T>
void quickSort(vector<T>& nums, int left, int right) {
    if (left >= right) return;
    int l = left, r = right; 
    int p = nums[l];
    while (l < r) {
        while (l < r && nums[r] >= p) --r;
        if (l < r) nums[l++] = nums[r];
        while (l < r && nums[l] <= p) ++l;
        if (l < r) nums[r--] = nums[l];
    }
    nums[l] = p;
    quickSort(nums, left, l -1);
    quickSort(nums, l + 1, right);
}

template<class T>
void randQuickSort(vector<T>& nums, int left, int right) {
    // 随机枢纽， 防止退化为链表复杂度为n方，例如已经排好序的数组
    if (left >= right) return;
    int l = left, r = right;
    int p = (rand() % (r - l + 1)) + l;
    swap(nums[l], nums[p]);
    p = nums[l];
    while (l < r) {
        while (l < r && nums[r] >= p) --r;
        if (l < r) nums[l++] = nums[r];
        while (l < r && nums[l] <= p) ++l;
        if (l < r) nums[r--] = nums[l];
    }
    nums[l] = p;
    randQuickSort(nums, left, l - 1);
    randQuickSort(nums, l + 1, right);
}


int main(int argc, char* argv[]) {
    // cout << argc << endl;
    // for (int i = 0; i < argc; ++i) cout << argv[i] << endl;
    vector<double> test{4, 3, 1, 6, 7, 2};
    randQuickSort(test, 0, test.size() - 1);
    for (auto num : test) {
        cout << num << ' ';
    }
    return 0;
}