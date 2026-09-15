#include <bits/stdc++.h>
using namespace std;

struct UndoRedo {
    struct Node {
        string state;
        Node* next;
        Node(const string& s) : state(s), next(nullptr) {}
    };

    Node* undoTop;
    Node* redoTop;
    string current;

    explicit UndoRedo(const string& initial) : undoTop(nullptr), redoTop(nullptr), current(initial) {}

    ~UndoRedo() {
        clear(undoTop);
        clear(redoTop);
    }

    void clear(Node*& top) {
        while (top) { Node* nx = top->next; delete top; top = nx; }
    }

    void push(Node*& top, const string& s) {
        Node* n = new Node(s);
        n->next = top;
        top = n;
    }

    void apply(const string& newState) {
        push(undoTop, current);
        clear(redoTop);
        current = newState;
    }

    string undo() {
        if (!undoTop) return current;
        push(redoTop, current);
        current = undoTop->state;
        Node* dead = undoTop;
        undoTop = undoTop->next;
        delete dead;
        return current;
    }

    string redo() {
        if (!redoTop) return current;
        push(undoTop, current);
        current = redoTop->state;
        Node* dead = redoTop;
        redoTop = redoTop->next;
        delete dead;
        return current;
    }
};

int main() {
    UndoRedo doc("");
    doc.apply("Hello");
    doc.apply("Hello World");
    doc.apply("Hello World!");
    cout << doc.undo() << "\n";
    cout << doc.undo() << "\n";
    cout << doc.redo() << "\n";
    doc.apply("Hello There");
    cout << doc.redo() << "\n";
    cout << doc.undo() << "\n";
    return 0;
}
