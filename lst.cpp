#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node *prev;
    Node *next;

    Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List
{
    Node<T> *head;
    Node<T> *tail;

    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List()
    {
        clear();
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    void insertFront(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (head == nullptr)
        {
            head = tail = newNode;
            size++;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;

        size++;
    }

    void insertBack(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (head == nullptr)
        {
            head = tail = newNode;
            size++;
            return;
        }

        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;

        size++;
    }

    void insertOnIndex(T value, int index)
    {
        if (index < 0 || index > size)
        {
            std::cerr << "List index out of range.\n";
            return;
        }

        if (index == 0)
        {
            insertFront(value);
            return;
        }
        if (index == size)
        {
            insertBack(value);
            return;
        }

        Node<T> *newNode = new Node<T>(value);

        Node<T> *current = head;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }

        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;

        size++;
    }

    T popFront()
    {
        if (!head)
        {
            std::cerr << "List is empty, cannot pop front.\n";
            return T();
        }

        Node<T> *temp = head;
        T poppedValue = temp->data;

        head = head->next;

        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
        size--;

        return poppedValue;
    }

    T popBack()
    {
        if (!tail)
        {
            std::cerr << "List is empty, cannot pop back.\n";
            return T();
        }

        Node<T> *temp = tail;
        T poppedValue = temp->data;

        tail = tail->prev;

        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;

        size--;

        return poppedValue;
    }

    T popOnIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            std::cerr << "List index out of range.\n";
            return T();
        }

        if (index == 0)
        {
            return popFront();
        }
        if (index == size - 1)
        {
            return popBack();
        }

        Node<T> *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        T poppedValue = current->data;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;

        return poppedValue;
    }

    void clear()
    {
        Node<T> *current = head;

        while (current)
        {
            Node<T> *nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = tail = nullptr;
        size = 0;
    }

    class Iterator {
        Node<T> *current;

    public:
        Iterator(Node<T> *startNode) : current(startNode) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }

            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (current) {
                current = current->prev;
            }

            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator rbegin() const {
        return Iterator(tail);
    }

    Iterator rend() const {
        return Iterator(nullptr);
    }
};
