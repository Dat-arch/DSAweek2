#include "DoublyLinkedList.h"
#include <sstream>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0)
{
    head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node *curr = head;
    while (curr)
    {
        Node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

// TODO implement DoublyLinkedList
template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node *newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node *newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    if (index < 0 || index > length)
        throw std::out_of_range("insertAt index out of range");
    if (index == 0)
    {
        insertAtHead(data);
        return;
    }
    if (index == length)
    {
        insertAtTail(data);
        return;
    }

    // find node currently at position index
    Node *curr;
    if (index <= length / 2)
    {
        curr = head->next;
        for (int i = 0; i < index; ++i)
            curr = curr->next;
    }
    else
    {
        curr = tail;
        for (int i = length; i > index; --i)
            curr = curr->prev;
    }
    // insert before curr
    Node *newNode = new Node(data, curr->prev, curr);
    curr->prev->next = newNode;
    curr->prev = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index >= length)
        throw std::out_of_range("deleteAt index out of range");

    Node *curr;
    if (index < length / 2)
    {
        curr = head->next;
        for (int i = 0; i < index; ++i)
            curr = curr->next;
    }
    else
    {
        curr = tail->prev;
        for (int i = length - 1; i > index; --i)
            curr = curr->prev;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    length--;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= length)
        throw std::out_of_range("get index out of range");

    const Node *curr;
    if (index < length / 2)
    {
        curr = head->next;
        for (int i = 0; i < index; ++i)
            curr = curr->next;
    }
    else
    {
        curr = tail->prev;
        for (int i = length - 1; i > index; --i)
            curr = curr->prev;
    }
    // Header declares non-const reference; cast away constness
    return const_cast<T &>(curr->data);
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    int idx = 0;
    for (Node *curr = head->next; curr != tail; curr = curr->next, ++idx)
    {
        if (curr->data == item)
            return idx;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const
{
    return indexOf(item) != -1;
}

template <typename T>
int DoublyLinkedList<T>::size() const
{
    return length;
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    // Reverse links for all nodes including sentinels, then swap head/tail pointers
    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        curr = next;
    }
    Node *tmp = head;
    head = tail;
    tail = tmp;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &) /*= 0*/) const
{
    std::ostringstream oss;
    oss << "[";
    Node *curr = head->next;
    bool first = true;
    while (curr != tail)
    {
        if (!first)
            oss << ", ";
        first = false;
        if (convert2str)
        {
            T &ref = const_cast<T &>(curr->data);
            oss << convert2str(ref);
        }
        else
        {
            oss << curr->data;
        }
        curr = curr->next;
    }
    oss << "]";
    return oss.str();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;