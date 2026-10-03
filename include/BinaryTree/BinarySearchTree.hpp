#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "BinarySearchTreeBase.hpp"

template <typename T>
class BinarySearchTree : public BinarySearchTreeBase<T> {
private:
    using Node = typename BinarySearchTreeBase<T>::Node;
    using BinarySearchTreeBase<T>::root;
    using BinarySearchTreeBase<T>::size;
    using BinarySearchTreeBase<T>::compare;

public:
    using Comparator = typename BinarySearchTreeBase<T>::Comparator;

    BinarySearchTree();
    BinarySearchTree(Comparator compare);

    void add(const T& data);
    void remove(const T& data);
};

#include "../../src/BinaryTree/BinarySearchTree.tpp"

#endif // BINARY_SEARCH_TREE_HPP
