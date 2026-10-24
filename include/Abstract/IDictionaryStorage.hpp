#ifndef IDICTIONARY_STORAGE_HPP
#define IDICTIONARY_STORAGE_HPP

#include <cstddef>

template <typename Key, typename Value>
class IDictionaryStorage {
public:
    virtual ~IDictionaryStorage() = default;

    virtual IDictionaryStorage* copy() const = 0;
    virtual Value& get(const Key& key) = 0;
    virtual const Value& get(const Key& key) const = 0;
    virtual bool contains_key(const Key& key) const = 0;
    virtual void add(const Key& key, const Value& value) = 0;
    virtual void remove(const Key& key) = 0;
    virtual std::size_t get_size() const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
};

#endif // IDICTIONARY_STORAGE_HPP
