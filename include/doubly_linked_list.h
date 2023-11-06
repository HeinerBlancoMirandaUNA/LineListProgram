#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T value) : data(value), next(nullptr), previous(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* current;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

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

    void print() {
        current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void reversePrint() {
        current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->previous;
        }
        std::cout << std::endl;
    }
};

