#include "List.h"

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
List<T>::List(const List<T> &other)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    for (Iterator it = other.begin(); it != other.end(); ++it)
    {
        insertBack(*it);
    }
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this != &other)
    {
        clear();
        size = 0;

        Node<T> *otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            insertBack(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    return *this;
}

template <typename T>
bool List<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
int List<T>::getSize()
{
    return size;
}

template <typename T>
void List<T>::insertFront(T value)
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

template <typename T>
void List<T>::insertBack(T value)
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

template <typename T>
void List<T>::insertOnIndex(T value, int index)
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

template <typename T>
T List<T>::popFront()
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

template <typename T>
T List<T>::popBack()
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

template <typename T>
T List<T>::popOnIndex(int index)
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

template <typename T>
void List<T>::clear()
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

template <typename T>
List<T>::Iterator::Iterator(Node<T> *startNode) : current(startNode) {}

template <typename T>
T &List<T>::Iterator::operator*() const
{
    return current->data;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    if (current)
    {
        current = current->next;
    }

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--()
{
    if (current)
    {
        current = current->prev;
    }

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::rbegin() const
{
    return Iterator(tail);
}

template <typename T>
typename List<T>::Iterator List<T>::rend() const
{
    return Iterator(nullptr);
}
