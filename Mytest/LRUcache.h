#ifndef __LRUCACHE__
#define __LRUCACHE__

#include <iostream>
#include <unordered_map>
using namespace std;

template<class K, class V>
class LRUnode {
public:
    LRUnode(K k = 0, V v = 0) : key(k), val(v), pre(nullptr), next(nullptr) {}
    K key;
    V val;
    LRUnode* pre;
    LRUnode* next;
};

template<class K, class V>
class LRUcache {
public:
    LRUcache(int s) : size(s){
        head = new LRUnode<K, V>();
        tail = new LRUnode<K, V>();
        head->next = tail;
        tail->pre = head;
    }

    void Size() { cout << um.size() << endl; }
    void put(K key, V value) {
        auto it = um.find(key);
        if (it == um.end()) {
            if (um.size() == size) {
                deleteEND();
            }
            insert(key, value);
        }
        else {
            um[key]->val = value;
            change(key);
        }
    }

    int get(K key) {
        auto it = um.find(key);
        if (it == um.end()) return -1;
        change(key);
        return um[key]->val;
    }

    void change(K key) {
        // 改到头部
        LRUnode<K, V>* node = um[key];
        node->pre->next = node->next;
        node->next->pre = node->pre;
        node->next = head->next;
        node->next->pre = node;
        node->pre = head;
        head->next = node;
    }

    void deleteEND() {
        LRUnode<K, V>* node = tail->pre;
        tail->pre = node->pre;
        node->pre->next = tail;
        um.erase(node->key);
        delete node;
    }

    void insert(K key, V value) {
        LRUnode<K, V>* node = new LRUnode<K, V>(key, value);
        node->next = head->next;
        node->next->pre = node;
        node->pre = head;
        head->next = node;
        um[key] = node;
    }

    ~LRUcache() { delete head; delete tail; }
private:
    int size;
    
    unordered_map<K, LRUnode<K, V>*> um;
    LRUnode<K, V>* head;
    LRUnode<K, V>* tail;
};




#endif