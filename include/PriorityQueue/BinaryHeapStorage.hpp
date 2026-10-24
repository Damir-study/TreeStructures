#ifndef BINARY_HEAP_STORAGE_HPP
#define BINARY_HEAP_STORAGE_HPP

#include "../Abstract/IPriorityQueueStorage.hpp"
#include "../BinaryHeap/BinaryHeap.hpp"

template <typename T>
class BinaryHeapStorage : public IPriorityQueueStorage<T> {
public:
    using Comparator = typename BinaryHeap<T>::Comparator;
private:
    BinaryHeap<T> heap;

public:
    BinaryHeapStorage(Comparator compare = default_compare<T>);
    ~BinaryHeapStorage() override = default;

    BinaryHeapStorage(const BinaryHeapStorage& other) = default;
    BinaryHeapStorage& operator=(const BinaryHeapStorage& other) = default;
    BinaryHeapStorage(BinaryHeapStorage&& other) = default;
    BinaryHeapStorage& operator=(BinaryHeapStorage&& other) = default;

    void add(const T& value) override;
    const T& top() const override;
    T extract_top() override;

    bool contains(const T& value) const override;
    bool is_empty() const override;
    std::size_t get_size() const override;
    void clear() override;

    BinaryHeapStorage* copy() const override;
};

#include "../../src/PriorityQueue/BinaryHeapStorage.tpp"

#endif // BINARY_HEAP_STORAGE_HPP
