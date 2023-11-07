#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T value) : data(value), next(nullptr), previous(nullptr) {}
};

enum Position {
    First,
    Last,
    Next,
    Back
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* current;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addItem(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void go(Position here) {
        if (here == First) {current = head;}
        if (here == Last) {current = tail;}
        if (!current) {return;};
        if (here == Back) {current = current->previous;}
        if (here == Next) {current = current->next;}
    }

    void print() {
        go(First);
        while (isValid()) {
            std::cout << getItem() << " ";
            go(Next);
        }
        std::cout << std::endl;
    }

    void reversePrint() {
        go(Last);
        while (isValid()) {
            std::cout << getItem() << " ";
            go(Back);
        }
        std::cout << std::endl;
    }

    T getItem() {
        return current->data;
    }

    bool isValid() {
        return current;
    }

};

