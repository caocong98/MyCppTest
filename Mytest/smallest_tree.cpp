//最小生成树 算法，  克鲁斯卡尔算法 并查集
// n个点 m条边  求最小生成树权值和  
// 边格式 from, to, dis
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


int find(int x, unordered_map<int, int>& father) {
    return x == father[x] ? x : father[x] = find(father[x], father);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m, vector<int>(3));
    unordered_map<int, int> father; //初始每个结点father为自身
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        father[edges[i][0]] = edges[i][0];
        father[edges[i][1]] = edges[i][1];
    }
    sort(edges.begin(), edges.end(), [](auto& a, auto& b){return a[0] < b[0];}); //距离从小到大
    if (m < n - 1) {  //至少需要n - 1 条边
        cout << "No solution\n";
        return 0;
    }
    int cnt = 0; //记录边数 达到n-1条即为答案
    int ans = 0; //记录权值和
    for (int i = 0; i < m && cnt <= n - 1; ++i) { //遍历所有边
        int pa = find(edges[i][1], father);
        int pb = find(edges[i][2], father);
        if (pa != pb) {  // 该边加入不会成环
            ++cnt;
            father[pa] = pb;
            ans += edges[i][0];
        }
    }
    if (cnt == n - 1) cout << ans << endl;
    else cout << "No solution\n";

    return 0;
}

