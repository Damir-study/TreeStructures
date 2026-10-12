#ifndef BINARY_TREE_DICTIONARY_HPP
#define BINARY_TREE_DICTIONARY_HPP

#include "../BinaryTree/BinarySearchTree.hpp"
#include "../Abstract/IBinaryTreeDictionary.hpp"

template <typename Key, typename Value>
class BinaryTreeDictionary : public IBinaryTreeDictionary<Key, Value> {
public:
    using Comparator = int (*)(const Key&, const Key&);
private:
    struct Pair {
        Key key;
        Value value;
        Comparator compare;

        Pair(const Key& key, Comparator compare) : key(key), value(), compare(compare) {}
        Pair(const Key& key, const Value& value, Comparator compare) : key(key), value(value), compare(compare) {}

        bool operator<(const Pair& other) const { return compare(key, other.key) < 0; }
        bool operator>(const Pair& other) const { return compare(key, other.key) > 0; }
    };

    Comparator compare;
    BinarySearchTree<Pair> tree;
public:
    BinaryTreeDictionary(Comparator compare = binary_tree_default_compare<Key>);
    ~BinaryTreeDictionary() override = default;
    BinaryTreeDictionary(const BinaryTreeDictionary&) = default;
    BinaryTreeDictionary& operator=(const BinaryTreeDictionary&) = default;
    BinaryTreeDictionary(BinaryTreeDictionary&&) noexcept = default;
    BinaryTreeDictionary& operator=(BinaryTreeDictionary&&) noexcept = default;

    void add(const Key& key, const Value& value) override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    bool contains_key(const Key& key) const override;
    void remove(const Key& key) override;
    std::size_t get_size() const override;
    bool is_empty() const override;
    void clear() override;
};

#include "../../src/BinarytreeDictionary/BinaryTreeDictionary.tpp"

#endif // BINARY_TREE_DICTIONARY_HPP
