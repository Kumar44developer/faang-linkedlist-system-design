#include <bits/stdc++.h>
using namespace std;

struct LFUCache {
    struct Node {
        int key, val, freq;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), freq(1), prev(nullptr), next(nullptr) {}
    };

    struct DList {
        Node *head, *tail;
        int size;
        DList() : size(0) {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
        }
        ~DList() { delete head; delete tail; }
        void push_front(Node* n) {
            n->next = head->next;
            n->prev = head;
            head->next->prev = n;
            head->next = n;
            ++size;
        }
        void remove(Node* n) {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            --size;
        }
        Node* back() { return tail->prev; }
        bool empty() const { return size == 0; }
    };

    int cap, minFreq;
    unordered_map<int, Node*> keyTable;
    unordered_map<int, DList*> freqTable;

    explicit LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    ~LFUCache() {
        for (auto& kv : keyTable) delete kv.second;
        for (auto& kv : freqTable) delete kv.second;
    }

    void touch(Node* n) {
        int f = n->freq;
        freqTable[f]->remove(n);
        if (freqTable[f]->empty() && minFreq == f) ++minFreq;
        ++n->freq;
        if (!freqTable.count(n->freq)) freqTable[n->freq] = new DList();
        freqTable[n->freq]->push_front(n);
    }

    int get(int key) {
        auto it = keyTable.find(key);
        if (it == keyTable.end()) return -1;
        touch(it->second);
        return it->second->val;
    }

    void put(int key, int value) {
        if (cap <= 0) return;
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            it->second->val = value;
            touch(it->second);
            return;
        }
        if ((int)keyTable.size() == cap) {
            Node* victim = freqTable[minFreq]->back();
            freqTable[minFreq]->remove(victim);
            keyTable.erase(victim->key);
            delete victim;
        }
        Node* n = new Node(key, value);
        keyTable[key] = n;
        if (!freqTable.count(1)) freqTable[1] = new DList();
        freqTable[1]->push_front(n);
        minFreq = 1;
    }
};

int main() {
    LFUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << "\n";
    cache.put(3, 30);
    cout << cache.get(2) << "\n";
    cout << cache.get(3) << "\n";
    cache.put(4, 40);
    cout << cache.get(1) << " " << cache.get(3) << " " << cache.get(4) << "\n";
    return 0;
}
