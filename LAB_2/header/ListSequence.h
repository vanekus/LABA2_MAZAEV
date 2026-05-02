#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T>
class MutableListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;

public:
    MutableListSequence(T* items, int count);
    MutableListSequence();
    MutableListSequence(const MutableListSequence<T>& other);
    MutableListSequence(MutableListSequence<T>&& other) noexcept;
    explicit MutableListSequence(const LinkedList<T>& lst);
    ~MutableListSequence() noexcept;

    
    MutableListSequence& operator=(const MutableListSequence&);
    MutableListSequence& operator=(MutableListSequence&&) noexcept;

    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const noexcept override;

    Sequence<T>* Append(const T& item) override;
    Sequence<T>* Prepend(const T& item) override;
    Sequence<T>* InsertAt(const T& item, int index) override;
    Sequence<T>* Concat(Sequence<T>* seq) override;
};

template <typename T>
class ImmutableListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;

public:
    ImmutableListSequence(T* items, int count);
    ImmutableListSequence();
    ImmutableListSequence(const ImmutableListSequence<T>& other);
    ImmutableListSequence(ImmutableListSequence<T>&& other) noexcept;
    explicit ImmutableListSequence(const LinkedList<T>& lst);
    // Конструктор, забирающий владение (для оптимизации)
    explicit ImmutableListSequence(LinkedList<T>* ownedList) noexcept;
    ~ImmutableListSequence() noexcept;

    
    ImmutableListSequence& operator=(const ImmutableListSequence&);
    ImmutableListSequence& operator=(ImmutableListSequence&&) noexcept;

    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const noexcept override;

    Sequence<T>* Append(const T& item) override;
    Sequence<T>* Prepend(const T& item) override;
    Sequence<T>* InsertAt(const T& item, int index) override;
    Sequence<T>* Concat(Sequence<T>* seq) override;
};

#include "ListSequence.tpp"

#endif