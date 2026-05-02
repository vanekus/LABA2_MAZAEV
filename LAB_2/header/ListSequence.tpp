#include "ListSequence.h"

// ---------- MutableListSequence ----------
template <typename T>
MutableListSequence<T>::MutableListSequence(T* items, int count)
    : list(new LinkedList<T>(items, count)) {}

template <typename T>
MutableListSequence<T>::MutableListSequence()
    : list(new LinkedList<T>()) {}

template <typename T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T>& other)
    : list(new LinkedList<T>(*(other.list))) {}

template <typename T>
MutableListSequence<T>::MutableListSequence(MutableListSequence<T>&& other) noexcept 
    : list(other.list) {
    other.list = nullptr;
}

template <typename T>
MutableListSequence<T>::MutableListSequence(const LinkedList<T>& lst)
    : list(new LinkedList<T>(lst)) {}

template <typename T>
MutableListSequence<T>::~MutableListSequence() noexcept {
    delete list;
}

template <typename T>
const T& MutableListSequence<T>::GetFirst() const {
    return list->GetFirst();
}

template <typename T>
const T& MutableListSequence<T>::GetLast() const {
    return list->GetLast();
}

template <typename T>
const T& MutableListSequence<T>::Get(int index) const {
    return list->Get(index);
}

template <typename T>
Sequence<T>* MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
    MutableListSequence<T>* sub = new MutableListSequence<T>(*subList);
    delete subList;
    return sub;
}

template <typename T>
int MutableListSequence<T>::GetLength() const noexcept {
    return list->GetLength();
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Append(const T& item) {
    list->Append(item);
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Prepend(const T& item) {
    list->Prepend(item);
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::InsertAt(const T& item, int index) {
    list->InsertAt(item, index);
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Concat(Sequence<T>* seq) {
    for (int i = 0; i < seq->GetLength(); ++i)
        list->Append(seq->Get(i));
    return this;
}

template <typename T>
MutableListSequence<T>& MutableListSequence<T>::operator=(MutableListSequence&& other) noexcept {
    if (this != &other) {
        delete list;
        list = other.list;
        other.list = nullptr;
    }
    return *this;
}

// ---------- ImmutableListSequence ----------
template <typename T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, int count)
    : list(new LinkedList<T>(items, count)) {}

template <typename T>
ImmutableListSequence<T>::ImmutableListSequence()
    : list(new LinkedList<T>()) {}

template <typename T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other)
    : list(new LinkedList<T>(*(other.list))) {}

template <typename T>
ImmutableListSequence<T>::ImmutableListSequence(ImmutableListSequence<T>&& other) noexcept 
    : list(other.list) {
    other.list = nullptr;
}

template <typename T>
ImmutableListSequence<T>::ImmutableListSequence(const LinkedList<T>& lst)
    : list(new LinkedList<T>(lst)) {}

template <typename T>
ImmutableListSequence<T>::ImmutableListSequence(LinkedList<T>* ownedList) noexcept
    : list(ownedList) {}

template <typename T>
ImmutableListSequence<T>::~ImmutableListSequence() noexcept {
    delete list;
}

template <typename T>
const T& ImmutableListSequence<T>::GetFirst() const {
    return list->GetFirst();
}

template <typename T>
const T& ImmutableListSequence<T>::GetLast() const {
    return list->GetLast();
}

template <typename T>
const T& ImmutableListSequence<T>::Get(int index) const {
    return list->Get(index);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
    ImmutableListSequence<T>* sub = new ImmutableListSequence<T>(*subList);
    delete subList;
    return sub;
}

template <typename T>
int ImmutableListSequence<T>::GetLength() const noexcept {
    return list->GetLength();
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Append(const T& item) {
    LinkedList<T>* newList = new LinkedList<T>(*list);
    newList->Append(item);
    return new ImmutableListSequence<T>(newList);  // передача владения
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Prepend(const T& item) {
    LinkedList<T>* newList = new LinkedList<T>(*list);
    newList->Prepend(item);
    return new ImmutableListSequence<T>(newList);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::InsertAt(const T& item, int index) {
    LinkedList<T>* newList = new LinkedList<T>(*list);
    newList->InsertAt(item, index);
    return new ImmutableListSequence<T>(newList);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Concat(Sequence<T>* seq) {
    LinkedList<T>* newList = new LinkedList<T>(*list);
    for (int i = 0; i < seq->GetLength(); ++i)
        newList->Append(seq->Get(i));
    return new ImmutableListSequence<T>(newList);
}

template <typename T>
ImmutableListSequence<T>& ImmutableListSequence<T>::operator=(ImmutableListSequence&& other) noexcept {
    if (this != &other) {
        delete list;
        list = other.list;
        other.list = nullptr;
    }
    return *this;
}

// ---------- Оператор присваивания копированием для MutableListSequence ----------
template <typename T>
MutableListSequence<T>& MutableListSequence<T>::operator=(const MutableListSequence<T>& other) {
    if (this != &other) {
        // Очищаем текущий список
        delete list;
        // Создаём глубокую копию списка other
        list = new LinkedList<T>(*(other.list));
    }
    return *this;
}

// ---------- Оператор присваивания копированием для ImmutableListSequence ----------
template <typename T>
ImmutableListSequence<T>& ImmutableListSequence<T>::operator=(const ImmutableListSequence<T>& other) {
    if (this != &other) {
        delete list;
        list = new LinkedList<T>(*(other.list));
    }
    return *this;
}