#ifndef BINARY_SEARCH_TREE_BASE_HPP
#define BINARY_SEARCH_TREE_BASE_HPP

#include <cstddef>
#include <ostream>
#include <string>
#include "../tools/Comparator.hpp"
#include "../tools/TreePrinter.hpp"

template <typename T>
class BinarySearchTreeBase;

template <typename T>
void traverse_lkp(const typename BinarySearchTreeBase<T>::INode* node,
                  typename BinarySearchTreeBase<T>::Visit visit);

template <typename T>
class BinarySearchTreeBase {
public:
    using Comparator = int (*)(const T&, const T&);
    using Visit = void (*)(const T&);
    using Transform = T (*)(const T&);
    using Predicate = bool (*)(const T&);
    using StringConverter = std::string (*)(const T&);
    template <typename Y>
    using Reducer = Y (*)(const T&, const Y&);
    class INode {
    public:
        virtual const T& get_data() const = 0;
        virtual const INode* get_left() const = 0;
        virtual const INode* get_right() const = 0;
        virtual ~INode() = default;
    };

    using Traversal = void (*)(const INode*, Visit);
protected:
    class Node : public INode {
    public:
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
        unsigned int height = 1;

        Node(const T& data);
        const T& get_data() const override { return data; }
        const INode* get_left() const override { return left; }
        const INode* get_right() const override { return right; }
    };

    Node* root;
    std::size_t size;
    Comparator compare;

    Node* copy(Node* other_root) const;
    Node* copy(Node* other_root, std::size_t& count) const;
    void clear(Node* node) const;
    Node* find_node(Node* node, const T& data) const;
    bool same_nodes(const Node* first, const Node* second) const;
    void map_nodes(Node* node, BinarySearchTreeBase<T>* result, Transform transform) const;
    void where_nodes(Node* node, BinarySearchTreeBase<T>* result, Predicate predicate) const;
    template <typename Y>
    void reduce_nodes(Node* node, Y& result, Reducer<Y> function) const;
    void save_nodes(Node* node, std::string& result, StringConverter converter) const;
        
public:
    BinarySearchTreeBase(Comparator compare = default_compare<T>);
    virtual ~BinarySearchTreeBase() = 0;

    BinarySearchTreeBase(const BinarySearchTreeBase& other);
    BinarySearchTreeBase& operator=(const BinarySearchTreeBase& other);
    BinarySearchTreeBase(BinarySearchTreeBase&& other) noexcept;
    BinarySearchTreeBase& operator=(BinarySearchTreeBase&& other) noexcept;

    virtual void add(const T& data) = 0;
    virtual void remove(const T& data) = 0;
    virtual BinarySearchTreeBase* create_empty() const = 0;
    virtual BinarySearchTreeBase* copy() const = 0;

    T& get(const T& data);
    const T& get(const T& data) const;
    BinarySearchTreeBase* get_subtree(const T& root_value) const;
    const T& top() const;
    T extract_top();
    bool contains(const T& data) const;
    bool contains_subtree(const BinarySearchTreeBase& subtree) const;
    bool contains_key(const T& data) const;
    std::size_t get_size() const;
    bool is_empty() const;
    void clear();
    
    BinarySearchTreeBase* map(Transform transform) const;
    BinarySearchTreeBase* where(Predicate predicate) const;
    template <typename Y>
    Y reduce(Reducer<Y> function, const Y& initial) const;
    std::string to_string(StringConverter converter) const;
    void traverse(Visit visit, Traversal traversal = traverse_lkp<T>) const;
    void print_structure(std::ostream& out, StringConverter converter, std::size_t max_depth = 3) const;
};

#include "../../src/BinaryTree/BinarySearchTreeBase.tpp"

#endif // BINARY_SEARCH_TREE_BASE_HPP
