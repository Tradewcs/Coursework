#pragma once
#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node *prev;
    Node *next;

    Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    List();
    List(int size);
    List(const List<T> &other);
    ~List();

    List& operator=(const List& other);

    bool isEmpty();
    int getSize();

    void insertFront(T value);
    void insertBack(T value);
    void insertOnIndex(T value, int index);

    T popFront();
    T popBack();
    T popOnIndex(int index);

    void clear();

    class Iterator {
    private:
        Node<T> *current;

    public:
        Iterator(Node<T> *startNode);

        T &operator*() const;

        Iterator &operator++();
        Iterator operator++(int);

        Iterator &operator--();
        Iterator operator--(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};
