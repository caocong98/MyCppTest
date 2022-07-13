#include <iostream>
#include <unordered_map>
using namespace std;

class ListNode {
public:
    ListNode(int k = 0, int v = 0) : key(k), value(v), pre(nullptr), next(nullptr) {}
    int key;
    int value;
    ListNode* pre;
    ListNode* next;
};


class LRU {
public:
    LRU(int sz = 10) : N(sz), head(new ListNode()), tail(new ListNode()) {
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        if (um.find(key) == um.end()) return -1;
        change(key);
        return um[key]->value;
    }
    void print() {
        ListNode* now = head->next;
        while (now != tail) {
            cout << now->key << " ";
            now = now->next;
        }
        cout << endl;
    }
    void put(int key, int value) {
        auto it = um.find(key);
        if (it == um.end()) {
            if (um.size() == N) delete_tail();
            insert_head(key, value);
        }
        else {
            um[key]->value = value;
            change(key);
        }
    }

private:
    void change(int key) {
        um[key]->pre->next = um[key]->next;
        um[key]->next->pre = um[key]->pre;
        um[key]->next = head->next;
        um[key]->pre = head;
        head->next->pre = um[key];
        head->next = um[key];
    }

    void insert_head(int key, int value) {

        ListNode* newNode = new ListNode(key, value);
        newNode->next = head->next;
        newNode->pre = head;
        head->next->pre = newNode;
        head->next = newNode;
        um[key] = newNode;

    }

    void delete_tail() {
        ListNode* delnode = tail->pre;
        // cout << "del value:" << delnode->key << endl; 
        delnode->pre->next = tail;
        tail->pre = delnode->pre;
        um.erase(delnode->key);
        delete delnode;
        delnode = nullptr;
        // ListNode* node = tail->pre;
        // tail->pre = node->pre;
        // node->pre->next = tail;
        // um.erase(node->key);
        // delete node;
    }

private:
    int N;
    unordered_map<int, ListNode*> um;
    ListNode* head;
    ListNode* tail;
};



int main() {


    LRU test(2);
    test.put(1, 0);
    test.put(2, 2);
    cout << test.get(1) << endl;
    test.put(3, 3);
    cout << test.get(2) << endl;
    test.put(4, 4);
    cout << test.get(1) << endl; //
    cout << test.get(3) << endl;
    cout << test.get(4) << endl;
    return 0;
}