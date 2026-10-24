#include "../../include/Dictionary/BinaryHeapDictionaryStorage.hpp"

#include <stdexcept>

template <typename Key, typename Value>
BinaryHeapDictionaryStorage<Key, Value>::BinaryHeapDictionaryStorage(Comparator compare)
    : compare(compare), heap() {
    if (!compare) throw std::invalid_argument("Comparator must not be null");
}

template <typename Key, typename Value>
void BinaryHeapDictionaryStorage<Key, Value>::add(const Key& key, const Value& value) {
    if (contains_key(key)) throw std::runtime_error("Value already exists");
    heap.add(Pair(key, value, compare));
}

template <typename Key, typename Value>
void BinaryHeapDictionaryStorage<Key, Value>::remove(const Key& key) {
    heap.remove(Pair(key, compare));
}

template <typename Key, typename Value>
Value& BinaryHeapDictionaryStorage<Key, Value>::get(const Key& key) {
    return heap.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
const Value& BinaryHeapDictionaryStorage<Key, Value>::get(const Key& key) const {
    return heap.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
bool BinaryHeapDictionaryStorage<Key, Value>::contains_key(const Key& key) const {
    return heap.contains(Pair(key, compare));
}

template <typename Key, typename Value>
std::size_t BinaryHeapDictionaryStorage<Key, Value>::get_size() const {
    return heap.get_size();
}

template <typename Key, typename Value>
bool BinaryHeapDictionaryStorage<Key, Value>::is_empty() const {
    return heap.is_empty();
}

template <typename Key, typename Value>
void BinaryHeapDictionaryStorage<Key, Value>::clear() {
    heap.clear();
}

template <typename Key, typename Value>
BinaryHeapDictionaryStorage<Key, Value>* BinaryHeapDictionaryStorage<Key, Value>::copy() const {
    return new BinaryHeapDictionaryStorage<Key, Value>(*this);
}
