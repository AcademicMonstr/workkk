#include <iostream>

// --- СТЕК (LIFO) ---
class Stack {
    struct Node { int data; Node* next; Node(int d) : data(d), next(nullptr) {} };
    Node* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { while (top) { Node* t = top; top = top->next; delete t; } }
    
    void push(int val) { top = new Node(val, top); } // Краткая запись вставки в начало
    void pop() { if (top) { Node* t = top; top = top->next; delete t; } }
    int peek() const { return top ? top->data : -1; }
    bool empty() const { return top == nullptr; }
};

// --- ОЧЕРЕДЬ (FIFO) ---
class Queue {
    struct Node { int data; Node* next; Node(int d) : data(d), next(nullptr) {} };
    Node *front, *rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() { while (front) { Node* t = front; front = front->next; delete t; } }
    
    void push(int val) {
        Node* newNode = new Node(val);
        if (!rear) { front = rear = newNode; return; }
        rear->next = newNode;
        rear = newNode;
    }
    void pop() {
        if (!front) return;
        Node* t = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
    }
    int peek() const { return front ? front->data : -1; }
};

int main() {
    Stack s;
    s.push(1); s.push(2); s.push(3);
    std::cout << "Stack peek: " << s.peek() << " (должно быть 3, LIFO)\n";
    s.pop();
    std::cout << "Stack после pop: " << s.peek() << " (должно быть 2)\n";

    Queue q;
    q.push(1); q.push(2); q.push(3);
    std::cout << "Queue peek: " << q.peek() << " (должно быть 1, FIFO)\n";
    q.pop();
    std::cout << "Queue после pop: " << q.peek() << " (должно быть 2)\n";
    return 0;
}