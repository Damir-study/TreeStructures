#ifndef TREE_TRAVERSALS_HPP
#define TREE_TRAVERSALS_HPP

#include "../BinaryTree/BinarySearchTreeBase.hpp"
#include "../../external/mutable_array_sequence.h"

template <typename T>
void traverse_klp(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    visit(node->get_data());
    traverse_klp<T>(node->get_left(), visit);
    traverse_klp<T>(node->get_right(), visit);
}

template <typename T>
void traverse_kpl(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    visit(node->get_data());
    traverse_kpl<T>(node->get_right(), visit);
    traverse_kpl<T>(node->get_left(), visit);
}

template <typename T>
void traverse_pkl(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    traverse_pkl<T>(node->get_right(), visit);
    visit(node->get_data());
    traverse_pkl<T>(node->get_left(), visit);
}

template <typename T>
void traverse_plk(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    traverse_plk<T>(node->get_right(), visit);
    traverse_plk<T>(node->get_left(), visit);
    visit(node->get_data());
}

template <typename T>
void traverse_lpk(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    traverse_lpk<T>(node->get_left(), visit);
    traverse_lpk<T>(node->get_right(), visit);
    visit(node->get_data());
}

template <typename T>
void traverse_lkp(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit) {
    if (!node || !visit) return;
    traverse_lkp<T>(node->get_left(), visit);
    visit(node->get_data());
    traverse_lkp<T>(node->get_right(), visit);
}

template <typename T>
void breadth_first_traversal(const typename BinarySearchTreeBase<T>::INode* root,
                             typename BinarySearchTreeBase<T>::Visit visit) {
    if (!root || !visit) return;
    mutable_array_sequence<const typename BinarySearchTreeBase<T>::INode*> nodes;
    nodes.append(root);
    for (int i = 0; i < nodes.get_length(); ++i) {
        const auto* node = nodes[i];
        visit(node->get_data());
        if (node->get_left()) nodes.append(node->get_left());
        if (node->get_right()) nodes.append(node->get_right());
    }
}

#endif // TREE_TRAVERSALS_HPP
