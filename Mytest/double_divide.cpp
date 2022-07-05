#include <iostream>
#include <vector>
using namespace std;

// 二分查找算法
// lower_bound:第一个大于等于位置 即左边界等同于插入位置  例： 1 2 2 2 3  target：2    ans = 1
// upper_bound:第一个大于目标元素位置   即右边界 - 1     例： 1 2 2 2 3  target：2    ans = 4  

// 二分查找算法1 左闭右闭
template<class T>
typename T::difference_type binary_search1(T& nums, typename T::value_type target) {
    // 针对无重复元素容器查找该元素位置若不存在则为插入位置
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;
        else if (target < nums[mid]) r = mid - 1;
        else if (target > nums[mid]) l = mid + 1;
    }
    return l;
}

// 二分查找算法2 左闭右开
template<class T>
typename T::difference_type binary_search2(T& nums, typename T::value_type target) {
    // 针对无重复元素容器查找该元素位置若不存在则为插入位置
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;
        else if (target < nums[mid]) r = mid; // mid 取不到
        else if (target > nums[mid]) l = mid + 1;
    }
    return l;
}

// lower_bound 左闭右开
template<class T>
typename T::difference_type lower_bound1(T& nums, typename T::value_type target) {
    // 第一个大于等于位置
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (target <= nums[mid]) r = mid;  // r向左收缩
        else if (target > nums[mid]) l = mid + 1;
    }
    return l; // 最终 l == r
}

// upper_bound 左闭右开
template<class T>
typename T::difference_type upper_bound1(T& nums, typename T::value_type target) {
    // 第一个大于位置
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (target >= nums[mid]) l = mid + 1;  // l向右收缩
        else if (target < nums[mid]) r = mid;
    }
    return l; // 最终 l == r
}


// 左闭右闭  l 最终 == r + 1
int lowr_bound2(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (target <= nums[mid]) r = mid - 1;
        else if (target > nums[mid]) l = mid + 1;
    }
    return l;
}
int upper_bound2(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (target >= nums[mid]) l = mid + 1;
        else if (target < nums[mid]) r = mid - 1;
    }
    return l;
}

// offer11 旋转数组最小
int version2(vector<int> nums) {
    //存在重复求最大
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (nums[r] > nums[mid]) l = mid + 1;
        else if (nums[r] < nums[mid]) r = mid;
        else r--;
    }
    return nums[l];
}



int main() {
    // vector<int> test{1, 2, 2, 2, 3};
    vector<int> test{1, 2, 3};
    cout << binary_search2(test, 2) << endl;
    cout << binary_search2(test, 4) << endl;
    cout << binary_search1(test, 4) << endl;
    return 0;
}