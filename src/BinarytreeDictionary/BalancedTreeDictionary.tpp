#include "../../include/BinaryTreeDictionary/BalancedTreeDictionary.hpp"

#include <stdexcept>

template <typename Key, typename Value>
BalancedTreeDictionary<Key, Value>::BalancedTreeDictionary(Comparator compare)
    : compare(compare), tree() {
    if (!compare) throw std::invalid_argument("Comparator must not be null");
}

template <typename Key, typename Value>
void BalancedTreeDictionary<Key, Value>::add(const Key& key, const Value& value) {
    tree.add(Pair(key, value, compare));
}

template <typename Key, typename Value>
Value& BalancedTreeDictionary<Key, Value>::get(const Key& key) {
    return tree.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
const Value& BalancedTreeDictionary<Key, Value>::get(const Key& key) const {
    return tree.get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
bool BalancedTreeDictionary<Key, Value>::contains_key(const Key& key) const {
    return tree.contains(Pair(key, compare));
}

template <typename Key, typename Value>
void BalancedTreeDictionary<Key, Value>::remove(const Key& key) {
    tree.remove(Pair(key, compare));
}

template <typename Key, typename Value>
std::size_t BalancedTreeDictionary<Key, Value>::get_size() const {
    return tree.get_size();
}

template <typename Key, typename Value>
bool BalancedTreeDictionary<Key, Value>::is_empty() const {
    return tree.is_empty();
}

template <typename Key, typename Value>
void BalancedTreeDictionary<Key, Value>::clear() {
    tree.clear();
}
