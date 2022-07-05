#include <iostream>
#include <vector>
using namespace std;


class mapTree {
public:
    mapTree() : Node(vector<mapTree*>(26, nullptr)), istrue(false) {
        cout << "create" << endl;
    }
    ~mapTree() {
        for (auto it : Node) {
            if (it != nullptr) delete it;
        }
        cout << "delete" << endl;
    }
    void insert(const string& word) {
        mapTree* node = this;
        for (auto& c : word) {
            int index = c - 'a';
            if (node->Node[index] == nullptr) node->Node[index] = new mapTree();
            node = node->Node[index];
        }
        node->istrue = true;
    }

    bool search(const string& word) {
        mapTree* node = this;
        for (auto& c : word) {
            int index = c - 'a';
            if (node->Node[index] == nullptr || node->Node[index]->istrue == false) return false;
            node = node->Node[index];
        }
        return true;
    }

private:
    vector<mapTree*> Node;
    bool istrue;
};


class Solution {
public:
    string longestWord(vector<string>& words) {
        string ans("");
        mapTree tree;
        for (auto& word : words) tree.insert(word);
        for (auto& word : words) {
            if (tree.search(word)) {
                if (word.size() > ans.size() || (word.size() == ans.size() && word < ans)) ans = word;
            }
        }
        return ans;
    }
};

int main() {
    vector<string> ss{"a", "aa", "aaa"};
    cout << Solution().longestWord(ss);
    return 0;
}