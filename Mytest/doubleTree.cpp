#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class TreeNode {
public:
    TreeNode(int v = 0) : val(v), left(nullptr), right(nullptr) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* create(vector<int>& node, int i) {
    if (i > node.size() || node[i - 1] == -1) return nullptr;
    TreeNode* root = new TreeNode(node[i - 1]);
    root->left = create(node, 2 * i);
    root->right = create(node, 2 * i + 1);
    return root;
}
void dfs(TreeNode* root) {
    if (!root) return;
    cout << root->val << ' ';
    dfs(root->left);
    dfs(root->right);
}

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        dfs(root);
        ans.pop_back();
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;
        stringstream min(data);
        vector<int> pre;
        string num;
        while (getline(min, num, ',')) {
            pre.push_back(stoi(num));
        }
        vector<int> in(pre.begin(), pre.end());
        sort(in.begin(), in.end());
        return rebulid(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
    }

    TreeNode* rebulid(vector<int>& pre, int b1, int e1, vector<int>& in, int b2, int e2) {
        if (b1 > e1) return nullptr;
        TreeNode* root = new TreeNode(pre[b1]);
        int mid = b2;
        while (in[mid] != pre[b1]) ++mid;
        int leftlen = mid - b2;
        root->left = rebulid(pre, b1 + 1, b1 + leftlen, in, b2, mid - 1);
        root->right = rebulid(pre, b1 + leftlen + 1, e1, in, mid + 1, e2);
        return root;
    }

    void dfs(TreeNode* root) {
        if (!root) return;
        ans += to_string(root->val) + ',';
        dfs(root->left);
        dfs(root->right);
    }
    string ans;
};

int main() {
    // vector<int> a{1, 2, 3, -1, 5};
    // TreeNode* root = create(a, 1);
    // dfs(root);
    vector<int> a{2, 1, 3};
    TreeNode* root = create(a, 1);
    Codec* ser = new Codec();
    Codec* deser = new Codec();
    string tree = ser->serialize(root);
    cout << tree << endl;
    TreeNode* ans = deser->deserialize(tree);
    dfs(ans);
    return 0;
}