#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T value) : data(value), next(nullptr), previous(nullptr) {}
};

enum ListPosition {
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
    T dummy;
    int listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr) {
        listSize = 0;
        std::cout << "!!!!!ListCreated" ;
    }

    void add(T value) {
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
        listSize++;

    }

    void del(int toDelete) {
        go(First);
        int counter = 1;
        while (isValid()) {
            if (counter == toDelete) {
                Node<T>* temp = current;
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete temp;
                listSize--;
                return;
            }
            go(Next);
            counter++;
        }
        return;
    }

    void go(ListPosition here) {
        if (here == First) {current = head;}
        if (here == Last) {current = tail;}
        if (!isValid()) {return;};
        if (here == Back) {current = current->previous;}
        if (here == Next) {current = current->next;}
    }

    T getItem() {
        if (!isValid()) { return dummy; }
        return current->data;
    }

    bool isValid() {
        return current;
    }

    int getSize() {
        return listSize;
    }

};

