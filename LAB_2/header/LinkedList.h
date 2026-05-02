#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "IndexOutOfRange.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& val, Node* p = nullptr, Node* n = nullptr);
    };
    Node* head;
    Node* tail;
    int length;

public:
    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& other);
    LinkedList(LinkedList<T>&& other) noexcept;
    ~LinkedList() noexcept;

    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;

    const T& GetFirst() const;
    const T& GetLast() const;
    const T& Get(int index) const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;
    int GetLength() const noexcept;

    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, int index);
    LinkedList<T>* Concat(LinkedList<T>* list) const;
};

#include "LinkedList.tpp"

#endif