#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// 1. 并查集是一种树型的数据结构，用于处理一些不相交集合（disjoint sets）的合并及查询问题。
// 2. 并查集通常包含两种操作
// 例题:LC 684    判断无向图是否成环
// 查找(Find)：查询两个元素是否在同一个集合中
// 合并(Union)：把两个不相交的集合合并为一个集合

class DSU {
public:
    DSU(int N) : n(N){
        //并查集初始化，每个结点根结点为自身, 结点随机不按顺序，将father数组换成哈希表存储
        for (int i = 1; i <= n; ++i) father[i] = i;
    }

    int find(int u) { //递归查找u结点的根结点
        return u == father[u] ? u : father[u] = find(father[u]);
    }

    void Union(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        father[u] = v;
        // father[v] = u;  两种都可
    }

    void print() {
        for (int i = 1; i <= n; ++i) {
            cout << i << " father is " << father[i] << endl;
        }
    }

private:
    int n;
    unordered_map<int, int> father;
    // vector<int> father;

};

int main() {
    // vector<vector<int>> edges{{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    vector<vector<int>> edges{{1,2}, {2,1}};
    DSU D1(2);
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        D1.Union(u, v);
    }
    D1.print();

    return 0;
}