#ifndef BINARY_TREE_STORAGE_HPP
#define BINARY_TREE_STORAGE_HPP

#include "../Abstract/IPriorityQueueStorage.hpp"
#include "../BinaryTree/BinarySearchTreeBase.hpp"

template <typename T>
class BinaryTreeStorage : public IPriorityQueueStorage<T> {
public:
    using Transform = typename IPriorityQueueStorage<T>::Transform;
    using Predicate = typename IPriorityQueueStorage<T>::Predicate;

private:
    BinarySearchTreeBase<T>* tree;

public:
    explicit BinaryTreeStorage(BinarySearchTreeBase<T>* tree);
    ~BinaryTreeStorage() override;

    BinaryTreeStorage(const BinaryTreeStorage& other);
    BinaryTreeStorage& operator=(const BinaryTreeStorage& other);
    BinaryTreeStorage(BinaryTreeStorage&& other) noexcept;
    BinaryTreeStorage& operator=(BinaryTreeStorage&& other) noexcept;

    void add(const T& value) override;
    const T& top() const override;
    T extract_top() override;

    bool contains(const T& value) const override;
    bool is_empty() const override;
    std::size_t get_size() const override;
    void clear() override;

    BinaryTreeStorage* copy() const override;
    BinaryTreeStorage* map(Transform transform) const override;
    BinaryTreeStorage* where(Predicate predicate) const override;
};

#include "../../src/PriorityQueue/BinaryTreeStorage.tpp"

#endif // BINARY_TREE_STORAGE_HPP
