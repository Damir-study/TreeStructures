#include "../../include/BinaryTree/BalancedTree.hpp"

#include <stdexcept>
#include "../../external/mutable_array_sequence.h"

template <typename T>
typename BinarySearchTreeBase<T>::Node* BalancedTree<T>::rotate_left(Node* node) {
    Node* new_root = node->right;
    Node* left_new_root = new_root->left;

    node->right = left_new_root;
    new_root->left = node;

    update_height(node);
    update_height(new_root);

    return new_root;
}

template <typename T>
typename BinarySearchTreeBase<T>::Node* BalancedTree<T>::rotate_right(Node* node) {
    Node* new_root = node->left;
    Node* right_new_root = new_root->right;

    node->left = right_new_root;
    new_root->right = node;

    update_height(node);
    update_height(new_root);

    return new_root;
}

template <typename T>
typename BinarySearchTreeBase<T>::Node* BalancedTree<T>::balance(Node* node) {
    if (!node) return nullptr;

    update_height(node);

    unsigned int left_height = node->left ? node->left->height : 0;
    unsigned int right_height = node->right ? node->right->height : 0;
    int balance_factor = static_cast<int>(left_height )- static_cast<int>(right_height);

    if (balance_factor > 1) {
        unsigned int left_left_height = node->left->left ? node->left->left->height : 0;
        unsigned int left_right_height = node->left->right ? node->left->right->height : 0;

        if (left_right_height > left_left_height) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }

    if (balance_factor < -1) {
        unsigned int right_left_height = node->right->left ? node->right->left->height : 0;
        unsigned int right_right_height = node->right->right ? node->right->right->height : 0;

        if (right_right_height < right_left_height) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }

    return node;
}

template <typename T>
void BalancedTree<T>::update_height(Node* node) {
    unsigned int left_node_height = node->left ? node->left->height : 0;
    unsigned int right_node_height = node->right ? node->right->height : 0;
    unsigned int max_height = right_node_height > left_node_height ? right_node_height : left_node_height;
    node->height = 1 + max_height;
}

template <typename T>
BalancedTree<T>::BalancedTree()
    : BinarySearchTreeBase<T>() {}

template <typename T>
BalancedTree<T>::BalancedTree(Comparator compare)
    : BinarySearchTreeBase<T>(compare) {}
    
template <typename T>
void BalancedTree<T>::add(const T& value) {
    mutable_array_sequence<Node**> path;

    Node** temp = &root;

    while (*temp) {
        path.append(temp);
        int result = compare(value, (*temp)->data);
        if (result > 0) temp = &(*temp)->right;
        else if (result < 0) temp = &(*temp)->left;
        else throw std::runtime_error("Value already exists");
    }

    (*temp) = new Node(value);
    ++size;

    for (int i = path.get_length()-1; i >= 0;--i) {
        *path[i] = balance(*path[i]);
    }

}

template <typename T>
void BalancedTree<T>::remove(const T& value) {
    mutable_array_sequence<Node**> path;

    Node** node_ptr = &root;

    while (*node_ptr) {
        path.append(node_ptr);
        int result = compare(value,(*node_ptr)->data);

        if (result == 0) break;
        if (result > 0) node_ptr = &(*node_ptr)->right;
        else node_ptr = &(*node_ptr)->left;
    }

    if (!*node_ptr) return;

    Node* removed = (*node_ptr);
    int main_path_length = path.get_length();

    if (!removed->left) {
        *node_ptr = removed->right;
    }
    else if (!removed->right) {
        *node_ptr = removed->left;
    }
    else {
        Node** replacement_ptr = &removed->right;

        while ((*replacement_ptr)->left) {
            path.append(replacement_ptr);
            replacement_ptr = &(*replacement_ptr)->left;
        }

        Node* replacement = *replacement_ptr;
        *replacement_ptr = replacement->right;

        for (int i = path.get_length() - 1; i >= main_path_length; --i) {
            *path[i] = balance(*path[i]);
        }

        replacement->left = removed->left;
        replacement->right = removed->right;
        *node_ptr = replacement;
    }

    delete removed;
    --size;

    for (int i = main_path_length - 1; i >= 0;--i) {
        *path[i] = balance(*path[i]);
    }
}