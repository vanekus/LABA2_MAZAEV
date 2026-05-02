#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

template <typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* data;

    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* Clone() const = 0;

    void AppendInternal(const T& item);
    void PrependInternal(const T& item);
    void InsertAtInternal(const T& item, int index);
    void ConcatInternal(Sequence<T>* list);

public:
    ArraySequence(T* items, int count);
    explicit ArraySequence(int size);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(ArraySequence<T>&& other) noexcept;
    explicit ArraySequence(const LinkedList<T>& list);
    virtual ~ArraySequence() noexcept;

    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override = 0;
    int GetLength() const noexcept override;

    Sequence<T>* Append(const T& item) override;
    Sequence<T>* Prepend(const T& item) override;
    Sequence<T>* InsertAt(const T& item, int index) override;
    Sequence<T>* Concat(Sequence<T>* list) override;
};

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* Instance() override;
    ArraySequence<T>* Clone() const override;
public:
    using ArraySequence<T>::ArraySequence;
    MutableArraySequence(const MutableArraySequence&) = default;
    MutableArraySequence(MutableArraySequence&&) = default;
    MutableArraySequence& operator=(const MutableArraySequence&) = default;
    MutableArraySequence& operator=(MutableArraySequence&&) noexcept;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* Instance() override;
    ArraySequence<T>* Clone() const override;
public:
    using ArraySequence<T>::ArraySequence;
    ImmutableArraySequence(const ImmutableArraySequence&) = default;
    ImmutableArraySequence(ImmutableArraySequence&&) = default;
    ImmutableArraySequence& operator=(const ImmutableArraySequence&) = default;
    ImmutableArraySequence& operator=(ImmutableArraySequence&&) noexcept;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
};

#include "ArraySequence.tpp"

#endif