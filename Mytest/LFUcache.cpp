#include <iostream>
#include <unordered_map>
using namespace std;

class LNode {
public:
    LNode(int k = 0, int v = 0, int c = 1) : key(k), value(v), cnt(c), pre(nullptr), next(nullptr) {}
    int key;
    int value;
    int cnt;
    LNode* pre;
    LNode* next;
};

class DoubleList {
public:
    DoubleList() : count(0), head(new LNode()), tail(new LNode()) {
        head->next = tail;
        tail->pre = head;
    }

    void add_head(LNode* node) {
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
        ++count;  //  易漏
    }

    void remove_node(LNode* node) {
        //移动不释放
        --count;  // 易漏
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void remove_tail() {
        --count;    // 易漏
        LNode* delNode = tail->pre;
        tail->pre = delNode->pre;
        delNode->pre->next = tail;
        delete delNode;
        delNode = nullptr;
    }

    int count;
    LNode* head;
    LNode* tail;
};

class LFUCache {
public:
    LFUCache(int capacity) : N(capacity) {
        mincnt = 1;
        um2[1] = new DoubleList();
    }

    int get(int key) {
        if (N == 0) return -1;
        if (um1.find(key) == um1.end()) return -1;
        int oldcnt = um1[key]->cnt;
        int newcnt = oldcnt + 1;
        um2[oldcnt]->remove_node(um1[key]);
        if (um2[newcnt] == nullptr) um2[newcnt] = new DoubleList();
        um2[newcnt]->add_head(um1[key]);
        um1[key]->cnt++;     // 易漏
        if (um2[oldcnt]->count == 0 && mincnt == oldcnt) ++mincnt;  // 重点
        return um1[key]->value;
    }

    void put(int key, int value) {
        if (N == 0) return;
        if (um1.find(key) == um1.end()) {
            if (um1.size() == N) {
                um1.erase(um2[mincnt]->tail->pre->key);
                um2[mincnt]->remove_tail();
            }
            mincnt = 1;  // 每次插入新结点 mincnt为1
            LNode* newNode = new LNode(key, value);
            um2[mincnt]->add_head(newNode);
            um1[key] = newNode;
        }
        else {
            get(key);
            um1[key]->value = value;
        }
    }


private:
    int N;
    int mincnt;
    unordered_map<int, LNode*> um1;
    unordered_map<int, DoubleList*> um2;

};

int main() {
    return 0;
}

