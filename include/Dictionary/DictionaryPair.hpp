#ifndef DICTIONARY_PAIR_HPP
#define DICTIONARY_PAIR_HPP

#include "../tools/Comparator.hpp"

template <typename Key, typename Value>
struct DictionaryPair {
    using Comparator = int (*)(const Key&, const Key&);

    Key key;
    Value value;
    Comparator compare;

    DictionaryPair() : key(), value(), compare(default_compare<Key>) {}
    DictionaryPair(const Key& key, Comparator compare) : key(key), value(), compare(compare) {}
    DictionaryPair(const Key& key, const Value& value, Comparator compare) : key(key), value(value), compare(compare) {}

    bool operator<(const DictionaryPair& other) const { return compare(key, other.key) < 0; }
    bool operator>(const DictionaryPair& other) const { return compare(key, other.key) > 0; }
    bool operator==(const DictionaryPair& other) const { return compare(key, other.key) == 0; }
};

#endif // DICTIONARY_PAIR_HPP
