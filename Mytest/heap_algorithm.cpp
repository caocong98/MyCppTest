#include <iostream>
#include <vector>
using namespace std;

/*
大顶堆(完全二叉树)
索引判断都从 1 开始 父节点 i 子结点 2*i and  2*i + 1
操作数组时 索引都减1 
主要操作：
1、下调(将当前元素调整至合适位置)
2、建堆(从第一个非叶子结点开始下调，循环至根结点)
3、堆排序(不断交换头尾元素，并下调头元素，循环 元素个数-1 次, 交换后的位置剔出下调范围)
4、pop(头尾交换元素， 剔除尾元素，将头元素下调至合适位置)
5、push(尾部插入元素上调只合适位置)
*/

template<class T>
void adjust_down(vector<T>& arr, int index, int endIndex) {
    //下调结点需为非叶子结点  endIndex为可下调的最末尾位置
    while (index <= endIndex/2) {
        // 判断无右孩子结点情况
        if (index == endIndex/2 && endIndex%2 == 0) {
            if (arr[index - 1] < arr[2 * index - 1]) {
                swap(arr[index - 1], arr[2 * index - 1]);
            }
            return;
        }
        int child = arr[2 * index - 1] > arr[2 * index + 1 - 1] ? 2 * index : 2 * index + 1;
        if (arr[index - 1] < arr[child - 1]) {
            swap(arr[index - 1], arr[child - 1]);
            index = child;
        }
        else {
            return;
        }
    }
}

template<class T>
void Make_heap(vector<T>& arr) {
    // 从第一个非叶子结点开始下调直至根结点
    int changeNode = arr.size() / 2;
    while (changeNode >= 1) {
        adjust_down(arr, changeNode, arr.size());
        --changeNode;
    }
}

template<class T>
T Pop(vector<T>& arr) {
    // 将根结点替换至最后一个结点，然后pop_back()尾结点，将根结点下调至合适位置
    if (arr.empty()) {
        cout << "empty to pop" << endl;
        return T(0);
    }
    T top = arr[0];
    swap(arr[0], arr[arr.size() - 1]);
    arr.pop_back();
    adjust_down(arr, 1, arr.size());
    return top;
}

template<class T>
void heap_sort(vector<T>& arr) {
    // 不断交换头尾元素，并下调头元素，循环 元素个数-1 次
    int n = arr.size();
    while (n > 1) {
        swap(arr[0], arr[n - 1]);
        adjust_down(arr, 1, n - 1); // 交换后的位置剔出下调范围
        --n;
    }
}

template<class T>
void Push(vector<int>& arr, T num) {
    // 末尾加入并上调至合适位置
    arr.push_back(num);
    int nowIndex = arr.size();
    if (nowIndex == 1) return;
    int parent = nowIndex / 2;
    while (parent >= 1 && arr[nowIndex - 1] > arr[parent - 1]) {
        swap(arr[nowIndex - 1], arr[parent - 1]);
        nowIndex = parent;
        parent = nowIndex / 2;
    }
}

template<class T>
void Print(T arr) {
    for (auto it : arr) {
        cout << it << ' ';
    }
    cout << endl;
}

int main() {
    vector<int> arr{0 , 1, 2, 3, 4, 8, 9, 3, 5};
    // vector<int> arr{4, 8, 9, 3, 5};
    Make_heap(arr);
    Print(arr);
    heap_sort(arr);
    Print(arr);
    return 0;
}



