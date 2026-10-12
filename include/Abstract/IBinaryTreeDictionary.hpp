#ifndef IBINARY_TREE_DICTIONARY_HPP
#define IBINARY_TREE_DICTIONARY_HPP

#include "IDictionary.hpp"

template <typename Key, typename Value>
class IBinaryTreeDictionary : public IDictionary<Key,Value> {
public:

    void add(const Key&, const Value&) override = 0;
    void remove(const Key&) override = 0;
    Value& get(const Key&) override = 0;
    const Value& get(const Key&) const override = 0;
    bool contains_key(const Key&) const override = 0;
    std::size_t get_size() const override = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
};

#endif // IBINARY_TREE_DICTIONARY_HPP
