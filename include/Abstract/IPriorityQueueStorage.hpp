#ifndef IPRIORITY_QUEUE_STORAGE_HPP
#define IPRIORITY_QUEUE_STORAGE_HPP

#include <cstddef>

template <typename T>
class IPriorityQueueStorage {
public:
    using Transform = T (*)(const T&);
    using Predicate = bool (*)(const T&);

    virtual ~IPriorityQueueStorage() = default;

    virtual void add(const T& value) = 0;
    virtual const T& top() const = 0;
    virtual T extract_top() = 0;

    virtual bool contains(const T& value) const = 0;
    virtual bool is_empty() const = 0;
    virtual std::size_t get_size() const = 0;
    virtual void clear() = 0;

    virtual IPriorityQueueStorage* copy() const = 0;
    virtual IPriorityQueueStorage* map(Transform transform) const = 0;
    virtual IPriorityQueueStorage* where(Predicate predicate) const = 0;
};

#endif // IPRIORITY_QUEUE_STORAGE_HPP
