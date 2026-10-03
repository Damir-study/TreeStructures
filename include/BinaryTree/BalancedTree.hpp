#ifndef BALANCED_TREE_HPP
#define BALANCED_TREE_HPP

#include "BinarySearchTreeBase.hpp"

template <typename T>
class BalancedTree : public BinarySearchTreeBase<T> {
private:
    using Node = typename BinarySearchTreeBase<T>::Node;
    using BinarySearchTreeBase<T>::root;
    using BinarySearchTreeBase<T>::size;
    
    Node* rotate_right(Node*);
    Node* rotate_left(Node*);
    Node* balance(Node*);

    void update_height(Node*);

public:
    using Comparator = typename BinarySearchTreeBase<T>::Comparator;

    BalancedTree();
    BalancedTree(Comparator compare);

    void add(const T& data);
    void remove(const T& data);
};

#include "../../src/BinaryTree/BalancedTree.tpp"

#endif // BALANCED_TREE_HPP
