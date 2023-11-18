#pragma once

template <typename T>
class Node {
public:
    Node(T value) : data(value), next(nullptr), previous(nullptr) {}
    Node() : next(nullptr), previous(nullptr) {}
    virtual ~Node() {}

    T data;
    Node<T>* next;
    Node<T>* previous;

};
