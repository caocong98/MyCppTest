#include <iostream>
#include <vector>
using namespace std;

template<class T>
struct Less {
    bool operator () (const T& left, const T& right) const {
        return left < right;
    }
};

template<class T>
struct Greater {
    bool operator () (const T& left, const T& right) const {
        return left > right;
    }
};

template<class T, class Compare = Less<T>>
class myHeap {   
// 默认大顶堆   操作数组时 将实际索引减1    不稳定算法， 插入，pop复杂度logn
//主要操作：  
// 1 ： 上调函数  用于push后调整新元素至正确位置
// 2 ： 下调函数  建堆（从 n/2 循环调用至第1个结点）  堆排序（第一个和最后一个元素交换后下调， 循环n - 1次）
public:
    myHeap(vector<T>& num = {}) : nums(num.begin(), num.end()) {}
    
    bool empty() { return nums.size() == 0; }
    
    T top() {
        if (empty()) {
            cout << "none of date." << endl;
            throw "none of date." ;
        }
        return nums[0];
    }

    void pop() {
        if (empty()) {
            cout << "none of date to delete." << endl;
            throw "none of date to delete.";
        }
        swap(nums[0], nums[nums.size() - 1]);
        nums.pop_back();
        adjust_down(1, nums.size());
    }

    void push(T num) {
        nums.push_back(num);
        adjust_up(nums.size());
    }

    void makeHeap() {
        for (int i = nums.size() / 2; i >= 1; --i) {
            adjust_down(i, nums.size());
        }
    }

    void heapSort() {
        int time = nums.size() - 1, n = nums.size();
        while (time--) {
            swap(nums[0], nums[n - 1]);
            n--;
            adjust_down(1, n);
        }
    }

    void print() {
        // cout << "size: " << nums.size() << endl;
        for (int i = 0; i < nums.size(); ++i) {
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

private:
    vector<int> nums;
    void adjust_down(int location, int end) {
        Compare com;
        int parent = location, child = 2 * location;
        while (child <= end) {
            if (child + 1 <= end && com(nums[child - 1], nums[child + 1 - 1])) {
                ++child;
            }
            if (com(nums[parent - 1], nums[child - 1])) {
                swap(nums[parent - 1], nums[child - 1]);
                parent = child;
                child = 2 * parent;
            }
            else {
                break;
            }
        }
    }

    void adjust_up(int location) {
        Compare com;
        int parent = location / 2, child = location;
        while (parent >= 1) {
            if (com(nums[parent - 1], nums[child - 1])) {
                swap(nums[parent - 1], nums[child - 1]);
                child = parent;
                parent = child / 2;
            }
            else break;
        }
    }

};



int main() {
    vector<int> test1{5, 44, 3, 22, 1};
    vector<int> test2{5, 4, 3, 2, 1};
    myHeap<int, Greater<int>> head1(test1);    // 小顶堆 排序从大到小   
    myHeap<int> head2(test2);   
    cout << "origin heap1:";
    head1.print();
    cout << "origin heap1:";
    head2.print();
    head1.makeHeap();
    cout << "maked heap1:";
    head1.print();
    head1.heapSort();
    cout << "sorted heap1:";
    head1.print();
    cout << "head2.top(): " << head2.top() << endl;
    head2.makeHeap();
    // head2.heapSort();
    int n = 3;
    while (n--) head2.pop();   
    cout << head2.top() << endl;
    head2.heapSort();
    cout << "sorted heap2: ";
    head2.print();
    return 0;
}