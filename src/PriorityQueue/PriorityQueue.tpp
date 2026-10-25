#include "../../include/PriorityQueue/PriorityQueue.hpp"

#include <stdexcept>

template <typename T>
PriorityQueue<T>::PriorityQueue(IPriorityQueueStorage<T>* storage)
    : storage(storage) {
    if (!storage) throw std::invalid_argument("Storage must not be null");
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
    delete storage;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other)
    : storage(other.storage ? other.storage->copy() : nullptr) {}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& other) {
    if (this == &other) return *this;

    IPriorityQueueStorage<T>* new_storage = other.storage ? other.storage->copy() : nullptr;
    delete storage;
    storage = new_storage;

    return *this;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue&& other) noexcept
    : storage(other.storage) {
    other.storage = nullptr;
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(PriorityQueue&& other) noexcept {
    if (this == &other) return *this;

    delete storage;
    storage = other.storage;
    other.storage = nullptr;

    return *this;
}

template <typename T>
void PriorityQueue<T>::push(const T& value) {
    if (!storage) throw std::runtime_error("Queue has no storage");
    storage->add(value);
}

template <typename T>
const T& PriorityQueue<T>::top() const {
    if (empty()) throw std::runtime_error("Queue is empty");
    return storage->top();
}

template <typename T>
T PriorityQueue<T>::pop() {
    if (empty()) throw std::runtime_error("Queue is empty");
    return storage->extract_top();
}

template <typename T>
bool PriorityQueue<T>::contains(const T& value) const {
    return storage && storage->contains(value);
}

template <typename T>
bool PriorityQueue<T>::empty() const {
    return !storage || storage->is_empty();
}

template <typename T>
std::size_t PriorityQueue<T>::get_size() const {
    return storage ? storage->get_size() : 0;
}

template <typename T>
void PriorityQueue<T>::clear() {
    if (storage) storage->clear();
}

template <typename T>
PriorityQueue<T> PriorityQueue<T>::map(Transform transform) const {
    if (!storage) return *this;
    return PriorityQueue<T>(storage->map(transform));
}

template <typename T>
PriorityQueue<T> PriorityQueue<T>::where(Predicate predicate) const {
    if (!predicate) throw std::invalid_argument("Predicate must not be null");
    if (!storage) return *this;
    return PriorityQueue<T>(storage->where(predicate));
}

template <typename T>
template <typename Y>
Y PriorityQueue<T>::reduce(Reducer<Y> function, const Y& initial) const {
    if (!function) throw std::invalid_argument("Reducer must not be null");

    Y result = initial;
    PriorityQueue<T> source(*this);

    while (!source.empty()) {
        T value = source.pop();
        result = function(value, result);
    }

    return result;
}
