#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "../Abstract/IDictionaryStorage.hpp"

template <typename Key, typename Value>
class Dictionary {
private:
    IDictionaryStorage<Key, Value>* storage;

public:
    Dictionary(IDictionaryStorage<Key, Value>* storage);
    ~Dictionary();

    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    Dictionary(Dictionary&& other) noexcept;
    Dictionary& operator=(Dictionary&& other) noexcept;

    void add(const Key& key, const Value& value);
    void remove(const Key& key);
    Value& get(const Key& key);
    const Value& get(const Key& key) const;
    bool contains_key(const Key& key) const;
    std::size_t get_size() const;
    bool is_empty() const;
    void clear();
};

#include "../../src/Dictionary/Dictionary.tpp"

#endif // DICTIONARY_HPP
