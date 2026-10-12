#ifndef BALANCED_TREE_DICTIONARY_HPP
#define BALANCED_TREE_DICTIONARY_HPP

#include "../BinaryTree/BalancedTree.hpp"
#include "../Abstract/IBinaryTreeDictionary.hpp"

template <typename Key, typename Value>
class BalancedTreeDictionary : public IBinaryTreeDictionary<Key, Value> {
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
    BalancedTree<Pair> tree;
public:
    BalancedTreeDictionary(Comparator compare = binary_tree_default_compare<Key>);
    ~BalancedTreeDictionary() override = default;
    BalancedTreeDictionary(const BalancedTreeDictionary&) = default;
    BalancedTreeDictionary& operator=(const BalancedTreeDictionary&) = default;
    BalancedTreeDictionary(BalancedTreeDictionary&&) noexcept = default;
    BalancedTreeDictionary& operator=(BalancedTreeDictionary&&) noexcept = default;

    void add(const Key& key, const Value& value) override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    bool contains_key(const Key& key) const override;
    void remove(const Key& key) override;
    std::size_t get_size() const override;
    bool is_empty() const override;
    void clear() override;
};

#include "../../src/BinarytreeDictionary/BalancedTreeDictionary.tpp"

#endif // BALANCED_TREE_DICTIONARY_HPP
