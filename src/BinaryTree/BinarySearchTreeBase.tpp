#include "../../include/BinaryTree/BinarySearchTreeBase.hpp"

#include <stdexcept>
#include <iostream>
#include <ostream>

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinarySearchTreeBase<T>& tree) {
    tree.print_in_stream(out);
    return out;
}

template <typename T>
BinarySearchTreeBase<T>::Node::Node(const T& data)
    : data(data), left(nullptr), right(nullptr), height(1) {}

template <typename T>
typename BinarySearchTreeBase<T>::Node*
BinarySearchTreeBase<T>::copy(Node* other_root) const {
    std::size_t count = 0;
    return copy(other_root, count);
}

template <typename T>
typename BinarySearchTreeBase<T>::Node*
BinarySearchTreeBase<T>::copy(Node* other_root, std::size_t& count) const {
    if (!other_root) return nullptr;

    Node* new_root = new Node(other_root->data);
    new_root->height = other_root->height;
    try {
        new_root->left = copy(other_root->left, count);
        new_root->right = copy(other_root->right, count);
    } catch (...) {
        clear(new_root);
        throw;
    }

    ++count;
    return new_root;
}

template <typename T>
void BinarySearchTreeBase<T>::clear(Node* node) const {
    if (!node) return;

    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
typename BinarySearchTreeBase<T>::Node*
BinarySearchTreeBase<T>::find_node(Node* node, const T& data) const {
    while (node) {
        int result = compare(data, node->data);
        if (result < 0) node = node->left;
        else if (result > 0) node = node->right;
        else return node;
    }

    return nullptr;
}

template <typename T>
bool BinarySearchTreeBase<T>::same_nodes(const Node* first, const Node* second) const {
    if (!first && !second) return true;
    if (!first || !second) return false;
    if (compare(first->data, second->data) != 0) return false;

    return same_nodes(first->left, second->left)
        && same_nodes(first->right, second->right);
}

template <typename T>
void BinarySearchTreeBase<T>::map_nodes(Node* node, BinarySearchTreeBase<T>* result, Transform transform) const {
    if (!node) return;

    result->add(transform(node->data));

    map_nodes(node->left, result, transform);
    map_nodes(node->right, result, transform);
}


template <typename T>
void BinarySearchTreeBase<T>::where_nodes(Node* node, BinarySearchTreeBase<T>* result, Predicate predicate) const {
    if (!node) return;

    if (predicate(node->data)) result->add(node->data);
    where_nodes(node->left, result, predicate);
    where_nodes(node->right, result, predicate);
}

template <typename T>
template <typename Y>
void BinarySearchTreeBase<T>::reduce_nodes(Node* node, Y& result, Reducer<Y> function, Order order) const {
    if (!node) return;

    Node* first;
    Node* second;
    if (order == Order::LPK || order == Order::LKP || order == Order::KLP) {
        first = node->left;
        second = node->right;
    }
    else {
        first = node->right;
        second = node->left;
    }

    if (order == Order::KLP || order == Order::KPL) {
        result = function(node->data, result);
    }
    reduce_nodes(first, result, function, order);
    if (order == Order::PKL || order == Order::LKP) {
        result = function(node->data, result);
    }
    reduce_nodes(second, result, function, order);
    if (order == Order::LPK || order == Order::PLK) {
        result = function(node->data, result);
    }
}

template <typename T>
void BinarySearchTreeBase<T>::save_nodes(Node* node, std::string& result, StringConverter converter, Order order) const {
    if (!node) return;

    Node* first;
    Node* second;
    if (order == Order::LPK || order == Order::LKP || order == Order::KLP) {
        first = node->left;
        second = node->right;
    }
    else {
        first = node->right;
        second = node->left;
    }

    if (order == Order::KLP || order == Order::KPL) {
        result += converter(node->data);
        result += ' ';
    }
    save_nodes(first, result, converter, order);
    if (order == Order::PKL || order == Order::LKP) {
        result += converter(node->data);
        result += ' ';
    }
    save_nodes(second, result, converter, order);
    if (order == Order::LPK || order == Order::PLK) {
        result += converter(node->data);
        result += ' ';
    }
}

template <typename T>
void BinarySearchTreeBase<T>::traverse(Node* node, Order order, Visit visit) const{
    if (!node) return;
    if (!visit) return;

    Node* first;
    Node* second;
    
    if (order == Order::LPK || order == Order::LKP || order == Order::KLP) {
        first = node->left;
        second = node->right;
    }
    else {
        first = node->right;
        second = node->left;
    }

    if (order == Order::KLP || order == Order::KPL) {
        visit(node->data);
    }

    traverse(first,order,visit);
    if (order == Order::PKL || order == Order::LKP) {
        visit(node->data);
    }
    traverse(second,order,visit);

    if (order == Order::LPK || order == Order::PLK) {
        visit(node->data);
    }
}

template <typename T>
void BinarySearchTreeBase<T>::print_node(Node* node, std::ostream& out) const {
    if (!node) return;

    print_node(node->left, out);
    out << node->data << ' ';
    print_node(node->right, out);
}

template <typename T>
void BinarySearchTreeBase<T>::print_function(const T& value) {
    std::cout << value << ' ';
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(Comparator compare)
    : root(nullptr), size(0), compare(compare) {
    if (!compare) throw std::invalid_argument("Comparator must not be null");
}

template <typename T>
BinarySearchTreeBase<T>::~BinarySearchTreeBase() {
    clear();
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(const BinarySearchTreeBase& other)
    : root(copy(other.root)), size(other.size), compare(other.compare) {}

template <typename T>
BinarySearchTreeBase<T>& BinarySearchTreeBase<T>::operator=(const BinarySearchTreeBase& other) {
    if (this == &other) return *this;

    clear();
    root = copy(other.root);
    size = other.size;
    compare = other.compare;

    return *this;
}

template <typename T>
BinarySearchTreeBase<T>::BinarySearchTreeBase(BinarySearchTreeBase&& other) noexcept
    : root(other.root), size(other.size), compare(other.compare) {
    other.root = nullptr;
    other.size = 0;
}

template <typename T>
BinarySearchTreeBase<T>& BinarySearchTreeBase<T>::operator=(BinarySearchTreeBase&& other) noexcept {
    if (this == &other) return *this;

    clear();
    root = other.root;
    size = other.size;
    compare = other.compare;
    other.root = nullptr;
    other.size = 0;

    return *this;
}

template <typename T>
T& BinarySearchTreeBase<T>::get(const T& data) {
    Node* node = find_node(root, data);
    if (!node) throw std::runtime_error("Value is not in the tree");
    return node->data;
}

template <typename T>
const T& BinarySearchTreeBase<T>::get(const T& data) const {
    Node* node = find_node(root, data);
    if (!node) throw std::runtime_error("Value is not in the tree");
    return node->data;
}

template <typename T>
BinarySearchTreeBase<T>* BinarySearchTreeBase<T>::get_subtree(const T& root_value) const {
    Node* node = find_node(root, root_value);
    if (!node) throw std::runtime_error("Value is not in the tree");

    BinarySearchTreeBase<T>* result = create_empty();
    try {
        result->root = copy(node, result->size);
    } catch (...) {
        delete result;
        throw;
    }

    return result;
}

template <typename T>
const T& BinarySearchTreeBase<T>::top() const {
    if (!root) throw std::runtime_error("Tree is empty");

    Node* node = root;
    while (node->left) node = node->left;
    return node->data;
}

template <typename T>
T BinarySearchTreeBase<T>::extract_top() {
    T value = top();
    remove(value);
    return value;
}

template <typename T>
bool BinarySearchTreeBase<T>::contains(const T& data) const {
    return find_node(root, data) != nullptr;
}

template <typename T>
bool BinarySearchTreeBase<T>::contains_subtree(const BinarySearchTreeBase& subtree) const {
    if (!subtree.root) return true;

    Node* node = find_node(root, subtree.root->data);
    return same_nodes(node, subtree.root);
}

template <typename T>
bool BinarySearchTreeBase<T>::contains_key(const T& data) const {
    return contains(data);
}

template <typename T>
std::size_t BinarySearchTreeBase<T>::get_size() const {
    return size;
}

template <typename T>
bool BinarySearchTreeBase<T>::is_empty() const {
    return size == 0;
}

template <typename T>
void BinarySearchTreeBase<T>::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}

template <typename T>
BinarySearchTreeBase<T>* BinarySearchTreeBase<T>::map(Transform transform) const {
    if (!transform) {
        return copy();
    }

    BinarySearchTreeBase<T>* result = create_empty();
    try {
        map_nodes(root, result, transform);
    } catch (...) {
        delete result;
        throw;
    }

    return result;
}

template <typename T>
BinarySearchTreeBase<T>* BinarySearchTreeBase<T>::where(Predicate predicate) const {
    if (!predicate) throw std::invalid_argument("Predicate must not be null");

    BinarySearchTreeBase<T>* result = create_empty();
    try {
        where_nodes(root, result, predicate);
    } catch (...) {
        delete result;
        throw;
    }

    return result;
}

template <typename T>
template <typename Y>
Y BinarySearchTreeBase<T>::reduce(Reducer<Y> function, const Y& initial, Order order) const {
    if (!function) throw std::invalid_argument("Reducer must not be null");

    Y result = initial;
    reduce_nodes(root, result, function, order);
    return result;
}

template <typename T>
std::string BinarySearchTreeBase<T>::to_string(StringConverter converter, Order order) const {
    if (!converter) throw std::invalid_argument("String converter must not be null");

    std::string result;
    save_nodes(root, result, converter, order);
    if (!result.empty()) result.pop_back();

    return result;
}

template <typename T>
void BinarySearchTreeBase<T>::traverse(Order order, Visit visit) const {
    traverse(root, order, visit);
}

template <typename T>
void BinarySearchTreeBase<T>::print_tree(Order order) const {
    traverse(order, print_function);
}

template <typename T>
void BinarySearchTreeBase<T>::print_in_stream(std::ostream& out) const {
    print_node(root, out);
}
