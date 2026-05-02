#ifndef INDEXOUTOFRANGE_H
#define INDEXOUTOFRANGE_H

#include <stdexcept>
#include <string>

class IndexOutOfRange : public std::out_of_range {
private:
    int index_;
    int size_;
public:
    IndexOutOfRange() 
        : std::out_of_range("Index out of range"), index_(-1), size_(-1) {}
    
    explicit IndexOutOfRange(const char* msg) 
        : std::out_of_range(msg), index_(-1), size_(-1) {}
    
    IndexOutOfRange(int idx, int sz) 
        : std::out_of_range("Index " + std::to_string(idx) + 
                           " out of range [0, " + std::to_string(sz) + ")"),
          index_(idx), size_(sz) {}
    
    int getIndex() const noexcept { return index_; }
    int getSize() const noexcept { return size_; }
};

#endif