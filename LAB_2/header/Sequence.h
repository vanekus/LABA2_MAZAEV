#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T>
class Sequence {
public:
    virtual ~Sequence() noexcept {}

    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const noexcept = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
};

#endif