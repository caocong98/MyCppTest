#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : head(new Lnode()), tail(new Lnode()), n(capacity) {
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if (um.count(key)) {
            change(um[key]);
            return um[key]->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (um.count(key)) {
            um[key]->value = value;
            change(um[key]);
        }
        else {
            if (um.size() == n) del_tail();
            insert(key, value);
        }
    }

private:

    struct Lnode {
        Lnode(int k = 0, int v = 0) : key(k), value(v) , pre(nullptr), next(nullptr) {} 
        int key;
        int value;
        Lnode* pre;
        Lnode* next;
    };

    void change(Lnode* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
        node->next = head->next;
        head->next->pre = node;
        node->pre = head;
        head->next = node;
    }

    void insert(int key, int value) {
        Lnode* node = new Lnode(key, value);
        node->next = head->next;
        head->next->pre = node;
        node->pre = head;
        head->next = node;
        um[key] = node;
    }

    void del_tail() {
        Lnode* del_node = tail->pre;
        tail->pre = del_node->pre;
        del_node->pre->next = tail;
        um.erase(del_node->key);
        delete del_node;
        del_node = nullptr;
    }

    unordered_map<int, Lnode*> um;
    Lnode* head, *tail;
    int n;
};



int main() {


    LRUCache test(2);
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