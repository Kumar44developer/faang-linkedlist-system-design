#include <bits/stdc++.h>
using namespace std;

struct BrowserHistory {
    struct Node {
        string url;
        Node *prev, *next;
        Node(const string& u) : url(u), prev(nullptr), next(nullptr) {}
    };

    Node* current;

    explicit BrowserHistory(const string& homepage) {
        current = new Node(homepage);
    }

    ~BrowserHistory() {
        Node* head = current;
        while (head->prev) head = head->prev;
        while (head) { Node* nx = head->next; delete head; head = nx; }
    }

    void visit(const string& url) {
        Node* nx = current->next;
        while (nx) { Node* tmp = nx->next; delete nx; nx = tmp; }
        Node* n = new Node(url);
        current->next = n;
        n->prev = current;
        current = n;
    }

    string back(int steps) {
        while (steps-- > 0 && current->prev) current = current->prev;
        return current->url;
    }

    string forward(int steps) {
        while (steps-- > 0 && current->next) current = current->next;
        return current->url;
    }
};

int main() {
    BrowserHistory bh("leetcode.com");
    bh.visit("google.com");
    bh.visit("facebook.com");
    bh.visit("youtube.com");
    cout << bh.back(1) << "\n";
    cout << bh.back(1) << "\n";
    cout << bh.forward(1) << "\n";
    bh.visit("linkedin.com");
    cout << bh.forward(2) << "\n";
    cout << bh.back(2) << "\n";
    cout << bh.back(7) << "\n";
    return 0;
}
