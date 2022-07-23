#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

//有向无环图   可能存在多个拓扑排序结果
//用来确定先后任务关系 ，可用来判断有向图是否成环  例题：LC: 210 115
// 步骤：1、建立领接表  ，各结点入度表   2、将入度为0的点入队，然后出队对相应边的尾结点做入度-1操作，若入度为0继续入队，循环至队列为空，若最终结点都遍历过则存在拓扑排序
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n  =numCourses;
        vector<int> ans, emp;
        vector<int> indegrees(n);
        vector<unordered_set<int>> edges(n);
        for (auto& prerequisite : prerequisites) {
            int head = prerequisite[1], tail = prerequisite[0];
            if (!edges[head].count(tail)) {
                edges[head].insert(tail);
                ++indegrees[tail];
            }
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int head = q.front();
            ans.push_back(head);
            q.pop();
            for (auto tail : edges[head]) {
                if (--indegrees[tail] == 0) q.push(tail);
            }
        }
        return ans.size() == n ? ans : emp;
    }
};
int main() {

    return 0;
}