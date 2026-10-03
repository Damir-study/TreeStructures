#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "BinarySearchTreeBase.hpp"

template <typename T>
class BinarySearchTree : public BinarySearchTreeBase<T> {
public:
    BinarySearchTree();
    BinarySearchTree(typename BinarySearchTreeBase<T>::Comparator compare);

    void add(const T& data);
    void remove(const T& data);
};

#include "../../src/BinaryTree/BinarySearchTree.tpp"

#endif // BINARY_SEARCH_TREE_HPP
