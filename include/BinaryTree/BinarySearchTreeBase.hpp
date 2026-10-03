#ifndef BINARY_SEARCH_TREE_BASE_HPP
#define BINARY_SEARCH_TREE_BASE_HPP

#include <cstddef>

template <typename T>
int binary_tree_default_compare(const T& first, const T& second) {
    if (first < second) return -1;
    if (second < first) return 1;
    return 0;
}

template <typename T>
class BinarySearchTreeBase {
public:
    using Comparator = int (*)(const T&, const T&);
protected:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
        unsigned int height = 1;

        Node(const T& data);
    };

    Node* root;
    std::size_t size;
    Comparator compare;

    Node* copy(Node* other_root) const;
    void clear(Node* node) const;
    Node* find_node(Node* node, const T& data) const;
public:
    BinarySearchTreeBase(Comparator compare = binary_tree_default_compare<T>);
    virtual ~BinarySearchTreeBase() = 0;

    BinarySearchTreeBase(const BinarySearchTreeBase& other);
    BinarySearchTreeBase& operator=(const BinarySearchTreeBase& other);
    BinarySearchTreeBase(BinarySearchTreeBase&& other) noexcept;
    BinarySearchTreeBase& operator=(BinarySearchTreeBase&& other) noexcept;

    T& get(const T& data);
    const T& get(const T& data) const;
    bool contains(const T& data) const;
    bool contains_key(const T& data) const;
    std::size_t get_size() const;
    bool is_empty() const;
    void clear();
};

#include "../../src/BinaryTree/BinarySearchTreeBase.tpp"

#endif // BINARY_SEARCH_TREE_BASE_HPP
