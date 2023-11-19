#pragma once
#include <iostream>
#include <cstdlib>
#include "node.h"

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

    T dummy;
    int listSize;
    int currentPosition;

    void deleteOperation (){

        Node<T>* temp = current;

        if (listSize == 1) {
            tail = nullptr;
            head = nullptr;
            current = nullptr;

        } else if (current->previous == nullptr) {
            current = current->next;
            head = current;
            head->previous = nullptr;

        } else if (current->next == nullptr) {

            current = current->previous;
            tail = current;
            tail->next = nullptr;

        } else {
            current->previous->next = current->next;
            current->next->previous = current->previous;
            current = current->next;
        }

        delete temp;
        listSize--;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr) {
        listSize = 0;
        currentPosition = 0;
        std::cout << "!!!!!ListCreated" ;
    }

    virtual ~DoublyLinkedList() {
        while(!isEmpty()) {
            del(1);
        }
    }

    Node<T>* current;

    void go(ListPosition here) {
        if (here == First) {current = head; currentPosition = 1; }
        if (here == Last) {current = tail; currentPosition = listSize; }
        if (!isValid()) {return;}
        if (here == Back) {current = current->previous; currentPosition--; }
        if (here == Next) {current = current->next; currentPosition++; }
    }

    void go(int thisPosition) {

        if (isEmpty()) { return; }
        if (thisPosition < 1) { return; }
        if (thisPosition > listSize) { return; }
        if (thisPosition == position()) { return; }

        if (!isValid()) { go(First); }
        if (thisPosition == 1) { go(First); return; }
        if (thisPosition == listSize) { go(Last); return; }

        int ToThere = abs(thisPosition - position());
        int ToFirst = abs(thisPosition - 1);
        int ToLast = abs(thisPosition - listSize);

        if (ToFirst < ToThere && ToFirst < ToLast) { go(First); }
        if (ToLast < ToThere && ToLast < ToFirst) { go(Last); }
        if (ToFirst == ToLast) { go(First); }

        while (thisPosition != position()) {
            if (position() < thisPosition) { go(Next); }
            if (position() > thisPosition) { go(Back); }
        }

    }


    void add(ListPosition here, Node<T>* newNode) {
        if ((here == Next)or(here == Back)) { return;}

        if (!head) {
            head = newNode;
            tail = newNode;
            listSize++; return;
        }
        if (here == Last) {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
            listSize++; return;
        }

        if (here == First) {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
            currentPosition++;
            listSize++; return;
        }

    }

    void add(int thisPosition, Node<T>* newNode) {

        if (thisPosition < 2) { add(First, newNode); return; }
        if (thisPosition >= listSize + 1) { add(Last, newNode); return; }

        go(thisPosition);

        newNode->next = current;
        newNode->previous = current->previous;

        current->previous->next = newNode;
        current->previous = newNode;

        current = current->previous;
        listSize++;

    }

    void add (ListPosition here, T value) {
        Node<T>* newNode = new Node<T>(value);
        add(here, newNode);
    }

    void add (int thisPosition, T value) {
        Node<T>* newNode = new Node<T>(value);
        add(thisPosition, newNode);
    }

    void add (ListPosition here) {
        Node<T>* newNode = new Node<T>();
        add(here, newNode);
    }

    void add (int thisPosition) {
        Node<T>* newNode = new Node<T>();
        add(thisPosition, newNode);
    }

    void del(int toDelete) {
        if (toDelete < 1 && toDelete > listSize) { return; }
        go(toDelete);
        if (!isValid()) { return;}
        if (position() != toDelete) { return;}
        deleteOperation();
    }

    void del (ListPosition here) {
        if ((here == Next)or(here == Back)) { return; }
        if (here == First) { del(1); }
        if (here == Last) { del(getSize()); }

    }


    T getItem() {
        if (!isValid()) { return dummy; }
        return current->data;
    }

    void setItem(T toThis) {
        if (!isValid()) { return; }
        current->data = toThis;
    }

    int position() {
        if (!isValid()) { return 0; }
        return currentPosition;
    }

    bool isValid() {
        return current;
    }

    int getSize() {
        return listSize;
    }

    bool isEmpty(){
        return listSize < 1;
    }

};
