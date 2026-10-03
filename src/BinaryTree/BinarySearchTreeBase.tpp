#include "../../include/BinaryTree/BinarySearchTreeBase.hpp"

#include <stdexcept>

template <typename T>
BinarySearchTreeBase<T>::Node::Node(const T& data)
    : data(data), left(nullptr), right(nullptr), height(1) {}

template <typename T>
typename BinarySearchTreeBase<T>::Node*
BinarySearchTreeBase<T>::copy(Node* other_root) const {
    if (!other_root) return nullptr;

    Node* new_root = new Node(other_root->data);
    new_root->height = other_root->height;
    try {
        new_root->left = copy(other_root->left);
        new_root->right = copy(other_root->right);
    } catch (...) {
        clear(new_root);
        throw;
    }

    return new_root;
}

template <typename T>
void BinarySearchTreeBase<T>::clear(Node* node) const {
    if (!node) return;

    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
typename BinarySearchTreeBase<T>::Node*
BinarySearchTreeBase<T>::find_node(Node* node, const T& data) const {
    while (node) {
        int result = compare(data, node->data);
        if (result < 0) node = node->left;
        else if (result > 0) node = node->right;
        else return node;
    }

    return nullptr;
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(Comparator compare)
    : root(nullptr), size(0), compare(compare) {
    if (!compare) throw std::invalid_argument("Comparator must not be null");
}

template <typename T>
BinarySearchTreeBase<T>::~BinarySearchTreeBase() {
    clear();
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(const BinarySearchTreeBase& other)
    : root(copy(other.root)), size(other.size), compare(other.compare) {}

template <typename T>
BinarySearchTreeBase<T>& BinarySearchTreeBase<T>::operator=(const BinarySearchTreeBase& other) {
    if (this == &other) return *this;

    clear();
    root = copy(other.root);
    size = other.size;
    compare = other.compare;

    return *this;
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(BinarySearchTreeBase&& other) noexcept
    : root(other.root), size(other.size), compare(other.compare) {
    other.root = nullptr;
    other.size = 0;
}

template <typename T>
BinarySearchTreeBase<T>& BinarySearchTreeBase<T>::operator=(BinarySearchTreeBase&& other) noexcept {
    if (this == &other) return *this;

    clear();
    root = other.root;
    size = other.size;
    compare = other.compare;
    other.root = nullptr;
    other.size = 0;

    return *this;
}

template <typename T>
T& BinarySearchTreeBase<T>::get(const T& data) {
    Node* node = find_node(root, data);
    if (!node) throw std::runtime_error("Value is not in the tree");
    return node->data;
}

template <typename T>
const T& BinarySearchTreeBase<T>::get(const T& data) const {
    Node* node = find_node(root, data);
    if (!node) throw std::runtime_error("Value is not in the tree");
    return node->data;
}

template <typename T>
bool BinarySearchTreeBase<T>::contains(const T& data) const {
    return find_node(root, data) != nullptr;
}

template <typename T>
bool BinarySearchTreeBase<T>::contains_key(const T& data) const {
    return contains(data);
}

template <typename T>
std::size_t BinarySearchTreeBase<T>::get_size() const {
    return size;
}

template <typename T>
bool BinarySearchTreeBase<T>::is_empty() const {
    return size == 0;
}

template <typename T>
void BinarySearchTreeBase<T>::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}
