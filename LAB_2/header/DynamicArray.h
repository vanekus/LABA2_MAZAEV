#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "IndexOutOfRange.h"

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    DynamicArray(T* items, int count);
    explicit DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray(DynamicArray<T>&& other) noexcept;
    ~DynamicArray() noexcept;

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    const T& Get(int index) const;
    int GetSize() const noexcept;
    void Set(int index, const T& value);
    void Resize(int newSize);
};

#include "DynamicArray.tpp"

#endif