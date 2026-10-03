#include "../../include/BinaryTree/BinarySearchTree.hpp"

#include <stdexcept>

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : BinarySearchTreeBase<T>() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(
    typename BinarySearchTreeBase<T>::Comparator compare)
    : BinarySearchTreeBase<T>(compare) {}

template <typename T>
void BinarySearchTree<T>::add(const T& new_value) {
    auto current = &this->root;

    while (*current) {
        int result = this->compare(new_value, (*current)->data);

        if (result < 0) current = &(*current)->left;
        else if (result > 0) current = &(*current)->right;
        else throw std::runtime_error("Value already exists");
    }

    *current = new typename BinarySearchTreeBase<T>::Node(new_value);
    ++this->size;
}

template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
    auto node_ptr = &this->root;

    while (*node_ptr) {
        int result = this->compare(value, (*node_ptr)->data);
        if (result == 0) break;

        if (result < 0) node_ptr = &(*node_ptr)->left;
        else node_ptr = &(*node_ptr)->right;
    }

    if (!*node_ptr) return;

    auto removed = *node_ptr;

    if (!removed->left) {
        *node_ptr = removed->right;
    }
    else if (!removed->right) {
        *node_ptr = removed->left;
    }
    else {
        auto replacement_link = &removed->right;

        while ((*replacement_link)->left) {
            replacement_link = &(*replacement_link)->left;
        }

        auto replacement = *replacement_link;
        *replacement_link = replacement->right;

        replacement->left = removed->left;
        replacement->right = removed->right;
        *node_ptr = replacement;
    }

    delete removed;
    --this->size;
}
