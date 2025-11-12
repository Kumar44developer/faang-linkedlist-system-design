#include <bits/stdc++.h>
using namespace std;
struct LFUCache {
    struct Node {
        int key, val, freq;
        Node *prev, *next;
        Node(int k,int v): key(k), val(v), freq(1), prev(nullptr), next(nullptr){}
    };
