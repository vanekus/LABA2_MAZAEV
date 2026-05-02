#include "DynamicArray.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
DynamicArray<T>::DynamicArray(T* items, int count) : size(count) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
    data = new T[count];
    for (int i = 0; i < count; ++i)
        data[i] = items[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(int size) : size(size) {
    if (size < 0) throw std::invalid_argument("Size cannot be negative");
    data = new T[size]();
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : size(other.size) {
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other) noexcept 
    : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

template <typename T>
DynamicArray<T>::~DynamicArray() noexcept {
    delete[] data;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        if (size > 0) {
            data = new T[size];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        } else {
            data = nullptr;
        }
    }
    return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
const T& DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= size) 
        throw IndexOutOfRange(index, size);
    return data[index];
}

template <typename T>
int DynamicArray<T>::GetSize() const noexcept {
    return size;
}

template <typename T>
void DynamicArray<T>::Set(int index, const T& value) {
    if (index < 0 || index >= size) throw IndexOutOfRange(index, size);
    data[index] = value;
}

template <typename T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) throw std::invalid_argument("New size cannot be negative");
    if (newSize == size) return;
    
    T* newData = new T[newSize]();
    int copySize = (newSize < size) ? newSize : size;
    for (int i = 0; i < copySize; ++i)
        newData[i] = data[i];
    
    delete[] data;
    data = newData;
    size = newSize;
}