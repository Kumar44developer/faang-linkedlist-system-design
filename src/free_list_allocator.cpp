#include <bits/stdc++.h>
using namespace std;

struct FreeListAllocator {
    struct Block {
        int offset, size;
        Block* next;
        Block(int o, int s) : offset(o), size(s), next(nullptr) {}
    };

    Block* freeHead;

    explicit FreeListAllocator(int totalSize) {
        freeHead = new Block(0, totalSize);
    }

    ~FreeListAllocator() {
        while (freeHead) { Block* nx = freeHead->next; delete freeHead; freeHead = nx; }
    }

    int allocate(int size) {
        Block* prev = nullptr;
        Block* cur = freeHead;
        while (cur) {
            if (cur->size >= size) {
                int offset = cur->offset;
                cur->offset += size;
                cur->size -= size;
                if (cur->size == 0) {
                    if (prev) prev->next = cur->next;
                    else freeHead = cur->next;
                    delete cur;
                }
                return offset;
            }
            prev = cur;
            cur = cur->next;
        }
        return -1;
    }

    void deallocate(int offset, int size) {
        Block* node = new Block(offset, size);
        Block* prev = nullptr;
        Block* cur = freeHead;
        while (cur && cur->offset < offset) { prev = cur; cur = cur->next; }
        node->next = cur;
        if (prev) prev->next = node; else freeHead = node;
        coalesce(prev ? prev : node);
    }

    void coalesce(Block* start) {
        Block* cur = start;
        while (cur && cur->next) {
            if (cur->offset + cur->size == cur->next->offset) {
                Block* dead = cur->next;
                cur->size += dead->size;
                cur->next = dead->next;
                delete dead;
            } else {
                cur = cur->next;
            }
        }
    }
};

int main() {
    FreeListAllocator alloc(100);
    int a = alloc.allocate(30);
    int b = alloc.allocate(20);
    int c = alloc.allocate(10);
    cout << a << " " << b << " " << c << "\n";
    alloc.deallocate(a, 30);
    alloc.deallocate(b, 20);
    int d = alloc.allocate(40);
    cout << d << "\n";
    return 0;
}
