#include <iostream>
#include <unordered_map>
using namespace std;

//两个哈希表  
// 表1 key - Lnode
// 表2 使用次数  - DoubleList(存使用频率相同的结点的双向链表)

class Lnode {
public:
    Lnode(int k, int v) : key(k), value(v), cnt(1), pre(nullptr), next(nullptr) {}
    int key;
    int value;
    int cnt;
    Lnode* pre;
    Lnode* next;
};

class DoubleList {
public:
    DoubleList() {
        head = new Lnode(0, 0);
        tail = new Lnode(0, 0);
        head->next = tail;
        tail->pre = head;
        count = 0;
    }

    void addHead(Lnode* node) {
        node->next = head->next;
        node->pre = head;
        node->next->pre = node;
        head->next = node;
        ++count;
    }

    void removeNode(Lnode* node) {
        //移动不释放
        node->pre->next = node->next;
        node->next->pre = node->pre;
        --count;
    }

    void removeTail() {
        //释放
        Lnode* delnode = tail->pre;
        delnode->pre->next = tail;
        tail->pre = delnode->pre;
        delete delnode;
        --count;
    }

    Lnode* head;
    Lnode* tail;
    int count;
};

class LFUCache {
public:
    LFUCache(int capacity) : sz(capacity) {
        mincnt = 1;
        um2[1] = new DoubleList();
    }
    
    int get(int key) {
        if (sz == 0) return -1;
        if (um1.find(key) == um1.end()) return -1;
        // 增加次数并移至新次数链表中
        int oldcnt = um1[key]->cnt;
        int newcnt = oldcnt + 1;
        DoubleList* pre = um2[oldcnt];
        um1[key]->cnt++;
        if (um2.find(newcnt) == um2.end()) um2[newcnt] = new DoubleList();
        DoubleList* after = um2[newcnt];
        pre->removeNode(um1[key]);
        after->addHead(um1[key]);
        // 关键点
        if (pre->count == 0 && mincnt == oldcnt) ++mincnt;
        return um1[key]->value;
    }
    
    void put(int key, int value) {
        if (sz == 0) return;
        if (um1.find(key) != um1.end()) {
            get(key);
            um1[key]->value = value;
        }
        else {
            //新插入
            if (um1.size() == sz) {
                um1.erase(um2[mincnt]->tail->pre->key);
                um2[mincnt]->removeTail();
            }
            Lnode* newNode = new Lnode(key, value);
            um2[1]->addHead(newNode);
            um1[key] = newNode;
            mincnt = 1;
        }
    }
    
    int sz;
    int mincnt;
    unordered_map<int, Lnode*> um1;
    unordered_map<int, DoubleList*> um2; 
};

int main() {
    return 0;
}
