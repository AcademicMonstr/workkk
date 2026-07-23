#include <iostream>

class DoublyLinkedList {
    struct Node {
        int data;
        Node *prev, *next;
        Node(int d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
    }

    bool remove(int val) {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) {
                if (curr->prev) curr->prev->next = curr->next;
                else head = curr->next; // Удаляем голову
                
                if (curr->next) curr->next->prev = curr->prev;
                
                delete curr;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void printForward() const {
        for (Node* c = head; c; c = c->next) std::cout << c->data << " <-> ";
        std::cout << "nullptr\n";
    }
};

int main() {
    DoublyLinkedList dll;
    dll.push_back(10);
    dll.push_back(20);
    dll.push_back(30);
    
    std::cout << "Forward: "; dll.printForward();
    dll.remove(20);
    std::cout << "After remove 20: "; dll.printForward();
    return 0;
}