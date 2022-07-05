#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
//逆序对
    int InversePairs(vector<int> data) {
        vector<int> temp(data.size());
        mergesort(data, temp, 0, data.size() - 1);
        return ans;
    }
    void mergesort(vector<int>& data, vector<int>& temp, int begin, int end) {
        if (begin >= end) return;
        int mid = begin + (end - begin) / 2;
        int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
        mergesort(data, temp, begin1, end1);
        mergesort(data, temp, begin2, end2);
        int k = begin;
        while (begin1 <= end1 && begin2 <= end2) {
            if (data[begin1] <= data[begin2]) {
                temp[k++] = data[begin1++];
            }
            else {
                ans = (ans + end1 - begin1 + 1) % mod;
                temp[k++] = data[begin2++];
            }
        }
        while (begin1 <= end1) temp[k++] = data[begin1++];
        while (begin2 <= end2) temp[k++] = data[begin2++];
        k = begin;
        while (k <= end) {
            data[k] = temp[k];
            ++k;
        }
    }
private:
    const int mod = 1000000007;
    int ans = 0;
};

template<class T>
void mergFunc(vector<T>& nums, vector<T>& temp, int star, int end) {  //nlogn  稳定算法  需要额外一个数组用于合并当前结果
    if (star >= end) return;
    int mid = star + (end - star) / 2;
    int start1 = star, end1 = mid;
    int start2 = mid + 1, end2 = end;
    mergFunc(nums, temp, start1, end1);
    mergFunc(nums, temp, start2, end2);
    int k = star, i = start1, j = start2;
    while (i <= end1 && j <= end2) {
        temp[k++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
    }
    while (i <= end1) {
        temp[k++] = nums[i++];
    }
    while (j <= end2) {
        temp[k++] = nums[j++];
    }
    k = star;
    while (k <= end) {
        nums[k] = temp[k];
        ++k;
    }
}

template<class T>
void mergSort(vector<T>& nums, int n) {
    vector<T> temp(n);
    mergFunc(nums, temp, 0, n - 1);
}


int main() {
    vector<int> nums1 = {1,2,3,4,5,6,7,0};
    vector<int> nums2 = {9, 10, 20, 5, 5, 3, 2, 1};
    // cout << Solution().InversePairs(nums1);
    // cout << Solution().InversePairs(nums2);
    mergSort(nums1, nums1.size());
    mergSort(nums2, nums2.size());
    for (auto num : nums1) cout << num << ' ';
    cout << endl;
    for (auto num : nums2) cout << num << ' ';
    cout << endl;
    return 0;
}