#include "../../include/BinaryTree/BinarySearchTree.hpp"

#include <stdexcept>

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : BinarySearchTreeBase<T>() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(
    Comparator compare)
    : BinarySearchTreeBase<T>(compare) {}

template <typename T>
void BinarySearchTree<T>::add(const T& new_value) {
    Node** current = &root;

    while (*current) {
        int result = compare(new_value, (*current)->data);

        if (result < 0) current = &(*current)->left;
        else if (result > 0) current = &(*current)->right;
        else throw std::runtime_error("Value already exists");
    }

    *current = new Node(new_value);
    ++size;
}

template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
    Node** node_ptr = &root;

    while (*node_ptr) {
        int result = compare(value, (*node_ptr)->data);
        if (result == 0) break;

        if (result < 0) node_ptr = &(*node_ptr)->left;
        else node_ptr = &(*node_ptr)->right;
    }

    if (!*node_ptr) return;

    Node* removed = *node_ptr;

    if (!removed->left) {
        *node_ptr = removed->right;
    }
    else if (!removed->right) {
        *node_ptr = removed->left;
    }
    else {
        Node** replacement_ptr = &removed->right;

        while ((*replacement_ptr)->left) {
            replacement_ptr = &(*replacement_ptr)->left;
        }

        Node* replacement = *replacement_ptr;
        *replacement_ptr = replacement->right;

        replacement->left = removed->left;
        replacement->right = removed->right;
        *node_ptr = replacement;
    }

    delete removed;
    --size;
}

template <typename T>
BinarySearchTreeBase<T>* BinarySearchTree<T>::create_empty() const{
    return new BinarySearchTree<T>(compare);
}

template <typename T>
BinarySearchTreeBase<T>* BinarySearchTree<T>::copy() const{
    return new BinarySearchTree<T>(*this);
}