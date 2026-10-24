#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <cstddef>
#include "../../external/mutable_array_sequence.h"
#include "../tools/Comparator.hpp"

template <typename T>
class BinaryHeap {
public:
    using Comparator = int (*)(const T&, const T&);
private:
    mutable_array_sequence<T> items;
    std::size_t size;
    Comparator compare;

    void swap_items(std::size_t first, std::size_t second);
    void sift_up(std::size_t index);
    void sift_down(std::size_t index);

    std::size_t find_index(const T& value) const;

public:
    BinaryHeap(Comparator compare = default_compare<T>);
    BinaryHeap(T* array, std::size_t count, Comparator compare = default_compare);
    ~BinaryHeap();

    BinaryHeap(const BinaryHeap& other);
    BinaryHeap& operator=(const BinaryHeap& other);
    BinaryHeap(BinaryHeap&& other);
    BinaryHeap& operator=(BinaryHeap&& other);

    void add(const T& value);
    void remove(const T& value);
    T& get(const T& value);
    const T& get(const T& value) const;
    const T& top() const;
    T extract_top();

    bool contains(const T& value) const;

    std::size_t get_size() const;
    bool is_empty() const;
    void clear();
    BinaryHeap* copy() const;
};

#include "../../src/BinaryHeap/BinaryHeap.tpp"

#endif // BINARY_HEAP_HPP
