#include <bits/stdc++.h>
using namespace std;

struct Playlist {
    struct Node {
        string title;
        Node *prev, *next;
        Node(const string& t) : title(t), prev(nullptr), next(nullptr) {}
    };

    Node* current;
    int count;

    Playlist() : current(nullptr), count(0) {}

    ~Playlist() {
        if (!current) return;
        current->prev->next = nullptr;
        Node* cur = current;
        while (cur) { Node* nx = cur->next; delete cur; cur = nx; }
    }

    void add(const string& title) {
        Node* n = new Node(title);
        if (!current) {
            n->prev = n;
            n->next = n;
            current = n;
        } else {
            Node* last = current->prev;
            last->next = n;
            n->prev = last;
            n->next = current;
            current->prev = n;
        }
        ++count;
    }

    string next() {
        if (!current) return "";
        current = current->next;
        return current->title;
    }

    string prev() {
        if (!current) return "";
        current = current->prev;
        return current->title;
    }

    string nowPlaying() const {
        return current ? current->title : "";
    }
};

int main() {
    Playlist pl;
    pl.add("Song A");
    pl.add("Song B");
    pl.add("Song C");
    cout << pl.nowPlaying() << "\n";
    cout << pl.next() << "\n";
    cout << pl.next() << "\n";
    cout << pl.next() << "\n";
    cout << pl.prev() << "\n";
    return 0;
}
