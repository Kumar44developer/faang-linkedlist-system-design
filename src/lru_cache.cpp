#include <bits/stdc++.h>
using namespace std;
struct LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v): key(k), val(v), prev(nullptr), next(nullptr) {}
    };
int cap, sz;
    unordered_map<int, Node*> mp;
    Node *head, *tail;
 explicit LRUCache(int capacity): cap(capacity), sz(0) {
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail; tail->prev = head;
    }
~LRUCache(){ clear(); delete head; delete tail; }

    void clear(){
        Node* cur = head->next;
        while(cur!=tail){ Node* nx=cur->next; delete cur; cur=nx; }
        head->next = tail; tail->prev = head;
        mp.clear(); sz=0;
    }
void _remove(Node* n){ n->prev->next = n->next; n->next->prev = n->prev; }
    void _push_front(Node* n){
        n->next = head->next; n->prev = head;
        head->next->prev = n; head->next = n;
    }
 int get(int key){
        auto it = mp.find(key);
        if(it==mp.end()) return -1;
        Node* n = it->second;
        _remove(n); _push_front(n);
        return n->val;
    }
 void put(int key, int value){
        auto it = mp.find(key);
        if(it!=mp.end()){
            Node* n = it->second;
            n->val = value;
            _remove(n); _push_front(n);
            return;
        }









