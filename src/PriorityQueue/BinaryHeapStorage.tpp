#include "../../include/PriorityQueue/BinaryHeapStorage.hpp"

template <typename T>
BinaryHeapStorage<T>::BinaryHeapStorage(Comparator compare)
    : heap(compare) {}

template <typename T>
void BinaryHeapStorage<T>::add(const T& value) {
    heap.add(value);
}

template <typename T>
const T& BinaryHeapStorage<T>::top() const {
    return heap.top();
}

template <typename T>
T BinaryHeapStorage<T>::extract_top() {
    return heap.extract_top();
}

template <typename T>
bool BinaryHeapStorage<T>::contains(const T& value) const {
    return heap.contains(value);
}

template <typename T>
bool BinaryHeapStorage<T>::is_empty() const {
    return heap.is_empty();
}

template <typename T>
std::size_t BinaryHeapStorage<T>::get_size() const {
    return heap.get_size();
}

template <typename T>
void BinaryHeapStorage<T>::clear() {
    heap.clear();
}

template <typename T>
BinaryHeapStorage<T>* BinaryHeapStorage<T>::copy() const {
    return new BinaryHeapStorage<T>(*this);
}
