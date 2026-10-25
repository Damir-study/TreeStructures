#ifndef BINARY_HEAP_DICTIONARY_STORAGE_HPP
#define BINARY_HEAP_DICTIONARY_STORAGE_HPP

#include "../Abstract/IDictionaryStorage.hpp"
#include "../BinaryHeap/BinaryHeap.hpp"
#include "DictionaryPair.hpp"

template <typename Key, typename Value>
class BinaryHeapDictionaryStorage : public IDictionaryStorage<Key, Value> {
public:
    using Pair = DictionaryPair<Key, Value>;
    using Comparator = typename Pair::Comparator;
    using Visit = typename IDictionaryStorage<Key, Value>::Visit;
private:
    Comparator compare;
    BinaryHeap<Pair> heap;

public:
    BinaryHeapDictionaryStorage(Comparator compare = default_compare<Key>);

    void add(const Key& key, const Value& value) override;
    void remove(const Key& key) override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    bool contains_key(const Key& key) const override;
    std::size_t get_size() const override;
    bool is_empty() const override;
    void clear() override;
    void traverse(Visit visit) const override;

    BinaryHeapDictionaryStorage* copy() const override;
};

#include "../../src/Dictionary/BinaryHeapDictionaryStorage.tpp"

#endif // BINARY_HEAP_DICTIONARY_STORAGE_HPP
