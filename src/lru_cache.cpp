#include <bits/stdc++.h>
using namespace std;
struct LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v): key(k), val(v), prev(nullptr), next(nullptr) {}
    };
