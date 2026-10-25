#include "../../include/BinaryHeap/BinaryHeap.hpp"

#include <stdexcept>
#include <utility>

template <typename T>
BinaryHeap<T>::BinaryHeap(Comparator compare)
    : items(), size(0), compare(compare) {
    if (!compare) throw std::invalid_argument("Comparator must not be null");
}

template <typename T>
BinaryHeap<T>::BinaryHeap(T* array, std::size_t count, Comparator compare)
    : BinaryHeap(compare) {
    if (!array && count != 0) throw std::invalid_argument("Array must not be null");

    for (std::size_t i = 0; i < count; ++i) {
        items.append(array[i]);
        ++size;
    }
    for (std::size_t i = size / 2; i > 0; --i) {
        sift_down(i - 1);
    }
}

template <typename T>
BinaryHeap<T>::~BinaryHeap() {}

template <typename T>
BinaryHeap<T>::BinaryHeap(const BinaryHeap& other)
    : items(other.items), size(other.size), compare(other.compare) {}

template <typename T>
BinaryHeap<T>& BinaryHeap<T>::operator=(const BinaryHeap& other) {
    if (this == &other) return *this;

    items = other.items;
    size = other.size;
    compare = other.compare;

    return *this;
}

template <typename T>
BinaryHeap<T>::BinaryHeap(BinaryHeap&& other)
    : items(std::move(other.items)), size(other.size), compare(other.compare) {
    other.size = 0;
}

template <typename T>
BinaryHeap<T>& BinaryHeap<T>::operator=(BinaryHeap&& other) {
    if (this == &other) return *this;

    items = std::move(other.items);
    size = other.size;
    compare = other.compare;
    other.size = 0;

    return *this;
}

template <typename T>
void BinaryHeap<T>::swap_items(std::size_t first, std::size_t second) {
    if (first >= size || second >= size) throw std::out_of_range("Heap index out of range");
    if (first == second) return;

    T temp = items[first];
    items[first] = items[second];
    items[second] = temp;
}

template <typename T>
void BinaryHeap<T>::sift_up(std::size_t index) {
    if (index == 0) return;
    std::size_t parent_index = (index-1)/2;
    int compare_result = compare(items[index],items[parent_index]);

    if (compare_result >= 0) {
        return;
    }
    swap_items(index,parent_index);
    sift_up(parent_index);
}

template <typename T>
void BinaryHeap<T>::sift_down(std::size_t index) {
    std::size_t left_child = 2*index+1;
    std::size_t right_child = 2*index+2;
    std::size_t priority_child;

    if (left_child >= size) return;

    if (right_child < size) {
        priority_child = compare(items[right_child], items[left_child]) < 0 ? right_child : left_child;
    }
    else {
        priority_child = left_child;
    }

    int compare_result = compare(items[index],items[priority_child]);

    if (compare_result <= 0) {
        return;
    }
    swap_items(index,priority_child);
    sift_down(priority_child);
}

template <typename T>
std::size_t BinaryHeap<T>::find_index(const T& value) const {
    for (int i = 0; i < items.get_length(); ++i) {
        if (items[i] == value) return i;
    }
    return size;
}

template <typename T>
bool BinaryHeap<T>::same_nodes(std::size_t index, const BinaryHeap& subtree, std::size_t subtree_index) const {
    if (index >= size && subtree_index >= subtree.size) return true;
    if (index >= size || subtree_index >= subtree.size) return false;
    if (compare(items[index], subtree.items[subtree_index]) != 0) return false;

    return same_nodes(2*index+1, subtree, 2*subtree_index+1)
        && same_nodes(2*index+2, subtree, 2*subtree_index+2);
}

template <typename T>
void BinaryHeap<T>::add(const T& value) {
    items.append(value);
    ++size;
    sift_up(size-1);
}

template <typename T>
void BinaryHeap<T>::remove(const T& value) {
    std::size_t index = find_index(value);
    if (index == size) return;
    swap_items(index, size-1);
    items.pop();
    --size;

    if (index == size) return;

    if (index > 0 && compare(items[index], items[(index-1)/2]) < 0) {
        sift_up(index);
    }
    else {
        sift_down(index);
    }

}

template <typename T>
T& BinaryHeap<T>::get(const T& value) {
    std::size_t index = find_index(value);
    if (index == size) throw std::runtime_error("Value is not in the heap");
    return items[index];
}

template <typename T>
const T& BinaryHeap<T>::get(const T& value) const {
    std::size_t index = find_index(value);
    if (index == size) throw std::runtime_error("Value is not in the heap");
    return items[index];
}

template <typename T>
BinaryHeap<T>* BinaryHeap<T>::get_subtree(const T& root_value) const {
    std::size_t index = find_index(root_value);
    if (index == size) throw std::runtime_error("Value is not in the heap");

    BinaryHeap<T>* result = new BinaryHeap<T>(compare);
    try {
        std::size_t first = index;
        std::size_t last = index;
        while (first < size) {
            for (std::size_t i = first; i <= last && i < size; ++i) {
                result->items.append(items[i]);
                ++result->size;
            }
            first = 2*first+1;
            last = 2*last+2;
        }
    } catch (...) {
        delete result;
        throw;
    }

    return result;
}

template <typename T>
const T& BinaryHeap<T>::top() const {
    if (size == 0) throw std::runtime_error("Heap is empty");
    return items[0];
}

template <typename T>
T BinaryHeap<T>::extract_top() {
    if (size == 0) throw std::runtime_error("Heap is empty");
    swap_items(0, size-1);
    T removed_item = items.pop();
    --size;

    if (size > 1) {
        sift_down(0);
    }
    return removed_item;
}

template <typename T>
bool BinaryHeap<T>::contains(const T& value) const {
    return find_index(value) != size;
}

template <typename T>
bool BinaryHeap<T>::contains_subtree(const BinaryHeap& subtree) const {
    if (subtree.is_empty()) return true;

    for (std::size_t i = 0; i < size; ++i) {
        if (same_nodes(i, subtree, 0)) return true;
    }
    return false;
}

template <typename T>
std::size_t BinaryHeap<T>::get_size() const {
    return size;
}

template <typename T>
bool BinaryHeap<T>::is_empty() const {
    return size == 0;
}

template <typename T>
void BinaryHeap<T>::clear() {
    items = mutable_array_sequence<T>();
    size = 0;
}

template <typename T>
BinaryHeap<T>* BinaryHeap<T>::copy() const {
    return new BinaryHeap<T>(*this);
}

template <typename T>
BinaryHeap<T> BinaryHeap<T>::map(Transform transform) const {
    if (!transform) return *this;

    BinaryHeap<T> result(compare);
    for (std::size_t i = 0; i < size; ++i) {
        result.add(transform(items[i]));
    }

    return result;
}

template <typename T>
BinaryHeap<T> BinaryHeap<T>::where(Predicate predicate) const {
    if (!predicate) throw std::invalid_argument("Predicate must not be null");

    BinaryHeap<T> result(compare);
    for (std::size_t i = 0; i < size; ++i) {
        if (predicate(items[i])) result.add(items[i]);
    }

    return result;
}
