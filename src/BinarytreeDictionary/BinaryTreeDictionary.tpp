#include "../../include/BinaryTreeDictionary/BinaryTreeDictionary.hpp"

template <typename Key, typename Value>
BinaryTreeDictionary<Key, Value>::BinaryTreeDictionary(Comparator compare)
    : compare(compare), tree() {}

template <typename Key, typename Value>
void BinaryTreeDictionary<Key, Value>::add(const Key& key, const Value& value) {
    tree.add(Pair(key, value, compare));
}

template <typename Key, typename Value>
Value& BinaryTreeDictionary<Key, Value>::get(const Key& key) {
    return tree.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
const Value& BinaryTreeDictionary<Key, Value>::get(const Key& key) const {
    return tree.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
bool BinaryTreeDictionary<Key, Value>::contains_key(const Key& key) const {
    return tree.contains(Pair(key, compare));
}

template <typename Key, typename Value>
void BinaryTreeDictionary<Key, Value>::remove(const Key& key) {
    tree.remove(Pair(key, compare));
}

template <typename Key, typename Value>
std::size_t BinaryTreeDictionary<Key, Value>::get_size() const {
    return tree.get_size();
}

template <typename Key, typename Value>
bool BinaryTreeDictionary<Key, Value>::is_empty() const {
    return tree.is_empty();
}

template <typename Key, typename Value>
void BinaryTreeDictionary<Key, Value>::clear() {
    tree.clear();
}
