#include "../../include/Dictionary/BinaryTreeDictionaryStorage.hpp"

#include <stdexcept>

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>::BinaryTreeDictionaryStorage(
    BinarySearchTreeBase<Pair>* tree, Comparator compare)
    : compare(compare), tree(tree) {
    if (!tree) throw std::invalid_argument("Tree must not be null");
    if (!compare) {
        delete tree;
        throw std::invalid_argument("Comparator must not be null");
    }
}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>::~BinaryTreeDictionaryStorage() {
    delete tree;
}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>::BinaryTreeDictionaryStorage(const BinaryTreeDictionaryStorage& other)
    : compare(other.compare), tree(other.tree ? other.tree->copy() : nullptr) {}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>&
BinaryTreeDictionaryStorage<Key, Value>::operator=(const BinaryTreeDictionaryStorage& other) {
    if (this == &other) return *this;

    BinarySearchTreeBase<Pair>* new_tree = other.tree ? other.tree->copy() : nullptr;
    delete tree;
    tree = new_tree;
    compare = other.compare;

    return *this;
}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>::BinaryTreeDictionaryStorage(BinaryTreeDictionaryStorage&& other) noexcept
    : compare(other.compare), tree(other.tree) {
    other.tree = nullptr;
}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>&
BinaryTreeDictionaryStorage<Key, Value>::operator=(BinaryTreeDictionaryStorage&& other) noexcept {
    if (this == &other) return *this;

    delete tree;
    tree = other.tree;
    compare = other.compare;
    other.tree = nullptr;

    return *this;
}

template <typename Key, typename Value>
void BinaryTreeDictionaryStorage<Key, Value>::add(const Key& key, const Value& value) {
    if (!tree) throw std::runtime_error("Storage has no tree");
    tree->add(Pair(key, value, compare));
}

template <typename Key, typename Value>
void BinaryTreeDictionaryStorage<Key, Value>::remove(const Key& key) {
    if (tree) tree->remove(Pair(key, compare));
}

template <typename Key, typename Value>
Value& BinaryTreeDictionaryStorage<Key, Value>::get(const Key& key) {
    if (!tree) throw std::runtime_error("Storage has no tree");
    return tree->get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
const Value& BinaryTreeDictionaryStorage<Key, Value>::get(const Key& key) const {
    if (!tree) throw std::runtime_error("Storage has no tree");
    const BinarySearchTreeBase<Pair>* const_tree = tree;
    return const_tree->get(Pair(key, compare)).value;
}

template <typename Key, typename Value>
bool BinaryTreeDictionaryStorage<Key, Value>::contains_key(const Key& key) const {
    return tree && tree->contains(Pair(key, compare));
}

template <typename Key, typename Value>
std::size_t BinaryTreeDictionaryStorage<Key, Value>::get_size() const {
    return tree ? tree->get_size() : 0;
}

template <typename Key, typename Value>
bool BinaryTreeDictionaryStorage<Key, Value>::is_empty() const {
    return !tree || tree->is_empty();
}

template <typename Key, typename Value>
void BinaryTreeDictionaryStorage<Key, Value>::clear() {
    if (tree) tree->clear();
}

template <typename Key, typename Value>
BinaryTreeDictionaryStorage<Key, Value>* BinaryTreeDictionaryStorage<Key, Value>::copy() const {
    return new BinaryTreeDictionaryStorage<Key, Value>(*this);
}
