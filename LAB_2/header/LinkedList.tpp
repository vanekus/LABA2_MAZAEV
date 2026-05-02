#include "LinkedList.h"

template <typename T>
LinkedList<T>::Node::Node(const T& val, Node* p, Node* n)
    : value(val), prev(p), next(n) {}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
LinkedList<T>::LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
    for (int i = 0; i < count; ++i)
        Append(items[i]);
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0) {
    Node* cur = other.head;
    while (cur) {
        Append(cur->value);
        cur = cur->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept 
    : head(other.head), tail(other.tail), length(other.length) {
    other.head = other.tail = nullptr;
    other.length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        length = 0;
        Node* curOther = other.head;
        while (curOther) {
            Append(curOther->value);
            curOther = curOther->next;
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = other.head;
        tail = other.tail;
        length = other.length;
        other.head = other.tail = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
const T& LinkedList<T>::GetFirst() const {
    if (!head) throw IndexOutOfRange("List is empty");
    return head->value;
}

template <typename T>
const T& LinkedList<T>::GetLast() const {
    if (!tail) throw IndexOutOfRange("List is empty");
    return tail->value;
}

template <typename T>
const T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length) throw IndexOutOfRange(index, length);
    Node* cur = head;
    for (int i = 0; i < index; ++i)
        cur = cur->next;
    return cur->value;
}

template <typename T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw IndexOutOfRange(startIndex, length);
    LinkedList<T>* sub = new LinkedList<T>();
    Node* cur = head;
    for (int i = 0; i < startIndex; ++i)
        cur = cur->next;
    for (int i = startIndex; i <= endIndex; ++i) {
        sub->Append(cur->value);
        cur = cur->next;
    }
    return sub;
}

template <typename T>
int LinkedList<T>::GetLength() const noexcept {
    return length;
}

template <typename T>
void LinkedList<T>::Append(const T& item) {
    Node* newNode = new Node(item, tail, nullptr);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++length;
}

template <typename T>
void LinkedList<T>::Prepend(const T& item) {
    Node* newNode = new Node(item, nullptr, head);
    if (!head) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }
    ++length;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& item, int index) {
    if (index < 0 || index > length) throw IndexOutOfRange(index, length);
    if (index == 0) {
        Prepend(item);
    } else if (index == length) {
        Append(item);
    } else {
        Node* cur = head;
        for (int i = 0; i < index; ++i)
            cur = cur->next;
        Node* newNode = new Node(item, cur->prev, cur);
        cur->prev->next = newNode;
        cur->prev = newNode;
        ++length;
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) const {
    LinkedList<T>* result = new LinkedList<T>(*this);
    Node* cur = list->head;
    while (cur) {
        result->Append(cur->value);
        cur = cur->next;
    }
    return result;
}