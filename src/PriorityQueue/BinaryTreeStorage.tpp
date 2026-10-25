#include "../../include/PriorityQueue/BinaryTreeStorage.hpp"

#include <stdexcept>

template <typename T>
BinaryTreeStorage<T>::BinaryTreeStorage(BinarySearchTreeBase<T>* tree)
    : tree(tree) {
    if (!tree) throw std::invalid_argument("Tree must not be null");
}

template <typename T>
BinaryTreeStorage<T>::~BinaryTreeStorage() {
    delete tree;
}

template <typename T>
BinaryTreeStorage<T>::BinaryTreeStorage(const BinaryTreeStorage& other)
    : tree(other.tree ? other.tree->copy() : nullptr) {}

template <typename T>
BinaryTreeStorage<T>& BinaryTreeStorage<T>::operator=(const BinaryTreeStorage& other) {
    if (this == &other) return *this;

    BinarySearchTreeBase<T>* new_tree = other.tree ? other.tree->copy() : nullptr;
    delete tree;
    tree = new_tree;

    return *this;
}

template <typename T>
BinaryTreeStorage<T>::BinaryTreeStorage(BinaryTreeStorage&& other) noexcept
    : tree(other.tree) {
    other.tree = nullptr;
}

template <typename T>
BinaryTreeStorage<T>& BinaryTreeStorage<T>::operator=(BinaryTreeStorage&& other) noexcept {
    if (this == &other) return *this;

    delete tree;
    tree = other.tree;
    other.tree = nullptr;

    return *this;
}

template <typename T>
void BinaryTreeStorage<T>::add(const T& value) {
    if (!tree) throw std::runtime_error("Storage has no tree");
    tree->add(value);
}

template <typename T>
const T& BinaryTreeStorage<T>::top() const {
    if (is_empty()) throw std::runtime_error("Storage is empty");
    return tree->top();
}

template <typename T>
T BinaryTreeStorage<T>::extract_top() {
    if (is_empty()) throw std::runtime_error("Storage is empty");
    return tree->extract_top();
}

template <typename T>
bool BinaryTreeStorage<T>::contains(const T& value) const {
    return tree && tree->contains(value);
}

template <typename T>
bool BinaryTreeStorage<T>::is_empty() const {
    return !tree || tree->is_empty();
}

template <typename T>
std::size_t BinaryTreeStorage<T>::get_size() const {
    return tree ? tree->get_size() : 0;
}

template <typename T>
void BinaryTreeStorage<T>::clear() {
    if (tree) tree->clear();
}

template <typename T>
BinaryTreeStorage<T>* BinaryTreeStorage<T>::copy() const {
    return new BinaryTreeStorage<T>(*this);
}

template <typename T>
BinaryTreeStorage<T>* BinaryTreeStorage<T>::map(Transform transform) const {
    if (!tree) return copy();

    BinarySearchTreeBase<T>* result = tree->map(transform);
    try {
        return new BinaryTreeStorage<T>(result);
    } catch (...) {
        delete result;
        throw;
    }
}

template <typename T>
BinaryTreeStorage<T>* BinaryTreeStorage<T>::where(Predicate predicate) const {
    if (!predicate) throw std::invalid_argument("Predicate must not be null");
    if (!tree) return copy();

    BinarySearchTreeBase<T>* result = tree->where(predicate);
    try {
        return new BinaryTreeStorage<T>(result);
    } catch (...) {
        delete result;
        throw;
    }
}
