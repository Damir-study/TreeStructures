#ifndef BINARY_TREE_DICTIONARY_STORAGE_HPP
#define BINARY_TREE_DICTIONARY_STORAGE_HPP

#include "../Abstract/IDictionaryStorage.hpp"
#include "../BinaryTree/BinarySearchTreeBase.hpp"
#include "DictionaryPair.hpp"

template <typename Key, typename Value>
class BinaryTreeDictionaryStorage : public IDictionaryStorage<Key, Value> {
public:
    using Pair = DictionaryPair<Key, Value>;
    using Comparator = typename Pair::Comparator;
private:
    Comparator compare;
    BinarySearchTreeBase<Pair>* tree;

public:
    BinaryTreeDictionaryStorage(BinarySearchTreeBase<Pair>* tree, Comparator compare = default_compare<Key>);
    ~BinaryTreeDictionaryStorage() override;

    BinaryTreeDictionaryStorage(const BinaryTreeDictionaryStorage& other);
    BinaryTreeDictionaryStorage& operator=(const BinaryTreeDictionaryStorage& other);
    BinaryTreeDictionaryStorage(BinaryTreeDictionaryStorage&& other) noexcept;
    BinaryTreeDictionaryStorage& operator=(BinaryTreeDictionaryStorage&& other) noexcept;

    void add(const Key& key, const Value& value) override;
    void remove(const Key& key) override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    bool contains_key(const Key& key) const override;
    std::size_t get_size() const override;
    bool is_empty() const override;
    void clear() override;

    BinaryTreeDictionaryStorage* copy() const override;
};

#include "../../src/Dictionary/BinaryTreeDictionaryStorage.tpp"

#endif // BINARY_TREE_DICTIONARY_STORAGE_HPP
