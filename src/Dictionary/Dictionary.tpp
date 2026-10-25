#include "../../include/Dictionary/Dictionary.hpp"

#include <stdexcept>

template <typename Key, typename Value>
Dictionary<Key, Value>::Dictionary(IDictionaryStorage<Key, Value>* storage)
    : storage(storage) {
    if (!storage) throw std::invalid_argument("Storage must not be null");
}

template <typename Key, typename Value>
Dictionary<Key, Value>::~Dictionary() {
    delete storage;
}

template <typename Key, typename Value>
Dictionary<Key, Value>::Dictionary(const Dictionary& other)
    : storage(other.storage ? other.storage->copy() : nullptr) {}

template <typename Key, typename Value>
Dictionary<Key, Value>& Dictionary<Key, Value>::operator=(const Dictionary& other) {
    if (this == &other) return *this;

    IDictionaryStorage<Key, Value>* new_storage = other.storage ? other.storage->copy() : nullptr;
    delete storage;
    storage = new_storage;

    return *this;
}

template <typename Key, typename Value>
Dictionary<Key, Value>::Dictionary(Dictionary&& other) noexcept
    : storage(other.storage) {
    other.storage = nullptr;
}

template <typename Key, typename Value>
Dictionary<Key, Value>& Dictionary<Key, Value>::operator=(Dictionary&& other) noexcept {
    if (this == &other) return *this;

    delete storage;
    storage = other.storage;
    other.storage = nullptr;

    return *this;
}

template <typename Key, typename Value>
void Dictionary<Key, Value>::add(const Key& key, const Value& value) {
    if (!storage) throw std::runtime_error("Dictionary has no storage");
    storage->add(key, value);
}

template <typename Key, typename Value>
void Dictionary<Key, Value>::remove(const Key& key) {
    if (storage) storage->remove(key);
}

template <typename Key, typename Value>
Value& Dictionary<Key, Value>::get(const Key& key) {
    if (!storage) throw std::runtime_error("Dictionary has no storage");
    return storage->get(key);
}

template <typename Key, typename Value>
const Value& Dictionary<Key, Value>::get(const Key& key) const {
    if (!storage) throw std::runtime_error("Dictionary has no storage");
    const IDictionaryStorage<Key, Value>* const_storage = storage;
    return const_storage->get(key);
}

template <typename Key, typename Value>
bool Dictionary<Key, Value>::contains_key(const Key& key) const {
    return storage && storage->contains_key(key);
}

template <typename Key, typename Value>
std::size_t Dictionary<Key, Value>::get_size() const {
    return storage ? storage->get_size() : 0;
}

template <typename Key, typename Value>
bool Dictionary<Key, Value>::is_empty() const {
    return !storage || storage->is_empty();
}

template <typename Key, typename Value>
void Dictionary<Key, Value>::clear() {
    if (storage) storage->clear();
}

template <typename Key, typename Value>
void Dictionary<Key, Value>::traverse(Visit visit) const {
    if (!visit) throw std::invalid_argument("Visitor must not be null");
    if (storage) storage->traverse(visit);
}
