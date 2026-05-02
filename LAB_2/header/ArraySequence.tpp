#include "ArraySequence.h"
#include <stdexcept>

// ---------- ArraySequence ----------
template <typename T>
ArraySequence<T>::ArraySequence(T* items, int count)
    : data(new DynamicArray<T>(items, count)) {}

template <typename T>
ArraySequence<T>::ArraySequence(int size)
    : data(new DynamicArray<T>(size)) {}

template <typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other)
    : data(new DynamicArray<T>(*(other.data))) {}

template <typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& other) noexcept 
    : data(other.data) {
    other.data = nullptr;
}

template <typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list)
    : data(new DynamicArray<T>(list.GetLength())) {
    for (int i = 0; i < list.GetLength(); ++i)
        data->Set(i, list.Get(i));
}

template <typename T>
ArraySequence<T>::~ArraySequence() noexcept {
    delete data;
}

template <typename T>
void ArraySequence<T>::AppendInternal(const T& item) {
    data->Resize(data->GetSize() + 1);
    data->Set(data->GetSize() - 1, item);
}

template <typename T>
void ArraySequence<T>::PrependInternal(const T& item) {
    data->Resize(data->GetSize() + 1);
    for (int i = data->GetSize() - 1; i > 0; --i)
        data->Set(i, data->Get(i - 1));
    data->Set(0, item);
}

template <typename T>
void ArraySequence<T>::InsertAtInternal(const T& item, int index) {
    if (index < 0 || index > data->GetSize()) throw IndexOutOfRange(index, data->GetSize());
    if (index == data->GetSize()) {
        AppendInternal(item);
        return;
    }
    data->Resize(data->GetSize() + 1);
    for (int i = data->GetSize() - 1; i > index; --i)
        data->Set(i, data->Get(i - 1));
    data->Set(index, item);
}

template <typename T>
void ArraySequence<T>::ConcatInternal(Sequence<T>* list) {
    int otherLen = list->GetLength();
    for (int i = 0; i < otherLen; ++i)
        AppendInternal(list->Get(i));
}

template <typename T>
const T& ArraySequence<T>::GetFirst() const {
    if (data->GetSize() == 0) throw IndexOutOfRange("Sequence is empty");
    return data->Get(0);
}

template <typename T>
const T& ArraySequence<T>::GetLast() const {
    int len = data->GetSize();
    if (len == 0) throw IndexOutOfRange("Sequence is empty");
    return data->Get(len - 1);
}

template <typename T>
const T& ArraySequence<T>::Get(int index) const {
    return data->Get(index);
}

template <typename T>
int ArraySequence<T>::GetLength() const noexcept {
    return data->GetSize();
}

template <typename T>
Sequence<T>* ArraySequence<T>::Append(const T& item) {
    ArraySequence<T>* self = Instance();
    self->AppendInternal(item);
    return self;
}

template <typename T>
Sequence<T>* ArraySequence<T>::Prepend(const T& item) {
    ArraySequence<T>* self = Instance();
    self->PrependInternal(item);
    return self;
}

template <typename T>
Sequence<T>* ArraySequence<T>::InsertAt(const T& item, int index) {
    ArraySequence<T>* self = Instance();
    self->InsertAtInternal(item, index);
    return self;
}

template <typename T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    ArraySequence<T>* self = Instance();
    self->ConcatInternal(list);
    return self;
}

// ---------- MutableArraySequence ----------
template <typename T>
ArraySequence<T>* MutableArraySequence<T>::Instance() {
    return this;
}

template <typename T>
ArraySequence<T>* MutableArraySequence<T>::Clone() const {
    return new MutableArraySequence<T>(*this);
}

template <typename T>
Sequence<T>* MutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= this->GetLength() || startIndex > endIndex)
        throw IndexOutOfRange(startIndex, this->GetLength());
    int newSize = endIndex - startIndex + 1;
    T* temp = new T[newSize];
    for (int i = 0; i < newSize; ++i)
        temp[i] = this->Get(startIndex + i);
    MutableArraySequence<T>* sub = new MutableArraySequence<T>(temp, newSize);
    delete[] temp;
    return sub;
}

template <typename T>
MutableArraySequence<T>& MutableArraySequence<T>::operator=(MutableArraySequence&& other) noexcept {
    if (this != &other) {
        delete this->data;
        this->data = other.data;
        other.data = nullptr;
    }
    return *this;
}

// ---------- ImmutableArraySequence ----------
template <typename T>
ArraySequence<T>* ImmutableArraySequence<T>::Instance() {
    return Clone();
}

template <typename T>
ArraySequence<T>* ImmutableArraySequence<T>::Clone() const {
    return new ImmutableArraySequence<T>(*this);
}

template <typename T>
Sequence<T>* ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= this->GetLength() || startIndex > endIndex)
        throw IndexOutOfRange(startIndex, this->GetLength());
    int newSize = endIndex - startIndex + 1;
    T* temp = new T[newSize];
    for (int i = 0; i < newSize; ++i)
        temp[i] = this->Get(startIndex + i);
    ImmutableArraySequence<T>* sub = new ImmutableArraySequence<T>(temp, newSize);
    delete[] temp;
    return sub;
}

template <typename T>
ImmutableArraySequence<T>& ImmutableArraySequence<T>::operator=(ImmutableArraySequence&& other) noexcept {
    if (this != &other) {
        delete this->data;
        this->data = other.data;
        other.data = nullptr;
    }
    return *this;
}