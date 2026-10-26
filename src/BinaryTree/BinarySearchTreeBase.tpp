#include "../../include/BinaryTree/BinarySearchTreeBase.hpp"
#include "../../include/tools/TreeTraversals.hpp"

#include <stdexcept>
#include <iostream>
#include <ostream>

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
void BinarySearchTreeBase<T>::reduce_nodes(Node* node, Y& result, Reducer<Y> function) const {
    if (!node) return;
    reduce_nodes(node->left, result, function);
    result = function(node->data, result);
    reduce_nodes(node->right, result, function);
}

template <typename T>
void BinarySearchTreeBase<T>::save_nodes(Node* node, std::string& result, StringConverter converter) const {
    if (!node) return;
    save_nodes(node->left, result, converter);
    result += converter(node->data);
    result += ' ';
    save_nodes(node->right, result, converter);
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
Y BinarySearchTreeBase<T>::reduce(Reducer<Y> function, const Y& initial) const {
    if (!function) throw std::invalid_argument("Reducer must not be null");

    Y result = initial;
    reduce_nodes(root, result, function);
    return result;
}

template <typename T>
std::string BinarySearchTreeBase<T>::to_string(StringConverter converter) const {
    if (!converter) throw std::invalid_argument("String converter must not be null");

    std::string result;
    save_nodes(root, result, converter);
    if (!result.empty()) result.pop_back();

    return result;
}

template <typename T>
void BinarySearchTreeBase<T>::traverse(Visit visit, Traversal traversal) const {
    if (!traversal || !visit) return;
    traversal(root, visit);
}

template <typename T>
void BinarySearchTreeBase<T>::print_structure(
    std::ostream& out, StringConverter converter, std::size_t max_depth) const {
    if (!converter) throw std::invalid_argument("String converter must not be null");
    if (max_depth > 5) throw std::invalid_argument("Maximum depth is 5");
    if (!root) { out << "[пусто]\n"; return; }

    mutable_array_sequence<const Node*> level;
    level.append(root);
    mutable_array_sequence<mutable_array_sequence<std::string>> levels;
    bool more = false;
    for (std::size_t depth = 0; depth <= max_depth; ++depth) {
        mutable_array_sequence<const Node*> next;
        mutable_array_sequence<std::string> values;
        more = false;
        for (int i = 0; i < level.get_length(); ++i) {
            const Node* node = level[i];
            std::string value = node ? converter(node->data) : "";
            values.append(node && value.empty() ? "\"\"" : value);
            next.append(node ? node->left : nullptr);
            next.append(node ? node->right : nullptr);
            if (node && (node->left || node->right)) more = true;
        }
        levels.append(values);
        if (!more) break;
        level = next;
    }
    print_tree_levels(out, levels);
    if (more) out << "... (ниже есть узлы)\n";
}
