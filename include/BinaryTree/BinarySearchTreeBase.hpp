#ifndef BINARY_SEARCH_TREE_BASE_HPP
#define BINARY_SEARCH_TREE_BASE_HPP

#include <cstddef>
#include <ostream>
#include <string>


template <typename T>
int binary_tree_default_compare(const T& first, const T& second) {
    if (first < second) return -1;
    if (second < first) return 1;
    return 0;
}

template <typename T>
class BinarySearchTreeBase {
public:
    enum class Order {
        KLP,
        KPL,
        PKL,
        PLK,
        LPK,
        LKP
    };

    using Comparator = int (*)(const T&, const T&);
    using Visit = void (*)(const T&);
    using Transform = T (*)(const T&);
    using Predicate = bool (*)(const T&);
    using StringConverter = std::string (*)(const T&);
    template <typename Y>
    using Reducer = Y (*)(const T&, const Y&);
protected:
    struct Node{
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
    void map_nodes(Node* node, BinarySearchTreeBase<T>* result, Transform transform) const;
    void where_nodes(Node* node, BinarySearchTreeBase<T>* result, Predicate predicate) const;
    template <typename Y>
    void reduce_nodes(Node* node, Y& result, Reducer<Y> function, Order order) const;
    void save_nodes(Node* node, std::string& result, StringConverter converter, Order order) const;
        
    void traverse(Node* node, Order order, Visit visit) const;

    void print_node(Node* node, std::ostream& out) const;
    static void print_function(const T& value);
public:
    BinarySearchTreeBase(Comparator compare = binary_tree_default_compare<T>);
    virtual ~BinarySearchTreeBase() = 0;

    BinarySearchTreeBase(const BinarySearchTreeBase& other);
    BinarySearchTreeBase& operator=(const BinarySearchTreeBase& other);
    BinarySearchTreeBase(BinarySearchTreeBase&& other) noexcept;
    BinarySearchTreeBase& operator=(BinarySearchTreeBase&& other) noexcept;

    virtual void add(const T& data) = 0;
    virtual void remove(const T& data) = 0;
    virtual BinarySearchTreeBase* create_empty() const = 0;
    virtual BinarySearchTreeBase* copy() const = 0;

    const T& get(const T& data) const;
    bool contains(const T& data) const;
    bool contains_key(const T& data) const;
    std::size_t get_size() const;
    bool is_empty() const;
    void clear();
    
    BinarySearchTreeBase* map(Transform transform) const;
    BinarySearchTreeBase* where(Predicate predicate) const;
    template <typename Y>
    Y reduce(Reducer<Y> function, const Y& initial, Order order = Order::LKP) const;
    std::string to_string(StringConverter converter, Order order = Order::LKP) const;
    void traverse(Order order, Visit visit) const;
    void print_tree(Order order) const;
    void print_in_stream(std::ostream& out) const;
};

#include "../../src/BinaryTree/BinarySearchTreeBase.tpp"

#endif // BINARY_SEARCH_TREE_BASE_HPP
