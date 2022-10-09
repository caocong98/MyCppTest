#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template<class T>
class Less {
public:
    bool operator() (const T& a, const T& b) const{
        return a < b;
    }
};

template<class T>
class Greater {
public:
    bool operator() (const T& a, const T& b) const {
        return a > b;
    }
};

template<class T, class Compare = Less<T>>
class myHeap {
public:
    myHeap(vector<T>& num) : nums(num.begin(), num.end()), size(nums.size()) {}
    myHeap() : size(0) {}

    bool empty() { return size == 0; }

    void make_heap() {
        for (int i = size / 2; i >= 1; --i) {
            adjust_down(i, size);
        }
    }

    void heap_sort() {
        int n = size;
        for (int i = 0; i < size - 1; ++i) {
            swap(nums[0], nums[n - 1]);
            adjust_down(1, --n);
        }
    }

    T top() {
        assert(size > 0);
        return nums[0];
    }

    void pop() {
        assert(size > 0);
        swap(nums[0], nums[size - 1]);
        --size;
        adjust_down(1, size);
    }

    void push(const T& num) {
        nums.push_back(num);
        ++size;
        adjust_up(size);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

private:
    void adjust_down(int ind, int end) {
        int parent = ind, child = 2 * parent;
        while (child <= end) {
            if (child + 1 <= end && com(nums[child - 1], nums[child])) ++child;
            if (com(nums[parent - 1], nums[child - 1])) {
                 swap(nums[parent - 1], nums[child - 1]);
                 parent = child;
                 child = 2 * parent;
            }
            else break;
        }
    }

    void adjust_up(int ind) {
        int parent = ind / 2, child = ind;
        while (parent >= 1) {
            if (com(nums[parent - 1], nums[child - 1])) {
                swap(nums[parent - 1], nums[child - 1]);
                child = parent;
                parent = child / 2;
            }
            else break;
        }
    }

private:
    vector<T> nums;
    int size;
    Compare com;
};



int main() {
    vector<int> test1{5, 44, 3, 22, 1};
    vector<int> test2{5, 4, 3, 2, 1};
    myHeap<int, Greater<int>> head1(test1);    // 小顶堆 排序从大到小   
    myHeap<int> head2(test2);   
    cout << "origin heap1:";
    head1.print();
    cout << "origin heap2:";
    head2.print();
    head1.make_heap();
    cout << "maked heap1:";
    head1.print();
    head1.heap_sort();
    cout << "sorted heap1:";
    head1.print();
    cout << "head2.top(): " << head2.top() << endl;
    head2.make_heap();
    // head2.heapSort();
    int n = 3;
    while (n--) head2.pop();   
    cout << head2.top() << endl;
    head2.heap_sort();
    cout << "sorted heap2: ";
    head2.print();
    myHeap<int> head3;
    cout << head3.empty() << endl; 
    return 0;

}