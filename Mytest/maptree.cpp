#include <iostream>
#include <vector>
using namespace std;

class mapTree {
//只由26个小写字母组成
private:
    vector<mapTree*> board;
    bool isend;

public:
    // mapTree() : board(vector<mapTree*>(26, nullptr)), isend(false) {}
    mapTree() : board(26, nullptr), isend(false) {}

    void insert(const string& word) {
        mapTree* now = this;
        for (auto& c : word) {
            int ind = c - 'a';
            if (now->board[ind] == nullptr) now->board[ind] = new mapTree();
            now = now->board[ind];
        }
        now->isend = true;
    }

    bool search(const string& word) {
        //查找字典树中是否存在单词word
        mapTree* now = this;
        for (auto& c : word) {
            int ind = c - 'a';
            if (now->board[ind] == nullptr) return false;
            now = now->board[ind];
        }
        return now->isend;
    }

};


int main() {
    mapTree mtree;
    vector<string> words{"a", "aa", "abcde", "cccccc", "c"};
    for (auto word : words) mtree.insert(word);
    cout << mtree.search("cc") << endl;
    cout << mtree.search("c") << endl;
    cout << mtree.search("abcde") << endl;
    return 0;
}