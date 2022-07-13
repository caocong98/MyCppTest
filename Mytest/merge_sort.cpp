#include <iostream>
#include <vector>
using namespace std;

template<class T>
class merge_sort {
public:
    merge_sort(vector<T>& nums, int begin, int end) : temp(vector<T>(nums.size())) {
        sort(nums, begin, end);
    }

    void sort(vector<T>& nums, int begin, int end) {
        if (begin >= end) return;
        int mid = begin + (end - begin) / 2;
        int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
        //先分
        sort(nums, begin1, end1);
        sort(nums, begin2, end2);
        //后合
        int now = begin;
        while (begin1 <= end1 && begin2 <= end2) {
            if (nums[begin1] <= nums[begin2]) {
                temp[now++] = nums[begin1++];
            }
            else temp[now++] = nums[begin2++];
        }
        while (begin1 <= end1) {
            temp[now++] = nums[begin1++];
        }
        while (begin2 <= end2) {
            temp[now++] = nums[begin2++];
        }
        now = begin;
        while (now <= end) {
            nums[now] = temp[now];
            ++now;
        }
    }


private:
    vector<T> temp; //临时辅助数组

};

int main() {
    vector<int> nums1 = {1,2,3,4,5,6,7,0};
    vector<int> nums2 = {9, 10, 20, 5, 5, 3, 2, 1};
    // merge_sort<int> a(nums1, 0, nums1.size() - 1);
    merge_sort<int> a(nums1, 0, nums1.size() - 2);
    // merge_sort<int> b(nums2, 0, nums2.size() - 1);
    merge_sort<int> b(nums2, 1, nums2.size() - 2); //指定范围排序


    for (auto num : nums1) cout << num << ' ';
    cout << endl;
    for (auto num : nums2) cout << num << ' ';
    cout << endl;
    return 0;
}